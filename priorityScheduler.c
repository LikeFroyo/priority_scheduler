/*Scheduler that uses a preemptive priority scheduling algorithm based on dynamically changing priority. 
  Larger number for priority indicates higher priority*. When the process starts execution (i.e. CPU assigned), 
  priority for that process changes at thera te of m=1. When the process waits for CPU in the ready queue (but not yet started execution),
  its priority changes at a rate n=2. All the processes are initially assigned priority value of 0 when	
  they enter ready queue for the first time . The time slice for each process is q = 1. When two
  processes want to join ready queue simultaneously, the process which has not executed
  recently is given priority. */


#include<stdio.h>

/* Structure database for Process creation  OR PCB*/ 

struct process_data{
	int pid,arr_time,serv_time,end_time,prio_key;
};

/*Swapping Process p1 and p2 through pointers if condition satisfied*/

void swap(struct process_data* p1,struct process_data* p2) { 
    struct process_data temp = *p1; 
    *p1 = *p2; 
    *p2 = temp; 
} 

/*QuickSort partition algorithm*/

int partition (struct process_data rqueue[], int low, int high) 
{ 
    int pivot = rqueue[high].prio_key;    // pivot taking as the priority of the last process in the array strucure
    int i = (low - 1),j; 
		  
    for (j = low; j <= high- 1; j++) { 
    	/*If the priority is greater swapping is done, otherwise slide window continues 
		  if the process having same priority then with recently selected is not executed*/
    	
        if (rqueue[j].prio_key > pivot || (rqueue[i].prio_key == rqueue[j].prio_key && rqueue[i].end_time > rqueue[j].end_time)) { 
            i++; 
            swap(&rqueue[i], &rqueue[j]); 
        } 
    } 
    swap(&rqueue[i + 1], &rqueue[high]); 
    return (i + 1); 
} 
  
/*Driver program for quicksort*/
void quickSort(struct process_data rqueue[], int low, int high) 
{ 
    if (low < high) { 
        int pi = partition(rqueue, low, high); 
        quickSort(rqueue, low, pi - 1); 
        quickSort(rqueue, pi + 1, high); 
    } 
} 
/*Preempitive priority scheduler and execution done within the scheduler*/

void process_execute(struct process_data process[],int no_of_proc)
{
	struct process_data ready_queue[no_of_proc];
	int i,j,rqcount=0,burst = 0,sum=0,unCompPro=no_of_proc;
	
	while(unCompPro !=0 ){
	
		for(i=0;i<no_of_proc;i++){
			/*If process is already been in ready_queue then it will not be added
			  If a process arrives matches with cpu clock it will added to ready_queue*/
			if(burst == process[i].arr_time){  
				ready_queue[rqcount] = process[i];
				rqcount++;
			}
		}
		
		quickSort(ready_queue,0,rqcount-1);	//Sorting queue according to their priority
	
	//  For checking the execution order
	//	printf("%d %d %d %d \n",ready_queue[0].pid,ready_queue[0].arr_time,ready_queue[0].serv_time,ready_queue[0].prio_key); 
	
	/* 	For checking the status of the ready queue at particular time 
		for(i=0;i<rqcount;i++)
		printf("%d %d %d %d \n",ready_queue[i].pid,ready_queue[i].arr_time,ready_queue[i].serv_time,ready_queue[i].prio_key);*/
	
		/*Cpu is allocated and Process execution start*/	
		ready_queue[0].serv_time--;
		ready_queue[0].end_time = burst;
		ready_queue[0].prio_key += 1;
	
		/*If First process of ready_queue is completed it will out of the memory*/
		if(ready_queue[0].serv_time == 0){
			sum += (ready_queue[0].end_time-ready_queue[0].arr_time-process[ready_queue[0].pid-1].serv_time)+1; // 1 bcz burst is incremented after
			--unCompPro;
			for(j=0;j<rqcount-1;j++)	
				ready_queue[j] = ready_queue[j+1];
			rqcount--;
		}
		/*Every other waiting in ready_queue will be incremented with 2 in the priority*/
		for(j=1;j<rqcount;j++)
			ready_queue[j].prio_key += 2;
		
		burst++;
	}
	printf("Average Waiting time for each process is %f sec: ",(float)sum/no_of_proc);			
}

int main()
{
	int i,no_of_proc;	
	/* Process creation */
	
	printf("Enter no. of process to crete & PID should be different : ");		
	scanf("%d",&no_of_proc);
	struct process_data process[no_of_proc];

	/* Process intiation */

	for(i=0;i<no_of_proc;i++){
		printf("Enter Pid | arrival_Time | service_Time for %d Process: ",i+1);
		scanf("%d%d%d",&process[i].pid,&process[i].arr_time,&process[i].serv_time);
		process[i].end_time = process[i].prio_key = 0;	
	}	
	
	process_execute(process,no_of_proc);
	return 0;
}
