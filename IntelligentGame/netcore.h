
#define GLEW_STATIC
#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <CL/cl.h>

#include "openfiles.h"
#include "matrices.h"
#include "sigmoid.h"


void CHRtoFLOAT(char *in, float *out)
{
	int i, sidecounter;
	float num;

	sidecounter = 0;
	num = 0;

	for (i = 0; in[i] != '\0'; i++)
		i++;

	for (i; in[i] != '\0'; --i)
	{
		if (in[i] != ' ')
			num = (num  + (in[i] - '0'))/10;
		else {
			out[sidecounter] = num;
			num = 0;
			sidecounter++;
		}
	}

}

void chartointarray(char *array, int *newarray)
{
	int i, num, sidecounter;
	
	num, sidecounter = 0;

	for (i = 0; array[i] != '\0'; i++)
	{
		if (array[i] != ' ')
			num = num * 10 + (array[i] - '0');
		else {
			newarray[sidecounter] = num;
			num = 0;
			sidecounter++;
		}
	}

}

void readfile(char *str, char *configbuffer)
{
	size_t lenconfig;
	FILE *conf;
	conf = fopen(str, "r");
	
	fseek(conf, 0L, SEEK_END);
	lenconfig = ftell(conf);
	fseek(conf, 0L, SEEK_SET);

	configbuffer = (char *)malloc(lenconfig + 1);
	configbuffer[lenconfig] = '\0';

	fread(configbuffer, sizeof(char), lenconfig, conf);
}

void Getconfig(char *filename, char *config)
{

	char *netconf, *newfilename;
	size_t len1, len2;

	netconf = "netconfig.txt";

	len1 = strlen(netconf);
	len2 = strlen((char *)filename);

	newfilename = (char *)malloc(len1 + len2 + 1);
	newfilename[len1 + len2] = '\0';

	strcat(newfilename, (char *)filename);
	strcat(newfilename, netconf);

	readfile(newfilename, config);
}

void interp(char *config, int layer, char *array)
{
	//vars
	char *filename, *suffix;
	int i, blank, num;
	
	//init
	suffix = ".layer";


	//exe
	//search for " " in the code (first 1 is free after that its only between layers)
	for (i = 0, blank = 0; config[i] != '\0'; i++)
	{
		
		if (config[i] == ' ')
			blank++;

		if (blank > layer + 1)
			break;
		
		if (blank == layer + 1)
		{
			num++;
			filename[num] = config[i+1];
		}
	
	}

	readfile(filename, array);

}

void GetandSplitcurrentlayer(int layer,float *m1, char *config)
{


	/*Database operator*/

	//vars
	int i;

	char *buffer, *configbuffer;

	interp(config, layer, buffer);
	
	CHRtoFLOAT(buffer, m1);
}

int netcore(const char filepath)
{
	/*given*/

	float *net, *layer, *weights;
	char *config;
	int *conf;

	int layernum, counter, size, bias, num, confignum, i;
	
	/*Bedingungen*/

	Getconfig((char *)filepath, config);
	chartointarray(config, conf);

	GetandSplitcurrentlayer(0, layer, config);

	/*einsetzen*/
	for (counter = 1; counter <= conf[0]; counter ++)
	{

		GetandSplitcurrentlayer(counter, weights, config);
		multiplyMatrix(layer, weights, layer); // multiply layer(n) * Weights(n) = layer(n+1) 
		sigmoid(layer);

	}
	
	return 0;
}

// neue Funktionen (Update)

//read the Config - File into an int array
void getConfig(FILE *config, int *conf)
{
	StrInt(config, conf); 
} 


//read the Main Network - File into an double array
void getNet(FILE *network, double *net)
{
	StrDouble(network, net);
}


//interpret the Config (layer amount, layer size, etc...)
void InterpretConfig()
{

}


//read one layer into an double array
void getLayer(int *conf, double* net, double* layer, int num)
{



}


//execute the Network 
void execNet(double *layer, double *weights)
{
	multiplyMatrix(layer, weights, layer);
}

//finish StrFloat in openfiles!!

/*
TODO:
	 
	 - Blackbox system
	 - Input system 
	 - Lernalgorythmen (Hebb'sche, Delta, Backpropagation, competative)

*/

/*
---------------------------
netconfig :

1: layers
return
{
1: filename of layer (every layer, except layer 0, is noted as weights not actionpotential)
} while n <= layers
---------------------------
*/