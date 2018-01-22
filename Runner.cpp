//#include <iostream>

#include <cstdlib>
#include <cstdio>
#include <cstring>

#include "FileTool.h"
#include "Editor.h"

/*
 *	needs to take in 3 param;
 *	file name, beg pointer, end pointer
 */

	char **beg;
	char **cur;
	char **end;

void read(const char *file, char ***beg, char ***end)
{
	// readFile (char *file, char ***beg, char ***end)
	readFile(file, beg, end);
}

void add(const char *input, char ***beg, char ***end)
{
	addLine(input, beg, end);
	++cur;
//	printf("beg: %s, end: %s", **beg, **end);	
}

void write(const char *file, char ***p)
{
	writeFile(file, *p);
}

int main(int argc, char **argv)
{

	if (argc != 2)
	{
		fprintf(stderr, "%s usage: <file name>\n", argv[0]);
		return 1;
	}

	printf("Enter a command: \n");

	read(argv[1], &beg, &end);
	
//	printf("beg: %s, end: %s", *beg, *end);	

	char buf[3];	
	char linebuf[100];
	buf[2] = '\0';
		
	while(strncmp(fgets(buf, sizeof(buf), stdin), "q", 1))
	{
		if (!strncmp(buf, "i", 1))
		{
			printf("Enter a line to insert: \n");
			fgets(linebuf, sizeof(linebuf), stdin);			

			add(linebuf, &beg, &end);
		}
		if (!strncmp(buf, "c", 1))
		{
			printf("%s", *cur);
		}

		if (!strncmp(buf, "v", 1))
		{
			if (cur < end)
				++cur;

		}
		if (!strncmp(buf, "^", 1))
		{
			if (cur > beg)
				--cur;
		}
	
		if (!strncmp(buf, "p", 1))
		{
			char **tmp = beg;
			while (tmp != end)
				printf("%s", *tmp++);
		}

		printf("Enter a command: \n");
	}	

	write(argv[1], &beg);

	printf("Session ended.\n");
}
