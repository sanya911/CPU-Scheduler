#include <stdio.h> 
#include <limits.h> 
#include <stdlib.h>
#include <sys/types.h> 
#define MAX 20
//Total no. of processes
#define N 10
//size of ready queue
#define TIME 300
//some large time

typedef struct{ 
// structure of process
pid_t pid;
int at;
int at_temp;
int bt;
int bt_temp;
int ct;
int tat;
int wt;
int rt;	
int q_temp;
}process;


struct Queue{ 
// structure for ready and waiting queue
    int front, rear, size; 
    unsigned capacity; 
    process p_r_q[100]; 
}queue_t; 

void Process_Creator(process p[],int time_q);
void Scheduler_Simulator(process p[], int, int , int);
int generate_random(int l, int r);
void at_sort(process p[]);
void at_temp_sort(struct Queue* queue, int);

struct Queue* createQueue(unsigned capacity){
// function to create a queue  
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue)); 
    queue->capacity = capacity; 
    queue->front = queue->size = 0; 
    queue->rear = 0; 
    return queue; 
} 
  
 
int isFull(struct Queue* queue){
// Queue is full when size becomes equal to the capacity
    return (queue->size == queue->capacity); 
} 
  

int isEmpty(struct Queue* queue){ 
// Queue is empty when size is 0 
    return (queue->size == 0); 
} 
  

void enqueue(struct Queue* queue, process p){ 
// Function to add an item to the queue
    	        queue->size++;
    	        queue->p_r_q[queue->rear] = p;
                queue->rear = queue->rear + 1;
				return;
} 
  
void dequeue(struct Queue* queue){
// Function to remove an item from queue
	int i = 0;
	for( i = 0;i<queue->rear-1;i++){
		
		queue->p_r_q[i] = queue->p_r_q[i+1];
	}
	queue->rear = queue->rear-1;
	queue->size--;
} 

void Process_Creator(process p[], int time){
// this will create an array of processes and assign random at and bt to each process
	int i;
	int lower = 1 ,upper = 20;
	for(i = 0; i< MAX; i++){
		p[i].pid = i+1;
		p[i].at = generate_random(lower, upper);
		p[i].bt = generate_random(lower, upper);
		p[i].bt_temp = p[i].bt;
		p[i].at_temp = p[i].at;
		p[i].q_temp = time;
	}
	at_sort(p);
	for(i = 0; i< MAX ; i++){
		printf(" pid : %3d  ",p[i].pid);
		printf("at : %3d  ",p[i].at);
		printf("bt : %3d \n",p[i].bt);
	}
	
}

int generate_random(int l, int r) {
 // this will generate random number in range l and r
   int val;
   val = ( rand() % (r - l + 1) ) + l;
   return val;
   
}
   
void at_sort(process p[]){
// this will sort the processes according to it's arrival time
	process temp;
	int i,j;
		for(i=1;i<MAX;i++)
			for(j=0;j<MAX-i;j++){
				if(p[j].at > p[j+1].at){
					temp = p[j];
					p[j] = p[j+1];
					p[j+1] = temp;
			}
		}
}

void at_temp_sort(struct Queue *queue, int time){
// this will sort the process according to it's arrival time at queue
	process temp;
	int i,j;
	queue->p_r_q[queue->rear].at_temp = time;
	for(i=1;i<queue->size;i++){
		for(j = 0;j<queue->size-i;j++){
			if(queue->p_r_q[j].at_temp > queue->p_r_q[j+1].at_temp){
				temp = queue->p_r_q[j];
				queue->p_r_q[j] = queue->p_r_q[j+1];
				queue->p_r_q[j+1] = temp;
			}
		}	
	}
}

