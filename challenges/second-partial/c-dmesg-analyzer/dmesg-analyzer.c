#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define REPORT_FILE "report.txt"
#define MAXLINES 5000
#define HASHSIZE 10000

char * arraylines[HASHSIZE];

void analizeLog(char * logFile, char * report);
int readlines(FILE * in_file, int n);

struct Item {
   char *key,
        defn[HASHSIZE];
};

struct Item* hashtab[HASHSIZE];

unsigned long hash(unsigned char *str){
  unsigned int hash = 0;
  int c;
  while (c = *str++)
    hash += c;
  return hash %= HASHSIZE;
}

void install(char *key, char *defn) {
    int hind = hash(key);
    while(hashtab[hind] != NULL) {
        if(strcmp(hashtab[hind]->key, key) == 0){ 
            strcat(hashtab[hind]->defn, "\t");
            strcat(hashtab[hind]->defn, defn);
            return;
        }
        ++hind;
        hind %= HASHSIZE;
    }
	
    struct Item *item = (struct Item*) malloc(sizeof(struct Item));
    item->key = (char*) malloc(100);
    strcpy(item->key, key);
    strcat(item->defn, "\t"); 
    strcat(item->defn, defn); 

    hashtab[hind] = item;
}

int readlines(FILE * in_file, int n) {
  int nlines = n;
  char * line = NULL;
  size_t len = 0;
  ssize_t read;

  int contador = 0;
  while ((read = getline( & line, & len, in_file)) != -1) { 
    arraylines[contador] = malloc(read+1);
    if ((contador > 4999)) {
      return -1;
    }

    if (strlen(line) == 0 || strcasecmp(line, "\n") == 0) continue;
    strcpy(arraylines[contador], line);
    contador++;
    nlines++;
  }

  return nlines;
}

void analizeLog(char * logFile, char * report) {
  FILE * in_file;
  int nlines = 0;

  printf("Generating Report from: [%s] log file\n", logFile);

  in_file = fopen(logFile, "r");
  nlines = readlines(in_file, nlines);
  fclose(in_file);
  
  for (int i = 0; i < nlines; i++) {
    int size = strlen(arraylines[i]);
    
    char key[5000] = "\0";
    char timelog[5000];
    char message[5000];
    char message2[5000];
    int first_points = 0;
    int cont_key = 0;
    int cont_menssage = 0;
    int flag = 0;

    for (int j = 0; j < size; j++) {
      if (j < 13) {
        if (!(arraylines[i][j] == ' ' && arraylines[i][j-1] == ']')) {
          timelog[j] = arraylines[i][j];
        }
      }else if(first_points == 0){
        if(!(arraylines[i][j] == ' ' && arraylines[i][j-1] == ':')){
          key[cont_key] = arraylines[i][j];
          cont_key++;
        }else{
          first_points = 1;
        }
      }else{
        message2[cont_menssage] = arraylines[i][j];
        cont_menssage++;
      }
    } 

    if(first_points == 0) {
      strcpy(message2, "");
      strcpy(message2, key);
      strcpy(key, "General :");
    }

    strcat(message,timelog);
    strcat(message," ");
    strcat(message,message2);

    install(key, message);

    memset(key, 0,5000);
    memset(timelog, 0,5000);
    memset(message, 0,5000);
    memset(message2, 0,5000);

  }
 
  // Crear reporte.txt
  int ptr = open(report, O_CREAT | O_WRONLY, 0600);

  if(ptr < 0){
    printf("¡Error! No se puede crear el report ");
    return;
  }

  for(int i = 0; i<HASHSIZE; i++) {
    if(hashtab[i] != NULL){
        const int SIZE = 10000;
        char item[SIZE];
        snprintf(item, SIZE, "%s: \n%s\n", hashtab[i]->key, hashtab[i]->defn);
        write(ptr, item, strlen(item));
    }
  }
  close(ptr);

  printf("Report is generated at: [%s]\n", report);
}

int main(int argc, char ** argv) {

  if (argc < 2) {
    printf("Usage:./dmesg-analizer logfile.txt\n");
    return 1;
  }

  analizeLog(argv[1], REPORT_FILE);

  return 0;
}