#include "stdafx.h"
FUNCTIONS::FUNCTIONS()
{
	flist = NULL, typelist = NULL;
	listn = 0, ftype = 0;
}
FUNCTIONS::FUNCTIONS(int z)
{
	flist = NULL, typelist = NULL;
	listn = 0, ftype = 0;
}
FUNCTIONS::FUNCTIONS(const FUNCTIONS& fff)
{
	fname = fff.fname;
	listn = fff.listn;
	fbody = fff.fbody;
	ftype = fff.ftype;
	if (listn)
	{
		flist = new string[listn];
		typelist = new int[listn];
	}
	else
	{
		flist = NULL;
		typelist = NULL;
	}
	for (int i = 0;i < listn;i++)
	{
		flist[i] = fff.flist[i];
		typelist[i] = fff.typelist[i];
	}
}
FUNCTIONS::~FUNCTIONS()
{
	delete[]flist;
	delete[]typelist;
}
FLIST::FLIST():next(NULL)
{
}
int Fempty(FUNCTIONS &fff)
{
	if (fff.fbody.empty() && fff.fname.empty()) return 1;
	return 0;
}
void Fcopy(FUNCTIONS &f1, FUNCTIONS fff)
{
	f1.fname = fff.fname;
	f1.listn = fff.listn;
	f1.fbody = fff.fbody;
	f1.ftype = fff.ftype;
	if (f1.flist) delete[]f1.flist;
	f1.flist = new string[f1.listn];
	if (f1.typelist) delete[]f1.typelist;
	f1.typelist = new int[f1.listn];
	for (int i = 0;i < f1.listn;i++)
	{
		f1.flist[i] = fff.flist[i];
		f1.typelist[i] = fff.typelist[i];
	}
}
FLIST FLhead;
void FLinsert(FUNCTIONS fff)
{
	FLIST *flp = new FLIST;
	flp->next = FLhead.next;
	FLhead.next = flp;
	Fcopy(flp->func, fff);
}
FUNCTIONS Ffind(string fname,int listn,int* typelist)
{
	FLIST *flp = FLhead.next;
	int i, flg;
	while (flp != NULL)
	{
		if (flp->func.fname == fname&&flp->func.listn == listn)
		{
			for (i = 0, flg = 0;i < listn;i++)
			{
				if (flp->func.typelist[i] != typelist[i])
				{
					flg = 1;
					break;
				}
			}
			if (!flg) return flp->func;
		}
		flp = flp->next;
	}
	if (flp == NULL) return FUNCTIONS();
}
void FAllOut()
{
	FLIST* p = FLhead.next;
	while (p != NULL)
	{
		cout << p->func.fname << " type=" << p->func.ftype << " listn=" << p->func.listn << endl;
		for (int i = 0;i < p->func.listn;i++)
		{
			cout << p->func.typelist[i] << p->func.flist[i] << ' ';
		}
		cout << endl;
		cout << p->func.fbody << endl;
		p = p->next;
	}
}
int setflist(FUNCTIONS& fff, string& scode, int pos)
{
	int i, j, n, flg, nlst;
	for (i = pos + 1, n = 0, flg = 0;scode[i] != ')';i++)
	{
		if (scode[i] != ' ') flg = 1;
		if (scode[i] == ',') n++;
	}
	if (flg) fff.listn = n + 1;
	else fff.listn = 0;
	if (fff.listn)
	{
		fff.flist = new string[fff.listn];
		fff.typelist = new int[fff.listn];
		string tvar;
		for (i = pos + 1, nlst = 0;scode[i] != ')';i++)
		{
			if (scode[i] == ')') break;
			if (scode.compare(i, 4, "int ")==0)
			{
				fff.typelist[nlst] = 0;
				for (j = 4;scode[i + j] != ','&&scode[i + j] != ')';j++)
				{
					tvar.append(1, scode[i + j]);
				}
				if (inreslist(tvar)) return 1;
				fff.flist[nlst] = tvar;
				nlst++;
				i = i + j;
				if (scode[i] == ')') i--;
				tvar.assign("");
				continue;
			}
			if (scode.compare(i, 5, "real ")==0)
			{
				fff.typelist[nlst] = 1;
				for (j = 5;scode[i + j] != ','&&scode[i + j] != ')';j++)
				{
					tvar.append(1, scode[i + j]);
				}
				if (inreslist(tvar)) return 1;
				fff.flist[nlst] = tvar;
				nlst++;
				i = i + j;
				if (scode[i] == ')') i--;
				tvar.assign("");
				continue;
			}
			if (scode.compare(i, 7, "string ")==0)
			{
				fff.typelist[nlst] = 2;
				for (j = 7;scode[i + j] != ','&&scode[i + j] != ')';j++)
				{
					tvar.append(1, scode[i + j]);
				}
				if (inreslist(tvar)) return 1;
				fff.flist[nlst] = tvar;
				nlst++;
				i = i + j;
				if (scode[i] == ')') i--;
				tvar.assign("");
				continue;
			}
		}
	}
	return 0;
}
void newfunction(string &scode, int pos,int len)
{
	FUNCTIONS ftmp,ftmp2;
	int i;
	if (scode.compare(pos, 4, "int ")==0)
	{
		ftmp.ftype = 0;
		pos += 4, len -= 4;
	}
	else if (scode.compare(pos, 5, "real ")==0)
	{
		ftmp.ftype = 1;
		pos += 5, len -= 5;
	}
	else if (scode.compare(pos, 7, "string ")==0)
	{
		ftmp.ftype = 2;
		pos += 7, len -= 7;
	}
	if (!isalpha(scode[pos])) return;
	for (i = pos;scode[i] != '(';i++);
	ftmp.fname.assign(scode, pos, i - pos);
	if (inreslist(ftmp.fname)) return;
	len-=i-pos, pos = i;
	if (setflist(ftmp, scode, pos)) return;
	while (scode[pos] != ')') pos++, len--;
	pos++, len--;
	for (i = 0;i < len;i++)
	{
		ftmp.fbody.append(1, scode[pos + i]);
	}
	Fcopy(ftmp2, Ffind(ftmp.fname, ftmp.listn, ftmp.typelist));
	if (!Fempty(ftmp2))
	{
		frepeat(ftmp.fname);
		return;
	}
	FLinsert(ftmp);
}
VARIABLE Frun(FUNCTIONS fff,string *tlist,int depth, int limm)
{
	VARIABLE tmp;
	int i, j, l, bracen=0;
	for (i = 0;i < fff.listn;i++)
	{
		string stmp;
		stmp = infsuf(tlist[i]);
		tmp = expcal(stmp,depth-1,limm);
		if (tmp.type == fff.typelist[i])
		{
			if (tmp.type == 0) newvar(fff.flist[i], depth, tmp.mint);
			else if (tmp.type == 1) newvar(fff.flist[i], depth, tmp.mreal);
			else if (tmp.type == 2) newvar(fff.flist[i], depth, tmp.mstring);
		}
		else {
			cout << "²ÎÊý´íÎó¡£" << endl;
			tmp = VARIABLE();
			tmp.type = fff.ftype;
			return tmp;
		}
	}
	enrun();
	analize(fff.fbody, depth, depth);
	deldep(depth);
	if (returning()) tmp = returningvar();
	delete[]tlist;
	tlist = NULL;
	disrun();
	if (tmp.type != fff.ftype)
	{
		stringstream sstr;
		if (tmp.type == 0)
		{
			if (fff.ftype == 1) tmp.mreal = tmp.mint;
			else if (fff.ftype == 2)
			{
				sstr << tmp.mint;
				sstr >> tmp.mstring;
			}
		}
		else if (tmp.type == 1)
		{
			if (fff.ftype == 0) tmp.mint = tmp.mreal;
			else if (fff.ftype == 2)
			{
				sstr << tmp.mreal;
				sstr >> tmp.mstring;
			}
		}
		else if (tmp.type == 2)
		{
			sstr << tmp.mstring;
			if (fff.ftype == 0) sstr >> tmp.mint;
			else if (fff.ftype == 1) sstr >> tmp.mreal;
		}
		else {
			if (fff.ftype == 0) tmp.mint = 0;
			else if (fff.ftype == 1) tmp.mreal = 0;
			else tmp.mstring = "";
		}
		tmp.type = fff.ftype;
	}
	return tmp;
}
VARIABLE Frun(string &fname, int listn, int *typelist, string *tlist,int depth, int limm)
{
	FUNCTIONS ftmp;
	Fcopy(ftmp, Ffind(fname, listn, typelist));
	if (Fempty(ftmp))
	{
		emptyfun(fname, listn, typelist);
		VARIABLE x = { 0 };
		delete[]typelist;
		return x;
	}
	delete[]typelist;
	return Frun(ftmp, tlist, depth, limm);
}
VARIABLE Runfun(string &fcode,int depth, int limm)
{
	string fname,exps,esuf;
	int listn = 0, listm = 0, i, j, l = fcode.length(), khn = 0, yh = 0;
	string *tlist;
	int *typelist;
	FUNCTIONS fff;
	for (i = 0;i < l;i++)
	{
		if (fcode[i] != '(') fname.append(1, fcode[i]);
		else break;
	}
	for (khn = 1,j=i+1;j < l;j++)
	{
		if (fcode[j] != ' '&&fcode[j] != '('&&fcode[j]!=')')
		{
			if (listn == 0) listn = 1;
		}
		if (fcode[j] == '"') yh = !yh;
		if (yh) continue;
		if (fcode[j] == '(')
		{
			if (!yh) khn++;
			continue;
		}
		if (fcode[j] == ')')
		{
			if (!yh) khn--;
			if (khn == 0) break;
		}
		if (fcode[j] == ',')
		{
			if (!yh)
			{
				if (khn == 1) listn++;
			}
		}
	}
	if (listn == 0) return Frun(fname, 0, NULL, NULL, depth, limm);
	else {
		typelist = new int[listn];
		tlist = new string[listn];
		for (khn = 1, j = i + 1;j <= l;j++)
		{
			if (fcode[j] == '"')
			{
				yh = !yh;
				tlist[listm].append(1, fcode[j]);
				continue;
			}
			if (yh)
			{
				tlist[listm].append(1, fcode[j]);
				continue;
			}
			if (fcode[j] == ' ')
			{
				if (khn == 1) continue;
				else tlist[listm].append(1, fcode[j]);
				continue;
			}
			if (fcode[j] == '(')
			{
				if (!yh) khn++;
				tlist[listm].append(1, fcode[j]);
				continue;
			}
			if (fcode[j] == ')')
			{
				if (!yh) khn--;
				if (khn == 0) break;
				tlist[listm].append(1, fcode[j]);
				continue;
			}
			if (fcode[j] == ',')
			{
				if (!yh)
				{
					if (khn == 1)
					{
						listm++;
						continue;
					}
					else {
						tlist[listm].append(1, fcode[j]);
						continue;
					}
				}
				else {
					tlist[listm].append(1, fcode[j]);
					continue;
				}
			}
			tlist[listm].append(1, fcode[j]);
		}
		for (j = 0;j < listn;j++)
		{
			exps = tlist[j];
			esuf = infsuf(exps);
			VARIABLE vtmp = expcal(esuf, depth-1, limm);
			typelist[j] = vtmp.type;
		}

		return Frun(fname, listn, typelist, tlist, depth, limm);
	}
}
int minmain()
{
	FUNCTIONS ftmp;
	Fcopy(ftmp, Ffind("main", 0, NULL));
	if (Fempty(ftmp))
	{
		nomain();
		return -1;
	}
	Frun(ftmp, NULL, 1, 0);
	return 0;
}