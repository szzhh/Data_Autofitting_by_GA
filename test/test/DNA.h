#pragma once
#include<math.h> 
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<algorithm>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h> 
#include "engine.h"  

using namespace std;
//相关参数：
float Pov[4] = { 1,1,1,1 };//变异的概率,其值分别为：增加树的层数，减少树的层数，数字变异，符号变异，P0与P1互斥，其余的变异均不冲突 
int max_layer;//最大层数
int prine_number;//初始种族数目
int max_c_p;//最大环境适应度
int max_generation;//最大演化代数
int die_generation;//每隔多少代淘汰一次
float die_rate;//每次淘汰的比例
int num_pre_generation;//每代产生的新个体个数
float environment[20][3] = { {-0.8,-0.4,0.447},{-0.4,-0.4,0.825},{0,0.8,0.6},{0.6,-0.8,0},{-0.8,-0.2,0.566},{-0.4,-0.6,0.693},
                          {0,1,0},{0.6,-0.6,0.529},{-0.8,0,0.6},{-0.4,-0.8,0.477},{0.2,-0.8,0.566},{0.6,-0.4,0.693},{-0.8,-0.2,0.566},
                          {0.2,-0.6,0.775},{0.6,-0.2,0.775},{-0.8,-0.4,0.447},{-0.2,-0.6,0.775},{-0.2,-0.4,0.894},{0.6,0,0.8},{-0.4,-0.8,0.566} };//学习所需的数据（环境） 

typedef struct Node
{
	Node* left;
	Node* right;
	string data;
};
typedef struct { //树根
	Node* root = NULL;
}Tree;

//遗传算法，用DNA类表示染色体：
class DNA {
public:
	string code;//逆波兰式 
	int layer;//层数
	vector<float> d;//储存常数 
	float c_p;//环境适应度 

