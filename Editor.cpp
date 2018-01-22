#include <cstdlib>
#include <cstdio>
#include <cstring>

static int num_lines = 0;

/*
 *	File protocol:
 *		beginning of file has size int bytes containing number of lines in the file
 *		beginning of each line has size int bytes containing number of characters/size of each line
 *	
 */

/*
 * Reads file size (in lines) into memory, mallocs that much space for char *s
 * Then, reads line size and mallocs that size in memory for that specific line
 * 
 * Possible struct for each "line":

 struct line
 {
 char *data;
 int deleted;

// won't need pointers to next and prev bc data will be allocated contiguously in an array
}

~version 2~

 */
void readFile(const char *file, char ***beg, char ***end)
{

	FILE *input = fopen(file, "a+");

	// find beginning of file
//	fseek(input, 0, SEEK_SET);	

	// reads in file size from file
//	int file_size;
	fread(&num_lines, sizeof(int), 1, input);

	int file_size = num_lines;	

//	printf("FILESIZE: %d\n", file_size);

	//mallocs array to hold each line
	char **lines = 0;

	if (num_lines)
		lines = (char **) malloc(sizeof(char *) * file_size);

	// terminate lines with null pointer for traversing later
	//	lines[file_size] = 0;

	// for each line, reads size from file, mallocs that size, copies string into that area
	for (int i=0; i<file_size; ++i)
	{
		// read line size
		int line_size;
		fread(&line_size, sizeof(int), 1, input);

		// malloc size of line in memory
		lines[i] = (char *) malloc(sizeof(char) * (line_size + 1));

		// read line into buffer
		char buf[line_size + 1];
		fread(buf, line_size, 1, input);
		buf[line_size] = '\0';

		// copy from buffer into memory
		strcpy(lines[i], buf);
//		printf("LINE READ: %s\n", lines[i]);
	}

	fclose(input);

//	return lines;

	*beg = lines;
	if ( file_size )
		*end = lines + (file_size);
}

/*
 * takes in char * to write to file. Must keep running total of lines and write that to the beginning of the file
 * (would end be easier?)
 * 
 * this function needs to add new char * to the end of the allocated memory
 * allocates new memory, copies data from old space to new space, frees old space, returns new pointer
 */
void addLine(const char *input, char ***beg, char ***end)
{
	++num_lines;

	// allocates new memory
	char **np;
	np = (char **) malloc(sizeof(char *) * num_lines);

	// copies old addresses into new space
	if (num_lines > 1)
		memcpy(np, *beg, sizeof(char *) * (num_lines - 1));

//	memset(np, 0, sizeof(char *) * num_lines);

	int len = strlen(input);

	np[num_lines-1] = (char *)malloc(sizeof(char *) * (len + 1));

	strcpy(np[num_lines-1], input);
//	printf("LINE ADDED: %s\n", np[num_lines-1]);

	// frees old space	
	if (*beg)
		free(*beg);

	*beg = np;
	*end = np + (num_lines);
}

/*
 * writes all of memory to the file
 *
 */
void writeFile(const char *file, char **p)
{
	FILE *fp = fopen(file, "r+");

	// write num_lines to file
	fwrite(&num_lines, sizeof(int), 1, fp);
	if (p)
	{
		for (int i=0; i < num_lines; ++i)
		{	
			int size = strlen(p[i]);
			fwrite(&size, sizeof(int), 1, fp);
			fwrite(p[i], size, 1, fp);
//			printf("LINE WRITTEN: %s\n", p[i]);
		}
		
		free(p);
	}
	fclose(fp);
}

void endEdit(char **p)
{
	free(p);
}
