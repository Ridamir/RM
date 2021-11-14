
		
Design of RM scheduler :
		
1	- Specification : Will be written in Latex.
			
2	- SW specification : Will be written in Latex.
			
3	- Detailed Desing : Will be written in Latex.
		
4	- Code solution : Will be written in C.
			
5	- The report : Will be written in Latex.	
			
			
- Partitioning of the Fonction :
			
* F1 :	Read data from the input			=> file or console
* F2 :	Storing the Data.				=> C code
* F3 :	Processing the Data/Schedulability analysis.	=> C code
* F4 :	Simulation of the scheduler.			=> C code
* F5 :	Plotting the schedule.				=> C code / use of gnuplot library interfaced with C.
		
- Used Techno : C.
			 
		
1- Specification : 
		
* GENERAL :
		
[REQ-0001] :	The System is composed of 6 different function and states, which are : 
			
<F0>	- The Idle State called <IDLE_STATE>, where the system is waiting for the user to start the RM scheduler application.
			
<F1>	- The Read State called <READ_STATE>, where the system is starting the acquisition of the data about tasks set.
			
<F2>	- The Storing State called <STORING_STATE>, where the system is storing the useful data acquired in the <READ_STATE> .
			
<F3>	- The Analysis State called <ANALYSIS_STATE>, where the system is performing analysis of the schedulability based on the data stored previously in the <STORING_STATE> and the RM scheduler algorithm. 
						
<F4>	- The Processing State called <PROCESS_STATE>, where the system is performing the simulation of the schedulability of tasks set provided in the <READ_STATE> .
							
<F5>	- The Result State called <RESULT_STATE>, where the system display the result of tasks set's schedulability processing.
							
<F6>	- The Result State called <RESULT_STATE>, where the system display the result of tasks set's schedulability processing.
	
		
-----------	
* F0 :	Idle State <IDLE_STATE> :
		
		
[REQ-0002] :	The System at his <IDLE_STATE> has an input document which contain the following informations :
			
- TASKS_NUMBER : The number of schedulable tasks in the tasks set.
					 		
- TASK_ID : Which represent the number of task's identification in the tasks set.
										
- TASK_PERIOD(TASK_ID) : Which represent the period of the task which has TASK_ID in the tasks set.
					
- TASK_COMPUTATION(TASK_ID) : Which represent the computation time of the task which has TASK_ID in the tasks set.
					
					
[REQ-0003] :	The System at his <IDLE_STATE> have the ability to switch to the <READ_STATE> once the user expresses his will to do so, in other words the system provides at <IDLE_STATE> the mechanism to go to the <READ_STATE>.
					
							
[REQ-0004] :	The algorithm of the function <F0> which manage the <IDLE_STATE> is computed as follows :
			
					<F0>
		----------------		    	 ----------------
                - <IDLE_STATE> -  		     |-->- <READ_STATE> -
		----------------                     |	 ----------------
		     |_______________________________|	
			Enable (Ready for start)	
					
Once the user express his will to start the system, which is the Enable, the system start working and switch from <IDLE_STATE> to <READ_STATE>.
					
-----------	
* F1 :	Read data from the input <READ_STATE>:

				
[REQ-0005] :	At any time in the <READ_STATE>, the System must be able to read from the input the different informations detailed in [REQ-0002] and prepared it to be stored in <STORING_STATE>, in other words that means the mechanism of reading the input is provided by the function <F1> which manage this state.
			
		
[REQ-0006] :	Reading element from the input in <READ_STATE> is done sequentially, which means element by element. 
		
		
[REQ-0007] :	Reading element from the input in <READ_STATE> is done with synchronization with storing it in the <STORING_STATE>, which means we cannot read a second element in the <READ_STATE> without waiting for the first element to be stored in <STORING_STATE>.
		
		
-----------	
* F2 :	Storing the Data <STORING_STATE> :

				
[REQ-0008] :	At any time in the <STORING_STATE>, the System must be able to store data that has been read from the input in the <READ_STATE> to prepare it for analysis in the <ANALYSIS_STATE>, in other words that means the mechanism of storing the input is provided by the function <F2> which manage this state.

				
[REQ-0009] :	Once an element is been stored properly in the <STORING_STATE>, the system must back to the <READ_STATE> to read another element, and this until there is no more element left in the input without being read and stored.
											
									
[REQ-0010] :	In the <STORING_STATE>, when all data in the input are been read and stored. The system switch to <ANALYSIS_STATE>. In other words, the function <F2> which manage this state must be able to provide the mechanism which allow such transition.
									
									
[REQ-0011] :	The algorithm of the functions <F1> and <F2> which manage the <READ_STATE> is computed as follows :
														
				<F1>												<F2>						
-------------      Read an element from input  	   ----------------          Store the element   	-------------------  Storing Done 	 --------------------
- The input -   ---------------------------------> - <READ_STATE> -   ---------------------------->     - <STORING_STATE> - ------------->	 - <ANALYSIS_STATE> -	 			
-------------                                      ----------------                         		-------------------      	         --------------------
							  ^ 						       |^	         		
   						   	  |____________________________________________________||_______________________________________________|
							    Back to be able to read another element from input	  Back to be able to store another read element		
									
									
-----------	
* F3 :	Processing the Data/ Schedulability analysis <ANALYSIS_STATE> :


