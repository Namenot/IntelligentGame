
#define GLEW_STATIC
#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <CL/cl.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <windows.h>

#include "matrices.h"

int main(int argc, char **argv)
{

	int m2[] = { 3, 2,
		1, 3, 
		4, 6,
		7, 9};

	int m1[] = {2, 2,
		1, 7,
		3, 4, };

	int out[11];

	int *p1 = m1;
	int *p2 = m2;
	int *p3 = out;

	multiplyMatrix(p1, p2, p3);

	int i = 0;
	int p = 0;

	while (i < (p3[0]*p3[1]))
	{
		p++;

		printf("| %i |", p3[i+2]);
		if (p == 2)
		{
			printf("\n");
			p = 0;
		}

		i++;
	}

	system("Pause");

}
