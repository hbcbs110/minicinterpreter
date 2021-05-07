#pragma once
#ifndef MINCFUNCTION_H
#define MINCFUNCTION_H
#include<string>
using namespace std;
class FUNCTIONS
{
public:
	string fname;
	string *flist;
	int *typelist;
	int listn;
	int ftype;
	string fbody;
	FUNCTIONS();
	FUNCTIONS(int z);
	FUNCTIONS(const FUNCTIONS& fff);
	~FUNCTIONS();
};
struct FLIST
{
	FUNCTIONS func;
	FLIST *next;
	FLIST();
};
int Fempty(FUNCTIONS &fff);
void Fcopy(FUNCTIONS &f1, FUNCTIONS fff);
void FLinsert(FUNCTIONS fff);
FUNCTIONS Ffind(string fname, int listn, int* typelist);
void FAllOut();
int setflist(FUNCTIONS& fff, string& scode, int pos);
void newfunction(string &scode, int pos,int len);
VARIABLE Frun(FUNCTIONS fff, string *tlist, int depth, int limm);
VARIABLE Frun(string &fname, int listn, int *typelist, string *tlist, int depth, int limm);
VARIABLE Runfun(string &fcode, int depth, int limm);
int minmain();

#endif