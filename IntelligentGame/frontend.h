#pragma once
#include <stdio.h>
#include <stdlib.h>

#include "utilities.h"
#include "openfiles.h"


int interface(char *Net, char *Input, int training)
{

	//create different vars

	//exec terminal

	//hand vars over to main-program (pointer


}

/*change interface to a small command-line Terminal:
- set 'file' -'operator' operators are 'i' (input) or 'n' (Network)
- cd 'path' opens a given directory
- ls list files of the currentpath
- exec will try to execute a network with the given informations*/

int mainThread(char *Net, char *Input, int training, int *output)
{

	if (Net[0] == "" and Input[0] == "" and training != 0 and training != 1) //ugly pls change
	{
		interface(char *Net, char *Input, int training);

	}
	else if (output[0] != 0)
	{
		organDump(output);

	}

	return 1;

}
