#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// adds/subtracts/multiplies all values that are in the *values array.
// nValues is the number of values you're reading from the array
// operator will indicate if it's an addition (1), subtraction (2) or
// multiplication (3)

long calc(int operator, int nValues, int *values) {
    
    int resultado = values[2];
    printf("%i", resultado);
    for (int i = 3; i < nValues; i++){
        if(operator == 1){
            printf(" + %i", values[i]);
            resultado += values[i];
        }else if(operator == 2){
            printf(" - %i", values[i]);
            resultado -= values[i];
        }else{
            printf(" * %i", values[i]);
            resultado *= values[i];
        }
    } 
    printf(" = %i \n", resultado);  
   
    return 0;
}

int main(int argc, char*argv[]) {

    if(argc > 3){
        int operator = 0;

        if(strcmp("add", argv[1]) == 0){
            operator = 1;
        }else if(strcmp("sub", argv[1]) == 0){
            operator = 2;     
        }else if(strcmp("mult", argv[1]) == 0){
            operator = 3;
        }else{
            printf("El operador %s no es valido \n", argv[1]);
            return -1;
        }

        int num[argc];     

        for (int i = 2; i < argc; ++i) {
            for(int j=0; j < strlen(argv[i]); j++){
                char letter = argv[i][j];
                if(!isdigit(argv[i][j])){
                    printf("No ingresaste un numero entero \n");
                    printf("No ingresaste suficientes parametros con el formato:");
                    printf("<operador> <numeros separados por espacio>\n");
                    return -1;
                } 
            }
            num[i]=atoi(argv[i]);   
        }
        
        calc(operator,argc, num);
        return -1;
    }else{
        printf("No ingresaste suficientes parametros: ");
        printf("<operador> <numeros separados por espacio>\n");
    }
}