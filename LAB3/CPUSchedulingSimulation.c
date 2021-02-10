// process file with id,arrival,burst is passed as argument.


// cat results.txt for viewing the content of the file.
// In analysis of the output file(results.txt) , if round Robin is executed twice , then 
// analysis is made on the last executed round robin.


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <fcntl.h> // for open
#include <unistd.h> // for close
#include<sys/types.h>
#define MAX_SIZE 100000
#define MAX_PROCESS 100000

typedef struct Process
{
    char *name;
    int arrival; // arrival time
    int cpburst; // burst time
    int turnaround; // turnaroundTime
    int wait; // waiting time.
}Process;

Process processTable[MAX_PROCESS];

int numProcess = 0; // number of processes;

int min(int a,int b)
{
    if(a<b)
    {
        return a;
    }
    return b;
}
// -1 is just Assumption
int avgWaitingRR = -1;
int avgWaitingFCFS = -1;
int avgWaitingSRBF = -1;
int avgTurnAroundRR = -1;
int avgTurnAroundFCFS = -1;
int avgTurnAroundSRBF = -1;
int currentAlgo = 0;

void result()
{
    // This function is called and executed just before exiting the program.
    
    
    // This functions gives analysis of the scheduling algorithms executed via this program.
    // if only one process is executed and executed then it gives just info about that one process
    // if no processes are present it just prints "No process has runned so far..".
    // if >=2 scheduling allgorithms are executed , it wil print its info 
    // and gives comparison in the output file.
    
    
    int fd = open("results.txt" , O_RDWR | O_CREAT | O_TRUNC); // if file is not present it will create one.
    
    if(fd<0)
    {
        fprintf(stderr,"Unable to create the file 'results.txt' \n");
        exit(1);
    }
    
    
    // redirecting output 
    close(1); // closing stdout;
    dup(fd); // dup ing into stdout;
    close(fd); // closing fd;
    
/*---------------------------------------------------------------------------------------------------------------------------------------------------------*/
    
    if(avgTurnAroundSRBF==-1&&avgTurnAroundFCFS==-1&&avgTurnAroundRR==-1)
    {
        printf("No process has runned so far..\n");
    }
    else if(avgTurnAroundRR==-1 && avgTurnAroundFCFS == -1)
    {
        printf("Average Time AroundTime for SRBF : %d\n",avgTurnAroundSRBF);
        printf("Average Waiting time for SRBF : %d\n\n",avgWaitingSRBF);
        
        printf("There are no other processes to compare..\n");
    }
    else if(avgTurnAroundSRBF==-1 && avgTurnAroundRR == -1)
    {
        printf("Average Time AroundTime for FCFS : %d\n",avgTurnAroundFCFS);
        printf("Average Waiting time for FCFS : %d\n\n",avgWaitingFCFS);
        
        printf("There are no other processes to compare..\n");
    }
    else if(avgTurnAroundFCFS==-1 && avgTurnAroundSRBF==-1 )
    {
        printf("Average Time AroundTime for FCFS : %d\n",avgTurnAroundRR);
        printf("Average Waiting time for FCFS : %d\n\n",avgWaitingRR);
        
        printf("There are no other processes to compare..\n");
    }
    else if(avgWaitingRR == -1)
    {
        printf("Average Time AroundTime for FCFS : %d\n",avgTurnAroundFCFS);
        printf("Average Waiting time for FCFS : %d\n\n\n",avgWaitingFCFS);
        
        printf("Average Time AroundTime for SRBF : %d\n",avgTurnAroundSRBF);
        printf("Average Waiting time for SRBF : %d\n\n\n",avgWaitingSRBF);
        
        if(avgWaitingSRBF > avgWaitingFCFS)
        {
            printf("In case of avgWaitingTime : FCFS has less avgWaitingTime compared to  SRBF\n\n");
        }
        else if(avgWaitingSRBF < avgWaitingFCFS)
        {
            printf("In case of avgWaitingTime : SRBF has less avgWaitingTime compared to FCFS\n\n");
        }
        else
        {
            printf("Both FCFS and SRBF has equal avgWaitingTime\n\n");
        }
        
        if(avgTurnAroundSRBF > avgTurnAroundFCFS)
        {
            printf("In case of avgTurnAroundTime : FCFS has less avgTurnAroundTime compared to  SRBF\n\n");
        }
        else if(avgTurnAroundSRBF < avgTurnAroundFCFS)
        {
            printf("In case of avgTurnAroundTime : SRBF has less avgTurnAroundTime comparedred to FCFS\n\n");
        }
        else
        {
            printf("Both FCFS and SRBF has equal avgTurnAroundTime\n\n");
        }
    }
    else if(avgWaitingSRBF == -1)
    {
        printf("Average Time AroundTime for FCFS : %d\n",avgTurnAroundFCFS);
        printf("Average Waiting time for FCFS : %d\n\n\n",avgWaitingFCFS);
        
        printf("Average Time AroundTime for RR : %d\n",avgTurnAroundRR);
        printf("Average Waiting time for RR : %d\n\n\n",avgWaitingRR);
        
        if(avgWaitingRR > avgWaitingFCFS)
        {
            printf("In case of avgWaitingTime : FCFS has less avgWaitingTime compared to  RR\n\n");
        }
        else if(avgWaitingRR < avgWaitingFCFS)
        {
            printf("In case of avgWaitingTime : RR has less avgWaitingTime compared to FCFS\n\n");
        }
        else
        {
            printf("Both FCFS and RR has equal avgWaitingTime\n\n");
        }
        
        if(avgTurnAroundRR > avgTurnAroundFCFS)
        {
            printf("In case of avgTurnAroundTime : FCFS has less avgTurnAroundTime compared to  RR\n\n");
        }
        else if(avgTurnAroundRR < avgTurnAroundFCFS)
        {
            printf("In case of avgTurnAroundTime : RR has less avgTurnAroundTime comparedred to FCFS\n\n");
        }
        else
        {
            printf("Both FCFS and RR has equal avgTurnAroundTime\n\n");
        }
    }
    else if(avgTurnAroundFCFS == -1)
    {
        printf("Average Time AroundTime for RR : %d\n",avgTurnAroundRR);
        printf("Average Waiting time for RR : %d\n\n\n",avgWaitingRR);
        
        printf("Average Time AroundTime for SRBF : %d\n",avgTurnAroundSRBF);
        printf("Average Waiting time for SRBF : %d\n\n\n",avgWaitingSRBF);
        
        if(avgWaitingSRBF > avgWaitingRR)
        {
            printf("In case of avgWaitingTime : RR has less avgWaitingTime compared to  SRBF\n\n");
        }
        else if(avgWaitingSRBF < avgWaitingRR)
        {
            printf("In case of avgWaitingTime : SRBF has less avgWaitingTime compared to RR\n\n");
        }
        else
        {
            printf("Both RR and SRBF has equal avgWaitingTime\n\n");
        }
        
        if(avgTurnAroundSRBF > avgTurnAroundRR)
        {
            printf("In case of avgTurnAroundTime : RR has less avgTurnAroundTime compared to  SRBF\n\n");
        }
        else if(avgTurnAroundSRBF < avgTurnAroundRR)
        {
            printf("In case of avgTurnAroundTime : SRBF has less avgTurnAroundTime comparedred to RR\n\n");
        }
        else
        {
            printf("Both RR and SRBF has equal avgTurnAroundTime\n\n");
        }
    }
    else
    {
        printf("Average Time AroundTime for FCFS : %d\n",avgTurnAroundFCFS);
        printf("Average Waiting time for FCFS : %d\n\n\n",avgWaitingFCFS);
        
        printf("Average Time AroundTime for SRBF : %d\n",avgTurnAroundSRBF);
        printf("Average Waiting time for SRBF : %d\n\n\n",avgWaitingSRBF);
        
        printf("Average Time AroundTime for RR : %d\n",avgTurnAroundRR);
        printf("Average Waiting time for RR : %d\n\n\n",avgWaitingRR);
        
        
        if(avgWaitingSRBF > avgWaitingRR)
        {
            printf("In case of avgWaitingTime : RR has less avgWaitingTime compared to  SRBF\n\n");
        }
        else if(avgWaitingSRBF < avgWaitingRR)
        {
            printf("In case of avgWaitingTime : SRBF has less avgWaitingTime compared to RR\n\n");
        }
        else
        {
            printf("Both RR and SRBF has equal avgWaitingTime\n\n");
        }
        
        if(avgTurnAroundSRBF > avgTurnAroundRR)
        {
            printf("In case of avgTurnAroundTime : RR has less avgTurnAroundTime compared to  SRBF\n\n");
        }
        else if(avgTurnAroundSRBF < avgTurnAroundRR)
        {
            printf("In case of avgTurnAroundTime : SRBF has less avgTurnAroundTime comparedred to RR\n\n");
        }
        else
        {
            printf("Both RR and SRBF has equal avgTurnAroundTime\n\n");
        }
        
        /* ----------------------------------------------------*/
        
        if(avgWaitingRR > avgWaitingFCFS)
        {
            printf("In case of avgWaitingTime : FCFS has less avgWaitingTime compared to  RR\n\n");
        }
        else if(avgWaitingRR < avgWaitingFCFS)
        {
            printf("In case of avgWaitingTime : RR has less avgWaitingTime compared to FCFS\n\n");
        }
        else
        {
            printf("Both FCFS and RR has equal avgWaitingTime\n\n");
        }
        
        if(avgTurnAroundRR > avgTurnAroundFCFS)
        {
            printf("In case of avgTurnAroundTime : FCFS has less avgTurnAroundTime compared to  RR\n\n");
        }
        else if(avgTurnAroundRR < avgTurnAroundFCFS)
        {
            printf("In case of avgTurnAroundTime : RR has less avgTurnAroundTime comparedred to FCFS\n\n");
        }
        else
        {
            printf("Both FCFS and RR has equal avgTurnAroundTime\n\n");
        }
        
        
        /* ----------------------------------------- */
        
        if(avgWaitingSRBF > avgWaitingFCFS)
        {
            printf("In case of avgWaitingTime : FCFS has less avgWaitingTime compared to  SRBF\n\n");
        }
        else if(avgWaitingSRBF < avgWaitingFCFS)
        {
            printf("In case of avgWaitingTime : SRBF has less avgWaitingTime compared to FCFS\n\n");
        }
        else
        {
            printf("Both FCFS and SRBF has equal avgWaitingTime\n\n");
        }
        
        if(avgTurnAroundSRBF > avgTurnAroundFCFS)
        {
            printf("In case of avgTurnAroundTime : FCFS has less avgTurnAroundTime compared to  SRBF\n\n");
        }
        else if(avgTurnAroundSRBF < avgTurnAroundFCFS)
        {
            printf("In case of avgTurnAroundTime : SRBF has less avgTurnAroundTime comparedred to FCFS\n\n");
        }
        else
        {
            printf("Both FCFS and SRBF has equal avgTurnAroundTime\n\n");
        }
        
        /*-----------------------------------------------*/
        
        
    }
}
void ReadProcessTable(char *fileName)
{
    FILE *fp ;
    
    fp = fopen(fileName,"r");
    
    if(fp==NULL)
    {
        fprintf(stderr,"Error in opening a file or File not found\n");
        exit(1);
    }
    
    char word[MAX_SIZE]; // this stores(extracts) one word for each process from the file.
    
    
    
    int count = 0; // count if words.
    
    // if count % 3==0 new process has begin.
    
    while(fscanf(fp,"%s",word) != EOF)
    {
        if(count%3==0)
        {
            int lenProcessName = strlen(word);
            
            char *s = (char *)malloc(sizeof(char)*lenProcessName); // dynamic memory allocation.
            
            for(int i=0;i<lenProcessName;i++)
            {
                s[i] = word[i];
            }
            
            s[lenProcessName] = '\0';
            
            processTable[numProcess].name = s;
        }
        else if(count%3==1)
        {
            processTable[numProcess].arrival = atoi(word);
        }
        else
        {
            // for every 3rd word(burst time of each process) we go to nextprocess and store in that.
            processTable[numProcess].cpburst = atoi(word);
            
            processTable[numProcess].wait = -1;
            
            processTable[numProcess].turnaround = -1;
            
            numProcess++;
        }
        
        count++;
       
    }
}

