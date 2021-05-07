#include"stdafx.h"
#include"mincvar.h"
#include"mincfunction.h"
#include"mincscanner.h"
FILE* fp=NULL;
string code_tot;
int lineindex[1005] = { 0 }, lncnt = 1;
bool istyped(int pos)
{
	if (code_tot.compare(pos, 4, "int ") == 0 || code_tot.compare(pos, 5, "real ") == 0 || code_tot.compare(pos, 7, "string ") == 0) return 1;
	return 0;
}
int openfile(const char* _fname)
{
	fp = fopen(_fname, "r");
	if (fp == NULL)
	{
		filefail(_fname);
		return -1;
	}
	setreslist();
	char cc,cb;
	int bracen = 0, yh2 = 0, khn = 0;
	while (cc = fgetc(fp))
	{
		if (cc == EOF) break;
		if (cc == '/')
		{
			if (!yh2)
			{
				cb = fgetc(fp);
				if (cb == '/')
				{
					while (cb = fgetc(fp))
					{
						if (cb == '\n' || cb == EOF) break;
					}
					continue;
				}
				else {
					code_tot.append(1, cc);
					cc = cb;
				}
			}
		}
		if (cc == '\\')
		{
			cb = fgetc(fp);
			code_tot.append(1, cc);
			if (cb != '\n') code_tot.append(1, cb);
			continue;
		}
		if (cc == '\"')
		{
			yh2 = !yh2;
			code_tot.append(1, cc);
			continue;
		}
		if (cc == '\t')
		{
			if (!yh2) cc = ' ';
		}
		if (cc == ' ')
		{
			if (!yh2)
			{
				while (cb = fgetc(fp))
				{
					if (cb != ' '&&cc != '\t') break;
				}
				code_tot.append(1, cc);
				cc = cb;
				if (cc == '\t') continue;
			}
		}
		if (cc == '\"')
		{
			yh2 = !yh2;
			code_tot.append(1, cc);
			continue;
		}
		if (cc == '\n')
		{
			if (!yh2)
			{
				lineindex[lncnt++] = code_tot.length();
				continue;
			}
			else{
				quotfail(lncnt);
				return -2;
			}
		}
		if (cc == '{')
		{
			if (!yh2) bracen++;
		}
		if (cc == '}')
		{
			if (!yh2) bracen--;
		}
		if (cc == '(')
		{
			if (!yh2) khn++;
		}
		if (cc == ')')
		{
			if (!yh2) khn--;
		}
		code_tot.append(1, cc);
	}
	if (bracen)
	{
		bracefail();
		return -2;
	}
	if (khn)
	{
		khfail();
		return -2;
	}
	fclose(fp);
	return 0;
}
int varfun()
{
	int codelen = code_tot.length(), i, j, bracen = 0, _isbg = 1, _line = 1, bracem = 0, yh = 0, kh = 0;
	for (i = 0;i < codelen;i++)
	{
		if (code_tot[i] == '{')
		{
			bracen++;
			_isbg = 0;
			continue;
		}
		if (code_tot[i] == '}')
		{
			bracen--;
			if(bracen==0) _isbg = 1;
			continue;
		}
		if (bracen) continue;
		if (code_tot[i] == ' ' || code_tot[i] == '\t') continue;
		if (code_tot[i] == ';')
		{
			_isbg = 1;
			continue;
		}
		if (!_isbg) continue;
		if (istyped(i))
		{
			for (j = 0;code_tot[i + j] != ' ';j++);
			if (!isalpha(code_tot[i + j + 1]))
			{
				i = i + j;
				_isbg = 0;
				continue;
			}
			for (j = j + 1,_line=1;i+j<codelen;j++)
			{
				if (code_tot[i + j] == '(') break;
				if (!isalpha(code_tot[i + j]) && !isdigit(code_tot[i + j]))
				{
					i = i + j - 1;
					_line = -1;
					break;
				}
			}
			if (_line != 1) continue;
			for (j = j + 1;i + j < codelen&&_line==1;j++)
			{
				if (code_tot[i + j] == ' ') continue;
				if (code_tot[i + j] == ',') continue;
				if (code_tot[i + j] == ')') break;
				if (istyped(i + j))
				{
					while (code_tot[i + j] != ' ') j++;
					if (!isalpha(code_tot[i + j + 1]))
					{
						i = i + j;
						_isbg = 0;
						_line = -1;
						break;
					}
					for (j = j + 1;i + j < codelen;j++)
					{
						if (code_tot[i + j] == ',') break;
						if (code_tot[i + j] == ')') j--;break;
						if (!isalpha(code_tot[i + j]) && !isdigit(code_tot[i + j]))
						{
							_line = -1;
							break;
						}
					}
				}
				else
				{
					_line = -1;
					break;
				}
			}
			if (_line != 1) continue;
			for (j = 0;i+j<codelen&&code_tot[i + j] != ')';j++);
			for (j = j + 1, bracem = 0;i + j < codelen;j++)
			{
				if (code_tot[i + j] == ' ' || code_tot[i + j] == '\t') continue;
				if (code_tot[i + j] == '{')
				{
					bracem = 1;
					break;
				}
				else
				{
					_line = -1;
					break;
				}
			}
			if (_line != 1) continue;
			for (j = j + 1;i + j < codelen&&bracem;j++)
			{
				if (code_tot[i + j] == '"') yh = !yh;
				if (!yh)
				{
					if (code_tot[i + j] == '(') kh++;
					if (code_tot[i + j] == ')') kh--;
					if (!kh)
					{
						if (code_tot[i + j] == '{') bracem++;
						if (code_tot[i + j] == '}') bracem--;
					}
				}
			}
			newfunction(code_tot, i, j);
			i = i + j - 1;
		}
	}
	return 0;
}
void outmidcode()
{
	cout << code_tot << endl;
}
void globalvar()
{
	int codelen = code_tot.length(), i, j, bracen = 0, _isbg = 1, _line = 1, vtype;
	for (i = 0;i < codelen;i++)
	{
		if (code_tot[i] == '{')
		{
			bracen++;
			_isbg = 0;
			continue;
		}
		if (code_tot[i] == '}')
		{
			bracen--;
			if (bracen == 0) _isbg = 1;
			continue;
		}
		if (bracen) continue;
		if (code_tot[i] == ' ' || code_tot[i] == '\t') continue;
		if (code_tot[i] == ';')
		{
			_isbg = 1;
			continue;
		}
		if (!_isbg) continue;
		if (istyped(i))
		{
			for (j = 0;code_tot[i + j] != ' ';j++);
			if (!isalpha(code_tot[i + j + 1]))
			{
				i = i + j;
				_isbg = 0;
				continue;
			}
			while (code_tot[i + j] != ';'&&_line==1)
			{
				for (j = j + 1, _line = 1;i + j < codelen;j++)
				{
					if (code_tot[i + j] == ',' || code_tot[i + j] == ';') break;
					if (!isalpha(code_tot[i + j]) && !isdigit(code_tot[i + j]))
					{
						i = i + j - 1;
						_line = -1;
						break;
					}
				}
				if (_line != 1) break;
				if (code_tot[i + j] == ';') break;
				if (!isalpha(code_tot[i + j + 1]))
				{
					i = i + j;
					_isbg = 0;
					_line = -1;
					break;
				}
			}
			if (_line != 1) continue;
			if (code_tot[i + j] == ';')
			{
				vtype = iskey(code_tot, i);
				for (j = 0;i + j < codelen && code_tot[j + i] != ' ';j++);
				string vname;
				for (j = j + 1;i + j < codelen;j++)
				{
					if (code_tot[i + j] == ',' || code_tot[i + j] == ';')
					{
						if (vtype == 0)
						{
							newvar(vname, 0, short(0));
						}
						else if (vtype == 1)
						{
							newvar(vname, 0, float(0));
						}
						else if (vtype == 2)
						{
							newvar(vname, 0, "");
						}
						vname = "";
						if (code_tot[i + j] == ',') continue;
						else break;
					}
					if (isalpha(code_tot[i + j]) || isdigit(code_tot[i + j])) vname.append(1, code_tot[i + j]);
				}
			}
			i = i + j - 1;
		}
	}
}