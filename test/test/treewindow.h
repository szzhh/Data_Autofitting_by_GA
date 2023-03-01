#pragma once
#include <atlbase.h>
#include <atlwin.h>


struct NodeInfo
{
	void* left;
	void* right;
	COLORREF ColorBorder;
	COLORREF ColorFill;
	COLORREF ColorLabel;
	TCHAR  Label[256];
};

class TreeWindow : public CWindowImpl<TreeWindow, CWindow, CWinTraits<WS_OVERLAPPEDWINDOW> >
{
public:
	TreeWindow()
	{
		_thread.Attach(AtlCreateThread<TreeWindow>(&TreeWindow::_threadCallback, this));

		while (!(const_cast<volatile HWND&>(m_hWnd)))
		{
			Sleep(100);
		}

	}

	~TreeWindow()
	{
		PostMessage(WM_QUIT);
		::WaitForSingleObject(_thread, INFINITE);
		_thread.Close();
	}

	BEGIN_MSG_MAP(TreeWindow)
		MESSAGE_HANDLER(WM_PAINT, OnPaint)
	END_MSG_MAP()

	void DisplayBinaryTree(void *tree, void(*nodeInfoCallback)(void*, void*, int, NodeInfo*), void* context)
	{
		ATLASSERT(tree);
		ATLASSERT(nodeInfoCallback);

		if (tree && nodeInfoCallback)
		{
			_tree = tree;
			_nodeInfoCallback = nodeInfoCallback;
			_context = context;

			Refresh();
		}
		else
		{
			_tree = nullptr;
			_nodeInfoCallback = nullptr;
		}
	}

	void Refresh()
	{
		Invalidate();
		UpdateWindow();
	}

protected:
	LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		PAINTSTRUCT sp;
		auto dc = BeginPaint(&sp);

		SetTextAlign(dc, TA_CENTER | TA_BOTTOM);
		SelectObject(dc, GetStockObject(DEFAULT_GUI_FONT));

		RECT rect;
		GetClientRect(&rect);

		auto width = rect.right - rect.left;
		auto height = rect.bottom - rect.top;

		auto halfWidth = width / 2;
		auto halfHeight = height / 2;

		POINT nodePos = { halfWidth, _rowSpacing };
		POINT nextNodePos = nodePos;


		if (_tree && _nodeInfoCallback)
		{

			void* nodeStack[256] = { _tree };       //节点栈， 保存当前访问节点在二叉树中的路径
			POINT nodePosStack[256] = { nodePos };  //节点栈中每个节点的位置， 
			int n = 1;   //

			void* y = nullptr;   // 临时变量， 保存最后访问的节点，用来维护层级
			int h = 1;    // 当前节点在二叉根中的层级

			while (n > 0)
			{
				void* x = nodeStack[n - 1];    // 取出当前节点
				nodePos = nodePosStack[n - 1]; // 取出当前位置

				NodeInfo nodeInfo = {};
				nodeInfo.ColorFill = 0xffffff;
				_nodeInfoCallback(_context, x, h, &nodeInfo);

				if (nodeInfo.left || nodeInfo.right)
				{
					if (y && (nodeInfo.left == y || nodeInfo.right == y))
					{
						n--;       // 退栈
						h--;
					}
					else
					{
						if (nodeInfo.right)
						{
							nextNodePos.y = nodePos.y + _rowSpacing;
							nextNodePos.x = nodePos.x + (halfWidth - 50) / (1 << h);

							MoveToEx(dc, nodePos.x, nodePos.y, nullptr);
							LineTo(dc, nextNodePos.x, nextNodePos.y);

							nodeStack[n] = nodeInfo.right;
							nextNodePos.y += 10;

							nodePosStack[n] = nextNodePos;
							n++;
						}


						if (nodeInfo.left)
						{
							nextNodePos.y = nodePos.y + _rowSpacing;
							nextNodePos.x = nodePos.x - (halfWidth - 50) / (1 << h);

							MoveToEx(dc, nodePos.x, nodePos.y, nullptr);
							LineTo(dc, nextNodePos.x, nextNodePos.y);


							nodeStack[n] = nodeInfo.left;
							nextNodePos.y += 10;
							nodePosStack[n] = nextNodePos;
							n++;
						}

						DrawNode(dc, &nodePos, &nodeInfo);

						h++;
					}

				}
				else
				{
					DrawNode(dc, &nodePos, &nodeInfo);
					n--;
				}

				y = x;
			}
		}

		EndPaint(&sp);
		return 0;
	}

	virtual DWORD _ThreadCallback()
	{
		MSG msg;

		Create(nullptr);
		UpdateWindow();
		ShowWindow(SW_SHOW);

		while (GetMessage(&msg, 0, 0, 0))
		{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}

		DestroyWindow();
		return 0;
	}

	virtual void DrawNode(HDC dc, LPPOINT pos, NodeInfo* nodeInfo)
	{
		COLORREF textColor = SetTextColor(dc, nodeInfo->ColorLabel);
		HBRUSH brush = CreateSolidBrush(nodeInfo->ColorFill);
		HPEN borderPen = CreatePen(PS_SOLID, 1, nodeInfo->ColorBorder);
		ATLASSERT(brush);
		HGDIOBJ oldBrush = SelectObject(dc, brush);
		HGDIOBJ oldPen = SelectObject(dc, borderPen);
		int oldBkMode = SetBkMode(dc, TRANSPARENT);

		SIZE size;
		int labelLen = _tcslen(nodeInfo->Label);
		::GetTextExtentPoint32(dc, nodeInfo->Label, labelLen, &size);

		size.cx += 20;
		size.cy += 20;
		RECT rect = { 0,0, size.cx , size.cy };

		::OffsetRect(&rect, pos->x - size.cx / 2, pos->y - size.cy + 10);

		::Ellipse(dc, rect.left, rect.top, rect.right, rect.bottom);

		if (nodeInfo->Label[0])
			TextOut(dc, pos->x, pos->y, nodeInfo->Label, labelLen);

		SetBkMode(dc, oldBkMode);
		SelectObject(dc, oldPen);
		SelectObject(dc, oldBrush);
		SetTextColor(dc, textColor);

		DeleteObject(brush);
		DeleteObject(borderPen);

	}

private:
	static DWORD CALLBACK _threadCallback(TreeWindow* pthis)
	{
		return pthis->_ThreadCallback();
	}

private:
	CHandle _thread;
	void* _tree = nullptr;
	void* _context = nullptr;
	void(*_nodeInfoCallback)(void*, void*, int, NodeInfo*) = nullptr;
	int _rowSpacing = 48;
};
