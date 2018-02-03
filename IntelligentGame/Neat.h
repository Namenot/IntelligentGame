#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <CL/cl.h>


float sigmoid(double x)
{
	//vars
	double val, temp1, temp2, temp3;
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

void fittness(double *output, double *expected, int *fittnesslvl)
{

	int score, i;

// einfache Prozentrechnung (auf basis 1000 oder mehr) machen

    for(i = 1; i < expected[0]; ++i)
    {

    }

	fittnesslvl[0]++;
	fittnesslvl[fittnesslvl[0]] = score;
}

void compare(int *fittnesslvl, int *winner)
{
    int i, strongest, secondplace, netstr, netsec;

    strongest   = fittnesslvl[1];
    netstr      = 1;

    secondplace = fittnesslvl[2];
    netsec      = 2;

    for(i = 1; i < fittnesslvl[0]; ++i)
    {

        if(fittnesslvl[i] >= strongest)
        {
            secondplace = strongest;
            strongest   = fittnesslvl[i];
            netsec      = netstr;
            netstr      = i;
        }
        else if(fittnesslvl[i] >= secondplace && fittnesslvl[i] <= strongest)
        {
            secondplace = fittnesslvl[i];
            netsec      = i;
        }

    }
    winner[0] = netstr;
    winner[1] = netsec;

}

void mutate(double *net){}

void breeding(double *net1, double *net2) {}

/*
rewrite netcore:
	- netcore musst take three variables (float * input, float *net, float *output)
*/
