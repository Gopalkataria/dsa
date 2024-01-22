
#ifndef COMMENT_H
#define COMMENT_H

#include "reply.h"

typedef struct Comment
{
    char *username;
    char *content;
    Reply  *replies ;
    int reply_count ; 
    struct Comment * next ; 
} Comment;

Comment * createComment( char * username , char * content ) ;

#endif


