
#define GLEW_STATIC
#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <CL/cl.h>

#include "openfiles.h"
#include "matrices.h"

//read the Config - File into an int array
void getConfig(FILE *config, int *conf){
	StrInt(config, conf);
}


//read the Main Network - File into an double array
void getNet(FILE *network, double *net)
{
	StrDouble(network, net);
}


//interpret the Config (layer amount, layer size, etc...)
void InterpretConfig(int *conf, int num, int *interpretation)
{

    interpretation[0] = conf[0					]; //amount of layers
    interpretation[1] = conf[num * 2 - 1]; //startingpointy of Layer// num starts at 1
    interpretation[2] = conf[num * 2    ]; //endpoint of the Layer
    interpretation[3] = interpretation[2] - interpretation[1]; //size of the layer / weights

}


//read one layer into an double array
void getLayer(int *confinterpretation, double *net, double *weights)
{

    int i;

    weights[0] = confinterpretation[3];

    for (i = 1; i <= confinterpretation[3]; ++i)
    {

        weights[i] = net[confinterpretation[1] + i];

    }

}


//execute the Network
void execNet(double *layer, double *weights)
{
	multiplyMatrix(layer, weights, layer);
}

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
