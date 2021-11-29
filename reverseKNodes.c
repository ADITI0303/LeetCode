#include<stdio.h>
#include<stdlib.h>

// Definition for singly-linked list.
struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode* reverseKGroup(struct ListNode* head, int k){
    struct ListNode* current = head;
    int size = 0;
    while(current != NULL){
        ++size;
        current = current->next;
    }
    int times = size/k;
    current = head;
    struct ListNode* nextBatch = head;
    while(times!=0){
        int elements[k];
        for(int i=k-1; i>=0; i--){
            elements[i] = nextBatch->val;
            nextBatch = nextBatch->next;
        }
        for(int i=0; i<k; i++){
            current->val = elements[i];
            current = current->next;
        }
        --times;
        current = nextBatch;
    }
    return head;
}

int main(){
    struct ListNode *current = (struct ListNode*)malloc(sizeof(struct ListNode));
    struct ListNode *headFirst = (struct ListNode*)malloc(sizeof(struct ListNode));
    headFirst = NULL;
    current->val = 7;
    current->next = NULL;
    headFirst = current;
    current = (struct ListNode*)malloc(sizeof(struct ListNode*));
    current->val = 6;
    current->next = headFirst;
    headFirst = current;
    current = (struct ListNode*)malloc(sizeof(struct ListNode*));
    current->val = 5;
    current->next = headFirst;
    headFirst = current;
    current = (struct ListNode*)malloc(sizeof(struct ListNode*));
    current->val = 4;
    current->next = headFirst;
    headFirst = current;
    current = (struct ListNode*)malloc(sizeof(struct ListNode*));
    current->val = 3;
    current->next = headFirst;
    headFirst = current;
    current = (struct ListNode*)malloc(sizeof(struct ListNode*));
    current->val = 2;
    current->next = headFirst;
    headFirst = current;
    current = (struct ListNode*)malloc(sizeof(struct ListNode*));
    current->val = 1;
    current->next = headFirst;
    headFirst = current;
    current = (struct ListNode*)malloc(sizeof(struct ListNode*));
    current = headFirst;
    while(current != NULL){
        printf("%d ", current->val);
        current = current->next;
    }
    printf("\n");
    headFirst = reverseKGroup(headFirst, 3);
    current = headFirst;
    while(current != NULL){
        printf("%d ", current->val);
        current = current->next;
    }
}