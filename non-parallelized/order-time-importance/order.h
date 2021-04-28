#ifndef ORDER_H
#define ORDER_H

/* Task's attributes */
struct Task{
	int exist; // flag that shows whether a task exists or not: 1 means exists, 0 means does not exist
    float time; // specifies the time for completing the task
    float importance; // specifies the importance of the task
    int type; // specifies the task type id for printing
};

/* Tasks's operations (interface) */
float Time(struct Task *t, float u, float avg_time, float b); // function for specifying the time for completing a task
float Importance(struct Task *t, float u,float avg_impt, float b); // function for specifying the importance of a task
void swap(struct Task *t1, struct Task *t2); // function for swapping the positions of two tasks 

#endif 
 
