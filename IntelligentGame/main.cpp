
#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <errno.h>

#include <string.h>
#include <math.h>
#include <CL/cl.h>

#include <stdio.h>
#include <dirent.h>
#include <unistd.h>

#include "backend.h"
#include "frontend.h"

#include "matrices.h"
#include "sigmoid.h"

#include "netdefaults.h"
#include "netcore.h"
#include "rules.h"
#include "Neat.h"

#include "terminal.h"
#include "utilities.h"
#include "openfiles.h"
