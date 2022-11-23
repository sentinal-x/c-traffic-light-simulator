#include <simulation.h>

/*----- simulation structure functions ------------------------------------------------------*/

extern void printResults(SIMULATION * sim) {
    printf("Time taken: ");
    printf("%d\n", sim->timeTaken);
    printf("Total cars passed on left: ");
    printf("%d\n", sim->totalCarsL);
    printf("Average wait time on left: ");
    printf("%f\n", sim->averageWaitL);
    printf("Max wait time on left: ");
    printf("%d\n", sim->maxWaitL);
    printf("Time taken to clear queue on left: ");
    printf("%d\n", sim->clearTimeL);
    printf("Total cars passed on right: ");
    printf("%d\n", sim->totalCarsR);
    printf("Average wait time on right: ");
    printf("%f\n", sim->averageWaitR);
    printf("Max wait time on right: ");
    printf("%d\n", sim->maxWaitR);
    printf("Time taken to clear queue on right: ");
    printf("%d\n", sim->clearTimeR);
}
