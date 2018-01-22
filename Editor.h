#ifndef __EDITOR_H__
#define __EDITOR_H__

#include <cstdio>

void readFile(const char *input, char ***beg, char ***end);

void writeFile(const char *file, char **p);

void addLine(const char *input, char ***beg, char ***end);

void endEdit(char **p);

#endif
