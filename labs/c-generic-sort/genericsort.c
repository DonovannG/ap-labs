#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void quicksort(void *lineptr[], int left, int right,
	   int (*comp)(void *, void *));

void mergesort(void *lineptr[], int left, int right,
	   int (*comp)(void *, void *));

int cmpstr(void* v1, void* v2){
    char *a1 = *(char**)v1;
    char *a2 = *(char**)v2;
    return strcmp(a1, a2);
}
  
// function for comparing two integer strings
int cmpnum(void* s1, void* s2){
    int *a = (int*)s1;
    int *b = (int*)s2;
    if ((*a) > (*b))
        return 1;
    else if ((*a) < (*b))
        return -1;
    else
        return 0;
}

int main(int argc, char **argv)
{
    return 0;
}
