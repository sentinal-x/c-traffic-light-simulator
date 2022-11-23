#include <runSimulations.h>

int runSimulations(float LeftQueueArrivalProbability, float RightQueueArrivalProbability, int LeftTrafficLightOnPeriod, int RightTrafficLightOnPeriod) {
    
    int ttcL = 0; /* total total cars from left */
    float tawL = 0.0; /* total average wait from left */
    int tmwL = 0; /* total max wait left */
    int tcsL = 0; /* total clearing time left */
    
    int ttcR = 0; /* total total cars from right */
    float tawR = 0.0; /* total average wait from right */
    int tmwR = 0; /* total max wait right */
    int tcsR = 0; /* total clearing time right */
    
    int i; /* i */
    int numberofsimulations = 100; /* number of simulations to run */
    
    SIMULATION onesim; /* SIMULATION for each sim */
    
    const gsl_rng_type *T;
    gsl_rng *r;
    /* create a random number generator */
    gsl_rng_env_setup();
    T = gsl_rng_default;
    r = gsl_rng_alloc(T);
    /* seed random number with current time*/
    gsl_rng_set(r,time(0));
    
    for(i=1;i<=numberofsimulations;i++) {
        /* run simulation */
        onesim = runOneSimulation(LeftQueueArrivalProbability, RightQueueArrivalProbability, LeftTrafficLightOnPeriod, RightTrafficLightOnPeriod, r);
        /* update totals */
        ttcL += onesim.totalCarsL;
        tawL = tawL + onesim.averageWaitL;
        tmwL += onesim.maxWaitL; 
        tcsL += onesim.clearTimeL;
        
        ttcR += onesim.totalCarsR;
        tawR = tawR + onesim.averageWaitR;
        tmwR += onesim.maxWaitR; 
        tcsR += onesim.clearTimeR;
    }
    
    /* calculate averages */
    float attcL = (float)ttcL/numberofsimulations;
    float atawL = tawL/numberofsimulations;
    float atmwL = (float)tmwL/numberofsimulations;
    float atcsL = (float)tcsL/numberofsimulations;
    float attcR = (float)ttcR/numberofsimulations;
    float atawR = tawR/numberofsimulations;
    float atmwR = (float)tmwR/numberofsimulations;
    float atcsR = (float)tcsR/numberofsimulations;
    
    /* send to stdout */
    fprintf(stdout, "Parameter values: \n");
    fprintf(stdout, "    from left: \n");
    fprintf(stdout, "        traffic arrival rate: %f\n", LeftQueueArrivalProbability);
    fprintf(stdout, "        traffic light period: %d\n", LeftTrafficLightOnPeriod);
    fprintf(stdout, "    from right: \n");
    fprintf(stdout, "        traffic arrival rate: %f\n", RightQueueArrivalProbability);
    fprintf(stdout, "        traffic light period: %d\n", RightTrafficLightOnPeriod);
    fprintf(stdout, "Results (averaged over %d runs): \n", numberofsimulations);
    fprintf(stdout, "    from left: \n");
    fprintf(stdout, "        number of vehicles: %f\n", attcL);
    fprintf(stdout, "        average waiting time: %f\n", atawL);
    fprintf(stdout, "        maximum waiting time: %f\n", atmwL);
    fprintf(stdout, "        clearance time: %f\n", atcsL);
    fprintf(stdout, "    from right: \n");
    fprintf(stdout, "        number of vehicles: %f\n", attcR);
    fprintf(stdout, "        average waiting time: %f\n", atawR);
    fprintf(stdout, "        maximum waiting time: %f\n", atmwR);
    fprintf(stdout, "        clearance time: %f\n", atcsR);
    
}

int main(int argc, char *argv[]) {

    if (argc == 5) {
        /* if user gives 4 values */

        /* assign them to respective variable */
        float LeftQueueArrivalProbability = atof(argv[1]);
        float RightQueueArrivalProbability = atof(argv[2]);
        int LeftTrafficLightOnPeriod = atof(argv[3]);
        int RightTrafficLightOnPeriod = atof(argv[4]);
        
        /* call runSimulations() */
        runSimulations(LeftQueueArrivalProbability, RightQueueArrivalProbability, LeftTrafficLightOnPeriod, RightTrafficLightOnPeriod);
        
    } else {
        /* if user gives wrong number of arguments */
        printf("Wrong number of arguments supplied.\n");
        printf("Should be in the format ./runSimulations LeftQueueArrivalProbability, RightQueueArrivalProbability, LeftTrafficLightOnPeriod, RightTrafficLightOnPeriod\n");
    }

}
