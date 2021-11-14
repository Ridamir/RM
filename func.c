// https://portailwifi.ec-nantes.fr/113/portal/
/*
 * func.c
 *
 *      Author: Ridamir
 */
#define _CRT_SECURE_NO_WARNINGS
#include <math.h> 
#include <stdio.h>
#include "rm.h"
#include "gnuplot_i.h"


// declare the objects array for plotting with gnuplot
char objectArray[256][200];

// declare the ytics string to give to gnuplot
char yticsString[1024] = "set ytics(\'CPU Idle\' 0, ";

// declare the array of color used for plotting with gnuplot
char* colors[] = {"'dark-grey'", "'red'", "'web-green'", "'web-blue'", "'dark-magenta'", "'dark-cyan'", "'dark-orange'", "dark-yellow", \
"royalblue", "goldenrod", "dark-spring-green", "purple", "steelblue", "dark-red", "dark-chartreuse", "orchid", "aquamarine", "brown", \
"yellow", "turquoise", "grey0", "grey10", "grey20", "grey30", "grey40", "grey50", "grey60", "grey70", \
"grey", "grey80", "grey90", "grey100", "light-red", "light-green", "light-blue", "light-magenta", "light-cyan", "light-goldenrod", \
"light-pink", "light-turquoise", "gold", "green", "dark-green", "spring-green", "forest-green", "sea-green", "blue", "dark-blue", \
"midnight-blue", "navy", "medium-blue", "skyblue", "cyan", "magenta", "dark-turquoise", "dark-pink", "coral", "light-coral", \
"orange-red", "salmon", "dark-salmon", "khaki", "dark-khaki", "dark-goldenrod", "beige", "olive", "orange", "violet", \
"dark-violet", "plum", "dark-plum", "dark-olivegreen", "orangered4", "brown4", "sienna4", "orchid4", "mediumpurple3", "slateblue1", \
"yellow4", "sienna1", "tan1", "sandybrown", "light-salmon", "pink", "khaki1", "lemonchiffon", "bisque", "honeydew", \
"slategrey", "seagreen", "antiquewhite", "chartreuse", "greenyellow", "gray", "light-gray", "light-grey", "dark-gray", "slategray", \
"gray0", "gray10", "gray20", "gray30", "gray40", "gray50", "gray60", "gray70", "gray80", "gray90", \
"gray100"};



/// <summary>
/// This function  scan the mode of data reading
// <the lenght of the tasks set="n"></param>
/// <returns></returns>
void SelectMode(task *t1, int n)
{
	int mode;
	printf("What mode do you prefer to read data ?\n");
	printf("For using console to enter data, choose 1\n");
	printf("For reading data from file in the adequat format, choose 2\n\n");
	printf("Adequat file format is : \n");
	printf("id_1 computation_1 period_1\n");
	printf("id_2 computation_2 period_2\n");
	printf(" .        .           .\n");
	printf(" .        .           .\n");
	printf("id_n computation_n period_n\n\n");	
	printf("The name of the file is input.txt which is in the same directory\n\n");	
	printf("Please care the number of your tasks must be the same as the number of the file lines\n\n");		

	printf("What mode do you prefer please 1 or 2 ?\n");

	scanf("%d", &mode);

	switch (mode)
	{
		case 1:
		StoreTasks(t1, n);
		break;

		case 2:
		StoreTasksFile(t1, n);
		break;

		default:
		StoreTasks(t1, n);
	}
}


/// <summary>
/// Store tasks parameters - Task id, Computation time and Period and generate internal parameters
/// </summary>
/// <task data structure="t1"></param>
/// <the lenght of the tasks set="n"></param>
/// <returns></returns>
void StoreTasksFile(task *t1, int n)
{
	FILE *file;

	file = fopen("input.txt", "r");

	while(!feof(file))
	{
		int i = 0;
		fscanf(file, "%d %d %d", &t1->T[id], &t1->T[computation], &t1->T[period]);

		// init of the task remaining computation time
		t1->T[remainingComputation] = t1->T[computation];
		
		// init of the task remaining time for the next period 
		t1->T[nextPeriod] = t1->T[period];
		
		// assign the color of the task
		t1->color = colors[i];

		// assign the indentation of the task used for plotting its schedule
		t1->T[indentation] = i+2;

		// assign the ready time for the task to 0 since it will be released at time t=0
		t1->T[readyTime] = 0;

		// initialize the running time for the task to 0 just for init purpose
		t1->T[runningTime] = 0;

		// initialize the response time for the task to 0 just for init purpose	
		t1->T[responseTime] = 0;	
		
		// initialize the average response time for the task to 0 just for init purpose
		t1->averageResponse = 0;

		t1++;
		i++;

	}
}


