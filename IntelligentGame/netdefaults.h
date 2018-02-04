#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <CL/cl.h>

#include "netcore.h"


void blackBox(double *layer1, double *layer2, FILE *weights)
{

  double *weight; // malloc size

  getNet(weights, weight);

  execNet(layer1, weight);
  execNet(layer2, weight);

  hebb(layer1, layer2, weight);

  /*
  - get the weights of the connections between the outputlayers (rdm generated)
  - use hebb'sch learning method to train them
  */

}

void looseNet()
{}

void defaultNet(FILE *conf, FILE *net)
{

  int    *config, *interp, i; //malloc size
  double *network, *layer, *weights;    //malloc size

  getConfig(conf, config );
  getNet   (net , network);

  InterpretConfig(config, 0      , interp);
  getLayer       (interp, network, layer );

  i = 0;

  while(i < interp[0]-1)
  {

    ++i;

    InterpretConfig(config, i      , interp );
    getLayer       (interp, network, weights);
    execNet        (layer , weights, layer  );

  }



}

void looseLayers()
{}
