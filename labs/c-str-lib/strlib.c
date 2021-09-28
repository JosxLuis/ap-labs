int mystrlen(char *str){
    int len=0;
    char *c;

    for(c=str;*c != '\0';c++){
        len++;
    }
    
    return len;
}

char *mystradd(char *origin, char *addition){
    char *result = origin + mystrlen(origin);
    while (*addition != '\0'){
        *result++ = *addition++;
    }

    *result = '\0';
    return origin;
}

int mystrfind(char *origin, char *substr){
    int len = 0, len2 = 0, verification = mystrlen(substr), tmp = 0;

    while(origin[len] != '\0') {
        tmp = len;
        while(origin[len] == substr[len2] && origin[len] != '\0') {
            len2++;
            len++;
        }
        if(len2 == verification){return tmp;}
        len2 = 0;
        len++;   
    }

    return -1;
}