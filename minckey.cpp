#include "stdafx.h"
using namespace std;
string reslists[11] = { "int ","real ","string ","while ","if ","else","out ","in ","return ","do","until " };
stack <VARIABLE> retv;
stack <int> nowreturning;
int returning()
{
	if (nowreturning.empty()) return 0;
	return nowreturning.top();
}
VARIABLE returningvar()
{
	if (retv.empty()) return VARIABLE();
	return retv.top();
}
void disrun()
{
	if (nowreturning.size()) nowreturning.pop();
	if (retv.size()) retv.pop();
}
void enrun()
{
	nowreturning.push(0);
	retv.push(VARIABLE());
}
int iskey(string &scode, int pos)
{
	for (int i = 0;i < 11;i++)
	{
		if (scode.compare(pos, reslists[i].length(), reslists[i]) == 0) return i;
	}
	return -1;
}
void mcifelse(string &ecode,int elsepos,int _depth,int limm)
{
	int i,j, bracem, l = ecode.length(), bracen = 0, yht = 0;
	string exps, esuf;
	VARIABLE vtmp;
	if (ecode[0] == 'i'&&ecode[1] == 'f')
	{
		for (i = 3;i < l;i++) if (ecode[i] == '{') break;
		exps = ecode.substr(3, i - 3);
		esuf = infsuf(exps);
		vtmp = expcal(esuf, _depth, limm);
		vtmp = !zerov(vtmp);
		if (vtmp.mint)
		{
			exps = ecode.substr(i, elsepos - 1 - i + 1);
			analize(exps, _depth + 1, limm);
			deldep(_depth + 1);
		}
		else {
			i = elsepos;
			if (i < 0) return;
			for (;i < l&&ecode[i] != '{';i++);
			for (j = 0, yht = 0, bracem = 0;i + j < l - 1;j++)
			{
				if (ecode[i + j] == '"') yht = !yht;
				if (yht) continue;
				if (ecode[i + j] == '{') bracem++;
				if (ecode[i + j] == '}')
				{
					bracem--;
					if (!bracem) break;
				}
			}
			exps = ecode.substr(i, j + 1);
			analize(exps, _depth + 1, limm);
			deldep(_depth + 1);
		}
	}
	else return;
}
char zhuanyi(char cc)
{
	switch (cc)
	{
	case 'a': return '\a';
	case 'b': return '\b';
	case 'f': return '\f';
	case 'n': return '\n';
	case 'r': return '\r';
	case 't': return '\t';
	case 'v': return '\v';
	case '\\': return '\\';
	case '\'': return '\'';
	case '"': return '"';
	case '?': return '\?';
	case '0': return '\0';
	default: return cc;
	}
}
void mcin(string &ecode, int _depth,int limm)
{
	int i, l = ecode.length(),flg=0,yh=0;
	string tshs,blmm;
	for (i = 0;i < l;i++)
	{
		if (ecode[i] == '"') flg = 1;
	}
	if (flg == 1)
	{
		for (i = 0;ecode[i] != '"';i++);
		for (yh = 1, i = i + 1;yh;i++)
		{
			if (ecode[i] == '\\')
			{
				switch (ecode[i + 1])
				{
				case 'a': tshs.append(1, '\a');break;
				case 'b': tshs.append(1, '\b');break;
				case 'f': tshs.append(1, '\f');break;
				case 'n': tshs.append(1, '\n');break;
				case 'r': tshs.append(1, '\r');break;
				case 't': tshs.append(1, '\t');break;
				case 'v': tshs.append(1, '\v');break;
				case '\\': tshs.append(1, '\\');break;
				case '\'': tshs.append(1, '\'');break;
				case '"': tshs.append(1, '"');break;
				case '?': tshs.append(1, '\?');break;
				case '0': tshs.append(1, '\0');break;
				default:break;
				}
				i = i + 1;
				continue;
			}
			if (ecode[i] == '"') yh = !yh;
			if (!yh)
			{
				++i;
				break;
			}
			tshs.append(1, ecode[i]);
		}
		cout << tshs;
		while (ecode[i] == ',' || ecode[i] == ' ') i++;
		if (!isalpha(ecode[i]))
		{
			cout << "非法变量名！" << endl;
			return;
		}
		for (;i < l&&ecode[i] != ';';i++)
		{
			if (ecode[i] == ' ') break;
			if (!isalpha(ecode[i]) && !isdigit(ecode[i]))
			{
				cout << "非法变量名！" << endl;
				return;
			}
			blmm.append(1, ecode[i]);
		}
		VARIABLE *p = &getvar(blmm, _depth,limm);
		getline(cin, tshs);
		for (i = 0, flg = 0;i < tshs.length();i++)
		{
			if (i == 0 && tshs[i] == '-') continue;
			if (!isdigit(tshs[i]) && tshs[i] != '.')
			{
				flg = 2;
				break;
			}
			if (tshs[i] == '.') flg = 1;
		}
		if (p->type == 2)
		{
			setval(p->mname, _depth, limm, tshs);
			p->mstring = tshs;
		}
		else if (p->type == 1)
		{
			stringstream sss(tshs);
			if (flg == 2)
			{
				cout << "读入错误！" << endl;
				return;
			}
			float x;
			sss >> x;
			if (tshs.length()==0) x = 0;
			setval(p->mname, _depth, limm, x);
			p->mreal = x;
		}
		else {
			if (flg == 2)
			{
				cout << "读入错误！" << endl;
				return;
			}
			stringstream sss(tshs);
			short x;
			sss >> x;
			if (tshs.length()==0) x = 0;
			setval(p->mname, _depth, limm, x);
			p->mint = x;
		}
	}
	else {
		for (i = 3;ecode[i] == ' ';i++);
		if (ecode[i] == ';')
		{
			cout << "缺少变量名！" << endl;
			return;
		}
		if (!isalpha(ecode[i]))
		{
			cout << "非法变量名！" << endl;
			return;
		}
		for (;i < l&&ecode[i] != ';'&&ecode[i]!=' ';i++)
		{
			if (!isdigit(ecode[i]) && !isalpha(ecode[i]))
			{
				cout<<"非法变量名！" << endl;
				return;
			}
			blmm.append(1, ecode[i]);
		}
		VARIABLE *p = &getvar(blmm, _depth,limm);
		getline(cin, tshs);
		for (i = 0, flg = 0;i < tshs.length();i++)
		{
			if (i == 0 && tshs[i] == '-') continue;
			if (!isdigit(tshs[i]) && tshs[i] != '.')
			{
				flg = 2;
				break;
			}
			if (tshs[i] == '.') flg = 1;
		}
		if (p->type == 2)
		{
			setval(p->mname, _depth, limm, tshs);
			p->mstring = tshs;
		}
		else if (p->type == 1)
		{
			stringstream sss(tshs);
			if (flg == 2)
			{
				cout << "读入错误！" << endl;
				return;
			}
			float x;
			sss >> x;
			if (tshs.length() == 0) x = 0;
			setval(p->mname, _depth, limm, x);
			p->mreal = x;
		}
		else {
			if (flg == 2)
			{
				cout << "读入错误！" << endl;
				return;
			}
			stringstream sss(tshs);
			short x;
			sss >> x;
			if (tshs.length() == 0) x = 0;
			setval(p->mname, _depth, limm, x);
			p->mint = x;
		}
	}
}
void mcout(string &ecode, int _depth,int limm)
{
	int ist, i, dss = 0, l = ecode.length(), yh = 0, kh = 0;
	for (ist = 0;ist < l&&ecode[ist] != ' ';ist++);
	for (i = 1;ist + i < l;i++)
	{
		if (ecode[ist+i] == '\\')
		{
			if (yh)
			{
				i++;
				continue;
			}
			else {
				cout << "out \\??" << endl;
				return;
			}
		}
		if (ecode[ist + i] == '"') yh = !yh;
		if (yh) continue;
		if (ecode[ist + i] == '(') kh++;
		if (ecode[ist + i] == ')') kh--;
		if (kh == 0)
		{
			if (ecode[ist + i] == ',')
			{
				dss++;
				continue;
			}
			else if (ecode[ist + i] == ';')
			{
				dss++;
				break;
			}
		}
	}
	if (yh)
	{
		cout << "out缺少引号！" << endl;
		return;
	}
	if (kh)
	{
		cout << "out缺少括号！" << endl;
		return;
	}
	if (ecode[ist + 1] == '"')
	{
		if (dss == 1)
		{
			string str;
			for (i = 2, yh = 1;ist+i < l&&yh;i++)
			{
				if (ecode[ist + i] == '"')
				{
					yh = !yh;
					continue;
				}
				if (ecode[ist + i] == '\\')
				{
					str.append(1,zhuanyi(ecode[ist + i + 1]));
					i++;
					continue;
				}
				str.append(1, ecode[ist + i]);
			}
			cout << str;
		}
		else if (dss == 2)
		{
			string str;
			for (i = 2, yh = 1;ist+i < l&&yh;i++)
			{
				if (ecode[ist + i] == '"')
				{
					yh = !yh;
					continue;
				}
				if (ecode[ist + i] == '\\')
				{
					str.append(1,zhuanyi(ecode[ist + i + 1]));
					i++;
					continue;
				}
				str.append(1, ecode[ist + i]);
			}
			cout << str;
			str = "";
			for (;ist + i < l;i++)
			{
				if (ecode[ist + i] != ','&&ecode[ist + i] != ' ') break;
			}
			if (ecode[ist + i] == '"')
			{
				for (i = i + 1, yh = 1;ist + i < l&&yh;i++)
				{
					if (ecode[ist + i] == '"')
					{
						yh = !yh;
						continue;
					}
					if (ecode[ist + i] == '\\')
					{
						str.append(1,zhuanyi(ecode[ist + i + 1]));
						i++;
						continue;
					}
					str.append(1, ecode[ist + i]);
				}
				cout << str;
			}
			else {
				if (isdigit(ecode[ist + i]) || ecode[ist + i] == '-'&&isdigit(ecode[ist + i + 1]))
				{
					int fflg = 0;
					for (;ist + i < l&&ecode[ist + i] != ';';i++)
					{
						str.append(1,ecode[ist + i]);
						if (ecode[ist + i] == '.') fflg = 1;
					}
					if (fflg) cout << atof(str.c_str());
					else cout << atoi(str.c_str());
				}
				else {
					for (;ist + i < l&&ecode[ist + i] != ';';i++)
					{
						str.append(1, ecode[ist + i]);
					}
					VARIABLE tmp = getvar(str, _depth, limm);
					if (tmp.type == 0) cout << tmp.mint;
					else if (tmp.type == 1) cout << tmp.mreal;
					else if (tmp.type == 2) cout << tmp.mstring;
					else cout << 0;
				}
			}
		}
		else
		{
			cout << "输出格式错误！" << endl;
		}
	}
	else {
		if (dss == 1)
		{
			if (isdigit(ecode[ist + 1]) || ecode[ist + 1] == '-'&&isdigit(ecode[ist + 2]))
			{
				string str;
				int fflg = 0;
				for (i = 1;ist + i < l&&ecode[ist + i] != ';';i++)
				{
					str.append(1, ecode[ist + i]);
					if (ecode[ist + i] == '.') fflg = 1;
				}
				if(!fflg) cout << atoi(str.c_str());
				else cout << atof(str.c_str());
			}
			else {
				string str;
				for (i=1;ist + i < l&&ecode[ist + i] != ';';i++)
				{
					str.append(1, ecode[ist + i]);
				}
				VARIABLE tmp = getvar(str, _depth, limm);
				if (tmp.type == 0) cout << tmp.mint;
				else if (tmp.type == 1) cout << tmp.mreal;
				else if (tmp.type == 2) cout << tmp.mstring;
				else cout << 0;
			}
		}
		else if (dss == 2)
		{
			string str;
			if (isdigit(ecode[ist + 1]) || ecode[ist + 1] == '-'&&isdigit(ecode[ist + 2]))
			{
				int fflg = 0, otn, j;
				for (i = 1;ist + i < l&&ecode[ist + i] != ',';i++)
				{
					str.append(1, ecode[ist + i]);
				}
				otn = atoi(str.c_str());
				for (;ecode[ist + i] == ' ' || ecode[ist + i] == ',';i++);
				if (isdigit(ecode[ist + i]) || ecode[ist + i] == '-'&&isdigit(ecode[ist + i + 1]))
				{
					str = "";
					for (;ist + i < l&&ecode[ist + i] != ';';i++)
					{
						str.append(1, ecode[ist + i]);
						if (ecode[ist + i] == '.') fflg = 1;
					}
					if (fflg) for (j = 0;j < otn;j++) cout << atof(str.c_str());
					else for (j = 0;j < otn;j++) cout << atoi(str.c_str());
				}
				else if (isalpha(ecode[ist + i]))
				{
					str = "";
					for (;ist + i < l&&ecode[ist + i] != ';';i++)
					{
						str.append(1, ecode[ist + i]);
					}
					VARIABLE tmp = getvar(str, _depth, limm);
					if (tmp.type == 0) for(j=0;j<otn;j++) cout << tmp.mint;
					else if (tmp.type == 1) for(j=0;j<otn;j++) cout << tmp.mreal;
					else if (tmp.type == 2) for(j=0;j<otn;j++) cout << tmp.mstring;
					else for(j=0;j<otn;j++) cout << 0;
				}
				else if (ecode[ist + i] == '"')
				{
					str = "";
					int yht = 1;
					for (i = i + 1;ist + i < l;i++)
					{
						if (ecode[ist + i] == '"') yht = !yht;
						if (!yht) break;
						if (ecode[ist + i] == '\\')
						{
							str.append(1,zhuanyi(ecode[ist + i + 1]));
							i++;
							continue;
						}
						str.append(1, ecode[ist + i]);
					}
					//while (str[str.length() - 1] != '"') str.erase(str.end());
					//str.erase(str.end());
					for (j = 0;j < otn;j++) cout << str;
				}
			}
			else {
				int fflg = 0, otn, j;
				for (i=1;ist + i < l&&ecode[ist + i] != ',';i++)
				{
					str.append(1, ecode[ist + i]);
				}
				VARIABLE tmp = getvar(str, _depth, limm);
				if (tmp.type == 0) otn = tmp.mint;
				else if (tmp.type == 1) otn = (int)tmp.mreal;
				else if (tmp.type == 2) otn = atoi(tmp.mstring.c_str());
				else otn = 0;
				for (;ist + i < l && (ecode[ist + i] == ' ' || ecode[ist + i] == ',');i++);
				if (isdigit(ecode[ist + i]) || ecode[ist + i] == '-'&&isdigit(ecode[ist + i + 1]))
				{
					str = "";
					for (;ist + i < l&&ecode[ist + i] != ';';i++)
					{
						str.append(1, ecode[ist + i]);
						if (ecode[ist + i] == '.') fflg = 1;
					}
					if (fflg) for (j = 0;j < otn;j++) cout << atof(str.c_str());
					else for (j = 0;j < otn;j++) cout << atoi(str.c_str());
				}
				else if(isalpha(ecode[ist+i]))
				{
					str = "";
					for (;ist + i < l&&ecode[ist + i] != ';';i++)
					{
						str.append(1, ecode[ist + i]);
					}
					VARIABLE tmp = getvar(str, _depth, limm);
					if (tmp.type == 0) for (j = 0;j<otn;j++) cout << tmp.mint;
					else if (tmp.type == 1) for (j = 0;j<otn;j++) cout << tmp.mreal;
					else if (tmp.type == 2) for (j = 0;j<otn;j++) cout << tmp.mstring;
					else for (j = 0;j<otn;j++) cout << 0;
				}
				else if (ecode[ist + i] == '"')
				{
					str = "";
					for (i = i + 1;ist + i < l;i++)
					{
						if (ecode[ist + i] == '"') break;
						if (ecode[ist + i] == '\\')
						{
							str.append(1,zhuanyi(ecode[ist + i + 1]));
							i++;
							continue;
						}
						str.append(1, ecode[ist + i]);
					}
					for (j = 0;j < otn;j++) cout << str;
				}
			}
		}
		else if (dss == 3)
		{
			string str;
			if (isdigit(ecode[ist + 1]) || ecode[ist + 1] == '-'&&isdigit(ecode[ist + 2]))
			{
				int fflg = 0, otn, j, yh = 0;
				for (i = 1;ist + i < l&&ecode[ist + i] != ',';i++)
				{
					str.append(1, ecode[ist + i]);
				}
				otn = atoi(str.c_str());
				for (;ecode[ist + i] == ' ' || ecode[ist + i] == ',';i++);
				if (ecode[ist + i] == '"')
				{
					str = "";
					for (i = i + 1;ist + i < l;i++)
					{
						if (ecode[ist + i] == '\\')
						{
							str.append(1,zhuanyi(ecode[ist + i + 1]));
							i++;
							continue;
						}
						if (ecode[ist + i] == '"') break;
						str.append(1, ecode[ist + i]);
					}
					for (j = 0;j < otn;j++) cout << str;
					str = "";
					for (i = i + 1;ist + i < l && (ecode[ist + i] == ' ' || ecode[ist + i] == ',');i++);
					if (isdigit(ecode[ist + i]) || ecode[ist + i] == '-'&&isdigit(ecode[ist + i + 1]))
					{
						int fflg = 0;
						for (;ist + i < l&&ecode[ist + i] != ';';i++)
						{
							str.append(1, ecode[ist + i]);
							if (ecode[ist + i] == '.') fflg = 1;
						}
						if (!fflg) cout << atoi(str.c_str());
						else cout << atof(str.c_str());
					}
					else if (isalpha(ecode[ist + i]))
					{
						for (;ist + i < l&&ecode[ist + i] != ';';i++)
						{
							str.append(1, ecode[ist + i]);
						}
						VARIABLE tmp = getvar(str, _depth, limm);
						if (tmp.type == 0) cout << tmp.mint;
						else if (tmp.type == 1) cout << tmp.mreal;
						else if (tmp.type == 2) cout << tmp.mstring;
						else cout << 0;

					}
					else if (ecode[ist + i] == '"')
					{
						string str;
						for (i = i + 1, yh = 1;ist + i < l&&yh;i++)
						{
							if (ecode[ist + i] == '"')
							{
								yh = !yh;
								continue;
							}
							if (ecode[ist + i] == '\\')
							{
								str.append(1, zhuanyi(ecode[ist + i + 1]));
								i++;
								continue;
							}
							str.append(1, ecode[ist + i]);
						}
						cout << str;
					}
				}
				else return;
			}
			else {
				int fflg = 0, otn, j;
				for (i = 1;ist + i < l&&ecode[ist + i] != ',';i++)
				{
					str.append(1, ecode[ist + i]);
				}
				VARIABLE tmp = getvar(str, _depth, limm);
				if (tmp.type == 0) otn = tmp.mint;
				else if (tmp.type == 1) otn = (int)tmp.mreal;
				else if (tmp.type == 2) otn = atoi(tmp.mstring.c_str());
				else otn = 0;
				for (;ecode[ist + i] == ' ' || ecode[ist + i] == ',';i++);
				if (ecode[ist + i] == '"')
				{
					str = "";
					for (i = i + 1;ist + i < l;i++)
					{
						if (ecode[ist + i] == '\\')
						{
							str.append(1,zhuanyi(ecode[ist + i + 1]));
							i++;
							continue;
						}
						if (ecode[ist + i] == '"') break;
						str.append(1, ecode[ist + i]);
					}
					for (j = 0;j < otn;j++) cout << str;
					str = "";
					for (i = i + 1;ist + i < l && (ecode[ist + i] == ' ' || ecode[ist + i] == ',');i++);
					if (isdigit(ecode[ist + i]) || ecode[ist + i] == '-'&&isdigit(ecode[ist + i + 1]))
					{
						int fflg = 0;
						for (;ist + i < l&&ecode[ist + i] != ';';i++)
						{
							str.append(1, ecode[ist + i]);
							if (ecode[ist + i] == '.') fflg = 1;
						}
						if (!fflg) cout << atoi(str.c_str());
						else cout << atof(str.c_str());
					}
					else if (isalpha(ecode[ist + i]))
					{
						for (;ist + i < l&&ecode[ist + i] != ';';i++)
						{
							str.append(1, ecode[ist + i]);
						}
						VARIABLE tmp = getvar(str, _depth, limm);
						if (tmp.type == 0) cout << tmp.mint;
						else if (tmp.type == 1) cout << tmp.mreal;
						else if (tmp.type == 2) cout << tmp.mstring;
						else cout << 0;

					}
					else if (ecode[ist + i] == '"')
					{
						string str;
						for (i = i + 1, yh = 1;ist + i < l&&yh;i++)
						{
							if (ecode[ist + i] == '"')
							{
								yh = !yh;
								continue;
							}
							if (ecode[ist + i] == '\\')
							{
								str.append(1, zhuanyi(ecode[ist + i + 1]));
								i++;
								continue;
							}
							str.append(1, ecode[ist + i]);
						}
						cout << str;
					}
				}
				else return;
			}
		}
		else
		{
			cout << "输出格式错误！" << endl;
		}
	}
}
void mcwhile(string &ecode, int _depth,int limm)
{
	int i, l = ecode.length();
	string exps, esuf;
	VARIABLE vtmp;
	for (i = 6;ecode[i] != '{';i++) exps.append(1, ecode[i]);
	esuf = infsuf(exps);
	vtmp = expcal(esuf, _depth, limm);
	vtmp = !zerov(vtmp);
	exps = ecode.substr(i, l - i);
	while (vtmp.mint)
	{
		analize(exps, _depth + 1, limm);
		deldep(_depth + 1);
		if (returning()) return;
		vtmp = expcal(esuf, _depth, limm);
		vtmp = !zerov(vtmp);
	}
}
void mcdountil(string &ecode, int upos, int _depth, int limm)
{
	int i, l = ecode.length();
	string exps, esuf;
	VARIABLE vtmp;
	for (i = upos + 5;i < l - 1;i++) exps.append(1, ecode[i]);
	esuf = infsuf(exps);
	exps = ecode.substr(2, upos - 2);
	do {
		analize(exps, _depth + 1, limm);
		deldep(_depth + 1);
		if (returning()) return;
		vtmp = expcal(esuf, _depth, limm);
		vtmp = zerov(vtmp);
	} while (vtmp.mint);
}
void analize(string &ecode, int _depth, int limm)
{
	int i, j, l = ecode.length(), yh = 0, yht, ktype, bracem = 0, elpos;
	string exps, esuf, str;
	for (i = 1;i < l-1;i++)
	{
		if (returning()) return;
		if (ecode[i] == '"') yh = !yh;
		if (yh)
		{
			if (ecode[i] == '\\') i++;
			continue;
		}
		if (ecode[i] == ' '||ecode[i]=='\t') continue;
		ktype = iskey(ecode, i);
		j = 0;
		switch (ktype)
		{
		case01:
		case -1:
			exps = "";
			for (j = 0, yht = 0;i + j < l - 1;j++)
			{
				if (ecode[i+j] == '"') yh = !yh;
				if (yh)
				{
					exps.append(1, ecode[i + j]);
					continue;
				}
				if (ecode[i + j] == ';') break;
				exps.append(1, ecode[i + j]);
			}
			esuf = infsuf(exps);
			expcal(esuf, _depth, limm);
			break;
		case 0:
			for (j = 4;i + j < l - 1;j++)
			{
				if (ecode[i + j] == ';')
				{
					if (str.length())
					{
						newvar(str, _depth, short(0));
						str = "";
					}
					break;
				}
				if (ecode[i + j] == ' ' || ecode[i + j] == ',')
				{
					newvar(str, _depth, short(0));
					str = "";
					continue;
				}
				if (isdigit(ecode[i + j]) || isalpha(ecode[i + j]))
				{
					str.append(1, ecode[i + j]);
					continue;
				}
			}
			break;
		case 1:
			for (j = 5;i + j < l - 1;j++)
			{
				if (ecode[i + j] == ';')
				{
					if (str.length())
					{
						newvar(str, _depth, float(0));
						str = "";
					}
					break;
				}
				if (ecode[i + j] == ' ' || ecode[i + j] == ',')
				{
					newvar(str, _depth, float(0));
					str = "";
					continue;
				}
				if (isdigit(ecode[i + j]) || isalpha(ecode[i + j]))
				{
					str.append(1, ecode[i + j]);
					continue;
				}
			}
			break;
		case 2:
			for (j = 7;i + j < l - 1;j++)
			{
				if (ecode[i + j] == ';')
				{
					if (str.length())
					{
						newvar(str, _depth, "");
						str = "";
					}
					break;
				}
				if (ecode[i + j] == ' ' || ecode[i + j] == ',')
				{
					newvar(str, _depth, "");
					str = "";
					continue;
				}
				if (isdigit(ecode[i + j]) || isalpha(ecode[i + j]))
				{
					str.append(1, ecode[i + j]);
					continue;
				}
			}
			break;
		case 3:
			for (j = 0, yht = 0, bracem = 0;i + j < l - 1;j++)
			{
				if (ecode[i + j] == '"') yht = !yht;
				if (yht) continue;
				if (ecode[i + j] == '{') bracem++;
				if (ecode[i + j] == '}')
				{
					bracem--;
					if (!bracem) break;
				}
			}
			str = ecode.substr(i, j + 1);
			mcwhile(str, _depth, limm);
			break;
		case 4:
			for (j = 0, yht = 0, bracem = 0;i + j < l - 1;j++)
			{
				if (ecode[i + j] == '"') yht = !yht;
				if (yht) continue;
				if (ecode[i + j] == '{') bracem++;
				if (ecode[i + j] == '}')
				{
					bracem--;
					if (!bracem) break;
				}
			}
			elpos = -1;
			if (ecode[i + j + 1] == 'e'&&ecode[i + j + 2] == 'l'&&ecode[i + j + 3] == 's'&&ecode[i + j + 4] == 'e')
			{
				elpos = i + j + 1;
				for (j = j+1, yht = 0, bracem = 0;i + j < l - 1;j++)
				{
					if (ecode[i + j] == '"') yht = !yht;
					if (yht) continue;
					if (ecode[i + j] == '{') bracem++;
					if (ecode[i + j] == '}')
					{
						bracem--;
						if (!bracem) break;
					}
				}
			}
			str = ecode.substr(i, j + 1);
			mcifelse(str, elpos-i, _depth, limm);
			break;
		case 5:
			if(ecode[i+4]==' '||ecode[i+4]=='{') cout << "else缺少if！" << endl;
			else goto case01;
			return;
		case 6:
			for (j = 0, yht = 0;i + j < l - 1;j++)
			{
				if (ecode[i + j] == '"') yht = !yht;
				if (yht) continue;
				if (ecode[i + j] == ';') break;
			}
			str = ecode.substr(i, j + 1);
			mcout(str, _depth, limm);
			break;
		case 7:
			for (j = 0, yht = 0;i + j < l - 1;j++)
			{
				if (ecode[i + j] == '"') yht = !yht;
				if (yht) continue;
				if (ecode[i + j] == ';') break;
			}
			str = ecode.substr(i, j + 1);
			mcin(str, _depth, limm);
			break;
		case 8:
			nowreturning.top() = 1;
			exps = "";
			for (j = 7, yht = 0;i + j < l - 1;j++)
			{
				if (ecode[i+j] == '"') yh = !yh;
				if (yh)
				{
					exps.append(1, zhuanyi(ecode[i + j]));
					continue;
				}
				if (ecode[i + j] == ';') break;
				exps.append(1, ecode[i + j]);
			}
			esuf = infsuf(exps);
			retv.top()=expcal(esuf, _depth, limm);
			return;
		case 9:
			if (ecode[i + 2] == ' ' || ecode[i + 2] == '{')
			{
				for (j = 0, yht = 0, bracem = 0;i + j < l - 1;j++)
				{
					if (ecode[i + j] == '"') yht = !yht;
					if (yht) continue;
					if (ecode[i + j] == '{') bracem++;
					if (ecode[i + j] == '}')
					{
						bracem--;
						if (!bracem) break;
					}
				}
				if (iskey(ecode, i + j + 1) == 10)
				{
					int upos = j + 1;
					for (j = j + 1, yht = 0;i + j < l - 1;j++)
					{
						if (ecode[i + j] == '"') yht = !yht;
						if (yht) continue;
						if (ecode[i + j] == ';') break;
					}
					str = ecode.substr(i, j+1);
					mcdountil(str, upos, _depth, limm);
				}
				else
				{
					cout << "until缺少do！" << endl;
					return;
				}
			}
			else goto case01;
			break;
		case 10:
			if (ecode[i + 5] == ' ')
			{
				cout << "until缺少do！" << endl;
				return;
			}
			else goto case01;
			break;
		default:break;
		}
		i = i + j;
	}
}