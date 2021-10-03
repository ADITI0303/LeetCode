#include<iostream>
#include<stdlib.h>

using namespace std;

int main(){
    // string name = "abcabcdbb";
    string name = "pwwkewabcdefgggg";
    string newString;
    int longestCount = 0;
    char* ptr = &name[0];
    newString = *ptr;
    char* next = ptr+1;
    char* current = &name[0];
    string longest = current;
    int newCount; 
    int oldCount = 0;
    while(*current != '\0'){
        //Extact first string
        next = current + 1;
            oldCount = newCount;
            newCount = 1;
            newString = *current;
            //evaluate the string and it's newCount
            while(*next != '\0'){
                char* value = &newString[0];
                int flag = 0;
                while(*value != '\0'){
                    if(*value == *next){
                        flag = 1;
                        break;
                    }
                    value++;
                }
                if(flag == 1){
                    break;
                }
                else{
                    newString = newString + *next;
                    newCount++;
                    next++;
                }
            }
        // }
        //save this as the newString
        //save its newCount as the newnewCount;
        if(newCount > oldCount){
            longest = newString;
            longestCount = newCount;
        }
        current++;
    }
    cout<<"The longest string is: "<<longest<<" with a count: "<<longestCount<<"\n";
    return 0;
}