void Scheduler_Simulator(process p[],int t, int select,int time_q){

	struct Queue* r_q = createQueue(N); 
	// this is the ready queue
	struct Queue* w_q = createQueue(MAX);
	// this is the waiting queue
	int time = p[0].at;
	int j = 0;
	int i = 0;
	int k;
	int c_temp = 0;
	process small_bt;
	int arr[MAX];
	int temp;
	

	FILE *fp1;
	FILE *fp4;
	FILE *fp2;
	FILE *fp5;
	FILE *fp3;
	FILE *fp6;

	
	if(select == 1){
		fp1 = fopen("status_fcfs.txt", "a");
	    fp4 = fopen("process_fcfs.txt", "a");

		fprintf(fp1,"\n    TIME (ms)      PID      STATUS   ");
		fprintf(fp1,"\n---------------------------------------\n");
		fprintf(fp4,"\n  PID   |   AT    |    BT   |    CT   |    RT   |   TAT   |   WT    ");
		fprintf(fp4,"\n----------------------------------------------------------------------\n");
	}
	if(select == 2){
		fp2 = fopen("status_srtf.txt", "a");
	    fp5 = fopen("process_srtf.txt", "a");

		fprintf(fp2,"\n    TIME (ms)      PID      STATUS   ");
		fprintf(fp2,"\n---------------------------------------\n");
		fprintf(fp5,"\n  PID   |   AT    |    BT   |    CT   |    RT   |   TAT   |   WT    ");
		fprintf(fp5,"\n-----------------------------------------------------------------------\n");
	}
	if(select == 3){
		
	    fp3 = fopen("status_rr.txt", "a");
	    fp6 = fopen("process_rr.txt", "a");
		fprintf(fp3,"\n    TIME (ms)      PID      STATUS   ");
		fprintf(fp3,"\n---------------------------------------\n");
		fprintf(fp6,"\n  PID   |   AT    |    BT   |    CT   |    RT   |   TAT   |   WT    ");
		fprintf(fp6,"\n-----------------------------------------------------------------------\n");	
	}

	while(time< TIME){
		// countdown
		j = 0;
		while(j<MAX && p[MAX-1].at >= time){ 
			if(p[j].at == time){
			// arrived process firstly will go inside the waiting queue
				enqueue(w_q, p[j]);
				}
			else if(p[MAX-1].at < time){
			// as all the process has been arrived
				break;
			}
			j = j+1;	
		}
		if (isEmpty(r_q) && isEmpty(w_q) && p[MAX-1].at < time){
			// both of queues are empty and no other processess are left to arrive
			break;
		}
		else if(isEmpty(r_q) && isEmpty(w_q)){
			// both are empty but other process can still arrive
			time = time+1;
			continue;
		}
		while(!((isFull(r_q) ) || (isEmpty(w_q)))){
			// fill ready queue until it is full or waiting queue is empty
			enqueue(r_q, w_q->p_r_q[w_q->front]);
			if(select == 1 && time < t){
				fprintf(fp1," %8d    %8d       Arrived\n",time,w_q->p_r_q[w_q->front].pid);
			}
			else if(select == 2 && time < t){
				fprintf(fp2," %8d    %8d       Arrived\n",time,w_q->p_r_q[w_q->front].pid);	
			}
			else if(select ==3 && time < t){
				fprintf(fp3," %8d    %8d       Arrived\n",time,w_q->p_r_q[w_q->front].pid);
			}
			dequeue(w_q);
		}

		if (select == 1){
		// FCFS	
			if (r_q->p_r_q[r_q->front].bt_temp != 0){
				// Running process
				if(r_q->p_r_q[r_q->front].bt == r_q->p_r_q[r_q->front].bt_temp){
					
					r_q->p_r_q[r_q->front].rt = time;
					if(time < t){
					    fprintf(fp1, " %8d    %8d       Running\n" ,time,r_q->p_r_q[r_q->front].pid);
					}
						
				}
			 	r_q->p_r_q[r_q->front].bt_temp = r_q->p_r_q[r_q->front].bt_temp - 1;
			 	time = time+1;
			 	continue;
			}
			else{
				// Process completed 
				if(time < t){
				   fprintf(fp1," %8d    %8d       Exit\n",time,r_q->p_r_q[r_q->front].pid); 
				}
					
				r_q->p_r_q[r_q->front].ct = r_q->p_r_q[r_q->front].rt + r_q->p_r_q[r_q->front].bt;
				r_q->p_r_q[r_q->front].tat = r_q->p_r_q[r_q->front].ct - r_q->p_r_q[r_q->front].at;
				r_q->p_r_q[r_q->front].wt =  r_q->p_r_q[r_q->front].tat-r_q->p_r_q[r_q->front].bt;
				r_q->p_r_q[r_q->front].rt = r_q->p_r_q[r_q->front].rt - r_q->p_r_q[r_q->front].at;
				fprintf(fp4,"%5d   | %5d   | %5d   | %5d   | %5d   | %5d   | %5d\n",r_q->p_r_q[r_q->front].pid,r_q->p_r_q[r_q->front].at,r_q->p_r_q[r_q->front].bt,r_q->p_r_q[r_q->front].ct,r_q->p_r_q[r_q->front].rt,r_q->p_r_q[r_q->front].tat,r_q->p_r_q[r_q->front].wt);
				dequeue(r_q);
				if(!(isEmpty(r_q))){
					// Next process will start
						if(r_q->p_r_q[r_q->front].bt == r_q->p_r_q[r_q->front].bt_temp ){
						r_q->p_r_q[r_q->front].rt = time;
						    if(time < t){
						    	fprintf(fp1, " %8d    %8d       Running\n" ,time,r_q->p_r_q[r_q->front].pid);
						    
						    }
						}
				 	r_q->p_r_q[r_q->front].bt_temp = r_q->p_r_q[r_q->front].bt_temp - 1;
				 	time = time+1;
				 	continue;		
				}	
			}
		time = time+1;
		}		

	else if (select == 2){
	// for SRTF

		if(r_q->size == 1 && r_q->p_r_q[r_q->front].bt_temp !=0){
		// Only one process in ready queue and bt is not zero so it will run
			if(r_q->p_r_q[r_q->front].bt_temp == r_q->p_r_q[r_q->front].bt){
				
				r_q->p_r_q[r_q->front].rt = time;
				if(time<t){
				fprintf(fp2, " %8d    %8d       Running\n" ,time,r_q->p_r_q[r_q->front].pid);
				}
			}
			r_q->p_r_q[r_q->front].bt_temp = r_q->p_r_q[r_q->front].bt_temp - 1;
		 	time = time+1;
		 	continue;	
		}
			
		else if(r_q->size == 1 && r_q->p_r_q[r_q->front].bt_temp ==0){
		// Only one process which will exit
			r_q->p_r_q[r_q->front].ct = time;
			r_q->p_r_q[r_q->front].tat = r_q->p_r_q[r_q->front].ct - r_q->p_r_q[r_q->front].at;
			r_q->p_r_q[r_q->front].wt =  r_q->p_r_q[r_q->front].tat - r_q->p_r_q[r_q->front].bt;
			r_q->p_r_q[r_q->front].rt = r_q->p_r_q[r_q->front].rt - r_q->p_r_q[r_q->front].at;
			fprintf(fp5,"%5d   | %5d   | %5d   | %5d   | %5d   | %5d   | %5d\n",r_q->p_r_q[r_q->front].pid,r_q->p_r_q[r_q->front].at,r_q->p_r_q[r_q->front].bt,r_q->p_r_q[r_q->front].ct,r_q->p_r_q[r_q->front].rt,r_q->p_r_q[r_q->front].tat,r_q->p_r_q[r_q->front].wt);
			if(time<t){
			fprintf(fp2, " %8d    %8d       EXIT\n" ,time,r_q->p_r_q[r_q->front].pid);   
			}
			dequeue(r_q);
			time = time + 1;
			continue;	
		}
			
		else{
		// This will choose the process to run according to it's burst time
			small_bt.bt_temp = 50;
			temp = 0;
			process p_temp;
			i = r_q->front;
			while(i<r_q->rear){
				if(r_q->p_r_q[i].bt_temp == 0){
				//This will dequeue the process if it is completed
					r_q->p_r_q[i].ct = time;
					r_q->p_r_q[i].tat = r_q->p_r_q[i].ct - r_q->p_r_q[i].at;
					r_q->p_r_q[i].wt =  r_q->p_r_q[i].tat-r_q->p_r_q[i].bt;
					r_q->p_r_q[i].rt = r_q->p_r_q[i].rt - r_q->p_r_q[i].at;
					fprintf(fp5,"%5d   | %5d   | %5d   | %5d   | %5d   | %5d   | %5d\n",r_q->p_r_q[i].pid,r_q->p_r_q[i].at,r_q->p_r_q[i].bt,r_q->p_r_q[i].ct,r_q->p_r_q[i].rt,r_q->p_r_q[i].tat,r_q->p_r_q[i].wt);
					if(time<t){
					fprintf(fp2, " %8d    %8d       EXIT\n" ,time,r_q->p_r_q[r_q->front].pid);
					}
					p_temp=r_q->p_r_q[i];
    				r_q->p_r_q[i]=r_q->p_r_q[r_q->front];
    				r_q->p_r_q[r_q->front]=p_temp;
					dequeue(r_q);
					
					if(!(isEmpty(w_q))){
						
						enqueue(r_q,w_q->p_r_q[w_q->front]);
						if(time<t){
						fprintf(fp2, " %8d    %8d       ARRIVED\n" ,time,r_q->p_r_q[r_q->front].pid);
						}
						dequeue(w_q);
					}
					break;
				}
				i = i+1;
			}
			k = r_q->front;
			for(k =0; k<r_q->rear;k++){
			// this will choose the process with the least bt
				if(r_q->p_r_q[k].bt_temp < small_bt.bt_temp){
					
					small_bt = r_q->p_r_q[k];
					temp = k;
				}
				else if(r_q->p_r_q[k].bt_temp == small_bt.bt_temp){
					
					if(r_q->p_r_q[k].at < small_bt.at){
						small_bt = r_q->p_r_q[k];
						temp = k;								
					}
				}
			}
		}
		if(r_q->p_r_q[temp].bt == r_q->p_r_q[temp].bt_temp){
		// this will store the value of rt
			r_q->p_r_q[temp].rt = time;
			if(time<t){
			fprintf(fp2, " %8d    %8d       Running\n" ,time,r_q->p_r_q[r_q->front].pid);
			}
		}
		r_q->p_r_q[temp].bt_temp = r_q->p_r_q[temp].bt_temp - 1;
		time = time+1;
	 	continue;		
	}
		
	// for ROUNDROBIN
	else if (select == 3){
//		if(time > t){
//			fclose(fp3);
//		}
			if(r_q->size == 1 && p[MAX-1].at < time && w_q->size == 0){
			// this will run the last process and then removes it
			    if(time<t){
				fprintf(fp3," %8d    %8d       EXIT\n",time+r_q->p_r_q[r_q->front].bt_temp,r_q->p_r_q[r_q->front].pid);
			    }
				r_q->p_r_q[r_q->front].ct = time+r_q->p_r_q[r_q->front].bt_temp;
				r_q->p_r_q[r_q->front].tat = r_q->p_r_q[r_q->front].ct - r_q->p_r_q[r_q->front].at;
				r_q->p_r_q[r_q->front].wt =  r_q->p_r_q[r_q->front].tat-r_q->p_r_q[r_q->front].bt;
				r_q->p_r_q[r_q->front].rt = r_q->p_r_q[r_q->front].rt - r_q->p_r_q[r_q->front].at;
				fprintf(fp6,"%5d   | %5d   | %5d   | %5d   | %5d   | %5d   | %5d\n",r_q->p_r_q[r_q->front].pid,r_q->p_r_q[r_q->front].at,r_q->p_r_q[r_q->front].bt,r_q->p_r_q[r_q->front].ct,r_q->p_r_q[r_q->front].rt,r_q->p_r_q[r_q->front].tat,r_q->p_r_q[r_q->front].wt);
				break;
			}
			else if(r_q->p_r_q[r_q->front].bt_temp != 0 && (r_q->p_r_q[r_q->front].q_temp == 0 || (r_q->p_r_q[r_q->front].q_temp < 0 && r_q->p_r_q[r_q->front].q_temp%time_q == 0))){
			// this will send the process back to queue as time quanta is finished and process is not finished
				enqueue(w_q,r_q->p_r_q[r_q->front]);
				w_q->p_r_q[w_q->rear].q_temp = time_q;
				w_q->p_r_q[w_q->rear].at_temp = time;
				dequeue(r_q);
				at_temp_sort(w_q, time);
				if(!isEmpty(r_q)){
				// this will run the next process
					if(r_q->p_r_q[r_q->front].bt == r_q->p_r_q[r_q->front].bt_temp){
						
						r_q->p_r_q[r_q->front].rt = time;
					}
					r_q->p_r_q[r_q->front].bt_temp = r_q->p_r_q[r_q->front].bt_temp -1;
					r_q->p_r_q[r_q->front].q_temp = r_q->p_r_q[r_q->front].q_temp -1;
                    if(time<t){
					fprintf(fp3, " %8d    %8d       Running\n" ,time,r_q->p_r_q[r_q->front].pid);
                    }
					time = time+1;
					continue;
				}
				time = time+1;
				continue;
			}
			else if(r_q->p_r_q[r_q->front].bt_temp == 0){
			// this ill dequeue the process as bt_temp = 0
				r_q->p_r_q[r_q->front].ct = time;
				if(time<t){
				fprintf(fp3, " %8d    %8d       EXIT\n" ,time,r_q->p_r_q[r_q->front].pid);	
				}
				r_q->p_r_q[i].tat = r_q->p_r_q[i].ct - r_q->p_r_q[i].at;
				r_q->p_r_q[i].wt =  r_q->p_r_q[i].tat-r_q->p_r_q[i].bt;
				r_q->p_r_q[i].rt = r_q->p_r_q[i].rt - r_q->p_r_q[i].at;
				fprintf(fp6,"%5d   | %5d   | %5d   | %5d   | %5d   | %5d   | %5d\n",r_q->p_r_q[r_q->front].pid,r_q->p_r_q[r_q->front].at,r_q->p_r_q[r_q->front].bt,r_q->p_r_q[r_q->front].ct,r_q->p_r_q[r_q->front].rt,r_q->p_r_q[r_q->front].tat,r_q->p_r_q[r_q->front].wt);
				dequeue(r_q);
					if(!isEmpty(r_q)){
					// this will run the next process
						if(r_q->p_r_q[r_q->front].bt == r_q->p_r_q[r_q->front].bt_temp){
							
							r_q->p_r_q[r_q->front].rt = time;
					}
					r_q->p_r_q[r_q->front].bt_temp = r_q->p_r_q[r_q->front].bt_temp -1;
					r_q->p_r_q[r_q->front].q_temp = r_q->p_r_q[r_q->front].q_temp -1;
					if(time<t){
					    fprintf(fp3, " %8d    %8d       Running\n" ,time,r_q->p_r_q[r_q->front].pid);
					}
					time = time+1;
					continue;
				}
			}
			else{
			// process is running
				if(r_q->p_r_q[r_q->front].bt == r_q->p_r_q[r_q->front].bt_temp){
					
					r_q->p_r_q[r_q->front].rt = time;
					if (time<t){
					    fprintf(fp3, " %8d    %8d       Running\n" ,time,r_q->p_r_q[r_q->front].pid);	
					}
					}
				r_q->p_r_q[r_q->front].bt_temp = r_q->p_r_q[r_q->front].bt_temp -1;
				r_q->p_r_q[r_q->front].q_temp = r_q->p_r_q[r_q->front].q_temp -1;	
				time = time+1;
				continue;
			}
		}
	}
	if(select == 1){
	  	fclose(fp1);
	fclose(fp4);
	
	  
	}
	else if(select == 2){
        fclose(fp5);
	    fclose(fp2);
	    
	}
	else{
	   fclose(fp3);
	    fclose(fp6);
	}

}

int main(){
// this will take input from the user and starts the scheduler and simulator
	process p[MAX];
	int i;
	int select,t,time_q;
	printf("\nSimulation time in miliseconds (prefarably between 50 to 300): \t");
	scanf("%d",&t);
	printf("\nChoose (1 or 2 or 3)\n1. FCFS \n2. SRTF \n3. RR");
    printf("\nChoice: ");
    scanf(" %d", &select);
    if (select != 1 && select != 2 && select != 3){
    	
    	printf("wrong input");
		return -1;
	}
	else if (select == 3){
		
		printf("time quantum in ms: \t");
		scanf("%d",&time_q);
	}
	else 
		time_q = 0;
		Process_Creator(p,time_q);	
		Scheduler_Simulator(p ,t, select, time_q);
		printf("\nfinished\n");
}



