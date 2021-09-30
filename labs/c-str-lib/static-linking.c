#include <stdio.h>
#include <string.h>

int mystrlen(char *str);
char *mystradd(char *origin, char *addition);
int mystrfind(char *origin, char *substr);

int main(int args, char* argv[]) {
    char add[] = "-add", find[] = "-find";
    if(args==4){
        if(strcmp(argv[1], add)==0){
            printf("Initial Lenght      : %d\n",mystrlen(argv[2]));
            printf("New String          : %s\n",mystradd(argv[2],argv[3]));
            printf("New Lenght          : %d\n",mystrlen(mystradd(argv[2],argv[3])));
        }else if(strcmp(argv[1], find)==0){
            if(mystrfind(argv[2], argv[3])!=1){
                printf("[%s] string was found at [%d] position\n",argv[3],mystrfind(argv[2], argv[3]));
            }else{
                printf("[%s] string wasn´t found in [%s] string\n",argv[3],argv[2]);
            }
        }else{
            printf("The only available options are [-add] and [-find], please use one of them\n");
            return 0;
        }
        return 1;
    }
    printf("Two strings are needed for this to work...\n");
    return 0;
}
