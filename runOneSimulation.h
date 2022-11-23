#ifndef __RUNONESIMULATION_H
#define __RUNONESIMULATION_H

#include <stdio.h>
#include <stdlib.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <queue.h>
#include <simulation.h>

/*----- function prototypes --------------------------------------------------*/

extern SIMULATION runOneSimulation(float, float, int, int, gsl_rng *);

#endif