void PrintProcessTable()
{
    // processName , processArrivalTime , processCpburst , processTurnaroundtime , processWaitingTime
    for(int i=0;i<numProcess;i++)
    {
        printf("%s %d %d %d %d\n",processTable[i].name,processTable[i].arrival,processTable[i].cpburst,processTable[i].turnaround,processTable[i].wait);
    }
}
void PrintStatistics()
{
    double sumTurnAround = 0; // represents totalTurnAroundTime.
    double sumWait = 0; // represnts totalWaitingtime of all the process
    
    printf("\nTurnaround times: ");
    for(int i=0;i<numProcess;i++)
    {
        printf("%s [%d]",processTable[i].name,processTable[i].turnaround);
        
        if(i!=numProcess-1)
        {
            printf(", ");
        }
        
        sumTurnAround += processTable[i].turnaround;
    }
    
    printf("\nWait times: ");
    for(int i=0;i<numProcess;i++)
    {
        printf("%s [%d]",processTable[i].name,processTable[i].wait);
        
        if(i!=numProcess-1)
        {
            printf(", ");
        }
        
        sumWait += processTable[i].wait;
    }
    
    // printing average turnaroundTime and average waiting time
    printf("\nAverage turnaround time: %.2f\n",sumTurnAround/numProcess);
    printf("Average wait time: %.2f\n",sumWait/numProcess);
    
    
    if(currentAlgo == 1)
    {
        avgTurnAroundFCFS = sumTurnAround/numProcess;
        avgWaitingFCFS = sumWait/numProcess;
    }
    else if(currentAlgo == 2)
    {
        avgTurnAroundRR = sumTurnAround/numProcess;
        avgWaitingRR = sumWait/numProcess;
    }
    else if(currentAlgo == 3)
    {
        avgTurnAroundSRBF = sumTurnAround/numProcess;
        avgWaitingSRBF = sumWait/numProcess;
    }
    
    
    
    
}

