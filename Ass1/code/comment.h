
#ifndef COMMENT_H
#define COMMENT_H

typedef struct Comment
{
    char *username;
    char *content;
  
} Comment;

Comment *createComment(char *username, char *content);

#endif
