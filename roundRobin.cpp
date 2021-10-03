#include<iostream>
#include<stdio.h>
#include<list>

using namespace std;

struct Process{
    int processName;
    int arrivalTime;
    int newArrivalTime;
    int burstTime;
};

struct ArrivalTimeComparator{
    bool operator()(const Process* process1, const Process* process2){
        return (*process1).arrivalTime < (*process2).arrivalTime;
    }
};

list<Process*> ready;
list<Process*> running;
list<Process*> waiting;
int id = 1;
int quantumTime = 3;
int completionTime = 0;
int processTime = 0;
int waitingTime = 0;
int runOnce = 1;

void addProcess(int arrival, int burst){
    Process* process = new Process;
    process->processName = id++;
    process->burstTime = burst;
    process->arrivalTime = arrival;
    process->newArrivalTime = process->arrivalTime;
    ready.push_back(process);
}

void printProcesses(){
    cout<<"\nProcess | Arrival Time | Burst Time\n";
    cout<<"-----------------------------------\n";
    for(Process* process : ready){
        cout<<"P"<<(*process).processName<<"      |      "<<(*process).arrivalTime<<"       |     "<<(*process).burstTime<<"     | ";
        cout<<"\n-----------------------------------";
        cout<<"\n";
    }
}

void processing(){
    list<Process*>* listName = &ready;
    while(!(*listName).empty()){
        printProcesses();
        Process* process = new Process;
        process = (*listName).front();
        processTime = (process->burstTime < quantumTime) ? (process->burstTime) : quantumTime;
        cout<<processTime<<endl;
        (*listName).pop_front();
        running.push_back(process);
        process->burstTime = (process->burstTime >= quantumTime) ? (process->burstTime - quantumTime) : 0;
        if(runOnce == 1 && process->arrivalTime != 0){
            completionTime = process->arrivalTime;
        }
        runOnce = 0;
        completionTime = completionTime + processTime;
        waitingTime = waitingTime + (completionTime - process->newArrivalTime - processTime);
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
        if(process->burstTime != 0){
            process->newArrivalTime = completionTime;
            ready.push_back(process);
        }
        if(!waiting.empty()){
            
            listName = &waiting;
        }
        else{
            listName = &ready;
        }
        cout<<"Completion Time: "<<completionTime<<endl;
    }
}

int main(){
    addProcess(0, 5);
    addProcess(1, 3);
    addProcess(2, 8);
    addProcess(3, 6);
    ready.sort(ArrivalTimeComparator());
    printProcesses();
    processing();
    cout<<"Completion Time: "<<completionTime<<endl;
    cout<<"Waiting Time: "<<waitingTime<<endl;
    return 0;
}