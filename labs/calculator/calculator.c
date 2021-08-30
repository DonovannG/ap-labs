#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// adds/subtracts/multiplies all values that are in the *values array.
// nValues is the number of values you're reading from the array
// operator will indicate if it's an addition (1), subtraction (2) or
// multiplication (3)
long calc(int operator, int nValues, int *values) {
    int result = values[0];
    int i;
    if(operator == 1){
        printf("%d",result);
        for(i = 1; i<nValues; i++){
            printf(" + %d",values[i]);
            result += values[i];
        }
        return result;

    }else if (operator == 2){
        printf("%d",result);
        int tmp = 0;
        for(i = 1; i<nValues; i++){
            printf(" - %d",values[i]);
            tmp += values[i];
        }
        result = tmp - result;
        return result;

    }else if (operator == 3){
        printf("%d",result);
        for(i = 1; i<nValues; i++){
            printf(" * %d",values[i]);
            result*= values[i];
        }
        return result;

    }else{
        printf("Something went wrong, try again\n");
    }
    
    return 0;
}



int main(int argc, char **argv) {
    char str1[] = "add", str2[] = "sub", str3[] = "mult";
    char *ptr;
    int *arr;
    arr = malloc(sizeof(int)*argc-1);
    int j;
    long res;
    int oper;
    int f = 0;
    if(strcmp(str1, argv[1])==0){
        oper = 1;
    }else if(strcmp(str2, argv[1])==0){
        oper = 2;
    }else if(strcmp(str3, argv[1])==0){
        oper = 3;
    }else{
            printf("Need to put add, sub or mult\n");
            return -1;
    }
    
    for(j=0;j<argc-2;j++){
        if(strtol(argv[2+j], &ptr, 10)!=0){
            arr[j]=atoi(argv[2+j]);
            f++;
        }else{
           printf("No strings, only numbers\n"); 
           return -1;
        }
    }
    res = calc(oper, f, arr);
    if(oper == 2){
        printf(" = -%lu\n",res);
    }
    else{
        printf(" = %lu\n",res);
    }
    return -1;
}
