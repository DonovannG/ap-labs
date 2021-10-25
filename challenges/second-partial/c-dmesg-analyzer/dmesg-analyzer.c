#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <fcntl.h> 
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define SIZE 4000
#define REPORT_FILE "report.txt"

void analizeLog(char *logFile, char *report);

struct Node{
    char *data;
    struct Node *next;
}; 

struct data{
    char *key; 
    char *info; 
};

struct nlist{
    struct nlist *next;
    char *name;
    char *def;
    struct Node *value;
};

void push(struct Node** ref, char *data){
    struct Node* node=(struct Node*)calloc(1,sizeof(struct Node));
    node->data=strdup(data);
    node->next=(*ref);
    (*ref) = node;
}

static struct nlist *table[SIZE];

unsigned hash(char *key){
    unsigned value;
    for(value = 0; *key != '\0'; key++){
        value = *key + 31 *value;
    }
    return  value % SIZE;
}

struct nlist *lookup(char *str){
    struct nlist *np;
    for(np = table[hash(str)]; np != NULL; np = np->next){
        if(strcmp(str, np->name) == 0){
            return np; 
        }
    }
    return NULL; 
}

struct nlist *insert(char *name, char *def){
    struct nlist *np;
    unsigned val;
    if((np=lookup(name))==NULL){ 
        np = (struct nlist *) calloc(1,sizeof(*np));
        if(np == NULL || (np->name=strdup(name))==NULL){
            return NULL;
        }
        val = hash(name);
        np->next = table[val];
        table[val] = np;
        np->value=NULL;
    }else
        free((void *)np->def);
    if((np->def = strdup(def))==NULL)
        return NULL;
    push(&np->value,def);
    return np;
}

struct data isGeneral(char *str){
    struct data data; 
    char* time;
    int len, lenK, trail, col; 
    len = lenK = trail = col = 0;
    char* tmp;
    char* msg;
    char* n = str;
    while(*n){
        len++;
        n++;
        if(*(n-1)==']') break;
    }
    if(len<1){
        data.key="General:";
        data.info=(char*) malloc(strlen(str)*sizeof(char)+1);
        strcpy(data.info, str);
        return data;
    };
    time = (char*) malloc(len*sizeof(char));
    strncpy(time, str, len);
    while(*n){
        if(lenK==0 && *n==' ') {
            trail++;
        }else if(col && *n==' '){
            break;
        }else if(*n==':' && !col){
            col=1;
            lenK++;
        }else{
            lenK++;
        }
        n++;

    }
    if(col){
        tmp=(char*) malloc(lenK*sizeof(char));
        strncpy(tmp,str+trail+len,lenK);
        msg = (char*) malloc(strlen(str)*sizeof(char)-trail-lenK+1);
        strcpy(msg, time);
        strcat(msg, n);
    }else{
        tmp = (char*) malloc(strlen("General:")*sizeof(char)+1);
        strcpy(tmp, "General:");
        msg = (char*) malloc(strlen(str)*sizeof(char)+1);
        strcpy(msg, str);
    }
    data.key=tmp;
    data.info=msg;
    return data;
}
   

int main(int argc, char **argv) {

    if (argc < 2) {
	    printf("Usage:./dmesg-analizer logfile.txt\n");
	    return 1;
    }

    analizeLog(argv[1], REPORT_FILE);

    return 0;
}

void analizeLog(char *logFile, char *report) {
    printf("Generating Report from: [%s] log file\n", logFile);


    // Implement your solution here.
    int bytes, file, pos, lenghtL, fp;
	char scanner;
    FILE *result = fopen(report, "w+");
    struct nlist *start;
    struct nlist *current; 
    file = 0;
    pos = 1;
    fp = open(logFile, O_RDONLY);
	if (fp == -1){
        printf("There's an error in the file, Fix it first I guess?\n");
        return;
    }
	do{
        bytes = read(fp, &scanner, 1);
        if(pos && bytes>0) {
            file++;
            pos=0;
        }
        if(scanner=='\n'){ 
            pos=1;
        }
    }while (bytes>0);
    lseek(fp,0,SEEK_SET);
    lenghtL = 0;
    do{
        bytes = read(fp, &scanner, 1);
        if(bytes>0){
            if(scanner =='\n'){
                if(lenghtL<1){
                    continue;
                }
                lenghtL++;
                lseek(fp,-lenghtL,SEEK_CUR);
                char* buffer = (char*) malloc(lenghtL*sizeof(char));
                read(fp,buffer,lenghtL);
                buffer[strcspn(buffer, "\n")] = 0;
                lenghtL=0;
                struct data data = isGeneral(buffer);
                insert(data.key,data.info);
            }else{
                lenghtL++;
            }
        }
    } while(bytes>0);
    close(fp);
    for(int i=0; i<=SIZE; i++){
        start=table[i];
        if(start==NULL){ 
            continue;
        }
        fputs(start->name, result);
        fputs("\n", result);
        for(current = start; current!=NULL; current = current->next){
            fputs(" ", result);
            fputs(current->def, result);
            fputs("\n", result);
        }
    }
    fclose(result);
    printf("Report is generated at: [%s]\n", report);
}