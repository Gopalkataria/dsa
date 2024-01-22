#ifndef REPLY_H
#define REPLY_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>


typedef struct Reply
{
    char *username;
    char *content;
    Reply * next ;
} Reply;

#endif