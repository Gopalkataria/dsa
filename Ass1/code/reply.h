#ifndef REPLY_H
#define REPLY_H
#define MAX_STR_LEN 100

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