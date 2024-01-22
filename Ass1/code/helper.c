 #include "helper.h"

char *initializeString(char * strn ) {
    char *new = (char *)malloc(sizeof(char) * MAX_STR_LEN); 
    strncpy(new , strn , MAX_STR_LEN) ;
    return new ; 
} 

