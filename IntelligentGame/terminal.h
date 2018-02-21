#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

#include "utilities.h"
#include "openfiles.h"

int set(char *parameter)
{

	int IoN;

	char net[] = "n";
	char inp[] = "i";

	if (strcmp(inp, parameter) == 0)
	{
		IoN = 1;
	}
	else if (strcmp(net, parameter) == 0)
	{
		IoN = 0;
	}else if(parameter == NULL)
	{
		printf("Help\n");
	}
	else
	{
		checkErr(0, "<Err> Unknown parameter in set()");
		IoN = 2;
	}

	return IoN;
}

int ls(char *path)
{
	DIR *dir = opendir(path);
	struct dirent *ent;
	int testcount = 0;

	if (dir) {

		while ((ent = readdir(dir)) != NULL)
		{
			if (testcount >= 2)
			{
				printf("<%i> %s\n", testcount - 1, ent->d_name);//check this part
			}
			testcount++;
		}

		closedir(dir);
	}
	else
	{
		return 0;
	}
	return 1;
}


int handlecmds(char *command, char *net, char *input, char *currentpath)
{

	//split string into command parameter and path
	int ret;
	int cdtrue;
	char *path;
	char *newcmd;
	char *parameter;

	//split chars
	const char c[] = " ";
	char *token;
	int count = 0;

	while (token)
	{
		switch (count)
		{
		case 0:
			newcmd = strtok(command, c);

		case 1:
			path = strtok(NULL, c);

		case 2:
			parameter = strtok(NULL, c);
		}
		count++;
		token = strtok(NULL, c);
	}

	if(path == NULL)
	{
		path = currentpath;
	}
	//check whether file or Folder exists
	ret = 0;
	ret = checkErr(isFile(path), "");
	cdtrue = checkErr(isFolder(path), "");

	if (ret == 0 && cdtrue == 0)
	{
		printf("<Err> given path neither points to a File nor a Folder\n");
	}


	char strset[5] = "set\0";
	char strls[4] = "ls\0";
	char strcd[4] = "cd\0";
	char strexec[6] = "exec\0";

	if (path == NULL)
	{
		printf("<Fatal Error> no path given\n");
	}
	else{

		//exec the given command
		if (strcmp(strset, newcmd) == 0)
		{
			ret = set(&parameter[0]);
			printf("parameter : %i \n", ret);
			if (ret == 0)
			{
				strcpy(net, path);

			}
			else if (ret == 1)
			{
				strcpy(input, path);
			}

		}
		else if (strcmp(strls, newcmd) == 0)
		{
			ret = ls(path);
		}
		else if (strcmp(strcd, newcmd) == 0)
		{
			if (cdtrue == 1)
			{
				strcpy(currentpath, path);
			}

		}
		else if (strcmp(strexec, newcmd) == 0)
		{
			return 1;
		}
	}
	return 0;
}

int terminal(char *inputpath, char *netpath)
{

	int i = 0;
	int cms;

	char currentpath[255];
	char defaultpath[12] = "/home/aaron";
	char command[255];

	char netbuffer[255];
	char inpbuffer[255];

	currentpath[0] = 0;
	command[0] = 0;
	netbuffer[0] = 0;
	inpbuffer[0] = 0;

	memcpy(currentpath, defaultpath, 45);

	while (i == 0)
	{

		printf("<%s> ", currentpath);
		scanf(" %[^\n]", command);

		command[strlen(command)] = '\0';
		fflush(stdin);

		cms = handlecmds(command, netbuffer, inpbuffer, currentpath);

		if (cms == 1)
		{
			strcpy(netpath, netbuffer);
			strcpy(inputpath, inpbuffer);
			i = 1;
		}
	}
	return 0;
}
