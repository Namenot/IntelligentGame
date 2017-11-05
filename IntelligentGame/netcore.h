
#define GLEW_STATIC
#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <CL/cl.h>

#include "openfiles.h"
#include "matrices.h"

void splitfiles(const char filename)
{

	int filesize = getlength(&filename);
	int netconfsize;
	int netsize;

	int *buff = malloc; //hier noch mallocen

	netconfsize = 1 + buff[0];
	netsize		= filesize - netconfsize;

	int *netconf = malloc;
	int *net	 = malloc;
	
	int i;

	//write to netconf
	for (i = 0; i < netconfsize; i++)
	{
		netconf[i] = buff[i];
	}

	//write to net
	for (i = 0; i < netsize; i++)
	{
		net[i] = buff[i + netconfsize];
	}


}

int netcore(int *net, int *netconf)
{

	int layers = netconf[0];
	int currentlayer[2]; //size of layer

	int layer;

	for ()
	{
		/*
		*set currentlayer[0] and currentlayer[1]
		* int m[currentlayer[0]+2]; fill(m, currentlayer[0], 1);
		* m[0] = currentlayer[0];
		* multiply  net[layer] with m[] = c
		* add net[currentlayer[1]] += c
		*/


	}

	return 0;
}

//finish the two functions first

/*
TODO:
	 
	 - Blackbox system
	 - Input system 
	 - Lernalgorythmen (Hebb'sche, Delta, Backpropagation, competative)

*/