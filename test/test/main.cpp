#include<iostream>
#include<math.h> 
#include<fstream>
#include<string>
#include<vector>
#include<algorithm>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<cstdlib>
#include<time.h>
#include<conio.h> 
#include<atlbase.h>
#include<atlwin.h>
#include "treewindow.h"
#include "engine.h"  
#include"DNA.h"
#include "test.h"
#include <QtWidgets/QApplication>

using namespace std;


vector<DNA> population;//DNA组（种族）
double zz1[181][181];

//清空vector 
template < class T >

void ClearVector(vector< T >& vt)
{
	vector< T > vtTemp;
	vtTemp.swap(vt);
}

void draw(double z1[][181], double size){
	Engine *ep;
	// open engine
	if (!(ep = engOpen("\0"))){
		fprintf(stderr, "\nCan't start MATLAB engine\n");
	}
	double xx[20] = { -0.8,-0.4,0.0,0.6,-0.8,-0.4,0.0,0.6,-0.8,-0.4,0.2,0.6,-0.8,-0.4,0.2,0.6,-0.8,-0.2,0.2,0.6 };
	double yy[20] = { -0.4,-0.4,0.8,-0.8,-0.2,-0.6,1.0,-0.6,0.0,-0.8,-0.8,-0.4,-0.2,-0.8,-0.6,-0.2,-0.4,-0.6,-0.4,0.0 };
	double zz[20] = { 0.477,0.825,0.600,0.000,0.566,0.693,0.000,0.529,0.600,0.477,0.566,0.693,0.566,0.566,0.775,0.775,0.447,0.775,0.894,0.800 };
	mxArray *X = NULL, *Y = NULL, *Z = NULL, *Z1 = NULL, *result = NULL;
	X = mxCreateDoubleMatrix(1, 20, mxREAL);
	Y = mxCreateDoubleMatrix(1, 20, mxREAL);
	Z = mxCreateDoubleMatrix(1, 20, mxREAL);
	Z1 = mxCreateDoubleMatrix(181, 181, mxREAL);
	memcpy((void *)mxGetPr(X), (void *)xx, sizeof(xx));
	memcpy((void *)mxGetPr(Y), (void *)yy, sizeof(yy));
	memcpy((void *)mxGetPr(Z), (void *)zz, sizeof(zz));
	memcpy((void *)mxGetPr(Z1), (void *)z1, size);
	engPutVariable(ep, "X", X);
	engPutVariable(ep, "Y", Y);
	engPutVariable(ep, "Z", Z);
	engPutVariable(ep, "Z1", Z1);// put data to engine
	// execute matlab operations
	//engEvalString(ep, "set(gcf, 'position', [300, 100, 500, 500]);");
	engEvalString(ep, "scatter3(X,Y,Z,'*');");
	engEvalString(ep, "hold on");
	engEvalString(ep, "X1=-0.8:0.01:1;");
	engEvalString(ep, "Y1=-0.8:0.01:1;");
	engEvalString(ep, "[X1,Y1]=meshgrid(X1,Y1);");
	engEvalString(ep, "mesh(X1,Y1,Z1);");
	engEvalString(ep, "hold off;");
	system("pause");
	//fgetc(stdin);
	mxDestroyArray(X);// clean operation
	mxDestroyArray(Y);
	mxDestroyArray(Z);
	mxDestroyArray(Z1);
	engEvalString(ep, "close;");
	engClose(ep);// 关闭引擎
}
int get_layer(string& str) {
	string str1 = str, str2 = str;
	int t, j, need = 0;
	for (t = int(str1.length()) - 1; t >= 0; t--) {
		if (str1[t] == '+' || str1[t] == '-' || str1[t] == '*' || str1[t] == '/') {
			break;
		}
	}
	if (t >= 0) {
		for (j = t; j >= 0; j--) {
			switch (str1[j]) {
			case '+':
				need++;
				break;
			case '-':
				need++;
				break;
			case '/':
				need++;
				break;
			case '*':
				need++;
				break;
			case '0':
				need--;
				break;
			case '1':
				need--;
				break;
			case '2':
				need--;
				break;
			default:
				break;
			}
			if (need == 0) { break; }
		}
		str1.erase(j);
		str2.erase(t);
		str2.erase(0, j);
		return int(str.length()) - t + max(get_layer(str1), get_layer(str2));
	}
	else {
		return str.length();
	}
}
void evolution()
{
	cout << "进化中···" << endl;
	double x1[181], y1[181];
	double tt = -0.8;
	for (int ii = 0; ii <= 180; ii++)
	{
		x1[ii] = tt;
		y1[ii] = tt;
		tt += 0.01;
	}

	for (int i = 0; i < prine_number; i++)
	{
		population.push_back(DNA());
	}
	vector <float> p_c_p;//适应性数组
	int add_c_p = 0;//适应性倒数和
	ClearVector(p_c_p);
	p_c_p.clear();
	for (int i = 0; i < population.size(); i++) {
		if (isnan(population[i].c_p) || isinf(population[i].c_p) || population[i].c_p > 1.0e+004) {
			population.erase(population.begin() + i);
			i--;
		}
	}
	for (int i = 0; i < population.size(); i++) {
		for (int j = 0; j < population.size() - i - 1; j++) {
			if (population[j].c_p > population[j + 1].c_p) {
				DNA tamporary = population[j];
				population[j] = population[j + 1];
				population[j + 1] = tamporary;
			}
		}
		p_c_p.insert(p_c_p.begin(), population[population.size() - 1 - i].c_p);
		add_c_p += 1 / p_c_p[0];
	}
	//每代的繁衍 
	for (int generation = 0; generation < max_generation; generation++) {
		int S = population.size();
		//繁衍过程 
		for (int i = 0; i < num_pre_generation; i++) {
			DNA t1, t2;
			float tp1 = 0, tp2 = 0;
			tp1 = rand() % 10000 / 10000.0; tp2 = rand() % 10000 / 10000.0;
			for (int i = 0; i < S; i++) {
				tp1 -= 1 / (add_c_p*p_c_p[i]);
				tp2 -= 1 / (add_c_p*p_c_p[i]);
				if (tp1 <= 0) {
					t1 = population[i];
					tp1 = 100;
				}
				if (tp2 <= 0) {
					t2 = population[i];
					tp2 = 100;
				}
				if (tp1 > 1 && tp2 > 1) {
					break;
				}
			}
			population.push_back(DNA(t1, t2));
		}

		ClearVector(p_c_p);
		for (int i = 0; i < population.size(); i++) {
			//if (isnan(population[i].c_p) || isinf(population[i].c_p) || population[i].c_p > max_c_p||get_layer(population[i].code) > max_layer) {
			if (isnan(population[i].c_p) || isinf(population[i].c_p) || population[i].c_p > max_c_p ) {
				population.erase(population.begin() + i);
				i--;
			}
		}
		for (int i = 0; i < population.size(); i++) {
			for (int j = 0; j < population.size() - i - 1; j++) {
				if (population[j].c_p > population[j + 1].c_p) {
					DNA tamporary = population[j];
					population[j] = population[j + 1];
					population[j + 1] = tamporary;
				}
			}
			p_c_p.insert(p_c_p.begin(), population[population.size() - 1 - i].c_p);
		}
		if ((generation + 1) % die_generation == 0) {
			population.erase(population.begin() + population.size() - int(population.size()*die_rate), population.begin() + population.size());
			p_c_p.erase(p_c_p.begin() + p_c_p.size() - int(p_c_p.size()*die_rate), p_c_p.begin() + p_c_p.size());
		}
		for (int i = 0; i < p_c_p.size(); i++) {
			add_c_p += 1 / p_c_p[i];
		}

	}
	//最后的输出函数 
	for (int i = 0; i < population.size(); i++) {
		cout<<"逆波兰式为：" << population[i].code << ' ' <<"适应度为："<< population[i].c_p << endl;
	}
	cout <<"最终种群数目的大小为："<< population.size() << endl;

	for (int ii = 0; ii <= 180; ii++)
	{
		for (int jj = 0; jj <= 180; jj++)
		{
			zz1[ii][jj] = population[0].output(x1[ii], y1[jj]);
		}
	}
}

