#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<string>
#include"mincvar.h"
#include"stdafx.h"
LIST Lhead={0},Ltail={0};
void Linit()
{
	Lhead.next=&Ltail;
	Ltail.pre=&Lhead;
}
void Linsert(VARIABLE *vp)
{
	if(vp==NULL) return;
	LIST *lp=new LIST;
	lp->dt=vp;
	lp->next=&Ltail;
	lp->pre=Ltail.pre;
	Ltail.pre->next=lp;
	Ltail.pre=lp;
}
VARIABLE* Lcheck(string &_mname,int _depth,bool _cal,int limm)
{
	LIST *lp=Ltail.pre;
	if (_mname.length()&&isdigit(_mname[0]))
	{
		cout << "非法变量名" << _mname << endl;
		return  NULL;
	}
	while(lp!=&Lhead)
	{
		if(lp->dt->mname==_mname)
		{
			if (_cal)
			{
				if(lp->dt->depth==_depth)
				{
					return lp->dt;
				}
			}
			else {
				if(lp->dt->depth<=_depth&&lp->dt->depth>=limm||lp->dt->depth==0)
				{
					return lp->dt;
				}
			}
		}
		lp=lp->pre;
	}
	return NULL;
}
void Lclear()
{
	LIST *p=Lhead.next;
	while(p!=&Ltail)
	{
		p->pre->next=p->next;
		p->next->pre=p->pre;
		delete p->dt;
		delete p;
		p=Lhead.next;
	}
}
void newvar(string &_mname,int _depth,short _mint)
{
	VARIABLE *p;
	if (_mname.length() && isdigit(_mname[0]))
	{
		cout << "非法变量名" << _mname << endl;
		return;
	}
	p=Lcheck(_mname,_depth,1,_depth);
	if(p!=NULL)
	{
		cout << "变量" << _mname << "已定义！" << endl;
		return;
	}
	p=new VARIABLE;
	p->mname=_mname;
	p->depth=_depth;
	p->mint=_mint;
	p->type=0;
	Linsert(p);
}
void newvar(string &_mname,int _depth,float _mreal)
{
	VARIABLE *p;
	if (_mname.length() && isdigit(_mname[0]))
	{
		cout << "非法变量名" << _mname << endl;
		return;
	}
	p=Lcheck(_mname,_depth,1,_depth);
	if(p!=NULL)
	{
		cout << "变量" << _mname << "已定义！" << endl;
		return;
	}
	p=new VARIABLE;
	p->mname=_mname;
	p->depth=_depth;
	p->mreal=_mreal;
	p->type=1;
	Linsert(p);
}
void newvar(string &_mname,int _depth,string _mstring)
{
	VARIABLE *p;
	if (_mname.length() && isdigit(_mname[0]))
	{
		cout << "非法变量名" << _mname << endl;
		return;
	}
	p = Lcheck(_mname, _depth, 1, _depth);
	if(p!=NULL)
	{
		cout << "变量" << _mname << "已定义！" << endl;
		return;
	}
	p=new VARIABLE;
	p->mname=_mname;
	p->depth=_depth;
	p->mstring=_mstring;
	p->type=2;
	Linsert(p);
}
void getval(string &_mname,int _depth,int limm,short &_mint)
{
	VARIABLE *p;
	if (_mname.length() && isdigit(_mname[0]))
	{
		cout << "非法变量名" << _mname << endl;
		return;
	}
	p=Lcheck(_mname, _depth,0,limm);
	if(p==NULL)
	{
		newvar(_mname, _depth, (short)0);
		_mint = 0;
		return;
	}
	if(p->type!=0)
	{
		_mint = 0;
		return;
	}
	_mint=p->mint;
}
void getval(string &_mname,int _depth,int limm,float &_mreal)
{
	VARIABLE *p;
	if (_mname.length() && isdigit(_mname[0]))
	{
		cout << "非法变量名" << _mname << endl;
		return;
	}
	p=Lcheck(_mname, _depth,0,limm);
	if(p==NULL)
	{
		newvar(_mname, _depth, (float)0.0);
		_mreal = 0;
		return;
	}
	if(p->type!=1)
	{
		_mreal = 0;
		return;
	}
	_mreal=p->mreal;
}
void getval(string &_mname,int _depth,int limm,string &_mstring)
{
	VARIABLE *p;
	if (_mname.length() && isdigit(_mname[0]))
	{
		cout << "非法变量名" << _mname << endl;
		return;
	}
	p=Lcheck(_mname, _depth,0,limm);
	if(p==NULL)
	{
		newvar(_mname, _depth, "");
		_mstring = "";
		return;
	}
	if(p->type!=2)
	{
		_mstring = "";
		return;
	}
	_mstring=p->mstring;
}
VARIABLE& getvar(string &_mname, int _depth,int limm)
{
	VARIABLE *p;
	p = Lcheck(_mname, _depth, 0, limm);
	if (p == NULL)
	{
		newvar(_mname, _depth, (short)0);
		p = Lcheck(_mname, _depth, 0, limm);
	}
	return *p;
}
void setval(string &_mname,int _depth,int limm,short _mint)
{
	VARIABLE *p;
	if (_mname.length() && isdigit(_mname[0]))
	{
		cout << "非法变量名" << _mname << endl;
		return;
	}
	p=Lcheck(_mname, _depth,0,limm);
	if(p==NULL)
	{
		return;
	}
	if(p->type!=0)
	{
		return;
	}
	p->mint=_mint;
}
void setval(string &_mname,int _depth,int limm,float _mreal)
{
	VARIABLE *p;
	if (_mname.length() && isdigit(_mname[0]))
	{
		cout << "非法变量名" << _mname << endl;
		return;
	}
	p=Lcheck(_mname, _depth,0,limm);
	if(p==NULL)
	{
		return;
	}
	if(p->type!=1)
	{
		return;
	}
	p->mreal=_mreal;
}
void setval(string &_mname,int _depth,int limm,string _mstring)
{
	VARIABLE *p;
	if (_mname.length() && isdigit(_mname[0]))
	{
		cout << "非法变量名" << _mname << endl;
		return;
	}
	p=Lcheck(_mname, _depth,0,limm);
	if(p==NULL)
	{
		return;
	}
	if(p->type!=2)
	{
		return;
	}
	p->mstring=_mstring;
}
int gettype(string &_mname, int _depth,int limm)
{
	VARIABLE *p;
	if (_mname.length() && isdigit(_mname[0]))
	{
		cout << "非法变量名" << _mname << endl;
		return -1;
	}
	p = Lcheck(_mname, _depth, 0,limm);
	return p->type;
}
void deldep(int _depth)
{
	LIST *lp=Ltail.pre,*lq;
	while(lp!=&Lhead)
	{
		if(lp->dt->depth>=_depth)
		{
			lp->pre->next=lp->next;
			lp->next->pre=lp->pre;
			lq=lp;
			lp=lp->pre;
			delete lq->dt;
			delete lq;
		}else break;
	}
}
void varallout()
{
	LIST *lp = Lhead.next;
	while (lp != &Ltail)
	{
		cout << "name=" << lp->dt->mname << " type=" << lp->dt->type;
		if (lp->dt->type == 0)
		{
			cout << " int=" << lp->dt->mint << endl;
		}
		else if (lp->dt->type == 1)
		{
			cout << " real=" << lp->dt->mreal << endl;
		}
		else if (lp->dt->type == 2)
		{
			cout << " string=\"" << lp->dt->mstring << "\"" << endl;
		}
		else cout << " invalid" << endl;
		lp = lp->next;
	}
}
VARIABLE zerov(VARIABLE va)
{
	VARIABLE ans;
	ans.type = 0;
	if (va.type == 0 && va.mint == 0) ans.mint = 1;
	else if (va.type == 1 && va.mreal == 0) ans.mint = 1;
	else if (va.type == 2 && va.mstring.empty()) ans.mint = 1;
	else ans.mint = 0;
	return ans;
}
VARIABLE operator + (VARIABLE va, VARIABLE vb)
{
	VARIABLE ans;
	if (va.type == vb.type)
	{
		ans.type = va.type;
		ans.mint = va.mint + vb.mint;
		ans.mreal = va.mreal + vb.mreal;
		ans.mstring = va.mstring + vb.mstring;
	}
	else
	{
		if (va.type == 0 && vb.type == 1)
		{
			ans.type = 1;
			ans.mreal = va.mint + vb.mreal;
		}
		else if (va.type == 1 && vb.type == 0)
		{
			ans.type = 1;
			ans.mreal = va.mreal + vb.mint;
		}
		else if (va.type == 2 || vb.type == 2)
		{
			cout << "Fail to plus " << va.mname << " " << vb.mname << endl;
			ans.type = -1;
		}
	}
	return ans;
}
VARIABLE operator - (VARIABLE va, VARIABLE vb)
{
	VARIABLE ans;
	if (va.type == 2 || vb.type == 2)
	{
		cout << "Fail to minus " << va.mname << " " << vb.mname << endl;
		ans.type = -1;
	}
	else if (va.type == vb.type)
	{
		ans.type = va.type;
		ans.mint = va.mint - vb.mint;
		ans.mreal = va.mreal - vb.mreal;
	}
	else
	{
		if (va.type == 0 && vb.type == 1)
		{
			ans.type = 1;
			ans.mreal = va.mint - vb.mreal;
		}
		else if (va.type == 1 && vb.type == 0)
		{
			ans.type = 1;
			ans.mreal = va.mreal - vb.mint;
		}
	}
	return ans;
}
VARIABLE operator * (VARIABLE va, VARIABLE vb)
{
	VARIABLE ans;
	if (va.type == 2 && vb.type == 2)
	{
		cout << "String Multiplication!" << endl;
		ans.type = -1;
	}
	else if (va.type == 2)
	{
		if (vb.type == 1)
		{
			cout << "String times real!" << endl;
			ans.type = -1;
		}
		else {
			ans.type = 2;
			for (int i = 0;i < vb.mint;i++) ans.mstring += va.mstring;
		}
	}
	else if (vb.type == 2)
	{
		if (va.type == 1)
		{
			cout << "String times real!" << endl;
			ans.type = -1;
		}
		else {
			ans.type = 2;
			for (int i = 0;i < va.mint;i++) ans.mstring += vb.mstring;
		}
	}
	else {
		if (va.type == 0)
		{
			if (vb.type == 0)
			{
				ans.type = 0;
				ans.mint = va.mint*vb.mint;
			}
			else {
				ans.type = 1;
				ans.mreal = va.mint*vb.mreal;
			}
		}
		else {
			if (vb.type == 0)
			{
				ans.type = 1;
				ans.mint = va.mreal*vb.mint;
			}
			else {
				ans.type = 1;
				ans.mreal = va.mreal*vb.mreal;
			}
		}
	}
	return ans;
}
VARIABLE operator / (VARIABLE va, VARIABLE vb)
{
	VARIABLE ans, tmp;
	if (va.type == 2 || vb.type == 2)
	{
		cout << "String division!" << endl;
		ans.type = -1;
	}
	else {
		if (va.type == 0)
		{
			if (vb.type == 0)
			{
				ans.type = 0;
				if (vb.mint == 0) ans.mint = 0;
				else ans.mint = va.mint/vb.mint;
			}
			else {
				ans.type = 1;
				if (vb.mreal == 0) ans.mreal = 0;
				else ans.mreal = va.mint/vb.mreal;
			}
		}
		else {
			if (vb.type == 0)
			{
				ans.type = 1;
				if (vb.mint == 0) ans.mreal = 0;
				else ans.mreal = va.mreal/vb.mint;
			}
			else {
				ans.type = 1;
				if (vb.mreal == 0) ans.mreal = 0;
				else ans.mreal = va.mreal/vb.mreal;
			}
		}
	}
	tmp = zerov(vb);
	if (tmp.mint == 1) cout << "Divided by zero!" << endl;
	return ans;
}
VARIABLE operator % (VARIABLE va, VARIABLE vb)
{
	VARIABLE ans;
	ans.type = 0;
	if (va.type == 0 && vb.type == 0)
	{
		if (vb.mint == 0)
		{
			cout << "Mod zero." << endl;
			ans.type = -1;
		}
		else ans.mint = va.mint%vb.mint;
	}
	else {
		cout << "Mod type failure." << endl;
		ans.type = -1;
	}
	return ans;
}
VARIABLE operator + (VARIABLE va)
{
	return va;
}
VARIABLE operator - (VARIABLE va)
{
	if (va.type == 0) va.mint = -va.mint;
	else if (va.type == 1) va.mreal = -va.mreal;
	else if (va.type == 2) reverse(va.mstring.begin(), va.mstring.end());
	return va;
}
VARIABLE operator ! (VARIABLE va)
{
	VARIABLE ans,aa=zerov(va);
	ans.type = 0;
	if (aa.mint) ans.mint = 1;
	else ans.mint = 0;
	return ans;
}
VARIABLE operator && (VARIABLE va, VARIABLE vb)
{
	VARIABLE ans,aa = zerov(va), bb = zerov(vb);
	ans.type = 0;
	if (aa.mint || bb.mint) ans.mint = 0;
	else ans.mint = 1;
	return ans;
}
VARIABLE operator || (VARIABLE va, VARIABLE vb)
{
	VARIABLE ans, aa = zerov(va), bb = zerov(vb);
	ans.type = 0;
	if (aa.mint&&bb.mint) ans.mint = 0;
	else ans.mint = 1;
	return ans;
}
VARIABLE operator == (VARIABLE va, VARIABLE vb)
{
	VARIABLE ans;
	ans.type = 0;
	if (va.type == vb.type)
	{
		if (va.type == 0)
		{
			if (va.mint == vb.mint) ans.mint = 1;
			else ans.mint = 0;
		}
		else if (va.type == 1)
		{
			if (va.mreal == vb.mreal) ans.mint = 1;
			else ans.mint = 0;
		}
		else if (va.type == 2)
		{
			if (va.mstring == vb.mstring) ans.mint = 1;
			else ans.mint = 0;
		}
		else ans.mint = 1;
	}
	else ans.mint = 0;
	return ans;
}
VARIABLE operator != (VARIABLE va, VARIABLE vb)
{
	VARIABLE ans = (va == vb);
	ans.mint = !ans.mint;
	return ans;
}
VARIABLE operator < (VARIABLE va, VARIABLE vb)
{
	VARIABLE ans;
	ans.type = 0;
	if (va.type == vb.type)
	{
		if (va.type == 0) ans.mint = (va.mint < vb.mint);
		else if (va.type == 1) ans.mint = (va.mreal < vb.mreal);
		else if (va.type == 2) ans.mint = (va.mstring < vb.mstring);
		else ans.mint = 0;
	}
	else {
		if (va.type == 2 || vb.type == 2)
		{
			cout << "Can't compare string with others." << endl;
			ans.mint = 0;
		}
		else {
			if (va.type == 0 && vb.type == 1) ans.mint = (va.mint < vb.mreal);
			else if (va.type == 1 && vb.type == 0) ans.mint = (va.mreal < vb.mint);
			else ans.mint = 0;
		}
	}
	return ans;
}
VARIABLE operator >= (VARIABLE va, VARIABLE vb)
{
	VARIABLE ans=!(va<vb);
	if (va.type != vb.type)
	{
		if (va.type == 2 || vb.type == 2) ans.mint = 0;
	}
	else if (va.type < 0 || va.type>2) ans.mint = 0;
	return ans;
}
VARIABLE operator <= (VARIABLE va, VARIABLE vb)
{
	VARIABLE ans = (va < vb) || (va == vb);
	if (va.type != vb.type)
	{
		if (va.type == 2 || vb.type == 2) ans.mint = 0;
	}
	else if (va.type < 0 || va.type>2) ans.mint = 0;
	return ans;
}
VARIABLE operator > (VARIABLE va, VARIABLE vb)
{
	VARIABLE ans = !(va <= vb);
	if (va.type != vb.type)
	{
		if (va.type == 2 || vb.type == 2) ans.mint = 0;
	}
	else if (va.type < 0 || va.type>2) ans.mint = 0;
	return ans;
}
VARIABLE operator & (VARIABLE va, VARIABLE vb)
{
	VARIABLE ans;
	ans.type = 2;
	if (va.type == 2 && vb.type == 2)
	{
		ans.mstring = va.mstring + vb.mstring;
	}
	else {
		cout << "$ What to append" << endl;
		ans.type = -1;
	}
	return ans;
}
VARIABLE& strdel(string _mname, int _depth)
{
	VARIABLE *p = Lcheck(_mname, _depth, 0, _depth);
	if (p == NULL)
	{
		return getvar(_mname, _depth, _depth);
	}
	else if (p->type != 2)
	{
		cout << "变量错误！" << endl;
		VARIABLE ans;
		ans.type = -1;
		return ans;
	}
	p->mstring.erase(p->mstring.end());
	if (p->mstring[p->mstring.length() - 1] == '\\') p->mstring.erase(p->mstring.end());
	return *p;
}
VARIABLE strdel(VARIABLE tmp)
{
	if (tmp.type != 2)
	{
		cout << "变量错误！" << endl;
		VARIABLE ans;
		ans.type = -1;
		return ans;
	}
	if (tmp.mstring.length()) tmp.mstring.erase(tmp.mstring.end()-1);
	if (tmp.mstring.length() && tmp.mstring[tmp.mstring.length() - 1] == '\\') tmp.mstring.erase(tmp.mstring.end()-1);
	return tmp;
}
VARIABLE operator ^ (VARIABLE va, VARIABLE vb)
{
	if (va.type == 2 || vb.type == 2)
	{
		cout << "变量错误！" << endl;
		return VARIABLE();
	}
	VARIABLE ans;
	if (vb.type == 0)
	{
		if (va.type == 0)
		{
			ans.type = 0;
			ans.mint = pow(va.mint, vb.mint);
		}
		else if (va.type == 1)
		{
			ans.type = 1;
			ans.mreal = pow(va.mreal, vb.mint);
		}
		else return VARIABLE();
	}
	else if (vb.type == 1)
	{
		ans.type = 1;
		if (va.type == 0) ans.mreal = pow(va.mint, vb.mreal);
		else if (va.type == 1) ans.mreal = pow(va.mreal, vb.mreal);
		else return VARIABLE();
	}
	else return VARIABLE();
	return ans;
}