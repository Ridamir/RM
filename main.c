/*
 * main.c
 *
 *      Author: Ridamir
 */
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "rm.h"

int main()
{
// --------- Declaration Area ---------

	//  declare the pointer to the tasks set structure
	task *t;
	
	// declare the lenght of the tasks set
	int tasksNumber = 0;
		
	// declare the hyper period of the tasks set	
	int hyperPeriod = 0; 

	// declare the pointer to the execution structure
	taskExecution *executionTasks = NULL;
		
	// declare an iterator for the lenght of hyperPeriod
	int i = 0;

	// declare the id of the prior task
	int idOfPriorTask = 0;

// --------- Body code ---------
		
	printf("Enter the lenght of the tasks set\n");
	int NofScannedArguments = 0; /* Number of arguments which were successfully filled by the most recent call to scanf() */
	NofScannedArguments = scanf("%d", &tasksNumber);
	if (NofScannedArguments != 1) /* should be one number */
	{
		exit(EXIT_FAILURE); /* failure, assumptions of program are not met */
	}
	

	t = malloc(tasksNumber * sizeof(task)) ;	
	StoreTasks(t, tasksNumber);
	TestSchedulability(t, tasksNumber);
	hyperPeriod = CalculateHyperPeriod(t, tasksNumber);

	// Define the pointer to the table of execution for the tasks set
	executionTasks = malloc(hyperPeriod * sizeof(taskExecution));
	
	// The body of the scheduler
	while (i < hyperPeriod)
	{
		idOfPriorTask = CalculateThePriorTask(t, tasksNumber, hyperPeriod);
		RunPriorTask(t, i, idOfPriorTask, executionTasks);
		UpdateNextPeriodTime(t, tasksNumber);
		i++;
	}


	for (i = 0; i < hyperPeriod; i++)
	{
		printf("The task_id of the task is %d, its color is %s\n", executionTasks->idOfTask, executionTasks->color);
		executionTasks++;
	}

//	PlotSchedule(executionTasks, hyperPeriod);
// 	Plot();
	free(t);	
	return 0;
}