void inorder(Node* node, string& st)//树的中序遍历
{

	if (node != NULL)
	{
		if (node->left != NULL) {
			if (node->left->data[0]<'0' || node->left->data[0]>'9'&&node->left->data[0] != 'x'&&node->left->data[0] != 'y') {
				st.insert(st.end(), '(');
				inorder(node->left, st);
				st.insert(st.end(), ')');
			}
			else {
				inorder(node->left, st);
			}
		}
		st += node->data;
		if (node->right != NULL) {
			if (node->right->data[0]<'0' || node->right->data[0]>'9'&&node->right->data[0] != 'x'&&node->right->data[0] != 'y') {
				st.insert(st.end(), '(');
				inorder(node->right, st);
				st.insert(st.end(), ')');
			}
			else {
				inorder(node->right, st);
			}
		}
	}
}

void NodeInfoCallback(void* context, void* node_, int hierarchy, NodeInfo* nodeInfo)
{
	auto x = (Node*)(node_);

	nodeInfo->left = x->left;           // 设置左节点
	nodeInfo->right = x->right;         // 设置右节点
	_stprintf_s(nodeInfo->Label, "%s", (x->data).c_str());    // 需要显示的文本
	nodeInfo->ColorFill = RGB(255, 255, 255);           // 填充色
	nodeInfo->ColorLabel = RGB(0, 0, 0);          // 文本颜色
	nodeInfo->ColorBorder = RGB(0, 0, 0);        // 边框颜色
}

void test::Display()
{
	TreeWindow wnd;
	wnd.DisplayBinaryTree(population[0].transform()->root, NodeInfoCallback, nullptr);
	system("pause");
}
void test::Draw()
{
	cout << "绘图中···" << endl;
	draw(zz1, sizeof(zz1));
}

void test::Evolution()
{
	bool ok;

	QString tempStr1;
	QString tempStr2;
	QString valueStr1 = ui->input_1->text();
	QString valueStr2 = ui->input_2->text();
	QString valueStr3 = ui->input_3->text();
	QString valueStr4 = ui->input_4->text();
	QString valueStr5 = ui->input_5->text();
	QString valueStr6 = ui->input_6->text();
	QString valueStr7 = ui->input_7->text();

	prine_number = valueStr1.toInt(&ok);
	max_generation = valueStr2.toInt(&ok);
	die_generation = valueStr3.toInt(&ok);
	max_c_p = valueStr4.toInt(&ok);
	max_layer = valueStr5.toInt(&ok);
	die_rate = valueStr6.toFloat(&ok);
	num_pre_generation = valueStr7.toInt(&ok);

	evolution();

	QString f = "z(x,y)=";
	string st; 
	inorder(population[0].transform()->root, st);
	cout << "最优函数为：" << endl;
	cout << "z(x,y)=" << st << endl;
	QString str = QString::fromStdString(st);
	ui->label_12->setText(f+str);
	ui->label_14->setText(tempStr2.setNum(population[0].c_p));
}


int main(int argc, char *argv[])
{
	//srand((unsigned)time(NULL));
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
	QApplication a(argc, argv);
	test w;
	w.show();
    return a.exec();
}
