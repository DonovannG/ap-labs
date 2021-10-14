#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void quicksort(void *lineptr[], int left, int right,
	   int (*comp)(void *, void *));

void mergesort(void *lineptr[], int left, int right,
	   int (*comp)(void *, void *));

  
// function for comparing two integer strings
int cmpnum(void* s1, void* s2){
    int a = atoi(s1);
    int b = atoi(s2);
    if (a > b)
        return 1;
    else
        return -1;
}

int main(int argc, char **argv){
	if(argc < 4 || argc > 6) {
        if(argc == 1){
            printf("Error, only the following grammar is permitted\n");
			printf("For numbers: ./genericsort -n <input file> -<sort> -o <output file>\n");
            printf("For Strings: ./genericsort <input file> -<sort> -o <output file>\n");
            return 0;
        }
        if(strcmp(argv[1], "-n") == 0 && argc != 6){
		    printf("Error, if you're trying to use a numerical sort try the following:\n");
		    printf("./genericsort -n <input file> -<sort> -o <output file>\n");
            return 0;
        }else if(strcmp(argv[1], "-n") != 0 && argc != 5){
            printf("Error, if you're trying to use a string sort try the following:\n");
		    printf("./genericsort <input file> -<sort> -o <output file>\n");
            return 0;
        }else{
		    printf("Error, only the following grammar is permitted\n");
			printf("For numbers: ./genericsort -n <input file> -<sort> -o <output file>\n");
            printf("For Strings: ./genericsort <input file> -<sort> -o <output file>\n");
            return 0;
        }
	}
    
    FILE *fp;
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	char *fName;
	char *sort;
	char output[50];
    int num = 0;
    int lines = 0;
    int f = 0;

	if(strcmp(argv[1], "-n") == 0) {
		num = 1;
	}
  
	if(num == 1) {
		fName = argv[2];
		fp = fopen(fName, "r");
		sort = argv[3];
		strcpy(output, argv[5]);
	} else {
		fName = argv[1];
		fp = fopen(fName, "r");
		sort = argv[2];
		strcpy(output, argv[4]);
	}

    if(fp == NULL) {
		printf("Error, you sure the %s file exists?\n", fName);
		return 0;
	}	

	while((read = getline(&line, &len, fp)) != -1) {
		lines++;
	}

	fseek(fp, 0, SEEK_SET);
	char **arr = (char **)malloc(lines*sizeof(char*));
	while((read = getline(&arr[f], &len, fp)) != -1) {
		f++;
	}
	fclose(fp);

	if(strcmp(sort, "-quicksort") == 0) {
		printf("... sorting %s file with quicksort\n", fName);
		if(num == 1) {
			quicksort((void **) arr, 0, lines-1, (int(*)(void*, void*))(cmpnum));
		} else {
			quicksort((void **) arr, 0, lines-1, (int(*)(void*, void*))(strcmp));
		}
	} else if(strcmp(sort, "-mergesort") == 0) {
		printf("... sorting %s file with mergesort\n", fName);
		if(num == 1) {
			mergesort((void **) arr, 0, lines-1, (int(*)(void*, void*))(cmpnum));
		} else {
			mergesort((void **) arr, 0, lines-1, (int(*)(void*, void*))(strcmp));
		}
	} else {
		printf("Sowwy, I can only use quicksort or mergsort\n");
		return 0;
	}
	fp = fopen(output, "w");
	for(int i = 0; i < lines; i++) {
		fprintf(fp, "%s", arr[i]);
	}
	printf("... Results file can be found at %s\n", output);
	fclose(fp);
	return 0;
}
