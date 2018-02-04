#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <CL/cl.h>

#include "openfiles.h"
#include "matrices.h"

#define aconst 0.4

void hebb(double *l1, double *l2, double *ws)
{

  int i, n;

  i = l1[0] + 1;

  while(i != 0)
  {

    while(n != 0)
    {

      n = l2[0]+ 1;

      if(l1[i] > aconst)
      {
        if(l2[n] > aconst)
        {
          //increase drastic
        }else
        {
          //decrease drastic
        }
      }else
      {
        if(l2[n] > aconst)
        {
          //decrease drastic
        }else
        {
          //increase a little
        }
      }
      --n;
    }
    --i;
  }

}

void delta()
{}

void comp()
{}

void bprop()
{}
