#include<stdio.h>
#include<stdlib.h>
// Definition for singly-linked list.
struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2){
    //initialize the string to be returned
    struct ListNode *head;
    struct ListNode *current = (struct ListNode*)malloc(sizeof(struct ListNode));
    // struct ListNode *sumOfNodes = (struct ListNode*)malloc(sizeof(struct ListNode));
    head = NULL;
    int carry=0;
    int sum=0;
    int size=0;
    //initialize two headers
    struct ListNode *header1 = (struct ListNode*)malloc(sizeof(struct ListNode));
    struct ListNode *header2 = (struct ListNode*)malloc(sizeof(struct ListNode));
    header1 = l1;
    header2 = l2;
    while(1){
        if(header1 == NULL || header2 == NULL){
            break;
        }
        sum = header1->val + header2->val + carry;
        if(sum>=10){
            sum = sum-10;
            carry = 1;
        }
        else{
            carry = 0;
        }
        current->val = sum;
        current->next = head;
        head = current;
        ++size;
        current = (struct ListNode*)malloc(sizeof(struct ListNode));
        header1 = header1->next;
        header2 = header2->next; 
    }
    if(header1==NULL){
        while(header2 != NULL){
            sum = header2->val + carry;
            if(sum >= 10){
                sum = sum-10;
                carry = 1;
            }
            else{
                carry = 0;
            }
            current->val = sum;
            current->next = head;
            head = current;
            current = (struct ListNode*)malloc(sizeof(struct ListNode));
            header2 = header2->next;
            ++size;
        }
    }
    else{
        while(header1 != NULL){
            sum = header1->val + carry;
            if(sum >= 10){
                sum = sum-10;
                carry = 1;
            }
            else{
                carry = 0;
            }
            current->val = sum;
            current->next = head;
            head = current;
            current = (struct ListNode*)malloc(sizeof(struct ListNode));
            header1 = header1->next;
            ++size;
        }
    }
    if(carry == 1){
        current->val = carry;
        current->next = head;
        head = current;
        current = (struct ListNode*)malloc(sizeof(struct ListNode));
        ++size;
    }
    
    current = head;
    // while(current != NULL){
    //     printf("(%d) ",current->val);
    //     current = current->next;
    // }
    //Reversing the array:
    // struct ListNode *sumOfNodes = (struct ListNode*)malloc(sizeof(struct ListNode));
    // struct ListNode *newCurrent = (struct ListNode*)malloc(sizeof(struct ListNode));
    int elements[size];
    printf("Size: %d\n", size);
    for (int i = size-1; i >= 0; i--)
    {
        elements[i] = current->val;
        current = current->next;
    }
    for (int i = 0; i < size; i++)
    {
        printf("elements[%d]: %d ", i, elements[i]);
    }
    
    current = (struct ListNode*)malloc(sizeof(struct ListNode));
    head = NULL;
    for (int i = size-1; i >= 0; i--)
    {
        current->val = elements[i];
        current->next = head;
        head = current;
        current = (struct ListNode*)malloc(sizeof(struct ListNode));
    }
    current = head;
    while(current != NULL){
        printf("(%d)",current->val);
        current = current->next;
    }
    
}

int main(){
    struct ListNode *current = (struct ListNode*)malloc(sizeof(struct ListNode));
    //Creating linked list 1
    struct ListNode *headFirst = (struct ListNode*)malloc(sizeof(struct ListNode));
    headFirst = NULL;
    current->val = 3;
    current->next = NULL;
    headFirst = current;
    current = (struct ListNode*)malloc(sizeof(struct ListNode*));
    current->val = 4;
    current->next = headFirst;
    headFirst = current;
    current = (struct ListNode*)malloc(sizeof(struct ListNode*));
    current->val = 2;
    current->next = headFirst;
    headFirst = current;

    //Creating list 2
    struct ListNode *headSecond = (struct ListNode*)malloc(sizeof(struct ListNode));
    headSecond = NULL;
    current = (struct ListNode*)malloc(sizeof(struct ListNode*));
    current->val = 9;
    current->next = NULL;
    headSecond = current;
    current = (struct ListNode*)malloc(sizeof(struct ListNode*));
    current->val = 8;
    current->next = headSecond;
    headSecond = current;
    current = (struct ListNode*)malloc(sizeof(struct ListNode*));
    current->val = 6;
    current->next = headSecond;
    headSecond = current;
    current = (struct ListNode*)malloc(sizeof(struct ListNode*));
    current->val = 9;
    current->next = headSecond;
    headSecond = current;
    addTwoNumbers(headFirst, headSecond);
}