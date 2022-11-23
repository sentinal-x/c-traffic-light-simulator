#include <queue.h>

/*----- queue functions ------------------------------------------------------*/

extern void printQueue(QUEUE * head) {
    QUEUE * current = head; /* head of queue */

    while (current != NULL) {
        printf("%d\n", current->val); /* Prints all time of cars in queue */
        current = current->next;
    }
    printf("\n");
}

extern void wait(QUEUE * head) {
    QUEUE * current = head;
    if (head->val != 0) {
        while (current != NULL) {
        current->val += 1; /* Increments waiting time of all cars by 1 */
        current = current->next;
        }
    }
}

extern void makeQueue(QUEUE * head) {
    head->val = 0;
    head->next = NULL;
}

extern void carcome(QUEUE * head) {
    QUEUE * current = head;
    
    if (current->val == 0) {
        current->val = 1; /* Case queue is empty */
    }
    else {
        while (current->next != NULL) {
            current = current->next;
        }

        current->next = (QUEUE *) malloc(sizeof(QUEUE)); /* allocates space */
        current->next->val = 1;
        current->next->next = NULL;
    }
}

extern int cargo(QUEUE ** head) {
    int retval = -1;
    QUEUE * next_node = NULL;

    if (*head == NULL) {
        return -1;
    }

    next_node = (*head)->next;
    retval = (*head)->val;
    if (next_node != NULL){
        free(*head); /* Frees memory */
        *head = next_node;  /* makes next car head of queue */
    } else {
        (*head)->val = 0;
    }

    return retval;
}


