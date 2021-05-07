#pragma once
#ifndef MINCKEY_H
#define MINCKEY_H
#include "stdafx.h"
int iskey(string &scode, int pos);
int returning();
VARIABLE returningvar();
void disrun();
void enrun();
void mcifelse(string &ecode, int elsepos, int _depth, int limm);
char zhuanyi(char cc);
void mcin(string &ecode, int _depth, int limm);
void mcout(string &ecode, int _depth, int limm);
void mcwhile(string &ecode, int _depth, int limm);
void analize(string &ecode, int _depth, int limm);

#endif