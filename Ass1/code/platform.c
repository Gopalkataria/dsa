#include "platform.h"

Platform *PLATFORM = NULL;

Platform *createPlatform()
{
    if (PLATFORM != NULL)
    {
        PLATFORM = (Platform *)malloc(sizeof(Platform));
        PLATFORM->posts = NULL;
        PLATFORM->lastViewedPost = NULL;
        PLATFORM->lastVeiwedEqualsLastPost = 1;
    }
    return PLATFORM;
}

bool addPost(char *username, char *caption)
{
    Post *newPost = createPost(username, caption);
    assert(newPost != NULL);
    Post *post = PLATFORM->posts;
    PLATFORM->posts->prev = newPost;
    PLATFORM->posts = newPost;
    newPost->next = post;

    PLATFORM->post_count++;
    return true;
}

bool delPost(int n)
{
    if (n > PLATFORM->post_count)
        return false;
    if (PLATFORM->post_count == 0)
        return false;
    Post *post = PLATFORM->posts;
    for (int i = 0; i < n - 1; i++)
    {
        post = post->next;
    }
    Post *prev_post = post->prev;
    Post *next_post = post->next;
    prev_post->next = next_post;
    next_post->prev = prev_post;

    free(post->username);
    free(post->caption);
    free(post);

    return true;
}

Post *viewPost(int n)
{
    if (n <= 0)
        return NULL;
    if (n > PLATFORM->post_count)
        return NULL;
    Post *post = PLATFORM->posts;
    for (int i = 0; i < n - 1; i++)
    {
        post = post->next;
    }
    PLATFORM->lastViewedPost = post;
    PLATFORM->lastVeiwedEqualsLastPost = 0;
    return post;
}

Post *currPost()
{
    return PLATFORM->lastViewedPost;
}

Post *nextPost()
{
    Post *next_post = PLATFORM->lastViewedPost->next;
    if (nextPost != NULL)
        PLATFORM->lastViewedPost = next_post;
    return next_post;
}

Post *prevPost() {
    Post * prev_post = PLATFORM->lastViewedPost->prev ; 
    if( prev_post != NULL) 
    PLATFORM->lastViewedPost = prev_post ; 
    return prev_post ; 
}