/// <summary>
/// Store tasks parameters - Task id, Computation time and Period and generate internal parameters
/// </summary>
/// <task data structure="t1"></param>
/// <the lenght of the tasks set="n"></param>
/// <returns></returns>
void StoreTasks(task *t1, int n)
{
	int i = 0;
	while (i < n)
	{
		printf("Enter Task %d parameters\n", i + 1);
		
		// store task id
		printf("Task id: ");
		scanf("%d", &t1->T[id]);
		//StoreData(t1, 0);
		
		// store task computation time
		printf("Task computation: ");
		scanf("%d", &t1->T[computation]);
		
		// store task Period time
		printf("Period: ");
		scanf("%d", &t1->T[period]);
		
		// init of the task remaining computation time
		t1->T[remainingComputation] = t1->T[computation];
		
		// init of the task remaining time for the next period 
		t1->T[nextPeriod] = t1->T[period];
		
		// assign the color of the task
		t1->color = colors[i];

		// assign the indentation of the task used for plotting its schedule
		t1->T[indentation] = i+2;

		// assign the ready time for the task to 0 since it will be released at time t=0
		t1->T[readyTime] = 0;

		// initialize the running time for the task to 0 just for init purpose
		t1->T[runningTime] = 0;

		// initialize the response time for the task to 0 just for init purpose	
		t1->T[responseTime] = 0;	
		
		// initialize the average response time for the task to 0 just for init purpose
		t1->averageResponse = 0;

		t1++;
		i++;
	}
}


/// <summary>
/// Test the schedulability of the tasks set
/// </summary>
/// <task data structure="t1"></param>
/// <the lenght of the tasks set="n"></param>
/// <returns></returns>
void TestSchedulability(task *t1, int n) 
{
	double utilizationOfCpu, leastUpperBound = 0;
	leastUpperBound = CalculateLeastUpperBound(n);
	utilizationOfCpu = CalculateCpuUtilization(t1, n);

	if (utilizationOfCpu <= leastUpperBound)
		printf("The tasks set is surely schedulable.\n");
	else
		printf("The system can't judge about tasks set schedulability.\n");
}


/// <summary>
/// Calculate the hyper period for the tasks set
/// </summary>
/// <task data structure="t1"></param>
/// <the lenght of the tasks set="n"></param>
/// <returns></returns>
int CalculateHyperPeriod(task *t1, int n)
{
	int i = 0, hyperPeriod, buffer[10];
	while (i < n)

	{
		buffer[i] = t1->T[period];
		t1++;
		i++;
	}
	hyperPeriod = CalculateLCM(buffer, n);

	return hyperPeriod;
}


/// <summary>
/// Calculate the least common multiple
/// </summary>
/// <a number="a"></param>
/// <the lenght of the tasks set="n"></param>
/// <returns></returns>
int CalculateLCM(int *a, int n)
{
	int lcm = 1, i;
	for (i = 0; i < n; i++)
	{
		lcm = lcm * a[i] / CalculateGCD(lcm, a[i]);
	}
	return lcm;
}


/// <summary>
/// Calculate the greatest common divisor
/// </summary>
/// <a number="a"></param>
/// <a number="b"></param>
/// <returns></returns>
int CalculateGCD(int a, int b)
{
	if (b == 0)
		return a;
	else
		return CalculateGCD(b, a % b);
}


/// <summary>
/// Calculate the CPU Utilization
/// </summary>
/// <task data structure="t1"></param>
/// <the lenght of the tasks set="n"></param>
/// <returns></returns>
double CalculateCpuUtilization(task *t1, int n)
{
	int i = 0;
	double cpuUtilization = 0;
	while (i < n)
	{
		cpuUtilization = cpuUtilization + (double)t1->T[computation] / (double)t1->T[period];
		t1++;
		i++;
	}
	return cpuUtilization;
}


/// <summary>
/// Calculate the Least upper bound
/// </summary>
/// <the lenght of the tasks set="n"></param>
/// <returns></returns>
double CalculateLeastUpperBound(int n)
{		
	return (double)(n) * ((pow(2.0, 1 / (double)(n))) - 1);
}


