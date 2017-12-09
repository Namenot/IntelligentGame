
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

	float m1[] = { 4, 2,
		1, 7, 
		4, 6,
		7, 9,
		1, 7,
		};

	float m2[] = {2, 4,
		10, 7, 10, 7,
		3,  4,  3, 4};
	 
	float out[16];

	float *p1 = m1;
	float *p2 = m2;
	float *p3 = out;

	multiplyMatrix(p1, p2, p3);

	int i = 0;
	int p = 0;


	while (i < (p3[0]*p3[1]))
	{
		p++;

		printf("| %.1f |", p3[i+2]);
		if (p == p3[1])
		{
			printf("\n");
			p = 0;
		}

		i++;
	}

	system("Pause");

}
