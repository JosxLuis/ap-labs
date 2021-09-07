#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* month_day function's prototype*/
void month_day(int year, int yearday, int *pmonth, int *pday){
    int year_day = yearday;
    
    static int month[]={0,31,59,90,120,151,181,212,243,273,304,334,365};
    static int month_bisi[]={0,31,60,91,121,152,182,213,244,274,305,335,366};

    if (year == 1){
        for(int i=0; i < 13; i++){
            if(year_day<=month_bisi[i]){ 
                *pmonth = i;
                *pday = year_day-month_bisi[i-1];
                break;
            }
        }   
    }else{
        for(int i=0; i < 13; i++){
            if(year_day<=month[i]){ 
                *pmonth = i;
                *pday = year_day-month[i-1];
                break;
            }
        }    
    } 
}

int main(int argc, char*argv[]) {
    int pmonth, pday;
    int data[argc];

    static char *name[] = {
       "Illegal month",
       "Jan", "Feb", "Mar",
       "Apr", "May", "Jun",
       "Jul", "Aug", "Sep",
       "Oct", "Nov", "Dec"
    };
    
    if (argc > 1){
        for (int i = 1; i < argc; i++){
            for (int j = 0; j < strlen(argv[i]); j++){
                if(!isdigit(argv[i][j])){
                    printf("No ingresaste un parametro valido \n");
                    printf("El formato es <year> <yearday> \n");
                    return -1;
                }
            }
            data[i]=atoi(argv[i]);   
        }
    }else{
        printf("No ingresaste un parametro valido \n");
        printf("El formato es <year> <yearday> \n");
        return -1; 
    } 
    
    if (data[1]%4 ==0 && data[1]%100 !=0 || data[1]%400 == 0){
        if (data[2] > 0 && data[2]<=366){
            month_day(1, data[2], &pmonth, &pday);
            printf("%s %i, %i \n",name[pmonth], pday, data[1]);
        }else{
            printf("el year %i solo tiene 366 dias: \n", data[1]);
            printf("El formato es <year> <yearday> \n");
        }      
    }else{
        if (data[2] > 0 && data[2]<=365){
            month_day(2, data[2], &pmonth, &pday);
            printf("%s %i, %i \n",name[pmonth], pday, data[1]);
        }else{
            printf("el year %i solo tiene 365 dias: \n", data[1]);
            printf("El formato es <year> <yearday> \n");
        }
    }

    return 0;
}