#pragma once
#ifndef _OPENFILESH_
#define _OPENFILESH_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <CL/cl.h>
#include <math.h>

#define MAX_LEN 255
#define MAX_SOURCE_SIZE (0x100000)


int openfiles(int *output, FILE *fp) // filename //functionname
{
	int   i, words;
	char *lines, filename[MAX_LEN];
	int  *nums;

	words = WordAmound(fp);
	lines = (char*)malloc(words * sizeof(char));
	nums  = (int *)malloc(words * sizeof(int));

	StrInt(fp, words, nums);

	fclose(fp);

	for (i = 0; i < words; ++i)
		printf("%i ", nums[i]);

	return words; // return length of the array ptr
}

int getlength(FILE *fp)
{

	//define var for the length of the file
	int length;

	if (!fp)
	{
		fprintf(stderr, "<Error> : Failed to load the length file\n");
		system("PAUSE");
		exit(1);
	}


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

void StrInt(FILE *fp, int *arr)
{
	int i, c, num;
	char ch;

	i   = 0;
	num = 0;
	c   = 0;

	rewind(fp);

	while ((ch = fgetc(fp)) != EOF){

		if (ch != ' ' && ch != '\n')
			num = num * 10 + (ch - '0');
		else{
			arr[c] = num;
			num    = 0;
			c++;
		}

	}
}

void StrDouble(FILE *fp, double *arr)
{

	int    c, count, num;
	char   ch;
	double buf;

	num = 0;
	c = 0;
	count = 1;

	rewind(fp);

	while (ch = fgetc(fp)) {

		if (ch == '.')
			count = 0;


		if (ch != ' ' && ch != '\n' && ch != '.' && ch != EOF) {

			count++;
			num = num * 10 + (ch - '0');

		}
		else if (ch == ' ' || ch == '\n' || ch == EOF) {

			buf = num / pow(10, count);
			arr[c] = buf;
			num = 0;
			count = 0;
			c++;
		}

		if (ch == EOF)
			break;

	}
}

int WordAmound(FILE *fp)
{
	int  words = 0;
	char ch;

	while ((ch = fgetc(fp)) != EOF)
	{

		if (ch == '\n' || ch == ' ')
			words++;
	}

	return ++words;
}
#endif
