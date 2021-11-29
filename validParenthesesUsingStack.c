#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

//Valid string combinations: (), [], {}
struct LinkedList{
    char val;
    struct LinkedList* next;
};

struct LinkedList* push(struct LinkedList* top, int data){
    struct LinkedList* node = (struct LinkedList*)malloc(sizeof(struct LinkedList));
    node->val = data;
    node->next = top;
    top = node;
    return top;
}

struct LinkedList* pop(struct LinkedList* top){
    struct LinkedList* node = top;
    top = node->next;
    node = NULL;
    return top;
}

bool isValid(char * s){
    char* ptr = s;
    ptr = s;
    struct LinkedList* top;
    top = NULL;
    while(*ptr != '\0'){
        if(*ptr == ')'){
            //check value at top of stack
            if(top != NULL){
                if(top->val == '('){
                    top = pop(top);
                }
                else{
                    //push the value
                    top = push(top,*ptr);
                }
            }
            else{
                //push the value
                top = push(top,*ptr);
            } 
        } 
        else if(*ptr == ']'){
            if(top != NULL){
                if(top->val == '['){
                    top = pop(top);
                }
                else{
                    //push the value
                    top = push(top,*ptr);
                }
            } 
            else{
                //push the value
                top = push(top,*ptr);
            }
        }
        else if(*ptr == '}'){
            if(top != NULL){
                if(top->val == '{'){
                    top = pop(top);
                }
                else{
                    // push the value
                    top = push(top,*ptr);
                }
            }
            else{
                //push the value
                top = push(top,*ptr);
            }           
        }
        //general block
        else{
            //push the value
            top = push(top,*ptr);
        }     
        ++ptr;
    }
    if(top == NULL){
        return true;
    }
    else{
        return false;
    }
}

int main(){
    bool value = isValid("((([]}))){}");
    printf("%d\n", value);
}