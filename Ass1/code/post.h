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
    int comment_count ; 
    struct Post * next ; 
    struct Post * prev ; 
} Post ; 

Post * createPost( char * username , char * caption ) ;



#endif