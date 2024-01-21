#include "post.h"
#include <stdlib.h>
#include <string.h>

Post *createPost(char *username, char *caption)
{
    Post *newPost = (Post *)malloc(sizeof(Post));
    if (newPost != NULL)
    {
        newPost->username = strdup(username);
        newPost->caption = strdup(caption);
    }
    return newPost;
}
