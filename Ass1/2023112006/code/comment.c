#include "comment.h"

Comment *createComment(char *username, char *content)
{
    Comment *newComment = (Comment *)malloc(sizeof(Comment));
    newComment->username = initializeString(username);
    newComment->content = initializeString(content) ; 
    newComment->next = NULL ; 
    newComment->reply_count = 0 ; 
    return newComment ; 
}
