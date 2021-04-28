#include "order.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
	
	int n;
	int h;
    /* Enter the number of task types */
    printf("Please enter the number of task types:\n");
    scanf("%d",&n); // store the number of task types in the variable n
    printf("The number of task types is %d \n",n);
    // tasks will appear at the beginning of each hour for 10 hours
    printf("Please enter the number of hour at the beginning of which tasks will appear:\n");
    scanf("%d",&h); // stores the number of hours at the beginning of which tasks will appear by random
    printf("Tasks will appear at the beginning of each hour for %d hours \n",h);
    int n1 = n*h; // size of Task structure array, maximum number of tasks
    
    /* define variables */
    float avg_time[n]; // for every type of task, the average completion time
    float avg_impt[n]; // for every type of task, the averge importance
    float prob[n]; // for every type of task, the probability of appearing 
    int i,j,k; // variable counters
	int deadline; // the deadline indicates the number of hours after the tasks appear  
	 
    struct Task Task_array[n1];
    
	/* Enter the average time of completion for each type of task */
	/* Enter the average importance for each type of task */
	/* Generate the probability of appearance of each type of task by random */
	for(i=0;i<n;i++){
		printf("Enter the average time of completion of task type %d \n:",i);
		scanf("%f",&avg_time[i]);
		while (avg_time[i]<=0 || avg_time[i]>10){
			printf("Average time must be greater than 0, less than 10. \n");
			printf("Enter the average time of completion of task type %d \n:",i);
			scanf("%f",&avg_time[i]);
		}
		printf("Enter the average importance of task type %d \n:",i);
		scanf("%f",&avg_impt[i]);
		while (avg_impt[i]<=0 || avg_impt[i]>10){
			printf("Average importance must be greater than 0, less than 10. \n");
			printf("Enter the average importance of task type %d \n:",i);
			scanf("%f",&avg_time[i]);
		}
		printf("Enter the probability of appearance of task type %d \n:",i);		
		scanf("%f",&prob[i]);
		while (prob[i]<=0 || prob[i]>=1){
			printf("Probability must be greater than 0, less than or equal to 1. \n");
			printf("Enter the probability of appearance of task type %d \n:",i);
			scanf("%f",&prob[i]);
		}
	}
		   
    /* Specify whether or not each type of task appears at each hour, the time for completing each task, and the importance of each task */
    for(i=0;i<n1;i++){
    	float p = rand()/((float)RAND_MAX);
    	float u = rand()/((float)RAND_MAX);
    	//printf("u = %f \n ",u);
    	
    	Task_array[i].type = i%n;
    	Task_array[i].hour = i/n;
    	if (p < prob[Task_array[i].type]){
    		Task_array[i].exist = 1;
    		Time(&Task_array[i], u, avg_time[Task_array[i].type], avg_time[Task_array[i].type]*0.1);
    		Importance(&Task_array[i], u, avg_impt[Task_array[i].type], avg_impt[Task_array[i].type]*0.1);
    		
		}
		else {
			Task_array[i].exist = 0;
			Task_array[i].time = 0;
			Task_array[i].importance = 0;
		}
    	
	}
	
	/* output the time for completing each task and the importance of each task */
	/* count the number of existing tasks */
	int num = 0;
	for(i=0;i<n1;i++){
		if (Task_array[i].exist !=0){
			printf("Time of completion of Task %d of hour %d and type %d is %f \n",i,Task_array[i].hour,Task_array[i].type,Task_array[i].time);
			printf("Importance of Task %d of hour %d and type %d is %f \n",i,Task_array[i].hour,Task_array[i].type,Task_array[i].importance);
			num += 1;
		}
	}
	
	/* set the deadline for all of the tasks */
	deadline = 0;
	for(i=0;i<n;i++){
		deadline += h*avg_time[i];
	}
	deadline = ceil(deadline);

	/* order the tasks by importance and print them out by order*/
	/* the importance here is scaled by penalty function */
	int output; // the index of the task to be output
	float max; // the variable storing the most important task at the moment, the task to be output
	float time = 0; // the total time elapsed
	printf("The list of tasks is performed in the order of : \n");
	for(k=0;k<num;k++){
		#pragma omp parallel
		{
		
		for(i=0;i<n1;i++){
			if (Task_array[i].exist==1 && Task_array[i].hour<=time){
				max = Task_array[i].importance * penalty(time,Task_array[i].time,deadline);
				output = i;
			}
			for(j=0;j<n1;j++){
				if (Task_array[j].exist==1 && Task_array[j].hour<=time && (Task_array[j].importance*penalty(time,Task_array[j].time,deadline))> max){
					max = Task_array[j].importance * penalty(time,Task_array[j].time,deadline);
					output = j;
				}
			}
			
		}
		}
		Task_array[output].exist = 0; // after the task is completed, it no longer exists
		printf("%d. task %d of hour %d and type %d with importance %f and time of completion %f \n",k+1,output,Task_array[output].hour,Task_array[output].type,
		Task_array[output].importance,Task_array[output].time);
		time += Task_array[output].time;
		
	}
	
}	
