#ifndef __FILETOOL_H__
#define __FILETOOL_H__

#include <cstdio>

class FileTool
{
	public:
		FileTool(const char *fileName, const char *mode);
	
		~FileTool();

		FileTool(const FileTool& ft);		

		FileTool& operator=(const FileTool& ft);

//		FILE *file();

	private: 
	
		FILE *file;
		
		const char *fileName;

		const char *mode;
};

#endif
