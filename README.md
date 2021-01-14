

<h1 align="center"> CPU-Scheduler </h1>
<p align = "center">
Assigning process to a CPU based on particular scheduling algorithm
</p>
<details open="open">
  <summary >Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
      <ul>
          <li><a href="#structures">Structures</a></li>
          <li><a href="#functions">Functions</a></li>
      </ul>
    </li>
        <li><a href="#built-with">Built With</a></li>
 
  <li>
    <a href=#getting-started>Getting Started</a>
  </li>
   </ol>
</details>

## About the Project
### Structures
<ol>
  <li>
  Process: This structure contains Process ID as pid, Burst Time as bt, Completion Time as ct, Waiting Time as wt, 
			Turn Around Time as tat, Response Time as rt and at_temp and bt_temp are used for preemptive processes.
  </li>
  <li>
	Queue: This structure contains array of process structure as p_r_q[], front as the position of front elemnt in queue,
			 rear as the last elemnt in queue, size as the size of queue, capacity is the limit of queue
  </li>
 </ol>
 
 ### Functions
 <ol>
  <li>Main: This will take input from the user Simulation time, the name of the scheduling algorithm and time quantum in case of Round Robin 
		 	and then calls the other Proces_Creator and after it's execution it will call the Scheduler_Simulator function.
    Here we intialized process struct as p[MAx].</li>
  <li>Process_Creator:  This will create an array of processes struct and assign random values to at and bt by calling generate_random function.</li>
  <li>Scheduler_Simulator:  This will intialize ready queue as r_q with fixed capacity as N and waiting queue as w_q with capacity as MAX where N and Max are defined globally.</li>
	<li>Generate_random: This will generate random number in range l and r which will be used to allocate value  bt and at to the specified no. of processes.
	</li>
	<li>at_sort: This will sort the processes according to it's arrival time.</li>
	<li>at_temp_sort: This will sort the processes according to it's arrival time in waiting queue. </li>
	<li> createQueue: To create a queue and allocate memory accordingly.c</li>
  </ol>
  
  ### Built With
  
  #### C-Programming language
  
  ### Getting Started
  
  
  <p>Then  loop timer will start from the  time when the first process arrive.
		 As The processes arrives in the w_q and if r_q is not full it is enqueued from w_q to r_q.
<ul>
		 	<li>If user has selected 1 (FCFS):
			 	The function will execute the process according to the sequence it has entered which is according to it's arrival time.
			 	When the process arrives it is updated at status.txt and when it starts running it is also updated similarly.
		 		If the process at front is completed it is dequeued from the queue and process_fcfs.txt  and status_fcfs.txt is updated with all the calculated values of that process.</li>
	<li>
	If user has selected 2 (SRTF):
		 		Process will be enqueued in ready queue according to it's burst time from the waiting queue.
		 		Then we will run the process with the least burst time until it finishes it's execution or any process with lesser burst time enter's ready queue.
		 		if process complete the execution we will dequeue it from the queue and enqueue next process from waiting queue and 
		update values of status_rr.txt and process.txt accordingly.</li>
	<li>If user has selected 3 (RR):
			 	This function will execute the process according to the sequence it enters the ready queue.
			 	if the process remaining bt is less than quanta so it will run completely otherwise if quanta finishes before the bt 
					 the process is stopped and next process is executed and the last process is swapped in ready queue back. 
		 		then if process finishes it's bt then it is dequeued from the queue and next process starts it's execution and 
		the values of status_rr.txt and process_rr.txt are updated accordingly.</li>
	</ul>
	</p>
    
 
