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
			cout << _name << "Ϊ�����֣�" << endl;
			return 1;
		}
	}
	return 0;
}
void filefail(const char* _fname)
{
	cout << "���ļ�" << _fname << "ʧ�ܣ�" << endl;
}
void quotfail(int _line)
{
	cout << "ȱ�����ţ�" << _line << "�С�" << endl;
}
void bracefail()
{
	cout << "ȱ�ٴ����ţ�"<<endl;
}
void khfail()
{
	cout << "ȱ�����ţ�" << endl;
}
void nomain()
{
	cout << "ȱ�������� int main()��"<<endl;
}
void deffail(int _t,int _line)
{
	switch (_t)
	{
	case 0:
		cout << "��ʶ����������ĸ��ͷ��" << _line << "�С�"<<endl;
		break;
	case 1:
		cout << "�ظ�����ı�ʶ��������" << _line << "�С�" << endl;
		break;
	case 2:
		cout << "����������ţ�" << _line << "�С�" << endl;
		break;
	default:
		cout << "Doubt.." << endl;
	}
}
void reservedid()
{
	cout << "�����ֲ�����Ϊ��ʶ����" << endl;
}
void frepeat(string fname)
{
	cout << "�ظ�����ĺ�����" << fname << endl;
}
void emptyfun(string fname,int listn,int *typelist)
{
	cout << "δ����ĺ�����" << fname<<'(';
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