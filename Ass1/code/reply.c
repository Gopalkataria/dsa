#include "reply.h"
#include <stdlib.h>
#include <string.h>

Reply *createReply(char *username, char *content)
{
    Reply *newReply = (Reply *)malloc(sizeof(Reply));
    if (newReply != NULL)
    {
        newReply->username = strdup(username);
        newReply->content = strdup(content);
    }
    return newReply;
}