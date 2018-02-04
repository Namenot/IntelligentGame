#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>


//check whether a file exists
int isFile(char *filename)
{

	FILE *fp;
	fp = fopen(filename, "r");

	if (!fp)
	{
		fclose(fp);
		return 0;
	}
	fclose(fp);
	return 1;

}

int isFolder(char *path)
{
	DIR *dir = opendir(path);
	if (dir)
	{
		return 1;
		closedir(dir);
	}
	else
	{
		return 0;
	}
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
