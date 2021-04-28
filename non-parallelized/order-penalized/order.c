#include "order.h"
#include <math.h> 

/* the time for completion follows a laplace distribution around the average time for completion */
void Time(struct Task *t, float u, float avg_time,float b) {

	if (u<=0.5){
		t->time = avg_time + b*log(2*u) ;
	}
	else{
		t->time = avg_time - b*log(2*(1-u));
	}
	
}

/* the importance of a type of task follows a laplace distribution around the average importance */
void Importance(struct Task *t, float u, float avg_impt, float b){

	if (u<=0.5){
		t->importance = avg_impt + b*log(2*u);
	}
	else{
		t->importance = avg_impt - b*log(2*(1-u));
	}
	
}

/* the function for calculating the penalty of a task according to the time */
/* the penalty function is y=x^2, centered at the deadline */
float penalty(float time, float time_task, float deadline){
	return 2*(deadline-time_task-time);
}
