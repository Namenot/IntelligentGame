#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <CL/cl.h>

#include "netcore.h"


void blackbox(double *layer1, double *layer2, FILE *weights)
{

  double *weight; // set size

  getNet(weights, weight);

  execNet(layer1, weight);
  execNet(layer2, weight);

  hebb(layer1, layer2, weights);

  /*
  - get the weights of the connections between the outputlayers (rdm generated)
  - use hebb'sch learning method to train em
  */

}

void loosenet()
{}

void defaultnet()
{}
