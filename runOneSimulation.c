#include <runOneSimulation.h>

extern SIMULATION runOneSimulation(float lqp, float rqp, int ltlp, int rtlp, gsl_rng * r) {
    
    SIMULATION thissim; /* SIMULATION for this simulation */
    /* allocate space for queues */
    QUEUE * leftqueue = (QUEUE *) malloc(sizeof(QUEUE));
    QUEUE * rightqueue = (QUEUE *) malloc(sizeof(QUEUE));
    /* set up queues */
    makeQueue(leftqueue);
    makeQueue(rightqueue);

    /* initilise variables */
    float randnum;
    int timeslice = 1;
    int lastswitch = 1;
    
    int totalcarsL = 0;
    int clearsliceL = 500;
    float averagewaitL = 0.0;
    
    int totalcarsR = 0;
    int clearsliceR = 500;
    float averagewaitR = 0.0;
    
    int currentwait = 0;
    
    short int leftlight = 1;
    short int rightlight = 0;
    short int lightschange = 0;
    
    
    int totalwaittimeL = 0;
    int maxwaitL = 0;
    int totalwaittimeR = 0;
    int maxwaitR = 0;
    
    totalwaittimeL = 0;
    maxwaitL = 0;
    averagewaitL = 0.0;
    
    totalwaittimeR = 0;
    maxwaitR = 0;
    averagewaitR = 0.0;
    
    currentwait = 0;
    
    while (timeslice < 500) {
        /* while less than 500 runs */
        
        if (leftlight == 1) {
            /* LEFT LIGHT ON */
            if (timeslice == lastswitch + ltlp) {
                leftlight = 0;
                rightlight = 1;
                lastswitch = timeslice;
                lightschange = 1;
                /* SWITCH */
            } else {
                lightschange = 0;
            }
        } else {
            /* RIGHT LIGHT ON */
            if (timeslice == lastswitch + rtlp) {
                rightlight = 0;
                leftlight = 1;
                lastswitch = timeslice;
                lightschange = 1;
                /* SWITCH */
            } else {
                lightschange = 0;
            }
        }
        
        if (lightschange == 0) {
            /* IF LIGHTS DON'T SWITCH */

            /* LEFT QUEUE PROBABILITY */
            randnum = gsl_ran_flat(r,0,1);
            if (randnum <= lqp) {
                carcome(leftqueue);
            }
            
            /* RIGHT QUEUE PROBABILITY */
            randnum = gsl_ran_flat(r,0,1);
            if (randnum <= rqp) {
                carcome(rightqueue);
            }
            
        }
        
        if (leftlight == 1) {
            /* LEFT LIGHT ON */
            currentwait = cargo(&leftqueue); /* remove from queue */
            if (currentwait > 0) {
                /* if car leaves queue */
                totalcarsL += 1;
                currentwait -= 1;
                totalwaittimeL = totalwaittimeL + currentwait; /* update values */
                if (maxwaitL < currentwait) {
                    maxwaitL = currentwait;
                }
            }
        } else {
            /* RIGHT LIGHT ON */
            currentwait = cargo(&rightqueue); /* remove from queue */
            if (currentwait > 0) {
                /* if car leaves queue */
                totalcarsR += 1; 
                currentwait -= 1;
                totalwaittimeR = totalwaittimeR + currentwait; /* update values */
                if (maxwaitR < currentwait) {
                    maxwaitR = currentwait;
                }
            }
        }
        
        
        /* increment values */
        timeslice += 1;
        wait(leftqueue);
        wait(rightqueue);
    }
    
    /* ONCE 500 TIME UNITS PASSED */
    if (leftqueue->val + rightqueue->val != 0) {
        while (leftqueue->val + rightqueue->val != 0) {

        /* REPEAT CODE FROM ABOVE WITHOUT ADDING CARS UNTIL QUEUES ARE EMPTY */
        
        if (leftlight == 1) {
            if (timeslice == lastswitch + ltlp) {
                leftlight = 0;
                rightlight = 1;
                lastswitch = timeslice;
                lightschange = 1;
            } else {
                lightschange = 0;
            }
        } else {
            if (timeslice == lastswitch + rtlp) {
                rightlight = 0;
                leftlight = 1;
                lastswitch = timeslice;
                lightschange = 1;
            } else {
                lightschange = 0;
            }
        }
        
        if (lightschange == 0) {
            
            if (leftlight == 1) {
                currentwait = cargo(&leftqueue);
                if (currentwait > 0) {
                    totalcarsL += 1;
                    currentwait -= 1;
                    totalwaittimeL = totalwaittimeL + currentwait;
                    if (maxwaitL < currentwait) {
                        maxwaitL = currentwait;
                    }
                }

            } else {
                currentwait = cargo(&rightqueue);
                if (currentwait > 0) {
                    totalcarsR += 1;
                    currentwait -= 1;
                    totalwaittimeR = totalwaittimeR + currentwait;
                    if (maxwaitR < currentwait) {
                        maxwaitR = currentwait;
                    }
                }
        
            }

            /* END OF REPEATED CODE */
            
            if (leftqueue->val == 0){
                if (clearsliceL == 500) {
                    clearsliceL = timeslice; /* time queue empty */
                }
            }
            
            if (rightqueue->val == 0){
                if (clearsliceR == 500) {
                    clearsliceR = timeslice; /* time queue empty */
                }
            }
        }
        
        /* increment values */
        timeslice += 1;
        wait(leftqueue);
        wait(rightqueue);
        }
        
    }
    
    /* CALCULATE AVERAGES */
    if (totalcarsL > 0) {
        averagewaitL = (float)totalwaittimeL/totalcarsL;
    } else {
        averagewaitL = 0;
    }
    
    if (totalcarsR > 0) {
        averagewaitR = (float)totalwaittimeR/totalcarsR;
    } else {
        averagewaitR = 0;
    }
    
    /* UPDATE SIMULATION */
    thissim.timeTaken = timeslice;
    thissim.totalCarsL = totalcarsL;
    thissim.averageWaitL = averagewaitL;
    thissim.maxWaitL = maxwaitL;
    thissim.clearTimeL = clearsliceL - 500;
    thissim.totalCarsR = totalcarsR;
    thissim.averageWaitR = averagewaitR;
    thissim.maxWaitR = maxwaitR;
    thissim.clearTimeR = clearsliceR - 500;
    
    /* FREE QUEUE MEMORY */
    free(leftqueue);
    free(rightqueue);
    
    /* RETURN SIMULATION */
    return thissim;
}