	Tree* transform() {
		Tree* tree = new Tree;
		char tamporary[40];
		int cst_num = d.size() - 1;
		Node* node = new Node[code.length()];
		for (int i = code.length() - 1; i >= 0; i--) {
			node[code.length() - 1 - i].left = NULL; node[code.length() - 1 - i].right = NULL;
			switch (code[i]) {
			case '0':
				node[code.length() - 1 - i].data = gcvt(d[cst_num], 5, tamporary);
				cst_num--;
				for (int j = code.length() - 2 - i; j >= 0; j--) {
					if (!node[j].right) {
						node[j].right = &node[code.length() - 1 - i];
						break;
					}
					else {
						if (!node[j].left) {
							node[j].left = &node[code.length() - 1 - i];
							break;
						}
					}
				}
				node[code.length() - 1 - i].left = &node[code.length() - 1 - i];
				node[code.length() - 1 - i].right = &node[code.length() - 1 - i];
				break;
			case '1':
				node[code.length() - 1 - i].data = "x";
				for (int j = code.length() - 2 - i; j >= 0; j--) {
					if (!node[j].right) {
						node[j].right = &node[code.length() - 1 - i];
						break;
					}
					else {
						if (!node[j].left) {
							node[j].left = &node[code.length() - 1 - i];
							break;
						}
					}
				}
				node[code.length() - 1 - i].left = &node[code.length() - 1 - i];
				node[code.length() - 1 - i].right = &node[code.length() - 1 - i];
				break;
			case '2':
				node[code.length() - 1 - i].data = "y";
				for (int j = code.length() - 2 - i; j >= 0; j--) {
					if (!node[j].right) {
						node[j].right = &node[code.length() - 1 - i];
						break;
					}
					else {
						if (!node[j].left) {
							node[j].left = &node[code.length() - 1 - i];
							break;
						}
					}
				}
				node[code.length() - 1 - i].left = &node[code.length() - 1 - i];
				node[code.length() - 1 - i].right = &node[code.length() - 1 - i];
				break;
			case '/':
				node[code.length() - 1 - i].data = "/";
				for (int j = code.length() - 2 - i; j >= 0; j--) {
					if (!node[j].right) {
						node[j].right = &node[code.length() - 1 - i];
						break;
					}
					else {
						if (!node[j].left) {
							node[j].left = &node[code.length() - 1 - i];
							break;
						}
					}
				}
				break;
			case '+':
				node[code.length() - 1 - i].data = "+";
				for (int j = code.length() - 2 - i; j >= 0; j--) {
					if (!node[j].right) {
						node[j].right = &node[code.length() - 1 - i];
						break;
					}
					else {
						if (!node[j].left) {
							node[j].left = &node[code.length() - 1 - i];
							break;
						}
					}
				}
				break;
			case '-':
				node[code.length() - 1 - i].data = "-";
				for (int j = code.length() - 2 - i; j >= 0; j--) {
					if (!node[j].right) {
						node[j].right = &node[code.length() - 1 - i];
						break;
					}
					else {
						if (!node[j].left) {
							node[j].left = &node[code.length() - 1 - i];
							break;
						}
					}
				}
				break;
			case '*':
				node[code.length() - 1 - i].data = "*";
				for (int j = code.length() - 2 - i; j >= 0; j--) {
					if (!node[j].right) {
						node[j].right = &node[code.length() - 1 - i];
						break;
					}
					else {
						if (!node[j].left) {
							node[j].left = &node[code.length() - 1 - i];
							break;
						}
					}
				}
				break;

			case 'f':
				node[code.length() - 1 - i].data = "fabs";
				for (int j = code.length() - 2 - i; j >= 0; j--) {
					if (!node[j].right) {
						node[j].right = &node[code.length() - 1 - i];
						break;
					}
					else {
						if (!node[j].left) {
							node[j].left = &node[code.length() - 1 - i];
							break;
						}
					}
				}
				node[code.length() - 1 - i].left = &node[code.length() - 1 - i];
				break;
			case 'e':
				node[code.length() - 1 - i].data = "exp";
				for (int j = code.length() - 2 - i; j >= 0; j--) {
					if (!node[j].right) {
						node[j].right = &node[code.length() - 1 - i];
						break;
					}
					else {
						if (!node[j].left) {
							node[j].left = &node[code.length() - 1 - i];
							break;
						}
					}
				}
				node[code.length() - 1 - i].left = &node[code.length() - 1 - i];
				break;
			case 'l':
				node[code.length() - 1 - i].data = "log";
				node[code.length() - 1 - i].data.insert(node[code.length() - 1 - i].data.end(), code[i]);
				for (int j = code.length() - 2 - i; j >= 0; j--) {
					if (!node[j].right) {
						node[j].right = &node[code.length() - 1 - i];
						break;
					}
					else {
						if (!node[j].left) {
							node[j].left = &node[code.length() - 1 - i];
							break;
						}
					}
				}
				node[code.length() - 1 - i].left = &node[code.length() - 1 - i];
				break;
			case 'a':
				node[code.length() - 1 - i].data = "atan";
				for (int j = code.length() - 2 - i; j >= 0; j--) {
					if (!node[j].right) {
						node[j].right = &node[code.length() - 1 - i];
						break;
					}
					else {
						if (!node[j].left) {
							node[j].left = &node[code.length() - 1 - i];
							break;
						}
					}
				}
				node[code.length() - 1 - i].left = &node[code.length() - 1 - i];
				break;
			case 's':
				node[code.length() - 1 - i].data = "sin";
				for (int j = code.length() - 2 - i; j >= 0; j--) {
					if (!node[j].right) {
						node[j].right = &node[code.length() - 1 - i];
						break;
					}
					else {
						if (!node[j].left) {
							node[j].left = &node[code.length() - 1 - i];
							break;
						}
					}
				}
				node[code.length() - 1 - i].left = &node[code.length() - 1 - i];
				break;
			case 'c':
				node[code.length() - 1 - i].data = "cos";
				for (int j = code.length() - 2 - i; j >= 0; j--) {
					if (!node[j].right) {
						node[j].right = &node[code.length() - 1 - i];
						break;
					}
					else {
						if (!node[j].left) {
							node[j].left = &node[code.length() - 1 - i];
							break;
						}
					}
				}
				node[code.length() - 1 - i].left = &node[code.length() - 1 - i];
				break;
				break;
			default:
				cout << "错误！未知的dna序列" << endl;
				system("pause");
				break;
			}
		}
		for (int i = code.length() - 1; i >= 0; i--) {
			if (code[i] == '0' || code[i] == '1' || code[i] == '2') {
				node[code.length() - 1 - i].left = NULL; node[code.length() - 1 - i].right = NULL;
			}
			else {
				if (code[i] != '+'&&code[i] != '-'&&code[i] != '*'&&code[i] != '/') {
					node[code.length() - 1 - i].left = NULL;
				}
			}
		}
		(*tree).root = &node[0];
		return tree;
	}

