#include <stdio.h>
#include <string.h>

extern int mystrlen(char *);
extern char *mystradd(char *, char *);
extern int mystrfind(char *, char *);

int main(int argc, char *argv[]) {

    if (strcmp(argv[1], "-add") == 0 && argc == 4) {

        printf("Initial Lenght      : %d\n", mystrlen(argv[2]));
        char *newString  = mystradd(argv[2],argv[3]);
        printf("New String          : %s\n", newString );
        printf("New length          : %d\n", mystrlen(newString));
        return 0;
    }

    if (strcmp(argv[1], "-find") == 0 && argc == 4) {
        int pos = mystrfind(argv[2], argv[3]);
        if (pos > -1) {
            printf("['%s'] string was found at [%d] position\n", argv[3], pos);
           
        } else {
            printf("String was not found");
        }
        return 0;
    }

    printf("Missing arguments or bad inputs\n");
    return 0;
}