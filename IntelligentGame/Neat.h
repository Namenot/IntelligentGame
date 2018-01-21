#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <CL/cl.h>


float sigmoid(float x)
{
	//vars
	float val, temp1, temp2, temp3;
	int e;

	//init
	e = 2.71828182845904550;

	temp1 = pow(e, x); // temp1 = e^(x) 
	temp2 = 1 / temp1; // temp2 = e^(-x)
	temp3 = 1 + temp2; // temp3 = e^(-x) + 1

	val = 1 / (temp3); // val = 1 / (e^(-x) + 1) ==> Sigmoid
	
	//exec
	return val;
}

void fittness(float *output, float *expected, int *fittnesslvl)
{

	int score;



	fittnesslvl[0]++;
	fittnesslvl[fittnesslvl[0]] = score;
}

void compare(int *fittnesslvl){}

void mutate(float *net){}

void breeding(float *net1, float *net2) {}

/*
rewrite netcore:
	- netcore musst take three variables (float * input, float *net, float *output)
*/