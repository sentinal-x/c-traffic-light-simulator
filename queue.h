#ifndef __QUEUE_H
#define __QUEUE_H

#include <stdio.h>
#include <stdlib.h>

/*----- structure definition -------------------------------------------------*/

struct node
{
    int val; /* Time car has queued. */
    struct node * next; /* Next car in queue */
};
typedef struct node QUEUE;

/*----- function prototypes --------------------------------------------------*/

extern void   printQueue (QUEUE *);
extern void   wait       (QUEUE *);
extern int    cargo      (QUEUE **);
extern void   carcome    (QUEUE *);
extern void   makeQueue  (QUEUE *);

#endif
