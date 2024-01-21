// post.h
#ifndef POST_H
#define POST_H

typedef struct Post
{
    char *username;
    char *caption;
} Post;

Post *createPost(char *username, char *caption);

#endif