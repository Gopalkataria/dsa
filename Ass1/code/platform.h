#ifndef PLATFORM_H
#define PLATFORM_H

#include "post.h"
#include "comment.h"

typedef struct Platform
{
    Post **posts;
    int postCount;
    int lastViewedPost;
} Platform;

Platform *createPlatform();
int addPost(Platform *platform, char *username, char *caption);
int deletePost(Platform *platform, int n);
Post *viewPost(Platform *platform, int n);


#endif
