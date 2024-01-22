
#ifndef COMMENT_H
#define COMMENT_H

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
