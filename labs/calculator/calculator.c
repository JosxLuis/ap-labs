#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// adds/subtracts/multiplies all values that are in the *values array.
// nValues is the number of values you're reading from the array
// operator will indicate if it's an addition (1), subtraction (2) or
// multiplication (3)
long calc(int operator, int nValues, int *values) {
    if(nValues > 1){
        int resultado = values[2];
        printf("%i", values[2]);
        for (int i = 3; i < nValues; i++){
            if(operator == 1){
                printf(" + %i", values[i]);
                resultado += values[i];
            }else if(operator == 2){
                printf(" - %i", values[i]);
                resultado -= values[i];
            }else if(operator == 3){
                 printf(" * %i", values[i]);
                resultado *= values[i];
            }
        } 
        printf(" = %i ", resultado);  
        printf("\n");  
    }
    return 0;
}

int main(int argc, char*argv[]) {
    int num[argc];
    for (int i = 0; i < argc; i++){
        num[i]=atoi(argv[i]);
    }
    
    int operator = 0;
    if(strcmp("add", argv[1]) == 0){
        operator = 1;
    }

    if(strcmp("sub", argv[1]) == 0){
        operator = 2;     
    }
    if(strcmp("mult", argv[1]) == 0){
        operator = 3;
    }
    
    calc(operator,argc, num);
    return -1;
}