/*---------------------------------------------------------------------------------------------------------------------------------------------------------*/
void FCFS()
{
    // copy of arrival time.
    int arrivalTime[numProcess];
    
    
    for(int i=0;i<numProcess;i++)
    {
        arrivalTime[i] = processTable[i].arrival;
    }
    
    int currentTime = 0;
    
    for(int i=0;i<numProcess;i++)
    {
        // intially setting mini to numProcess, here mini represnts
        // minimum index / first process that has arrived in <= currentTime.
        int mini = numProcess;
        
        while(mini==numProcess)
        {
            for(int i=0;i<numProcess;i++)
            {
                if(arrivalTime[i]!=-1&&currentTime>=arrivalTime[i])
                {
                    mini = min(mini,i);
                }
            }
            
            // as we are still in for loop all processes are not yuet completed.
            // as mini = numProcess , then it represents that no processes are arrived at <=currentTime
            // so increase currentTime until you get the process
            // if you get the process complete its whole process and set currentTime to its completionTime
            if(mini==numProcess)
            {
                currentTime++;
            }
            else
            {
                break;
            }
        }
        
        // setting copy of arrivalTime to -1 as it must not to be considered in next iteration.
        arrivalTime[mini] = -1;
        
        // updating processTable for turnaroundTime
        processTable[i].turnaround = currentTime + processTable[i].cpburst - processTable[i].arrival;
        
        // updating processTable for waiting time.
        processTable[i].wait = processTable[i].turnaround - processTable[i].cpburst;
        
        // printing the current running processs.
        printf("[ %d - %d ]  %s running\n",currentTime,currentTime + processTable[i].cpburst,processTable[i].name);
        
        currentTime += processTable[i].cpburst;
        
    }
    
    
    // fucntion call for printing statistics.
    PrintStatistics();
}