/// <summary>
/// Give the id of the instant prior task in the tasks set
/// </summary>
/// <task data structure="t1"></param>
/// <the lenght of the tasks set="n"></param>
/// <the hyper period calculated for the tasks set="hyperPeriod"></param>
/// <returns></returns>
int CalculateThePriorTask(task *t1, int n, int hyperPeriod)
{
	int i = 0;
	int priorTask = -1;
	int minPeriod = hyperPeriod;
	while (i < n)
	{
		if ( t1->T[remainingComputation] > 0)
		{
			if (t1->T[period] <= minPeriod)
			{
				priorTask = t1->T[id];
				minPeriod = t1->T[period];
			}

		}
		t1++; // just increment the pointer of the tasks set to the next id for check
		i++;
	}
	return priorTask;
}
 

/// <summary>
/// Run the task with the prior id in the tasks set given as parameter and constract the execution task data structre
/// </summary>
/// <task data structure="t1"></param>
/// <the instance unit time="time"></param>
/// <the id of the prior task to execute="priorTaskID"></param>
/// <the execution task data structure of the schedule="t2"></param>
void RunPriorTask(task* t1, int time, int priorTaskID, taskExecution* t2)
{
	t2+=time;
	if (priorTaskID == -1)
	{
		printf("in time %d-%d, the CPU is Idle\n", time, time+1);		
		t2->color = "'black'";
		t2->indent = 0;
	}
	else
	{
		while (t1->T[id] != priorTaskID)				
		{
			t1++;
		}
		printf("in time %d-%d, task %d is running\n", time, time + 1, priorTaskID);
		t2->color = t1->color;
		t2->indent = t1->T[indentation];
		if (t1->T[remainingComputation] == t1->T[computation])
		{
			t1->T[runningTime] = time;
		}	
		t1->T[remainingComputation]--;		
	}
	t2->idOfTask = priorTaskID;	
}


/// <summary>
/// Update the next time remaining to start of period for each task in tasks set
/// </summary>
/// <task data structure="t1"></param>
/// <the lenght of the tasks set="n"></param>
void UpdateNextPeriodTime(task *t1, int n, int time)
{
	for (int i = 0; i < n; i++)
	{
		t1->T[nextPeriod]--;
		if (t1->T[nextPeriod] == 0)
		{
			t1->T[responseTime] += t1->T[runningTime] - t1->T[readyTime];
			if(t1->T[remainingComputation] > 0)
			{
				printf("There is a deadline miss for the task %d in time t = %d\n",t1->T[id],time+1);
			}
			t1->T[nextPeriod] = t1->T[period];
			t1->T[readyTime] = time+1;
			t1->T[remainingComputation] = t1->T[computation];
		}
		t1++;
	}
}


/// <summary>
/// Display metric of the tasks set
/// </summary>
/// <task data structure="t1"></param>
/// <the lenght of the tasks set="n"></param>
/// <the hyper period calculated for the tasks set="hyperPeriod"></param>
void CalculateAverageResponse(task* t1, int n, int hyperPeriod)
{
	for (int i = 0; i < n; i++)
		{
			int jobInHyperperiod = 0;
			jobInHyperperiod = hyperPeriod/t1->T[period];
			t1->averageResponse = t1->T[responseTime]/jobInHyperperiod;
			t1++;
		}
}


/// <summary>
/// Display metric of the tasks set
/// </summary>
/// <task data structure="t1"></param>
/// <the lenght of the tasks set="n"></param>
void DisplayMetric(task* t1, int n)
{	
	for (int i = 0; i < n; i++)
		{
			printf("The average response time for the task with the id %d is : %f\n", t1->T[id],t1->averageResponse);
			t1++;
		}
}


/// <summary>
///  Store data for task data structure
/// </summary>
/// <task data structure="t1"></param>
/// <the element index in the task data structure="n"></param>
void StoreData(task *t1, int n)
{
	int NofScannedArguments = 0; /* Number of arguments which were successfully filled by the most recent call to scanf() */
	NofScannedArguments = scanf("%d", &t1->T[n]);
	if (NofScannedArguments != 1) /* should be one number */
	{
		exit(EXIT_FAILURE); /* failure, assumptions of program are not met */
	}
}


