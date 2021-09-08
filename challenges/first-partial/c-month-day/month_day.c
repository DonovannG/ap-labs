#include <stdio.h>
#include <stdlib.h>

static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

char *month_name(int *n) {

   static char *name[] = {
       "Illegal month",
       "January", "February", "March",
       "April", "May", "June",
       "July", "August", "September",
       "October", "November", "December"
   };

   return (*n < 1 || *n > 12) ? name[0] : name[*n];
}

/* month_day function's prototype*/
void month_day(int year, int yearday, int *pmonth, int *pday){
    int leap, i;
    leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
    if((leap == 0 && yearday > 365) || (leap == 1 && yearday > 366) ){
        printf("%s\n", "Error in Day");
    }else if (year < 0){
        printf("%s\n", "Error in year");
    }else{
        pday = &yearday;
        for(i=1; *pday > daytab[leap][i]; i++){
            *pday -= daytab[leap][i];
        }
        pmonth = &i;
        printf("%s %i, %i\n", month_name(pmonth), *pday, year);
    } 
}

int main(int agrc, char **args) {
    int year, yearday, *pmonth, *pday;
    if(args[1] == NULL || args[2] == NULL){
        printf("%s\n", "Error in inputs, write a month and year");
    }
    else{
        year = atoi(args[1]);
        yearday = atoi(args[2]);
        month_day(year, yearday, pmonth, pday);
    }
    return 0;
}