void RR(int quantum)
{
    // ready queue.
    int queue[MAX_SIZE];
    // cpburstCopy , copy cpburst of the prrocesses.
    int cpburstCopy[MAX_PROCESS];
    // arrivalTime copy
    int arrivalTime[MAX_PROCESS];
    // storing completionTime of each processes .
    int completionTime[numProcess];
    
    // copying cpburstCopy and arrivalTime
    for(int i=0;i<numProcess;i++)
    {
        cpburstCopy[i] = processTable[i].cpburst;
        arrivalTime[i] = processTable[i].arrival;
    }
    
    
    // front of the queue.
    int front = -1;
    // rear of the queue.
    int rear = -1;
    
    /*
    condition for empty queue----
    
    if(front==-1||front>rear) -> then queue is empty...
    
    */
    
    // curremt time.
    int currentTime = 0;
    
    int zeroBurstCount = numProcess;
    
     int flag = -1;
     
     // here flag is intialised with -1 , 
     // here queue is ready queue.
     // if flag !=-1 (by that time I am checking which processes are arrived) and inserting this 
     //flag(actually processes_id(0,1,2,..)) into the queue at last.
     // here I am using zeroBurstCount , such that it will execute if atleast one cpburst is not zero. 
    
    while(zeroBurstCount)
    {
       
        while(1)
        {
            int mini = numProcess;
            for(int i=0;i<numProcess;i++)
            {
                // first checking by arrivalTime if same arrivalTime then checking by 
                // processes_id , here considering processes_id as 0,1,2,(although it is P0,P1,P2);
                if(arrivalTime[i]!=-1&&arrivalTime[i]<=currentTime)
                {
                    // taking minimum processes_id // although we can break when found.
                    mini = min(mini,i);
                }
            }
            
           
            //  if minimum processes_id is not found , then  the processes are
            //  not yet arrived till the currentTime, so we will goto the second condition.
            
            // if minimum processes_id is found then continue again.
            if(mini!=numProcess)
            {
                // setting arrivalTime to -1 so that is not taken into account again.
                 arrivalTime[mini] = -1;
                 
                if(front==-1)
                {
                    front = 0;
                }
                
                rear = rear + 1;
                
                queue[rear] = mini;
            }
            else
            {
                // if queue is empty and flag = -1 then increase currentTime;
                // becoz if flag !=-1 then already the before process that executed for a quantum and 
                // cpburst!=0 can be 
                // added to the queue.
                if((front==-1||front>rear) && flag == -1)
                {
                    currentTime++;
                }
                // if already elements are present in the ready queue then there
                // is no need to increase the currentTime.
                else
                {
                    break;
                }
            }
            
            
        }
        
        //this is to add the processes_id
        // that has not yet completed execution.
        
        if(flag!=-1)
        {
            rear = rear + 1;
                
            queue[rear] = flag;
                        
            flag = -1;
        }
        
        // removing and considering the front element of the queue., so increase front ...
        int pid = queue[front];
        
        front = front + 1;

        // checking whether remaining cpburst is greater than quantum
        // if so we can execute for quantum and add it to queue.
        // else no need to add to the queue.
        if(quantum < cpburstCopy[pid])
        {
            
            
            printf("[ %d - %d ]  %s running\n",currentTime,currentTime + quantum,processTable[pid].name);
            
            currentTime += quantum;
            
            cpburstCopy[pid] = cpburstCopy[pid] - quantum;
            
            // this completionTime will get updated whenever the process comes from the queue.
            // instead of tracking the last time it executed
            // I am updating for every quantum/time interval it executed.
            completionTime[pid] = currentTime;
            
            
            flag = pid;
            
            
        }
        else
        {
            
            
            printf("[ %d - %d ]  %s running\n",currentTime,currentTime + cpburstCopy[pid],processTable[pid].name);
            
            // as the process executed for remaining cpburstCopy[pid]
            // then currentTime will increase for that much time.
            currentTime += cpburstCopy[pid];
            
            cpburstCopy[pid] = 0;
            
            // as quantum is greater than remaining cpburst then number of 
            // remaining process that has not completed(meaning cpburst is not yet 0)
            // is decreased.
            zeroBurstCount--;
            
            completionTime[pid] = currentTime;
        }
        
    }
    
    // UPDATING turnaround and UPDATING wait in the processTable.
    for(int i=0;i<numProcess;i++)
    {
        processTable[i].turnaround = completionTime[i] - processTable[i].arrival;
        processTable[i].wait = processTable[i].turnaround - processTable[i].cpburst;
    }
    
    // calling function for printing statistics.
    PrintStatistics();
}

