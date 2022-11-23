#ifndef __SIMULATION_H
#define __SIMULATION_H

#include <stdio.h>
#include <stdlib.h>

/*----- structure definition -------------------------------------------------*/

struct simStruct
{
    int timeTaken; /* Time taken for simulation to run. */
    int totalCarsL; /* The number of vehicles that passed through the traffic lights. */
    float averageWaitL; /* The average waiting time. */
    int maxWaitL; /* The maximum waiting time. */
    int clearTimeL; /* The time taken to clear the queue once vehicles have stopped arriving. */
    int totalCarsR; /* The number of vehicles that passed through the traffic lights. */
    float averageWaitR; /* The average waiting time. */
    int maxWaitR; /* The maximum waiting time. */
    int clearTimeR; /* The time taken to clear the queue once vehicles have stopped arriving. */
};
typedef struct simStruct SIMULATION;

/*----- function prototypes --------------------------------------------------*/

extern void printResults (SIMULATION *);

#endif
