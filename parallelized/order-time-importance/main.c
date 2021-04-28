#include "order.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
 
	int n;
    /* Enter the number of task types */
    printf("Please enter the number of task types:\n");
    scanf("%d",&n); /* store the number of task types in the variable n */
    printf("The number of task types is %d \n",n);
    
    /* define variables */
    float avg_time[n]; // for every type of task, the average completion time
    float avg_impt[n]; // for every type of task, the averge importance
    float prob[n]; // for every type of task, the probability of appearing 
    int i,j,k; // variable counters
	int deadline; // the deadline indicates the number of hours after the tasks appear  
	 
    struct Task Task_array[n];
    
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
		   
    /* Specify whether or not each type of task appears, the time for completing each task, and the importance of each task */
    for(i=0;i<n;i++){
    	float p = rand()/((float)RAND_MAX);
    	float u = rand()/((float)RAND_MAX);
    	//printf("u = %f \n ",u);
    	Task_array[i].type = i;
    	if (p < prob[i]){
    		Task_array[i].exist = 1;
    		Time(&Task_array[i], u, avg_time[i], avg_time[i]*0.1);
    		Importance(&Task_array[i], u, avg_impt[i], avg_impt[i]*0.1);
    		
		}
		else {
			Task_array[i].exist = 0;
			Task_array[i].time = 0;
			Task_array[i].importance = 0;
		}
		printf("The time for completion for task type %d is %f\n",i,Task_array[i].time);
		printf("The importance of task type %d is %f\n",i,Task_array[i].importance);
    	
	}
	
	/* output the time for completing each task and the importance of each task */
	for(i=0;i<n;i++){
		if (Task_array[i].exist !=0){
			printf("Time of completion of Task %d is %f \n",i,Task_array[i].time);
			printf("Importance of Task %d is %f \n",i,Task_array[i].importance);
		}
	}
	
	/* set the deadline for all of the tasks */
	deadline = 0;
	for(i=0;i<n;i++){
		deadline += avg_time[i];
	}
	
	/* select the method for ordering each task*/
	printf("How do you want to order the tasks? \n");
	printf("If you want to have as many tasks completed as possible, enter 'a'. \n ");
	printf("If you want to have as many important tasks completed as possible, enter 'b'. \n ");
	char order;
	printf("Enter your choice of task ordering: \n");
	scanf(" %c",&order);
	while(order!='a'&&order!='b'){
		printf("Enter your choice of task ordering: \n");
		scanf(" %c",&order);	
	}
	printf("The type of ordering is %c. \n",order);
	
	#pragma omp parallel
	{
	
	if (order=='a'){
		for(i=0;i<n;i++){
			for(j=i+1;j<n;j++){
				if (Task_array[i].exist == 1 && Task_array[j].exist == 1 && Task_array[i].time>Task_array[j].time){
					
					swap(&Task_array[i],&Task_array[j]);
				}
			}		
		}
	}
	else if (order=='b'){
		for(i=0;i<n;i++){
			for(j=i+1;j<n;j++){
				if (Task_array[i].exist == 1 && Task_array[j].exist == 1 && Task_array[i].importance>Task_array[j].importance){
					
					swap(&Task_array[i],&Task_array[j]);
				}
			}		
		}		
	}
	else{
		printf("Enter your choice of ordering: \n");
		scanf("%c",&order);
	}
	}
		
	/* print out ordered tasks in a list*/
	printf("The list of tasks is performed in the order of : \n");

	k = 0;
	for(i=0;i<n;i++){
		if (Task_array[i].exist == 1) {
			k += 1;
			printf("%d. task type %d \n",k,Task_array[i].type);
			
		}
	}

	
	
}
