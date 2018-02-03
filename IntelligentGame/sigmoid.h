#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <CL/cl.h>

#define MAX_SOURCE_SIZE (0x100000)

void sigmoid(double *m1)
{

	FILE *prog;
	prog = fopen("sigmoid.cl", "r");

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
	cl_mem mat;

	mat = clCreateBuffer(context, CL_MEM_COPY_HOST_PTR, m1[0] * m1[1]* sizeof(double*), m1, &ret);


	/*
	end memory Objekts
	*/

	cl_program program = clCreateProgramWithSource(context, 1, (const char **)&source_str, (const size_t *)&source_size, &ret);
	ret = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);

	cl_kernel kernel = clCreateKernel(program, "Sigmoid", &ret);

	/*
	Kernel Arguments
	*/

	ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&mat);

	/*
	end Kernel Arguments
	*/

	size_t local_item_size = 1;
	size_t global_item_size = m1[1];


	ret = clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL, &global_item_size, &local_item_size, 0, NULL, NULL);

	ret = clEnqueueReadBuffer(command_queue, mat, CL_TRUE, 0, m1[1] * sizeof(double *), m1, 0, NULL, NULL);

	ret = clFlush(command_queue);
	ret = clFinish(command_queue);

	ret = clReleaseKernel(kernel);
	ret = clReleaseProgram(program);

	ret = clReleaseMemObject(mat);

	ret = clReleaseCommandQueue(command_queue);
	ret = clReleaseContext(context);
}
