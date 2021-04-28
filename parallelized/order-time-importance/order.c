#include "order.h"
#include <math.h> 

/* implement functions */
/* function for swapping two elements in a structure array */
void swap(struct Task *t1, struct Task *t2){
	struct Task temp = *t1;
	*t1 = *t2;
	*t2 = temp;
}

/* the time for completion follows a laplace distribution around the average time for completion */
float Time(struct Task *t, float u, float avg_time,float b) {

	if (u<=0.5){
		t->time = avg_time + b*log(2*u) ;
	}
	else{
		t->time = avg_time - b*log(2*(1-u));
	}
	
}

/* the importance of a type of task follows a laplace distribution around the average importance */
float Importance(struct Task *t, float u, float avg_impt, float b){

	if (u<=0.5){
		t->importance = avg_impt + b*log(2*u);
	}
	else{
		t->importance = avg_impt - b*log(2*(1-u));
	}
	
}
