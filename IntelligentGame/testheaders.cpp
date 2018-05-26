#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "terminal.h"

//opencl
#include <CL/cl.h>

int test(int argc, char**argv)
{
	cl_int err;
	cl_uint numPlatforms;

	err = clGetPlatformIDs(0, NULL, &numPlatforms);
	if (CL_SUCCESS == err)
		printf("\nDetected OpenCL platforms: %d", numPlatforms);
	else
		printf("\nError calling clGetPlatformIDs. Error code: %d", err);

	return 0;
}

int main()
{

	char *inp = (char *)malloc (255 * sizeof(char *));
	char *net = (char *)malloc (255 * sizeof(char *));

	terminal(inp, net);

	printf("%s\n", inp);
	printf("%s\n", net);


	printf("new instance of the program wich is nessesery ");
	printf("Test1\n");
	return 0;
}

//TODO : set() crashing the whole thing
//				- parameter is the 3rd argument. set() crashes
//				  if it cant find parameter and / or file arg
//					strtk() splits *str in 3 token -> fails with too few args
//TODO : solution fot the above part ..
//				- devide it only in two token
//				- hand in always the second parameter
//				- but make sure its never longer than one char
