#ifndef __RUNSIMULATIONS_H
#define __RUNSIMULATIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <queue.h>
#include <simulation.h>
#include <runOneSimulation.h>

/*----- function prototypes --------------------------------------------------*/

extern int runSimulations(float, float, int, int);

#endif
