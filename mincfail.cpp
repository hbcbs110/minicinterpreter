#include "stdafx.h"
using namespace std;
string reslist[9];
void setreslist()
{
	reslist[0].assign("int");
	reslist[1].assign("real");
	reslist[2].assign("string");
	reslist[3].assign("while");
	reslist[4].assign("if");
	reslist[5].assign("else");
	reslist[6].assign("out");
	reslist[7].assign("in");
	reslist[8].assign("return");
}
int inreslist(string &_name)
{
	for (int i = 0;i < 9;i++)
	{
		if (_name == reslist[i])
		{
			cout << _name << "为保留字！" << endl;
			return 1;
		}
	}
	return 0;
}
void filefail(const char* _fname)
{
	cout << "打开文件" << _fname << "失败！" << endl;
}
void quotfail(int _line)
{
	cout << "缺少引号！" << _line << "行。" << endl;
}
void bracefail()
{
	cout << "缺少大括号！"<<endl;
}
void khfail()
{
	cout << "缺少括号！" << endl;
}
void nomain()
{
	cout << "缺少主函数 int main()！"<<endl;
}
void deffail(int _t,int _line)
{
	switch (_t)
	{
	case 0:
		cout << "标识符必须以字母开头！" << _line << "行。"<<endl;
		break;
	case 1:
		cout << "重复定义的标识符或函数！" << _line << "行。" << endl;
		break;
	case 2:
		cout << "包含特殊符号！" << _line << "行。" << endl;
		break;
	default:
		cout << "Doubt.." << endl;
	}
}
void reservedid()
{
	cout << "保留字不能作为标识符！" << endl;
}
void frepeat(string fname)
{
	cout << "重复定义的函数！" << fname << endl;
}
void emptyfun(string fname,int listn,int *typelist)
{
	cout << "未定义的函数！" << fname<<'(';
	for (int i = 0;i < listn;i++)
	{
		if (i) cout << ',';
		if (typelist[i] == 0) cout << "int";
		else if (typelist[i] == 1) cout << "real";
		else if (typelist[i] == 2) cout << "string";
	}
	cout << ')' << endl;
}
void stkerr()
{
	cout << "Stack error!" << endl;
}