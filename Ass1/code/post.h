#ifndef POST_H
#define POST_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "comment.h"

typedef struct Post {
    char * username ; 
    char * caption ; 
    Comment * comments ; 
    Post * next ; 
} Post ; 

Post * createPost( char * name , char * caption ) ;

#endif