[REQ-0012] :	The algorithm of the function <F3> which manage the <ANALYSIS_STATE> is divided into different sub-function :

# SF31 :	Test of the schedulability NC. 	
# SF32 :	Calculate the GCD of the TASKS_NUMBER period. 	
# SF33 :	Calculate the LCM of the TASKS_NUMBER period. 	
# SF34 :	Calculate the Hyper-Period of the TASKS_NUMBER present in tasks set. 
# SF35 :	Handle the point interrupt of a running task.	
# SF36 :	Calculate the CPU Utilization.	
# SF37 :	Calculate the least upper bound.	
						
									
-----------	
# SF31 :	Test of the schedulability NC :
					
[REQ-0013] :	The algorithm of the sub-function <SF31> which test the schedulability of the tasks set under RM scheduler system compute the following formula:
				
The tasks set are schedulable under RM scheduler system if :
				
U = sigma Ui {from i to n} = sigma (Ci/Ti) {from i to n} <= n(2^(1/n)-1) where :
											
	- Ci : TASK_COMPUTATION(TASK_ID)
	- Ti : TASK_PERIOD(TASK_ID)
	- n  : TASKS_NUMBER

	Else :

	We cannot judge. 
					
					
[REQ-0014] :	The sub-function <SF1> must be able to use the values described in [REQ-0002] of tasks set stored earlier in the <STORING_STATE>.
			
					
[REQ-0015] :	When the algorithm of the sub-function <SF31> performs the formula of [REQ-0013], it must store the result of the schedulability test internally, and be able to provide it to the concerning sub-functions or functions lately.
					
					
-----------	
# SF32 :	Calculate the GCD of the TASKS_NUMBER period.  	
					
[REQ-0016] : 	The sub-function <SF32> must be able to compute the value of GCD of the TASKS_NUMBER present in the tasks set.


[REQ-0017] : 	The sub-function <SF32> must be able to store internally the value of GCD computed as per [REQ-0016] for late use by the concerning sub-function.
						
									
-----------	
# SF3 :	Calculate the LCM of the TASKS_NUMBER period.  	
					
[REQ-0018] : 	The sub-function <SF33> must be able to compute the value of LCM of the TASKS_NUMBER present in the tasks set.


[REQ-0019] : 	The sub-function <SF33> must be able to store internally the value of LCM computed as per [REQ-0016] for late use by the concerning sub-function.


-----------	
# SF34 :	Calculate the Hyper-Period of the TASKS_NUMBER present in tasks set.	

[REQ-0020] : 	The sub-function <SF34> must be able to compute the value of Hyper-Period of the TASKS_NUMBER present in the tasks set, defined as HP.


[REQ-0021] : 	The sub-function <SF34> must be able to store internally the value of Hyper-Period computed as per [REQ-0019] for late use by the concerning sub-function.



-----------	
# SF35 :	Handle the point interrupt of a running task.	

[REQ-0022] : 	The sub-function <SF35> must be able to interrupt an already running task to execute another one with higher priority when it arrives.


-----------	
# SF36 :	Calculate the CPU Utilization.	

[REQ-0023] : 	The sub-function <SF36> must compute the CPU utilization for the task sets which is the right operand in the formula defined in [REQ-0013]


-----------	
# SF37 :	Calculate the least upper bound.
					
[REQ-0024] : 	The sub-function <SF37> must compute the least upper bound for the task sets which is the left operand in the formula defined in [REQ-0013]

-----------	
* F4 :	Simulation of the scheduler <PROCESS_STATE> :
					
[REQ-0025] : 	The function <F4> must be able to simulate the tasks set schedulability from arrival time T=0 to T=HP.
			
			
[REQ-0026] :	The algorithm of the function <F4> which manage the <PROCESS_STATE> is divided into different sub-function :

# SF41 :	Calculate the prior task in each t time. 
# SF42 :	Run the prior task in each t time. 
# SF43 : 	Update the Task Descriptor. 	


[REQ-0027] : 	The sub-function <SF41> must be able to calculate the prior task each time t, and thus according to the following algorithm :
								
- Statically, the task with the minimum period is given the highest priority.
- Each time t, the task with higher priority and a remaining computation time is the one which is executed.
								
							
[REQ-0028] : 	The sub-function <SF42> must be able to run the prior task each time t, which means the CPU must be executing this task.
						
						
[REQ-0029] : 	The sub-function <SF43> must be able to update the Task Descriptor task each time t, just after the CPU end executing the prior task, which means:
							
- Decreasing the remaining computation time of the prior task just executed.
- Decreasing the time to the next period for the each task in the task sets.
- a task when executed can be preempted by another task with higher priority.
- a task when executed cannot be preempted by any task with a lower priority.
- If no task is ready for execution, which means no remaining computation time for any of the task belonging to	the task set, the CPU will be idle.
		
			
-----------	
* F5 :	Priting the result. <RESULT_STATE> :
				
[REQ-0030] : 	The System at his <RESULT_STATE> must be able to plot a GANT chart of the schedule already calculated in the <PROCESS_STATE> .

				
[REQ-0031] : 	The System at his <RESULT_STATE> will generate an output which for each TASK_ID contain the following informations :
			
- AVERAGE_RESPONSE_TIME(TASK_ID) : The average response time of a task TASK_ID.
- AVERAGE_WAITING_TIME(TASK_ID) : The average waiting time of a task TASK_ID.


