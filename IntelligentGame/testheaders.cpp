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

	char *inp;
	char *net;

	terminal(inp, net);

	printf("%s\n", inp);
	printf("%s\n", net);

	return 0;
}