void SRBF()
{
    int arrivalTime[numProcess];
    int cpburstCopy[numProcess];
    int completionTime[numProcess];
    int prevProcess[numProcess];
    
    
    
    // creating copies of arrivalTime , cpburstCopy
    for(int i=0;i<numProcess;i++)
    {
        arrivalTime[i] = processTable[i].arrival;
        cpburstCopy[i] = processTable[i].cpburst;
        prevProcess[i] = 0;
    }
    
    int zeroBurstCount = numProcess;
    
    // intialise currentTime = 0;
    int currentTime = 0;
    
    int mini;
    
    while(zeroBurstCount)
    {
         mini = numProcess;
        
        while(mini==numProcess)
        {
            for(int i=0;i<numProcess;i++)
            {
                if(cpburstCopy[i]&&arrivalTime[i]<=currentTime)
                {
                    // first time update of mini.
                    if(mini==numProcess)
                    {
                        mini = i;
                    }
                    // fprintfding shortest burst time process
                    if(cpburstCopy[mini]>cpburstCopy[i])
                    {
                        mini = i;
                    }
                    // if burst time of shortest burst time process and current process are equal
                    // then gogin with FCFS
                    else if(cpburstCopy[mini]==cpburstCopy[i])
                    {
                        // checking arrival time.
                        if(arrivalTime[mini]>arrivalTime[i])
                        {
                            mini = i;
                        }
                    }
                }
            }
            // as process is not yet arrived and zeroBurstCount !=0 it represents still processes
            // are there that are yet to be arrived 
            // so mini = numProcess , increase currentTime .
            if(mini==numProcess)
            {
                currentTime++;
            }
            else
            {
                break;
            }
        }
        
      //  printf("[ %d - %d ]  %s running\n",currentTime,currentTime + 1,processTable[mini].name);
        
        // prevProcess[mini] = 0 , represents its not the same as previous Process.
        // so print prevProcessess which executed 
        if(prevProcess[mini]==0)
        {
            for(int i=0;i<numProcess;i++)
            {
                if(prevProcess[i])
                {
                    printf("[ %d - %d ]  %s running\n",currentTime-prevProcess[i],currentTime,processTable[i].name);
                    prevProcess[i] = 0;
                    break;
                    
                }
            }
        }
        
        // as now for 1 quantum mini will bew executed increase prevProcess[mini]-> this repres number of times
        // consecutively executed for each of 1 quantum.
        prevProcess[mini]++;
        
        // as we  are checking for every time quantum of 1 , then increase currentTime by 100000
        currentTime += 1;
        
        // keeping track of completionTime.
        completionTime[mini] = currentTime;
        
        // as we are going through every time quantum of 1. , decrement the current process(mini) cpburstCopy
        // by 1.
        cpburstCopy[mini] -= 1;
        
        // if current process cpburstCopy[mini] = 0 , then it means currents process
        // completed its whole execution.
        // hence decreasing the zeroBurstCount-> zeroBurstCount represents
        // remaming number of non-zeroBurstCounts.
        if(!cpburstCopy[mini])
        {
            zeroBurstCount--;
        }
        
        
    }
    
    // for printing of last process/\
      
    for(int i=0;i<numProcess;i++)
    {
        if(prevProcess[i])
        {
            printf("[ %d - %d ]  %s running\n",currentTime-prevProcess[i],currentTime,processTable[i].name);
            prevProcess[i] = 0;
            break;
                    
        }
    }
    
    
    // UPDATING turnaround and UPDATING wait in the processTable.
    for(int i=0;i<numProcess;i++)
    {
        processTable[i].turnaround = completionTime[i] - processTable[i].arrival;
        processTable[i].wait = processTable[i].turnaround - processTable[i].cpburst;
    }
    
    // calling function for printing statistics.
    PrintStatistics();
}

