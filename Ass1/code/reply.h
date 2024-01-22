#ifndef REPLY_H
#define REPLY_H


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "helper.h"

typedef struct Reply
{
    char *username;
    char *content;
    struct Reply * next ;
} Reply;

Reply* createReply( char * username , char * content ) ; 

#endif