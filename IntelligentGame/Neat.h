#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <CL/cl.h>

int createNet(FILE *kern, char *Net)
{


	if (!kern)
	{
		fprintf(stderr, "<Error> : Failed to load the N.E.A.T. Kernel");
		system("PAUSE");
		exit(1);
	}

	int Netarraylen;

	if (Net != NULL)
	{
		Netarraylen = getlength((const char *)Net);
		int *Netarray[Netarraylen];
		openfiles(Netarray, (const char *)Net);
	}
	else {
		Netarraylen = 0;
	}


	char *source_str;
	size_t source_size;

	source_str = (char*)malloc(MAX_SOURCE_SIZE);
	source_size = fread(source_str, 1, MAX_SOURCE_SIZE, kern);

	cl_platform_id platform_id = NULL;
	cl_device_id device_id = NULL;

	cl_uint ret_num_devices;
	cl_uint ret_num_platforms;

	cl_int ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);
	ret = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_ALL, 1, &device_id, &ret_num_devices);

	cl_context context = clCreateContext(NULL, 1, &device_id, NULL, NULL, &ret);

	cl_command_queue command_queue = clCreateCommandQueueWithProperties(context, device_id, 0, &ret);

	//mem_objekte
	cl_mem Netinfos = clCreateBuffer(context, CL_MEM_READ_WRITE, getlength((const char *)Net) * sizeof(int *), Netarray, &ret);
	cl_mem output = clCreateBuffer(context, CL_MEM_READ_WRITE, *sizeof(int *), , &ret); //hier vorher noch ne output variable definieren


	cl_program program = clCreateProgramWithSource(context, 1, (const char **)&source_str, (const size_t *)&source_size, &ret);

	ret = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);

	cl_kernel kernel = clCreateKernel(program, "Neat", &ret);

	ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&Netinfos);

	size_t global_item_size;
	size_t local_item_size;

	global_item_size = ; //check here
	local_item_size = global_item_size;

	ret = clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL, &global_item_size, &local_item_size, 0, NULL, NULL);

	ret = clEnqueueReadBuffer(command_queue, info, CL_TRUE, 0, size * sizeof(int *), infos, 0, NULL, NULL);


	ret = clFlush(command_queue);
	ret = clFinish(command_queue);
	ret = clReleaseKernel(kernel);
	ret = clReleaseProgram(program);
	ret = clReleaseMemObject();
	ret = clReleaseCommandQueue(command_queue);
	ret = clReleaseContext(context);



}
