#include "comment.h"
#include <stdlib.h>
#include <string.h>

Comment *createComment(char *username, char *content)
{
    Comment *newComment = (Comment *)malloc(sizeof(Comment));
    if (newComment != NULL)
    {
        newComment->username = strdup(username);
        newComment->content = strdup(content);
    }
    return newComment;
}
