#include<iostream>
#include<stdlib.h>
#include<list>

using namespace std;

//Find the completion time
//Find the average waiting time;

struct Process{
    int processName;
    int burstTime;
    int arrivalTime;
};

struct ArrivalTimeComparator{
    bool operator()(const Process* process1, const Process* process2){
        return (*process1).arrivalTime < (*process2).arrivalTime;
    }
};

struct BurstTimeComparator{
    bool operator()(const Process* process1, const Process* process2){
        return (*process1).burstTime < (*process2).burstTime;
    }
};

list<Process*> ready;
list<Process*> running;
list<Process*> waiting;
int completionTime;
int waitingTime = 0;
int numberOfProcesses;
int id;
int runOnce = 1;

void sortByBurstTimes(){
    waiting.sort(BurstTimeComparator());
}

void processing(){
    //1. If ready is not empty, pick a process from ready
    //2. place it in runnning
    //3. when in running, add all process to waiting that have arrivals lesser than or equal to burst
    //4. sort the waiting queue
    //5. take first from waiting, place in running. 
    //6. Go to Step 3 until running is empty.
    //7. Go to Step 1.
    list<Process*>* listName = &ready;

    while(!(*listName).empty()){
        Process* process = new Process;
        process = (*listName).front();
        running.push_back(process);
        if(runOnce == 1 && process->arrivalTime != 0){
            completionTime = process->arrivalTime;
        }
        runOnce = 0;
        completionTime = process->burstTime + completionTime;
        waitingTime = waitingTime + (completionTime - process->arrivalTime - process->burstTime);
        (*listName).pop_front();
        numberOfProcesses++;
        Process* currProcess = new Process;
        while(!ready.empty()){
            currProcess = ready.front();
            if(currProcess->arrivalTime <= completionTime){
                waiting.push_back(currProcess);
                ready.pop_front();
            }
            else{
                break;
            }
        }
        running.pop_front();
        if(!waiting.empty()){
            sortByBurstTimes();
            listName = &waiting;
        }
        else{
            listName = &ready;
        }
    } 
}

void addProcess(int burst, int arrival){
    Process* process = new Process;
    process->processName = id++;
    process->burstTime = burst;
    process->arrivalTime = arrival;
    ready.push_back(process);
}

void printProcesses(){
    cout<<"\nProcess | Burst Time | Arrival Time\n";
    cout<<"-----------------------------------\n";
    for(Process* process : ready){
        cout<<"P"<<(*process).processName<<"      |      "<<(*process).burstTime<<"     |     "<<(*process).arrivalTime<<"       | ";
        cout<<"\n-----------------------------------";
        cout<<"\n";
    }
}

int main(){
    completionTime = 0;
    waitingTime = 0;
    numberOfProcesses = 0;
    id = 1;

    // Total Completion Time: 23
    // Number of Processes: 5
    // Average Waiting Time: 5.2
    // addProcess(6, 2);
    // addProcess(2, 5);
    // addProcess(8, 1);
    // addProcess(3, 0);
    // addProcess(4, 4);

    // Total Completion Time: 13
    // Number of Processes: 4
    // Average Waiting Time: 2
    // addProcess(3, 2);
    // addProcess(4, 0);
    // addProcess(2, 4);
    // addProcess(4, 5);

    addProcess(2, 3);
    addProcess(0, 4);
    addProcess(4, 2);
    addProcess(5, 4);
    printProcesses();

    ready.sort(ArrivalTimeComparator());
    processing();
    cout<<"Total Completion Time: "<<completionTime<<endl;
    cout<<"Number of Processes: "<<numberOfProcesses<<endl;
    cout<<"Total Waiting Time: "<<waitingTime<<endl;
    if(numberOfProcesses!=0){
        cout<<"Average Waiting Time: "<<(float)waitingTime/numberOfProcesses<<endl;
    }
    return 0;
}