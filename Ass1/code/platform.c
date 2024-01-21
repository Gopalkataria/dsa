#include "platform.h"
#include <stdlib.h>

Platform *createPlatform()
{
    Platform *newPlatform = (Platform *)malloc(sizeof(Platform));
    if (newPlatform != NULL)
    {
        newPlatform->posts = NULL;
        newPlatform->postCount = 0;
        newPlatform->lastViewedPost = -1;
    }
    return newPlatform;
}

int addPost(Platform *platform, char *username, char *caption)
{
}

int deletePost(Platform *platform, int n)
{
}

Post *viewPost(Platform *platform, int n)
{
}

