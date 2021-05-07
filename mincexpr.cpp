#include "stdafx.h"
using namespace std;
//0( 1) 2! 3- 4+ 5* 6/ 7% 8+ 9- 10$ 11< 12<= 13> 14>= 15== 16<> 17 && 18|| 19= no#
stack <int> opstk;
stack <int> oppro;
struct STKN
{
	VARIABLE *p;
	int tmp=0;
};
void stkout(string &esuf, int i)
{
	if (i > 1 || i < 0) esuf.append(" ");
	switch (i)
	{
	case -1:
		esuf.append("^");
		break;
	case 0:case 1:return;
	case 2:
		esuf.append("!");
		break;
	case 3:
		esuf.append("_");
		break;
	case 4:break;
	case 5:
		esuf.append("*");
		break;
	case 6:
		esuf.append("/");
		break;
	case 7:
		esuf.append("%");
		break;
	case 8:
		esuf.append("+");
		break;
	case 9:
		esuf.append("-");
		break;
	case 10:
		esuf.append("$");
		break;
	case 11:
		esuf.append("<");
		break;
	case 12:
		esuf.append("<=");
		break;
	case 13:
		esuf.append(">");
		break;
	case 14:
		esuf.append(">=");
		break;
	case 15:
		esuf.append("==");
		break;
	case 16:
		esuf.append("<>");
		break;
	case 17:
		esuf.append("&&");
		break;
	case 18:
		esuf.append("||");
		break;
	case 19:
		esuf.append("=");
		break;
	case 20:
		esuf.append("#");
		break;
	default:break;
	}
	esuf.append(" ");
}
//0( 1) 2! 3- 4+ 5* 6/ 7% 8+ 9- 10$ 11< 12<= 13> 14>= 15== 16<> 17 && 18|| 19= 20#
//prio 1() 2!-+ 3*/% 4+-$ 5<<=>>= 6==<> 7&& 8|| 9=
string infsuf(string &exps)
{
	int i, l = exps.length(),khn=0,yh=0,yh2=0;
	string esuf;
	for (i = 0;i < l;i++)
	{
		if (yh)
		{
			if (exps[i] == '\\')
			{
				esuf.append(1, exps[i]);
				esuf.append(1, exps[i + 1]);
				i++;
				continue;
			}
			if (exps[i] == '"') yh = !yh;
			esuf.append(1, exps[i]);
			continue;
		}
		else if (exps[i] == '"')
		{
			yh = !yh;
			esuf.append(" ");
			esuf.append(1, exps[i]);
			continue;
		}
		else if (exps[i] == ' ') continue;
		else if (exps[i] == ';') break;
		else {
			if (exps[i] == '-')
			{
				esuf.append(" ");
				if (i == 0)
				{
					opstk.push(3);
					oppro.push(2);
				}
				else if (exps[i - 1] == '(' || exps[i - 1] == '*' || exps[i - 1] == '/' || exps[i - 1] == '%')
				{
					opstk.push(3);
					oppro.push(2);
				}
				else if (exps[i - 1] == '!' || exps[i - 1] == '<' || exps[i - 1] == '=' || exps[i - 1] == '>' || exps[i - 1] == '&' || exps[i - 1] == '|')
				{
					opstk.push(3);
					oppro.push(2);
				}
				else if (exps[i - 1] == '^')
				{
					opstk.push(3);
					oppro.push(2);
				}
				else {
					while (!opstk.empty() && (oppro.top() <= 4 && oppro.top() > 1 || oppro.top() < 0))
					{
						stkout(esuf, opstk.top());
						esuf.append(" ");
						opstk.pop();
						oppro.pop();
					}
					opstk.push(9);
					oppro.push(4);
				}
			}
			else if (exps[i] == '(')
			{
				if (i > 0 && (isdigit(exps[i - 1]) || isalpha(exps[i - 1])))
				{
					esuf.append(1, exps[i]);
					khn = 1, i++;
					for (;khn&&i < l;i++)
					{
						if (exps[i] == '"')
						{
							yh2 = !yh2;
							esuf.append(1,exps[i]);
							continue;
						}
						if (yh2) esuf.append(1,exps[i]);
						else {
							if (exps[i] == '(') khn++;
							else if (exps[i] == ')') khn--;
							esuf.append(1, exps[i]);
						}
					}
					--i;
				}
				else {
					opstk.push(0);
					oppro.push(1);
					esuf.append(" ");
				}
			}
			else if (exps[i] == ')')
			{
				esuf.append(" ");
				while (!opstk.empty() && opstk.top() != 0)
				{
					stkout(esuf, opstk.top());
					esuf.append(" ");
					opstk.pop();
					oppro.pop();
				}
				opstk.pop();
				oppro.pop();
			}
			else if (exps[i] == '!')
			{
				esuf.append(" ");
				opstk.push(2);
				oppro.push(2);
			}
			else if (exps[i] == '^')
			{
				esuf.append(" ");
				opstk.push(-1);
				oppro.push(-1);
			}
			else if (exps[i] == '#')
			{
				esuf.append(" ");
				opstk.push(20);
				oppro.push(2);
			}
			else if (exps[i] == '+')
			{
				if (i == 0)
				{
					esuf.append(" ");
					continue;
				}
				else if (exps[i - 1] == '(' || exps[i - 1] == '*' || exps[i - 1] == '/' || exps[i - 1] == '%')
				{
					esuf.append(" ");
					continue;
				}
				else if (exps[i - 1] == '!' || exps[i - 1] == '<' || exps[i - 1] == '=' || exps[i - 1] == '>' || exps[i - 1] == '&' || exps[i - 1] == '|')
				{
					esuf.append(" ");
					continue;
				}
				else if (exps[i - 1] == '^')
				{
					esuf.append(" ");
					continue;
				}
				else {
					esuf.append(" ");
					while (!opstk.empty() && (oppro.top() <= 4 && oppro.top() > 1 || oppro.top() < 0))
					{
						stkout(esuf, opstk.top());
						esuf.append(" ");
						opstk.pop();
						oppro.pop();
					}
					opstk.push(8);
					oppro.push(4);
				}
			}
			else if (exps[i] == '*')
			{
				esuf.append(" ");
				while (!opstk.empty() && (oppro.top() <= 3 && oppro.top() > 1 || oppro.top() < 0))
				{
					stkout(esuf, opstk.top());
					esuf.append(" ");
					opstk.pop();
					oppro.pop();
				}
				opstk.push(5);
				oppro.push(3);
			}
			else if (exps[i] == '/')
			{
				esuf.append(" ");
				while (!opstk.empty() && (oppro.top() <= 3 && oppro.top() > 1 || oppro.top() < 0))
				{
					stkout(esuf, opstk.top());
					esuf.append(" ");
					opstk.pop();
					oppro.pop();
				}
				opstk.push(6);
				oppro.push(3);
			}
			else if (exps[i] == '%')
			{
				esuf.append(" ");
				while (!opstk.empty() && (oppro.top() <= 3 && oppro.top() > 1 || oppro.top() < 0))
				{
					stkout(esuf, opstk.top());
					esuf.append(" ");
					opstk.pop();
					oppro.pop();
				}
				opstk.push(7);
				oppro.push(3);
			}
			else if (exps[i] == '$')
			{
				esuf.append(" ");
				while (!opstk.empty() && (oppro.top() <= 4 && oppro.top() > 1 || oppro.top() < 0))
				{
					stkout(esuf, opstk.top());
					esuf.append(" ");
					opstk.pop();
					oppro.pop();
				}
				opstk.push(10);
				oppro.push(4);
			}
			else if (exps[i] == '<')
			{
				esuf.append(" ");
				if (exps[i + 1] == '=')
				{
					while (!opstk.empty() && (oppro.top() <= 5 && oppro.top() > 1 || oppro.top() < 0))
					{
						stkout(esuf, opstk.top());
						esuf.append(" ");
						opstk.pop();
						oppro.pop();
					}
					opstk.push(12);
					oppro.push(5);
					i++;
				}
				else if (exps[i + 1] == '>')
				{
					while (!opstk.empty() && (oppro.top() <= 6 && oppro.top() > 1 || oppro.top() < 0))
					{
						stkout(esuf, opstk.top());
						esuf.append(" ");
						opstk.pop();
						oppro.pop();
					}
					opstk.push(16);
					oppro.push(6);
					i++;
				}
				else {
					while (!opstk.empty() && (oppro.top() <= 3 && oppro.top() > 1 || oppro.top() < 0))
					{
						stkout(esuf, opstk.top());
						esuf.append(" ");
						opstk.pop();
						oppro.pop();
					}
					opstk.push(11);
					oppro.push(5);
				}
			}
			else if (exps[i] == '>')
			{
				esuf.append(" ");
				if (exps[i + 1] == '=')
				{
					while (!opstk.empty() && (oppro.top() <= 5 && oppro.top() > 1 || oppro.top() < 0))
					{
						stkout(esuf, opstk.top());
						esuf.append(" ");
						opstk.pop();
						oppro.pop();
					}
					opstk.push(14);
					oppro.push(5);
					i++;
				}
				else {
					while (!opstk.empty() && (oppro.top() <= 5 && oppro.top() > 1 || oppro.top() < 0))
					{
						stkout(esuf, opstk.top());
						esuf.append(" ");
						opstk.pop();
						oppro.pop();
					}
					opstk.push(13);
					oppro.push(5);
				}
			}
			else if (exps[i] == '=')
			{
				esuf.append(" ");
				if (exps[i + 1] == '=')
				{
					while (!opstk.empty() && (oppro.top() <= 6 && oppro.top() > 1 || oppro.top() < 0))
					{
						stkout(esuf, opstk.top());
						esuf.append(" ");
						opstk.pop();
						oppro.pop();
					}
					opstk.push(15);
					oppro.push(6);
					i++;
				}
				else {
					while (!opstk.empty() && (oppro.top() <= 5 && oppro.top() > 1 || oppro.top() < 0))
					{
						stkout(esuf, opstk.top());
						esuf.append(" ");
						opstk.pop();
						oppro.pop();
					}
					opstk.push(19);
					oppro.push(9);
				}
			}
			else if (exps[i] == '&')
			{
				esuf.append(" ");
				if (exps[i + 1] != '&')
				{
					cout << "No single &!" << endl;
					return "";
				}
				while (!opstk.empty() && (oppro.top() <= 7 && oppro.top() > 1 || oppro.top() < 0))
				{
					stkout(esuf, opstk.top());
					esuf.append(" ");
					opstk.pop();
					oppro.pop();
				}
				opstk.push(17);
				oppro.push(7);
				i++;
			}
			else if (exps[i] == '|')
			{
				esuf.append(" ");
				if (exps[i + 1] != '|')
				{
					cout << "No single |!" << endl;
					return "";
				}
				while (!opstk.empty() && (oppro.top() <= 8 && oppro.top() > 1 || oppro.top() < 0))
				{
					stkout(esuf, opstk.top());
					esuf.append(" ");
					opstk.pop();
					oppro.pop();
				}
				opstk.push(18);
				oppro.push(8);
				i++;
			}
			else esuf.append(1,exps[i]);
		}
	}
	while (!opstk.empty())
	{
		stkout(esuf, opstk.top());
		esuf.append(" ");
		opstk.pop();
		oppro.pop();
	}
	if (yh)
	{
		cout << "表达式缺少引号！" << endl;
		esuf = "";
	}
	esuf.append(" ");
	return esuf;
}
int jdgexp(string exps)
{
	if (exps.compare(0, 4, "int ")==0) return 0;
	if (exps.compare(0, 5, "real ")==0) return 1;
	if (exps.compare(0, 7, "string ")==0) return 2;
	if (exps.compare(0, 6, "while ")==0) return 3;
	if (exps.compare(0, 3, "if ")==0) return 4;
	if (exps.compare(0, 5, "else ")==0) return 5;
	if (exps.compare(0, 5, "else{")==0) return 5;
	if (exps.compare(0, 3, "in ")==0) return 6;
	if (exps.compare(0, 4, "out ")==0) return 7;
	if (exps.compare(0, 7, "return ")==0) return 8;
	int i, l = exps.length();
	for (i = 0;i < l;i++) if (exps[i] == '#') return 9;
	return 10;
}
string stringtostring(string &org)
{
	string ans;
	for (int i = 0;i < org.length();i++)
	{
		if (org[i] == '\\')
		{
			switch (org[i + 1])
			{
			case 'a': ans.append(1, '\a');break;
			case 'b': ans.append(1, '\b');break;
			case 'f': ans.append(1, '\f');break;
			case 'n': ans.append(1, '\n');break;
			case 'r': ans.append(1, '\r');break;
			case 't': ans.append(1, '\t');break;
			case 'v': ans.append(1, '\v');break;
			case '\\': ans.append(1, '\\');break;
			case '\'': ans.append(1, '\'');break;
			case '"': ans.append(1, '"');break;
			case '?': ans.append(1, '\?');break;
			case '0': ans.append(1, '\0');break;
			default:break;
			}
			i = i + 1;
			continue;
		}
		ans.append(1, org[i]);
	}
	return ans;
}
//0const int 1const real 2const string 3variable 4function
//stk:0const 1var
//0( 1) 2! 3- 4+ 5* 6/ 7% 8+ 9- 10$ 11< 12<= 13> 14>= 15== 16<> 17 && 18|| 19= no#
//prio 1() 2!-+ 3*/% 4+-$ 5<<=>>= 6==<> 7&& 8|| 9=
VARIABLE expcal(string &esuf,int _depth,int &limm)
{
	stack <STKN> calstk;
	STKN ntmp;
	STKN ntmp1, ntmp2;
	VARIABLE vtmp;
	string stmp;
	int i, j, l = esuf.length(), ll, gtype, yh=0;
	for (i = 0;i < l;i++)
	{
		if (esuf[i] == ' ') continue;
		stmp.assign("");
		if (esuf[i]=='!')
		{
			if (calstk.empty())
			{
				stkerr();
				return VARIABLE();
			}
			ntmp1 = calstk.top();
			calstk.pop();
			ntmp.p = new VARIABLE;
			ntmp.tmp = 0;
			*(ntmp.p) = !(*ntmp1.p);
			calstk.push(ntmp);
			if (ntmp1.tmp == 0) delete ntmp1.p;
		}
		else if (esuf[i] == '#')
		{
			if (calstk.empty())
			{
				stkerr();
				return VARIABLE();
			}
			ntmp1 = calstk.top();
			calstk.pop();
			ntmp.p = new VARIABLE;
			ntmp.tmp = 0;
			*(ntmp.p) = strdel(*ntmp1.p);
			calstk.push(ntmp);
			if (ntmp1.tmp == 0) delete ntmp1.p;
		}
		else if (esuf[i] == '_')
		{
			if (calstk.empty())
			{
				stkerr();
				return VARIABLE();
			}
			ntmp1 = calstk.top();
			calstk.pop();
			ntmp.p = new VARIABLE;
			*ntmp.p = -(*ntmp1.p);
			ntmp.tmp = 0;
			calstk.push(ntmp);
			if (ntmp1.tmp == 0) delete ntmp1.p;
		}
		else if (esuf[i] == '-')
		{
			if (calstk.size() < 2)
			{
				stkerr();
				return VARIABLE();
			}
			ntmp1 = calstk.top();
			calstk.pop();
			ntmp2 = calstk.top();
			calstk.pop();
			ntmp.p = new VARIABLE;
			*ntmp.p = (*ntmp2.p) - (*ntmp1.p);
			ntmp.tmp = 0;
			calstk.push(ntmp);
			if (ntmp1.tmp == 0) delete ntmp1.p;
			if (ntmp2.tmp == 0) delete ntmp2.p;
		}
		else if (esuf[i] == '+')
		{
			if (calstk.size() < 2)
			{
				stkerr();
				return VARIABLE();
			}
			ntmp1 = calstk.top();
			calstk.pop();
			ntmp2 = calstk.top();
			calstk.pop();
			ntmp.p = new VARIABLE;
			*ntmp.p = (*ntmp2.p) + (*ntmp1.p);
			ntmp.tmp = 0;
			calstk.push(ntmp);
			if (ntmp1.tmp == 0) delete ntmp1.p;
			if (ntmp2.tmp == 0) delete ntmp2.p;
		}
		else if (esuf[i] == '*')
		{
			if (calstk.size() < 2)
			{
				stkerr();
				return VARIABLE();
			}
			ntmp1 = calstk.top();
			calstk.pop();
			ntmp2 = calstk.top();
			calstk.pop();
			ntmp.p = new VARIABLE;
			*ntmp.p = (*ntmp2.p) * (*ntmp1.p);
			ntmp.tmp = 0;
			calstk.push(ntmp);
			if (ntmp1.tmp == 0) delete ntmp1.p;
			if (ntmp2.tmp == 0) delete ntmp2.p;
		}
		else if (esuf[i] == '/')
		{
			if (calstk.size() < 2)
			{
				stkerr();
				return VARIABLE();
			}
			ntmp1 = calstk.top();
			calstk.pop();
			ntmp2 = calstk.top();
			calstk.pop();
			ntmp.p = new VARIABLE;
			*ntmp.p = (*ntmp2.p) / (*ntmp1.p);
			ntmp.tmp = 0;
			calstk.push(ntmp);
			if (ntmp1.tmp == 0) delete ntmp1.p;
			if (ntmp2.tmp == 0) delete ntmp2.p;
		}
		else if (esuf[i] == '%')
		{
			if (calstk.size() < 2)
			{
				stkerr();
				return VARIABLE();
			}
			ntmp1 = calstk.top();
			calstk.pop();
			ntmp2 = calstk.top();
			calstk.pop();
			ntmp.p = new VARIABLE;
			*ntmp.p = (*ntmp2.p) % (*ntmp1.p);
			ntmp.tmp = 0;
			calstk.push(ntmp);
			if (ntmp1.tmp == 0) delete ntmp1.p;
			if (ntmp2.tmp == 0) delete ntmp2.p;
		}
		else if (esuf[i] == '^')
		{
			if (calstk.size() < 2)
			{
				stkerr();
				return VARIABLE();
			}
			ntmp1 = calstk.top();
			calstk.pop();
			ntmp2 = calstk.top();
			calstk.pop();
			ntmp.p = new VARIABLE;
			*ntmp.p = (*ntmp2.p) ^ (*ntmp1.p);
			ntmp.tmp = 0;
			calstk.push(ntmp);
			if (ntmp1.tmp == 0) delete ntmp1.p;
			if (ntmp2.tmp == 0) delete ntmp2.p;
		}
		else if (esuf[i] == '$')
		{
			if (calstk.size() < 2)
			{
				stkerr();
				return VARIABLE();
			}
			ntmp1 = calstk.top();
			calstk.pop();
			ntmp2 = calstk.top();
			calstk.pop();
			ntmp.p = new VARIABLE;
			*ntmp.p = (*ntmp2.p) & (*ntmp1.p);
			ntmp.tmp = 0;
			calstk.push(ntmp);
			if (ntmp1.tmp == 0) delete ntmp1.p;
			if (ntmp2.tmp == 0) delete ntmp2.p;
		}
		else if (esuf[i] == '<')
		{
			if (esuf[i + 1] == '>')
			{
				if (calstk.size() < 2)
				{
					stkerr();
					return VARIABLE();
				}
				ntmp1 = calstk.top();
				calstk.pop();
				ntmp2 = calstk.top();
				calstk.pop();
				ntmp.p = new VARIABLE;
				*ntmp.p = (*ntmp2.p) != (*ntmp1.p);
				ntmp.tmp = 0;
				calstk.push(ntmp);
				if (ntmp1.tmp == 0) delete ntmp1.p;
				if (ntmp2.tmp == 0) delete ntmp2.p;
				i++;
			}
			else if (esuf[i + 1] == '=')
			{
				if (calstk.size() < 2)
				{
					stkerr();
					return VARIABLE();
				}
				ntmp1 = calstk.top();
				calstk.pop();
				ntmp2 = calstk.top();
				calstk.pop();
				ntmp.p = new VARIABLE;
				*ntmp.p = (*ntmp2.p) <= (*ntmp1.p);
				ntmp.tmp = 0;
				calstk.push(ntmp);
				if (ntmp1.tmp == 0) delete ntmp1.p;
				if (ntmp2.tmp == 0) delete ntmp2.p;
				i++;
			}
			else {
				if (calstk.size() < 2)
				{
					stkerr();
					return VARIABLE();
				}
				ntmp1 = calstk.top();
				calstk.pop();
				ntmp2 = calstk.top();
				calstk.pop();
				ntmp.p = new VARIABLE;
				*ntmp.p = (*ntmp2.p) < (*ntmp1.p);
				ntmp.tmp = 0;
				calstk.push(ntmp);
				if (ntmp1.tmp == 0) delete ntmp1.p;
				if (ntmp2.tmp == 0) delete ntmp2.p;
			}
		}
		else if (esuf[i] == '>')
		{
			if (esuf[i + 1] == '=')
			{
				if (calstk.size() < 2)
				{
					stkerr();
					return VARIABLE();
				}
				ntmp1 = calstk.top();
				calstk.pop();
				ntmp2 = calstk.top();
				calstk.pop();
				ntmp.p = new VARIABLE;
				*ntmp.p = (*ntmp2.p) >= (*ntmp1.p);
				ntmp.tmp = 0;
				calstk.push(ntmp);
				if (ntmp1.tmp == 0) delete ntmp1.p;
				if (ntmp2.tmp == 0) delete ntmp2.p;
				i++;
			}
			else {
				if (calstk.size() < 2)
				{
					stkerr();
					return VARIABLE();
				}
				ntmp1 = calstk.top();
				calstk.pop();
				ntmp2 = calstk.top();
				calstk.pop();
				ntmp.p = new VARIABLE;
				*ntmp.p = (*ntmp2.p) < (*ntmp1.p);
				ntmp.tmp = 0;
				calstk.push(ntmp);
				if (ntmp1.tmp == 0) delete ntmp1.p;
				if (ntmp2.tmp == 0) delete ntmp2.p;
			}
		}
		else if (esuf[i] == '=')
		{
			if (esuf[i + 1] == '=')
			{
				if (calstk.size() < 2)
				{
					stkerr();
					return VARIABLE();
				}
				ntmp1 = calstk.top();
				calstk.pop();
				ntmp2 = calstk.top();
				calstk.pop();
				ntmp.p = new VARIABLE;
				*ntmp.p = (*ntmp2.p) == (*ntmp1.p);
				ntmp.tmp = 0;
				calstk.push(ntmp);
				if (ntmp1.tmp == 0) delete ntmp1.p;
				if (ntmp2.tmp == 0) delete ntmp2.p;
				i++;
			}
			else {
				if (calstk.size() < 2)
				{
					stkerr();
					return VARIABLE();
				}
				ntmp1 = calstk.top();
				calstk.pop();
				ntmp2 = calstk.top();
				calstk.pop();
				if (ntmp2.tmp == 0)
				{
					cout << "非法赋值！" << endl;
					return VARIABLE();
				}
				if (ntmp2.p->type == 0)
				{
					if (ntmp1.p->type == 0) ntmp2.p->mint = ntmp1.p->mint;
					else if (ntmp1.p->type == 1) ntmp2.p->mint = ntmp1.p->mreal;
					else if (ntmp1.p->type == 2)
					{
						stringstream sstr;
						sstr << ntmp1.p->mstring;
						sstr >> ntmp2.p->mint;
					}
					else ntmp2.p->mint = 0;
				}
				else if (ntmp2.p->type == 1)
				{
					if (ntmp1.p->type == 0) ntmp2.p->mreal = ntmp1.p->mint;
					else if (ntmp1.p->type == 1) ntmp2.p->mreal = ntmp1.p->mreal;
					else if (ntmp1.p->type == 2)
					{
						stringstream sstr;
						sstr << ntmp1.p->mstring;
						sstr >> ntmp2.p->mreal;
					}
					else ntmp2.p->mreal = 0;
				}
				else if (ntmp2.p->type == 2)
				{
					stringstream sstr;
					if (ntmp1.p->type == 0)
					{
						sstr << ntmp1.p->mint;
						sstr >> ntmp2.p->mstring;
					}
					else if (ntmp1.p->type == 1)
					{
						sstr << ntmp1.p->mreal;
						sstr >> ntmp2.p->mstring;
					}
					else if (ntmp1.p->type == 2) ntmp2.p->mstring = ntmp1.p->mstring;
					else ntmp2.p->mstring = "";

				}
				else
				{
					cout << "非法赋值！" << endl;
					return VARIABLE();
				}
				calstk.push(ntmp2);
				if (ntmp1.tmp == 0) delete ntmp1.p;
				if (ntmp2.tmp == 0) delete ntmp2.p;
			}
		}
		else if (esuf[i] == '&')
		{
			if (esuf[i + 1] == '&')
			{
				if (calstk.size() < 2)
				{
					stkerr();
					return VARIABLE();
				}
				ntmp1 = calstk.top();
				calstk.pop();
				ntmp2 = calstk.top();
				calstk.pop();
				ntmp.p = new VARIABLE;
				*ntmp.p = (*ntmp2.p) && (*ntmp1.p);
				ntmp.tmp = 0;
				calstk.push(ntmp);
				if (ntmp1.tmp == 0) delete ntmp1.p;
				if (ntmp2.tmp == 0) delete ntmp2.p;
				i++;
			}
		}
		else if (esuf[i] == '|')
		{
			if (esuf[i + 1] == '|')
			{
				if (calstk.size() < 2)
				{
					stkerr();
					return VARIABLE();
				}
				ntmp1 = calstk.top();
				calstk.pop();
				ntmp2 = calstk.top();
				calstk.pop();
				ntmp.p = new VARIABLE;
				*ntmp.p = (*ntmp2.p) || (*ntmp1.p);
				ntmp.tmp = 0;
				calstk.push(ntmp);
				if (ntmp1.tmp == 0) delete ntmp1.p;
				if (ntmp2.tmp == 0) delete ntmp2.p;
				i++;
			}
		}
		else {
			for (j = 0;i + j < l;j++)
			{
				if (esuf[i + j] == '"') yh = !yh;
				else if (!yh)
				{
					if (esuf[i + j] == ' ') break;
				}
				stmp.append(1, esuf[i + j]);
			}
			if (inreslist(stmp))
			{
				return VARIABLE();
			}
			ll = stmp.length();
			gtype = -1;
			if (isdigit(stmp[0])) gtype = 0;
			else if (isalpha(stmp[0])) gtype = 3;
			else if (stmp[0] == '"') gtype = 2;
			else {
				cout << "算式错误！" << endl;
				return VARIABLE();
			}
			if (gtype == 0)
			{
				for (j = 0;j < stmp.length();j++)
				{
					if (!isdigit(stmp[j]) && stmp[j] != '.')
					{
						gtype = -1;
						break;
					}
					else if (stmp[j] == '.') gtype = 1;
				}
			}
			else if (gtype == 3)
			{
				for (j = 0;j < stmp.length();j++)
				{
					if (stmp[j] == '(')
					{
						gtype = 4;
						break;
					}
				}
			}
			if (gtype == -1)
			{
				cout << "表达式量错误！" << endl;
				return VARIABLE();
			}
			if (gtype == 0)
			{
				stringstream sstr;
				sstr << stmp;
				ntmp.p = new VARIABLE();
				ntmp.p->type = 0;
				ntmp.p->depth = _depth;
				sstr >> ntmp.p->mint;
				ntmp.p->mstring = "";
				ntmp.tmp = 0;
				calstk.push(ntmp);
			}
			else if (gtype == 1)
			{
				stringstream sstr;
				sstr << stmp;
				ntmp.p = new VARIABLE();
				ntmp.p->type = 1;
				ntmp.p->depth = _depth;
				sstr >> ntmp.p->mreal;
				ntmp.p->mstring = "";
				ntmp.tmp = 0;
				calstk.push(ntmp);
			}
			else if (gtype == 2)
			{
				ntmp.p = new VARIABLE();
				ntmp.p->type = 2;
				ntmp.p->depth = _depth;
				stmp.erase(stmp.begin());
				stmp.erase(stmp.end()-1);
				ntmp.p->mstring = stringtostring(stmp);
				ntmp.tmp = 0;
				calstk.push(ntmp);
			}
			else if (gtype == 3)
			{
				VARIABLE *vp = &getvar(stmp, _depth, limm);
				ntmp.p = vp;
				ntmp.tmp = 1;
				calstk.push(ntmp);
			}
			else if (gtype == 4)
			{
				vtmp = Runfun(stmp,_depth+1,limm);
				ntmp.p = new VARIABLE;
				*ntmp.p = vtmp;
				ntmp.tmp = 0;
				calstk.push(ntmp);
			}
			i = i + ll - 1;
		}
	}
	if (calstk.size() > 1)
	{
		stkerr();
		return VARIABLE();
	}
	if (calstk.empty()) return VARIABLE();
	ntmp = calstk.top();
	calstk.pop();
	return *ntmp.p;
}