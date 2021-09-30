#include <stdio.h>
#include <stdlib.h>


int mystrlen(char *str){
    int len = 0;
    while(*str != '\0'){
        len++;
        str++;
    }
    return len;
}

char *mystradd(char *origin, char *addition){
    int originLen = mystrlen(origin), addLen = mystrlen(addition), newLen = originLen + addLen;
    char* newString = (char *)malloc(newLen + 1);
    for(int i = 0; i < originLen; i++){
        newString[i] = origin[i];
    }
    for(int j = originLen; j < newLen; j++){
        newString[j] = addition[j-originLen];
    }
    return newString;
}

int mystrfind(char *origin, char *substr){
    int originLen = mystrlen(origin), subLen = mystrlen(substr);
    for(int i = 0; i <= originLen-subLen; i++){
        int j = 0;
        for(j; j < subLen; j++){
            if(origin[i+j] != substr[j]){
                break;
            }
        }
        if(j == subLen){
            return i;
        }
    }
    return -1;
}