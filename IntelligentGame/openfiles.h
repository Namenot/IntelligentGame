#pragma once
#ifndef _OPENFILESH_
#define _OPENFILESH_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <CL/cl.h>


#define MAX_SOURCE_SIZE (0x100000)



int openfiles(int *output, const char *filename) // filename //functionname
{
	//open th wanted file
	int length;
	char *str;

	FILE * fp;
	fp = fopen(filename, "r");

	//figure out the files length
	fseek(fp, 0L, SEEK_END);
	length = ftell(fp);
	fseek(fp, 0L, SEEK_SET);
	rewind(fp);

	//correct the given length
	length--;

	//create 3 vars
	char c;
	str = (char *)calloc(length, sizeof(char));   //the second one serves as a buffer to change the single letters of the file to chars
	int i = 0;	  //serves as a counter

				  //every letter is read in written into the string "str" as char
	while ((c = fgetc(fp)) != EOF)
	{
		str[i] = c;
		i++;
	}
	fclose(fp); //close the file properly


	int filecontent = getlength(filename); // infos
	if (filecontent <= 0) {
		printf("File empty, size = %i\n", length);
		abort();
	}


	int counter = 0;
	int pos = 0;
	int var;
	while (counter <= length - 2)
	{
		if (str[counter] != ' ')
		{
			var = str[counter] - '0';
			output[pos] = output[pos] * 10 + var;//wtf


		}
		else {
			pos++;
			output[pos] = 0;
		}

		counter++;
	}
	return pos; // return length of the array ptr
}

int getlength(const char * filename)
{
	//open file
	FILE * fp;
	fp = fopen(filename, "r");

	if (!fp)
	{
		fprintf(stderr, "<Error> : Failed to load the length file\n");
		system("PAUSE");
		exit(1);
	}

	//define var for the length of the file
	int length;

	//get the length of the file
	fseek(fp, 0L, SEEK_END);
	length = ftell(fp);
	fseek(fp, 0L, SEEK_SET);
	rewind(fp);

	//correct the length and close the file
	length--;
	fclose(fp);
	return length;
}

void freemem(int *ptr, int length)//needs to know the length of the file
{

	while (length != 0)
	{
		ptr[length - 1] = 0;
		length--;
	}

}

void save(int* data, const char *filename, int length)
{

	FILE *fp;
	fp = fopen(filename, "w");
	if (fp == NULL)
	{
		printf("<Error> opening File : %c !\n", filename);
		exit(1);
	}
	int i = 0;

	while (i <= length) {
		fprintf(fp, "%i ", data[i]);
		i++;
	}
	fclose(fp);


}
#endif
