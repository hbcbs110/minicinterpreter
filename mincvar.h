#ifndef MINCVAR_H
#define MINCVAR_H
#include<string>
using namespace std;
struct VARIABLE
{
	int type,depth;
	short mint;
	float mreal;
	string mstring;
	string mname;
};
struct LIST
{
	VARIABLE *dt;
	LIST *next;
	LIST *pre;
};
void Linsert(VARIABLE *vp); 
void Linit();
VARIABLE* Lcheck(string &_mname, int _depth,bool _cal,int limm);
void Lclear();
void newvar(string &_mname,int _depth,short _mint);
void newvar(string &_mname,int _depth,float _mreal);
void newvar(string &_mname,int _depth,string _mstring);
void getval(string &_mname,int _depth,int limm,short &_mint);
void getval(string &_mname,int _depth,int limm,float &_mreal);
void getval(string &_mname,int _depth,int limm,string &_mstring);
VARIABLE& getvar(string &_mname, int _depth,int limm);
void setval(string &_mname,int _depth,int limm,short _mint);
void setval(string &_mname,int _depth,int limm,float _mreal);
void setval(string &_mname,int _depth,int limm,string _mstring);
int gettype(string &_mname, int _depth,int limm);
void deldep(int _depth);
void varallout();
VARIABLE zerov(VARIABLE va);
VARIABLE operator + (VARIABLE va, VARIABLE vb);
VARIABLE operator - (VARIABLE va, VARIABLE vb);
VARIABLE operator * (VARIABLE va, VARIABLE vb);
VARIABLE operator / (VARIABLE va, VARIABLE vb);
VARIABLE operator % (VARIABLE va, VARIABLE vb);
VARIABLE operator + (VARIABLE va);
VARIABLE operator - (VARIABLE va);
VARIABLE operator ! (VARIABLE va);
VARIABLE operator && (VARIABLE va, VARIABLE vb);
VARIABLE operator || (VARIABLE va, VARIABLE vb);
VARIABLE operator == (VARIABLE va, VARIABLE vb);
VARIABLE operator != (VARIABLE va, VARIABLE vb);
VARIABLE operator < (VARIABLE va, VARIABLE vb);
VARIABLE operator >= (VARIABLE va, VARIABLE vb);
VARIABLE operator <= (VARIABLE va, VARIABLE vb);
VARIABLE operator > (VARIABLE va, VARIABLE vb);
VARIABLE operator & (VARIABLE va, VARIABLE vb);
VARIABLE& strdel(string _mname, int _depth);
VARIABLE strdel(VARIABLE tmp);
VARIABLE operator ^ (VARIABLE va, VARIABLE vb);

#endif
