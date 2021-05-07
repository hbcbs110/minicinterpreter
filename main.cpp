//#pragma comment(linker, "/STACK:67108864,67108864") 

#include "stdafx.h"

using namespace std;
int main(int argc, char** argv)
{
	Linit();
	string flname;
	if (argc > 1)
	{
		flname = string(argv[1]);
	}
	else {
		cout << "输入文件名：" << endl;
		getline(cin, flname);
	}
	clock_t ttt = clock();
	if (!openfile(flname.c_str()))
	{
		varfun();
		globalvar();
		cout << "Running..." << endl;
		minmain();
		Lclear();
		cout << endl;
	}
	cout << "用时" << clock() - ttt << "ms" << endl;
	system("pause");
	return 0;
}