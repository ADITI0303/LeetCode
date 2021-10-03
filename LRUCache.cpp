#include<iostream>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

using namespace std;

#define NUMOFFRAMES 4

//frame 0 is for administrative purposes only
//frames[0] = -1 always
int frames[NUMOFFRAMES+1];
int pageFaults = 0; 
int numOfPages = 0;

typedef struct _listitem{
    struct _listitem *next;
    struct _listitem *prev;
    int data;
}queueItem;

typedef struct _queueHeader{
    queueItem* first;
    queueItem* last;
}queueHeader;

queueHeader head;
int counter = 0;

int sizeOf(queueHeader* headNode){
    int count = 0;
    queueItem* item = headNode->first;
    if(head.first == (queueItem*)(&head)){
        return 0;
    }
    else{
        while(item != headNode->last){
            count++;
            item = item->next;
        }
        count++;
        return count;
    }
}

void enqueue(queueHeader* headNode, int data){
    queueItem* item = (queueItem*)malloc(sizeof(queueItem));
    item->data = data;
    item->next = item->prev = NULL;
    queueItem* temp = headNode->last;
    headNode->last = item;
    temp->next = item;
    item->prev = temp;
    item->next = (queueItem*)&head;
    counter++;
}

queueItem* dequeue(queueHeader* headNode){
    queueItem* item = headNode->first;
    if(item == (queueItem*)headNode){
        item = NULL;
    }
    else{
        headNode->first = item->next;
        headNode->first->prev = (queueItem*)headNode;
    }
    counter--;
    return item;
}

void printQueue(queueHeader* headNode){
    queueItem* item = headNode->first;
    for(int i=0; i<sizeOf(headNode); i++){
        cout<<"Item: "<<item->data<<" ";
        item = item->next;
    }
    cout<<"\n";
}

queueItem* removeAt(queueHeader* headNode, int position){
    queueItem* item = headNode->first;
    if(position < 0 || item == (queueItem*)headNode){
        return NULL;
    }
    int i = 0;
    while(item->next != headNode->first){
        if(position == i){
            item->prev->next = item->next;
            item->next->prev = item->prev;
            item->next = NULL;
            item->prev = NULL;
            counter--;
            return item;
        }
        item = item->next;
        i++;
    }
    return NULL;
}

int checkPage(queueHeader* headNode, int page){
    queueItem* item = headNode->first;
    for(int j=0; j<sizeOf(&head); j++){
        if(item->data == page){
            return j;
        }
        item = item->next;
    }
    return -1;
}

int main(){
    head.first = (queueItem*)(&head);
    head.last = (queueItem*)(&head); 
    int pages[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 5, 3, 0, 3, 2};
    for(int i=0; i<NUMOFFRAMES+1; i++){
        frames[i] = -1;
    }
    int size = 0;
    int index = 0;
    int frameCount = 0;
    int numOfPages = sizeof(pages)/sizeof(pages[0]);
    cout<<"Size: "<<sizeOf(&head)<<endl;
    for(int i=0; i<numOfPages; i++){
        int page = pages[i];
        queueItem* item = head.first;
        int result = checkPage(&head, page);
        if(result != -1){
            item = removeAt(&head, result);
            enqueue(&head, item->data);
        }
        else{
            if(sizeOf(&head) < NUMOFFRAMES){
                frames[i+1] = page;
                enqueue(&head, page);
            }
            else{
                item = dequeue(&head);
                enqueue(&head, page);
                for(int i=0; i<NUMOFFRAMES; i++){
                    if(frames[i+1] == item->data){
                        frames[i+1] = page;
                        break;
                    }
                }
            }
            pageFaults++;
        }
        // printQueue(&head);
        for(int i=0; i<NUMOFFRAMES; i++){
            cout<<frames[i+1]<<" ";
        }  
        cout<<endl; 
        // cout<<"frames[0]: "<<frames[0]<<endl;
    }
    cout<<"The number of page faults is: "<<pageFaults<<endl;
    return 0;
}