/// <summary>
///  Build object that will be plot using gnuplot and return the number of object existant
/// </summary>
/// <execution task data structure="t2"></param>
/// <the hyper period of the tasks set"hyperPeriod"></param>
int BuildObject(taskExecution *t2, int hyperPeriod)
{
	int numberOfObject=0;
	int object = 1;
	int start = 0;
	int end = 0;
	int lastValue = 0;
	int yIndentation = 0;
	char *color = "";

	for (int i=0; i<hyperPeriod; i++)
	{
		if (t2->idOfTask != lastValue && lastValue != 0)
		{
			end = i;
			sprintf(objectArray[numberOfObject], "set object %d rectangle from %d,%d to %d, 1 fc rgb %s", object,start,yIndentation,end,color);

			numberOfObject++;
			object++;
			start = i;		
		}

		end++;
		lastValue = t2->idOfTask ;
		color = t2->color ;
		yIndentation = t2->indent;
		t2++;
		
		if (i == hyperPeriod-1) 
		{
			sprintf(objectArray[numberOfObject], "set object %d rectangle from %d,%d to %d, 1 fc rgb %s", object,start,yIndentation,end,color);
		}
	}

	return numberOfObject;
}

/// <summary>
///  PLot the schedule using gnuplot
/// </summary>
/// <task data structure="t1"></param>
/// <lenght of the tasks set="n"></param>
/// <number of objects existant="lenghtOfObjects"></param>
/// <the hyper period of the tasks set"hyperPeriod"></param>
void Plot(task *t1, int n,int lenghtOfObjects, int hyperPeriod)
{
	char buffer[32]= "";	
	gnuplot_ctrl *h ;

	h = gnuplot_init();
	gnuplot_cmd(h, "set term pngcairo dashed size %d,%d",800,400) ;
	gnuplot_cmd(h, "set output \'taskschedule.png\'");
	gnuplot_cmd(h, "set style fill solid");
	gnuplot_cmd(h, "unset ytics");

	for (int i=0; i<n; i++)
	{
		if (i!=n-1)
		{
			sprintf(buffer, "\'Task %d\' %d, ", t1->T[id],i+2);
		}
		else 
		{
			sprintf(buffer, "\'Task %d\' %d)", t1->T[id],i+2);
		}
		strcat(yticsString, buffer);		
		t1++;
	}

	gnuplot_cmd(h, "%s",yticsString);
	gnuplot_cmd(h, "unset key");
	gnuplot_cmd(h, "set xrange [0:%d]",hyperPeriod);
	gnuplot_cmd(h, "set yrange [0:%d]",n+2);
	gnuplot_cmd(h, "set xlabel \'time t\'");

	for (int i=0; i<lenghtOfObjects+1; i++)
	{
		gnuplot_cmd(h, "%s",objectArray[i]);
	}

	gnuplot_cmd(h, "plot 1 w l lt 2 lc rgb \'red\'");
	sleep(1) ;
	gnuplot_close(h) ;

}


/*	
	gnuplot_cmd(h, "set object 1 rectangle from 2,1 to 7, 1.7 fc rgb \'gold\'");
	gnuplot_cmd(h, "set object 2 rectangle from 7,1 to 12,1.7 fc rgb \'light-green\'");
	gnuplot_cmd(h, "set object 3 rectangle from 12,1 to 17,1.7 fc rgb \'light-blue\'");
	gnuplot_cmd(h, "set object 4 rectangle from 0,0 to 9,0.7 fc rgb \'red\'");
	gnuplot_cmd(h, "set object 5 rectangle from 10,0 to 13,0.7 fc rgb \'blue\'");
//	gnuplot_cmd(h, "set arrow 1 from 2, 1 to 2, 1.85  fc rgb \'gold\'");
//	gnuplot_cmd(h, "set arrow 2 from 7,1 to 7,1.85 filled fc rgb \'light-green\'");
//	gnuplot_cmd(h, "set arrow 3 from 12,1 to 12,1.85 filled fc rgb \'light-blue\'");
//	gnuplot_cmd(h, "set arrow 4 from 0,0 to 0,0.85 filled fc rgb \'red\'");
//	gnuplot_cmd(h, "set arrow 5 from 10,0 to 10,0.85 filled fc rgb \'blue\'");
	gnuplot_cmd(h, "set label 1 \'t4\' at 2,1.05");	
	gnuplot_cmd(h, "set label 2 \'t3\' at 7,1.05");
	gnuplot_cmd(h, "set label 3 \'t2\' at 12,1.05");
	gnuplot_cmd(h, "set label 4 \'t5\' at 0,0.05");
	gnuplot_cmd(h, "set label 5 \'t1\' at 10,0.05");

*/



