#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <CL/cl.h>

#define MAX_SOURCE_SIZE (0x100000)

int sortsys(float *m1, float *m2)//-----------------------------------------------------------------------------------------------------------------------
{

	int ret;
	if (m1[1] == m2[0])
	{
		ret =  1;
	}
	else if (m1[0] == m2[1])
	{
		ret =  2;
	}
	else {
		ret = 0;
	}

	return ret;
}

void fill(float *C, int size, int num)
{
	int i;

	for (i = 0; size+2 > i; i++)
	{
		C[i] = num;
	}

}

int getGlobalitemsize(int min)
{
	int newmin = min;
	float testmin = min;

	while (newmin / 8  != testmin / 8 )
	{
		newmin++;
		testmin++;
	}
	return newmin;
}

void checkCLMeMError(cl_int ret)
{
	
	printf("\n<FATAL-ERROR> UNABLE TO WRITE TO MEMORY:\n\n");

	switch (ret)
	{
	case CL_INVALID_CONTEXT:
		printf("	CL_INVALID_CONTEXT\n");

	case CL_INVALID_VALUE:
		printf("	CL_INVALID_VALUE\n");

	case CL_INVALID_BUFFER_SIZE:
		printf("	CL_INVALID_BUFFER_SIZE\n");

	case CL_INVALID_HOST_PTR:
		printf("	CL_INVALID_HOST_PTR\n");

	case CL_MEM_OBJECT_ALLOCATION_FAILURE:
		printf("	CL_MEM_OBJECT_ALLOCATION_FAILURE\n");

	case CL_OUT_OF_HOST_MEMORY:
		printf("	CL_OUT_OF_HOST_MEMORY\n");

	default:
		printf("\n");
	}

}

void MatrixOP(float *matrix, float *matrix2, float *output, FILE* prog, int *sizes, size_t *global_item_size, int dim)//----------------------------------------------------------------------------------------------
{

	int size1 = sizes[0];
	int size2 = sizes[1];
	int size3 = sizes[2];

	char *source_str;
	size_t source_size;

	source_str = (char *)malloc(MAX_SOURCE_SIZE);
	source_size = fread(source_str, 1, MAX_SOURCE_SIZE, prog);

	cl_platform_id platform_id = NULL;
	cl_device_id device_id = NULL;

	cl_uint ret_num_devices;
	cl_uint ret_num_platforms;

	cl_int ret;
	ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);
	ret = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_GPU, 1, &device_id, &ret_num_devices);

	cl_context context = clCreateContext(NULL, 1, &device_id, NULL, NULL, &ret);
	cl_command_queue command_queue = clCreateCommandQueueWithProperties(context, device_id, 0, &ret);

	/*
	memory Objekts
	*/
	cl_mem mat1;
	cl_mem mat2;
	cl_mem out;

	mat1 = clCreateBuffer(context, CL_MEM_USE_HOST_PTR, size1 * sizeof(int *), matrix, &ret);
	mat2 = clCreateBuffer(context, CL_MEM_USE_HOST_PTR, size2 * sizeof(int *), matrix2, &ret);
	out = clCreateBuffer(context, CL_MEM_COPY_HOST_PTR, size3 * sizeof(int *), output, &ret);

	if (!mat1 || !mat2 || !out)
	{
		checkCLMeMError(ret);
	}

	/*
	end memory Objekts
	*/

	cl_program program = clCreateProgramWithSource(context, 1, (const char **)&source_str, (const size_t *)&source_size, &ret);
	ret = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);

	cl_kernel kernel = clCreateKernel(program, "MatrixOp", &ret);
	
	/*
	Kernel Arguments
	*/

	ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&mat1);
	ret = clSetKernelArg(kernel, 1, sizeof(cl_mem), (void *)&mat2);
	ret = clSetKernelArg(kernel, 2, sizeof(cl_mem), (void *)&out);
	
	/*
	end Kernel Arguments
	*/

	size_t local_item_size[2];
	if (dim == 1)
	{
		local_item_size[0] = 16;
		local_item_size[1] = 8;
	}
	else
	{
		local_item_size[0] = global_item_size[0]; // hier noch nachgucken / ueberlegen
		local_item_size[1] = 1;
	}

	ret = clEnqueueNDRangeKernel(command_queue, kernel, dim, NULL, global_item_size, local_item_size, 0, NULL, NULL);

	printf("size3 : %i\n", size3);
	printf("new size3 : %i\n", size3* sizeof(int *));
	ret = clEnqueueReadBuffer(command_queue, out, CL_TRUE, 0, size3 * sizeof(int *), output, 0, NULL, NULL);

	printf("?\n");

	ret = clFlush(command_queue);
	ret = clFinish(command_queue);

	ret = clReleaseKernel(kernel);
	ret = clReleaseProgram(program);

	ret = clReleaseMemObject(mat1);
	ret = clReleaseMemObject(mat2);
	ret = clReleaseMemObject(out);

	ret = clReleaseCommandQueue(command_queue);
	ret = clReleaseContext(context);
}


void addMatrix(float *m1, float *m2, float *out)
{
	int sizes = m1[0] * m2[1] + 2;

	int size[3];
	size[0] = sizes;
	size[1] = sizes;
	size[2] = sizes;
	
	fill(out, sizes, 0);

	out[0] = m1[0];
	out[1] = m2[1];

	int *size_ptr = size;

	FILE *add;
	add = fopen("add.cl", "r");

	if (!add)
	{
		printf("File not found! \nUnable to continue");
	}
	
	size_t global_item_size[1];
	global_item_size[0] = getGlobalitemsize(size[0]);

	MatrixOP(m1, m2, out, add, size_ptr, global_item_size, 1);


}

void multiplyMatrix(float *m1, float *m2, float *out)
{
	float *m1_ptr = NULL;
	float *m2_ptr = NULL;

	int size[3];
	size[0] = m1[0] * m1[1] + 2;
	size[1] = m2[0] * m2[1] + 2;
	
	/*
	sort the two matrices
	*/
	int sort = sortsys(m1, m2);

	if (sort != 0) {
		if (sort == 1)
		{
			size[2] = m1[0] * m2[1] + 2;
			printf("\n size[2]: %i\n\n", size[2]);
			fill(out, size[2], 0);

			out[0] = m1[0];
			out[1] = m2[1];

			m1_ptr = m1;
			m2_ptr = m2;

		}
		else if (sort == 2)
		{
			size[2] = m1[1] * m2[0] + 2;

			fill(out, size[2], 0);

			out[0] = m2[0];
			out[1] = m1[1];

			m1_ptr = m2;
			m2_ptr = m1;
		}
	}
	else
	{
		printf("<Err> Unable to multiply the given matrices");
		system("Pause");
		exit(1);
	}

	/*
	End sorting
	*/

	int *size_ptr;
	size_ptr = size;

	FILE* multi;
	multi = fopen("multiply.cl","r");
	//multi = fopen("test.cl", "r");

	if (!multi)
	{
		printf("File not found! \nUnable to continue");
	}

	size_t global_item_size[2];

	global_item_size[0] = getGlobalitemsize(m2[0]);
	global_item_size[1] = getGlobalitemsize(size[0]);
	
	printf("m1[0] = %.2f\n", m1[0]);

 	MatrixOP(m1_ptr, m2_ptr, out, multi, size_ptr, global_item_size, 2);


}
/*
matrix:

[0] = height (for e.g. 20)
[1] = width (for e.g. 30)
*/