	//解码方式:
	float output(float A1, float A2) {
		//用数组储存暂时数据
		float tample[128];
		//逆波兰式解码 
		int i1 = 0;//需要的记录数 
		int i2 = 0;
		for (int i = 0; i < code.length(); i++) {
			switch (code[i]) {
			case '0':
				tample[i1++] = d[i2++];
				break;
			case '1':
				tample[i1++] = A1;
				break;
			case '2':
				tample[i1++] = A2;
				break;
			case '+':
				tample[i1 - 2] += tample[i1 - 1];
				i1--;
				break;
			case '-':
				tample[i1 - 2] -= tample[i1 - 1];
				i1--;
				break;
			case '/':
				tample[i1 - 2] /= tample[i1 - 1];
				i1--;
				break;
			case '*':
				tample[i1 - 2] *= tample[i1 - 1];
				i1--;
				break;
			case 'f':
				tample[i1 - 1] = fabs(tample[i1 - 1]);
				break;
			case 'e':
				tample[i1 - 1] = exp(tample[i1 - 1]);
				break;
			case 'l':
				tample[i1 - 1] = log(tample[i1 - 1]);
				break;
			case 'a':
				tample[i1 - 1] = atan(tample[i1 - 1]);
				break;
			case 's':
				tample[i1 - 1] = sin(tample[i1 - 1]);
				break;
			case 'c':
				tample[i1 - 1] = cos(tample[i1 - 1]);
				break;
			default:
				cout << "错误！未知的dna序列" << endl;
				system("pause");
				break;
			}
		}
		return tample[0];
	}
	//初代种族构造函数 
	DNA() {
		int const_need = 0;
		int num_tample;
		int t = 0;
		//随机DNA骨架生成
		for (int i = 0; i < 7; i++) {
			switch (rand() % 4) {
			case 0:
				code.push_back('+');
				break;
			case 1:
				code.push_back('-');
				break;
			case 2:
				code.push_back('/');
				break;
			case 3:
				code.push_back('*');
				break;
			default:
				cout << "错误！未知的dna序列" << endl;
				system("pause");
				break;
			}
		}
		//添加数字部分
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				for (int k = 0; k < 2; k++) {
					num_tample = rand() % 3;
					if (num_tample == 0) {
						const_need++;
					}
					code.insert(code.begin() + 7 * i + 3 * j, num_tample + 48);
				}
			}
		}
		//随机添加单目运算符 
		t = rand() % 6;
		for (int i = 0; i < t; i++) {
			int k = rand() % code.length() + 1;
			switch (4 + rand() % 6) {
			case 4:
				code.insert(code.begin() + k, 'f');
				break;
			case 5:
				code.insert(code.begin() + k, 'e');
				break;
			case 6:
				code.insert(code.begin() + k, 'l');
				break;
			case 7:
				code.insert(code.begin() + k, 'a');
				break;
			case 8:
				code.insert(code.begin() + k, 's');
				break;
			case 9:
				code.insert(code.begin() + k, 'c');
				break;
			default:
				cout << "错误！未知的dna序列" << endl;
				system("pause");
				break;
			}
		}
		//随机常数生成 
		for (int i = 0; i < const_need; i++) {
			this->d.push_back(float(rand() % 10000) / 1000.0);
		}

		//适应力计算 
		float a = 0;
		for (int i = 0; i < 20; i++) {
			a += powl(environment[i][2] - this->output(environment[i][0], environment[i][1]), 2);
		}
		this->c_p = a;
	}
	//遗传与变异函数
	DNA(const DNA p1, const DNA p2) {
		int need;
		int i, j;
		int const1 = 0, const2 = 0;
		const1 = p1.d.size();
		if (rand() % 1000 / 1000.0 < Pov[0] + Pov[1]) {//层数变异 
			if (rand() % 1000 / 1000.0 < Pov[0] / (Pov[1] + Pov[0])) {//增层变异 
				//混合DNA 
				this->code = p1.code + p2.code;
				//增加树干 
				switch (rand() % 4) {
				case 0:
					code.push_back('+');
					break;
				case 1:
					code.push_back('-');
					break;
				case 2:
					code.push_back('*');
					break;
				case 3:
					code.push_back('/');
					break;
				}
				//混合常数
				this->d = p1.d;
				this->d.insert(this->d.end(), p2.d.begin(), p2.d.end());
			}
			else {//减层变异
				//获取parent2的右半树（包含树干） 
				int t;
				for (t = p2.code.length(); t >= 0; t--) {
					if (p2.code[t] == '+' || p2.code[t] == '-' || p2.code[t] == '*' || p2.code[t] == '/') {
						break;
					}
				}

				need = 0;
				for (j = t; j >= 0; j--) {
					switch (p2.code[j]) {
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
						const2++;
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
				//获取DNA 
				this->code = p2.code;
				this->code.erase(0, j);
				this->code.erase(this->code.end() - 1);
				//获取常数
				this->d.assign(p2.d.end() - const2, p2.d.end());
			}
		}
		else {//正常遗传 
			need = 0;
			//获取parent1号的左半树（不包含树干） 
			int t;
			for (t = p1.code.length() - 1; t >= 0; t--) {
				if (p1.code[t] == '+' || p1.code[t] == '-' || p1.code[t] == '*' || p1.code[t] == '/') {
					break;
				}
			}
			for (i = t; i >= 0; i--) {
				switch (p1.code[i]) {
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
					const1--;
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
			//获取parent2的右半树（包含树干）
			need = 0;
			for (t = p2.code.length() - 1; t >= 0; t--) {
				if (p2.code[t] == '+' || p2.code[t] == '-' || p2.code[t] == '*' || p2.code[t] == '/') {
					break;
				}
			}
			for (j = t; j >= 0; j--) {
				switch (p2.code[j]) {
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
					const2++;
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
			//混合DNA 
			this->code = p2.code;
			this->code.erase(0, j);
			string tam;
			tam = p1.code;
			tam.erase(i);
			this->code = tam + this->code;
			//混合常数值
			int z;
			z = p1.d.size();
			for (int i = 0; i < const1; i++) {
				this->d.push_back(p1.d[i]);
			}
			z = p2.d.size();
			for (int i = 0; i < const2; i++) {
				this->d.push_back(p2.d[z - const2 + i]);
			}
		}
		//数字变异
		if (rand() % 1000 / 1000.0 < Pov[2]) {
			vector<vector <int> > tample;
			int num = 0;
			for (int i = 0; i < code.size(); i++) {
				if (code[i] == '0' || code[i] == '1' || code[i] == '2') {
					vector <int> t;
					t.push_back(i);
					if (code[i] == '0') {
						t.push_back(num);
						num++;
					}
					else {
						t.push_back(num);
					}
					tample.push_back(t);
				}
			}
			int a;
			a = rand() % tample.size();
			if (code[tample[a][0]] == '0') {
				d.erase(d.begin() + tample[a][1]);
				if (rand() % 2) {
					code[tample[a][0]] = '1';
				}
				else {
					code[tample[a][0]] = '2';
				}
			}
			else {
				if (code[tample[a][0]] == '1') {
					if (rand() % 1) {
						code[tample[a][0]] = '0';
						d.insert(d.begin() + tample[a][1], rand() % 1000 / 1000.0);
					}
					else {
						code[tample[a][0]] = '2';
					}
				}
				else {
					if (code[tample[a][0]] == '2') {
						if (rand() % 1) {
							code[tample[a][0]] = '0';
							d.insert(d.begin() + tample[a][1], rand() % 1000 / 1000.0);
						}
						else {
							code[tample[a][0]] = '1';
						}
					}
				}
			}
		}
		//符号变异
		if (rand() % 1000 / 1000.0 < Pov[3]) {
			vector<vector <int> > tample;
			for (int i = 0; i < code.length(); i++) {
				if (code[i] != '0'&&code[i] != '1'&&code[i] != '2') {
					vector <int> t;
					t.push_back(i);
					if (code[i] == '+' || code[i] == '-' || code[i] == '*' || code[i] == '/') {
						t.push_back(0);
					}
					else {
						t.push_back(1);
					}
					tample.push_back(t);
				}
			}

			int a = rand() % tample.size();
			if (tample[a][1]) {
				switch (rand() % 6) {
				case 0:
					code[tample[a][0]] = 'f';
					break;
				case 1:
					code[tample[a][0]] = 'e';
					break;
				case 2:
					code[tample[a][0]] = 'l';
					break;
				case 3:
					code[tample[a][0]] = 'a';
					break;
				case 4:
					code[tample[a][0]] = 's';
					break;
				case 5:
					code[tample[a][0]] = 'c';
					break;
				}
			}
			else {
				switch (rand() % 4) {
				case 0:
					code[tample[a][0]] = '+';
					break;
				case 1:
					code[tample[a][0]] = '-';
					break;
				case 2:
					code[tample[a][0]] = '*';
					break;
				case 3:
					code[tample[a][0]] = '/';
					break;
				}
			}
		}
		//适应力计算 
		float a = 0;
		for (int i = 0; i < 20; i++) {
			a += powl(environment[i][2] - this->output(environment[i][0], environment[i][1]), 2);
		}
		this->c_p = a;
	}
};