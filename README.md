

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
    <a href=#getting started>Getting Started</a>
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
  </ol>
 
