/*
 * rm.h
 *
 *      Author: Ridamir
 * "This software uses the gnuplot_i library written by N.Devillard, many thanks to him."
 */
#define _CRT_SECURE_NO_WARNINGS


#include <stdlib.h>
#include <string.h>
#define id						0
#define computation				1
#define period	 				2
#define remainingComputation	3
#define nextPeriod				4
#define indentation				5

#define NUMBER_OF_STRING 		4
#define MAX_STRING_SIZE 		25

//#define EXIT_FAILURE /*implementation defined*/
//#define EXIT_SUCCESS /*implementation defined*/

//stucture of a task
typedef struct
{
	int T[6];
/*
	External parameters		
		
		T[0] == T[id]								(task id)
		T[1] == T[computation]  					(Computation time)	
		T[2] == T[period]  			    			(Period)
	
	Internal parameters

		T[3] == T[remainingComputation]  			(Computation time for the time present, internal use only)
		T[4] == T[nextPeriod]						(Remaining time for the next period for the time present, internal use only)
		T[5] == T[indentation]						(indentation used in ploting the schedule of a task)
*/
	char *color;

}task;

typedef struct
{
	int idOfTask;			//						(task id)
	int indent;				//						(task indentation)
	char *color;			//						(color)

}taskExecution;

//onst char* const colors[109][20]




void StoreTasks(task *t1,int n);											//Store tasks parameters - Task id, Computation time and Period
int CalculateHyperPeriod(task *t1,int n);									//Calculate hyperiod period of the task set  
int CalculateLCM(int *a, int n);											//Calculate the least common multiple
int CalculateGCD(int a, int b);												//Calculate the greatest common divisor
void TestSchedulability(task *t1, int n);									//Test the schedulability of the tasks set
double CalculateLeastUpperBound(int n);										//Calculate the Least upper bound
double CalculateCpuUtilization(task *t1, int n);							//Calculate the CPU Utilization 
int CalculateThePriorTask(task *t1, int n, int hyperPeriod);				//Give the id of the instant prior task in the tasks set
void RunPriorTask(task* t1, int time, int priorTaskID, taskExecution* t2);	//Run the prior task id
void UpdateNextPeriodTime(task *t1, int n);									//Update the next time remaining to start of period for each task in tasks set
void StoreData(task* t1, int n);											//Store data for task structure
void PlotSchedule(int *t2, int n);											//Plot with the use of a pipe the schedule of the CPU
void Plot();
int BuildObject(taskExecution *t2, int hyperPeriod);