#pragma once
#include <stdio.h>
#include <stdlib.h>

#include "utilities.h"

int exec(int netstate, char * filename)
{

	if (filename != NULL)
	{

		if (netstate == 0)
		{
			Netgenerator();
		}
		else if (netstate == 1)
		{
			loadNet();
		}
		else {
			checkErr(0, "<Err> No action is defined for 'netstate %i'\n", netstate);
		}

	}
	else {
		randomeNet();
	}
	return 0;
}
/*netstate can be 1 or 0
if netstate == 1 load an existing Net
else if netstate == 0 generate a new map form scratch based of given Informations*/
