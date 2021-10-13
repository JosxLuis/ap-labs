#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char **lineptr;

void quicksort(void *lineptr[], int left, int right,
	   int (*comp)(void *, void *));

void mergesort(void *lineptr[], int left, int right,
	   int (*comp)(void *, void *));

int readlines(FILE *in_file, int n){
	int nlines = n;
	char *line = NULL;
    size_t len = 0;
    ssize_t read;

	while((read = getline(&line, &len, in_file)) != -1) {
        nlines++;
    }

	fseek(in_file, 0, SEEK_SET);
    lineptr = (char **)malloc(nlines*sizeof(char*));
    int index = 0;
   
    while((read = getline(&lineptr[index], &len, in_file)) != -1) {
        index++;
    }

	return nlines;
}

void writelines(FILE *out_file, int nlines){
    for(int i = 0; i < nlines; i++) {
		fprintf(out_file, "%s", lineptr[i]);
	}
}

int numcmp(char *s1, char *s2){
    double v1,v2;
    v1 = atoi(s1);
    v2 = atoi(s2);
    if (v1 < v2){
        return -1;
    }else if (v1 > v2){
        return 1;
    }else{
        return 0;
    }
}

int main(int argc, char **argv){
    
	FILE *in_file;
    FILE *out_file;
    int nlines = 0, number = 0;
    char name_output[200] = "";
    char *algorithm;
	
    if (argc<3){
        printf("¡Error! Faltan argumentos:\n");
		printf("El formato para sort numberos: ./genericsort -n {input file} -{sort algorithm} -o {output file} \n");
		printf(" Or \n");
		printf("El formato para sort strings: ./genericsort {input file} -{sort algorithm} -o {output file} \n");
		printf(" \n"); 
        return -1;
    }

    if (strcmp(argv[1], "-n") == 0){ 
		if (argc == 6){
			number = 1;
			algorithm = argv[3];
			in_file = fopen(argv[2], "r"); 
			if (in_file == NULL){
				printf("¡Error! Archivo no encontrado");
				printf(" \n"); 
				return -1;
			}
		}else{
			printf("¡Error! Faltan argumentos:\n");
			printf("El formato para sort numberos: ./genericsort -n {input file} -{sort algorithm} -o {output file} \n");
			printf(" Or \n");
			printf("El formato para sort strings: ./genericsort {input file} -{sort algorithm} -o {output file} \n");
			printf(" \n"); 
			return -1;
		}
        
    }else{
		if (argc == 5){
			algorithm = argv[2];
			in_file = fopen(argv[1], "r"); 
			if (in_file == NULL){
				printf("¡Error! Archivo no encontrado");
				printf(" \n"); 
				return -1;
			}
		}else{
			printf("¡Error! Faltan argumentos:\n");
			printf("El formato para sort numberos: ./genericsort -n {input file} -{sort algorithm} -o {output file} \n");
			printf(" Or \n");
			printf("El formato para sort strings: ./genericsort {input file} -{sort algorithm} -o {output file} \n");
			printf(" \n"); 
			return -1;
		}
    }

	nlines = readlines(in_file, nlines);
    //printf("lines: %i\n", nlines);
	fclose(in_file);
	
	if (strcmp(algorithm, "-quicksort") == 0){
        quicksort((void **) lineptr, 0, nlines-1, number? (int (*)(void *, void *))numcmp : (int (*)(void *, void *))strcmp);
    }else if(strcmp(algorithm, "-mergesort") == 0){
		mergesort((void **) lineptr, 0, nlines -1, number? (int (*)(void *, void *))numcmp : (int (*)(void *, void *))strcmp);
    }else{
        printf("¡Error! Ingresaste mal el nombre del algortimo de ordenamiento:  \n");
		printf("Puedes usar mergesort o quicksort  \n");
		printf(" \n"); 
    }

    strcat(name_output, (number ? argv[5] : argv[4]));

	if ((out_file = fopen(name_output, "w")) == NULL){
		printf("¡Error! El archivo no puede crear \n");
		printf(" \n"); 
        return -1;
    }

	writelines(out_file, nlines);
    fclose(out_file);
	printf("El archivo con los resultados se puede encontrar en ./%s\n", name_output);
	printf(" \n"); 
    return 0;
}