#pragma once
#ifndef MINCFILE_H
#define MINCFILE_H
void setreslist();
int inreslist(string &_name);
void filefail(const char* _fname);
void quotfail(int _line);
void bracefail();
void khfail();
void nomain();
void deffail(int _t, int _line);
void reservedid();
void frepeat(string fname);
void emptyfun(string fname, int listn, int *typelist);
void stkerr();

#endif
