#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void merge(void *lineptr[], int left, int m, int right,
 			int (*comp)(void *, void *)) {
	int sizeL, sizeR, i, j, k;
	sizeL = m-left+1;
	sizeR = right-m;
	void L[sizeL], R[sizeR];
	for(i=0;i<sizeL;i++){
		L[i] = lineptr[left+i];
	}
	for(j=0;i<sizeR;j++){
		R[j] = lineptr[m+1+j];
	}
	i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
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
	int m = (left + right)/2;
	if(left<right){
		mergesort(lineptr[], left,  m, comp);
		mergesort(lineptr[], m+1,  right, comp);
		merge(lineptr[], left,  m, right, comp);
	}
}