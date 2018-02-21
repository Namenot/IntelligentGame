
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <errno.h>

//check whether a file exists
int isFile(char *filename)
{

	int is;
 	is = 0;

	if (access( filename, F_OK ) != -1)
	{
		is = 1;
	}

	return is;

}

int isFolder(char *path)
{

	DIR *dir = opendir(path);

	int is;
	is = 0;

	if (dir)
	{
		is = 1;
	}else if(ENOENT == errno)
	{
		is = 0;
	}

	closedir(dir);
	return is;
}

//dump an error with the representing error msg
int checkErr(int err, char *errmsg)
{

	if (err == 0)
	{
		printf("%s\n", errmsg);
		return 0;
	}
	return 1;
}
