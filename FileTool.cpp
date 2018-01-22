#include <cstdio>

#include "FileTool.h"

FileTool::FileTool(const char *fileName, const char *mode)
{
	file = fopen(fileName, mode);
	this->fileName = fileName;
	this->mode = mode;
	
//	printf("HI\n");
}

FileTool::~FileTool()
{
	fclose(file);

//	printf("Bye\n");
}

FileTool::FileTool(const FileTool& ft)
{
	file = fopen(ft.fileName, ft.mode);
	
	this->fileName = ft.fileName;
	this->mode = ft.mode;
}

FileTool& FileTool::operator=(const FileTool& ft)
{
	if (this == &ft)
		return *this;
	
	fclose(file);

	file = fopen(ft.fileName, ft.mode);

	this->fileName = ft.fileName;
	this->mode = ft.mode;
	
	return *this;
}
/*
FILE * FileTool::file()
{
	return file;
}
*/

