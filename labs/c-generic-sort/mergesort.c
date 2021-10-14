#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void merge(void *lineptr[], int left, int m, int right,
 			int (*comp)(void *, void *)) {
				 printf("2\n");
	int sizeL, sizeR, i, j, k;
	sizeL = m-left+1;
	sizeR = right-m;
	void *L[sizeL], *R[sizeR];
	for(i=0;i<sizeL;i++){
		L[i] = lineptr[left+i];
	}
	for(j=0;i<sizeR;j++){
		R[j] = lineptr[m+1+j];
	}
	i = 0; 
    j = 0; 
    k = left;
	while(i<sizeL && j<sizeR){
		if((*comp)(L[i],R[j])<=0){
			lineptr[k]=L[i];
			i++;
		}else{
			lineptr[k]=R[j];
			j++;
		}
		k++;
	}
	while(i<sizeL){
		lineptr[k]=L[i];
		i++;
		k++;
	}
	while(j<sizeR){
		lineptr[k]=R[j];
		j++;
		k++;
	}

}
void mergesort(void *lineptr[], int left, int right,
	       int (*comp)(void *, void *)) {
			   printf("1\n");
	int m = left  + (right - left)/2;
	if(left<right){
		mergesort(lineptr, left,  m, comp);
		mergesort(lineptr, m+1,  right, comp);
		merge(lineptr, left,  m, right, comp);
	}
}