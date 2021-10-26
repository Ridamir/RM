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
char yticsString[1024] = "set ytics(\'Idle\' 0, ";

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


/// Store tasks parameters - Task id, Computation time and Period
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

		t1++;
		i++;
	}
}



/// Test the schedulability of the tasks set
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


/// Calculate the hyper period for the tasks set
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


/// Calculate the least common multiple

/// <summary>
/// 
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
/// Run the task with the prior id in the tasks set given as parameter
/// </summary>
/// <task data structure="t1"></param>
/// <the instance unit time="time"></param>
/// <the id of the prior task to execute="priorTaskID"></param>
/// <table of execution of the schedule="t2"></param>


//void RunPriorTask(task *t1, int time, int priorTaskID)
void RunPriorTask(task* t1, int time, int priorTaskID, taskExecution* t2)
{
	t2=t2+time;
	if (priorTaskID == -1)
	{
		printf("in time %d-%d, the CPU is Idle\n", time, time+1);		// if -1 returned so no task is prior for running the CPU
		t2->color = "'black'";
		t2->indent = 0;
	}
	else
	{
		while (t1->T[id] != priorTaskID)				// pointing to the id of the prior task to run on the CPU
		{
			t1++;
		}
		printf("in time %d-%d, task %d is running\n", time, time + 1, priorTaskID);	// the prior task is running on the CPU
		t2->color = t1->color;
		t2->indent = t1->T[indentation];	
		t1->T[remainingComputation]--;		
	}
	//t2[time] = priorTaskID;
	t2->idOfTask = priorTaskID;
	
}


/// <summary>
/// Update the next time remaining to start of period for each task in tasks set
/// </summary>
/// <task data structure="t1"></param>
/// <the lenght of the tasks set="n"></param>
void UpdateNextPeriodTime(task *t1, int n)
{
	for (int i = 0; i < n; i++)
	{
		t1->T[nextPeriod]--;
		if (t1->T[nextPeriod] == 0)
		{
			t1->T[nextPeriod] = t1->T[period];
			t1->T[remainingComputation] = t1->T[computation];
		}
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
/// Plot with the use of a pipe the schedule of the CPU
/// </summary>
/// <table of execution of the schedule="t2"></param>
/// <the lenght of the hyperperiod="n"></param>
/*void PlotSchedule(int *t2, int n)
{
	gnuplot_ctrl *h ;
	double d[n];

	h = gnuplot_init();
	gnuplot_setstyle(h, "boxes") ;
	for (int i = 0; i < n; i++)
	{
        d[i] = (double)(t2[i]) ;
	//	printf("%lf\n", d[i]);
	}
	gnuplot_cmd(h, "set ytics(\'Idle\' -1.0, \'Task 1\' 1.0, \'Task 2\' 2.0, \'Task 3\' 3.0)") ;
//	set ytics('Processor1' 1.5,'Processor2' 0.5)
	gnuplot_plot_x(h,d,n,"Schedule of the CPU");
	sleep(30) ;
	//gnuplot_cmd(h, "pause mouse");
	gnuplot_close(h) ;		
}
*/

/*
void BuildYaxis(int n)
{
	for (int i=0; i<n; i++)
	{

	}

}
s
*/
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

	for (int i=0; i<numberOfObject+1; i++)
	{
		printf("%s \n",objectArray[i]);
	}
	return numberOfObject;
}


void Plot(task *t1, int n,int lenghtOfObjects)
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

	printf("%s\n",yticsString);

	gnuplot_cmd(h, "%s",yticsString);
	gnuplot_cmd(h, "unset key");
	gnuplot_cmd(h, "set xrange [0:20]");
	gnuplot_cmd(h, "set yrange [0:10]");
	gnuplot_cmd(h, "set xlabel \'time t\'");

	for (int i=0; i<lenghtOfObjects+1; i++)
	{
		gnuplot_cmd(h, "%s",objectArray[i]);
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

	gnuplot_cmd(h, "plot 1 w l lt 2 lc rgb \'red\'");
	sleep(1) ;
	gnuplot_close(h) ;

}

