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
void Time(struct Task *t, float u, float avg_time, float b); // function for specifying the time for completing a task
void Importance(struct Task *t, float u,float avg_impt, float b); // function for specifying the importance of a task
float penalty(float time, float time_task, float deadline); // penalty function scaled by the importance of a task and the time it is completed if executed

#endif 