int main(int argc, char** args)
{
    numProcess = 0; // intialisizng number of Processes to zero(0);
    
    ReadProcessTable(args[1]); // reading file.
    
    // jsut for checking correct file input.
    //PrintProcessTable(); // for printing the table;
    

    while(1)
    {
        printf("-------------------------------------------------\n");
        printf("            CPU Scheduling Simulation              \n");
        printf("-------------------------------------------------\n");
        
        
        printf("Select the scheduling algorithm [1,2,3 or 4]:\n");
        printf("1. First Come First Served (FCFS)\n");
        printf("2. Round Robin (RR)\n");
        printf("3. SRBF\n");
        printf("4. Exit\n");
        
        int choice ;
        
        scanf("%d",&choice);
        
        currentAlgo = choice;
        
        if(choice == 1)
        {
             printf("------------------------------------------------------------------\n");
             printf("                  First Come First Served Scheduling              \n");
             printf("------------------------------------------------------------------\n");
            FCFS();
        }
        else if(choice == 2)
        {
             printf("-------------------------------------------------------------------\n");
             printf("                   Round Robin Scheduling                          \n");
             printf("-------------------------------------------------------------------\n");
            int quantum;
            
            printf("Enter the time quantum: ");
            scanf("%d",&quantum);
            
            RR(quantum);
        }
        else if(choice == 3)
        {
            printf("-------------------------------------------------------------------\n");
            printf("                   SRBF                          \n");
            printf("-------------------------------------------------------------------\n"); 
            
            SRBF();
        }
        else if(choice == 4)
        {
            result(); // analysis of the Scheduling Algorithms.
            // for exit.
            exit(0);
        }
        
        printf("Hit ENTER key to continue ... \n");
        char x;
        scanf("%c",&x); // this for previous entered "\n";
        scanf("%c",&x); // this for pressing new 'enter'
       // getch();
        //getch(); // taking input some random number.
    }
    
    
    
    
    
    
    
    
    
    
    
}


