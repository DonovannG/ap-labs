void merge(void *lineptr[], int a, int m, int b, int (*comp)(void *, void *))
{
    int i, j, k;
    int sizeL = m - a + 1;
    int sizeR = b - m;
  
    void *L[sizeL];
	void *R[sizeR];
  
    for (i = 0; i < sizeL; i++) {
		L[i] = lineptr[a + i];
	}
    for (j = 0; j < sizeR; j++) {
		R[j] = lineptr[m + 1 + j];
	}
  
    i = 0;
    j = 0; 
    k = a; 
    while (i < sizeL && j < sizeR) {
        if ((*comp)(L[i], R[j]) <= 0) {
            lineptr[k] = L[i];
            i++;
        }
        else {
            lineptr[k] = R[j];
            j++;
        }
        k++;
    }
  
    while (i < sizeL) {
        lineptr[k] = L[i];
        i++;
        k++;
    }
  
    while (j < sizeR) {
        lineptr[k] = R[j];
        j++;
        k++;
    }
}
  
void mergesort(void *lineptr[], int left, int right, 
	int (*comp)(void *, void *)) {
    if (left < right) {
        int middle = (left + right) / 2;
        mergesort(lineptr, left, middle, comp);
        mergesort(lineptr, middle + 1, right, comp);
        merge(lineptr, left, middle, right, comp);
    }
}