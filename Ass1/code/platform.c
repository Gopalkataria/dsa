#include "platform.h"

Platform *PLATFORM = NULL;

// @brief Creates a new platform
Platform *createPlatform()
{

    PLATFORM = (Platform *)malloc(sizeof(Platform));
    PLATFORM->posts = NULL;
    PLATFORM->lastViewedPost = NULL;
    PLATFORM->lastVeiwedEqualsLastPost = 1;
    PLATFORM->post_count = 0;
    return PLATFORM;
}

// @brief Adds a new post to the platform
// @param username The username of poster
// @param caption The caption of the post
bool addPost(char *username, char *caption)
{
    Post *new_post = createPost(username, caption);
    assert(new_post != NULL);
    Post *post = PLATFORM->posts;
    if (post != NULL)
    {
        post->prev = new_post;
    }
    new_post->next = post;
    PLATFORM->posts = new_post;

    if (PLATFORM->lastVeiwedEqualsLastPost)
    {
        PLATFORM->lastViewedPost = PLATFORM->posts;
    }
    PLATFORM->post_count++;
    return true;
}

// @brief Deletes nth recent post from the platform
// 
bool deletePost(int n)
{
    if (n > PLATFORM->post_count || PLATFORM->post_count == 0)
        return false;
    Post *post = PLATFORM->posts;
    for (int i = 0; i < n - 1; i++)
    {
        post = post->next;
    }
    Post *prev_post = post->prev;
    Post *next_post = post->next;
    if (prev_post != NULL)
        prev_post->next = next_post;
    if (next_post != NULL)
        next_post->prev = prev_post;

    if (n == 1)
    {
        PLATFORM->posts = next_post;
    }

    if (PLATFORM->lastViewedPost == post)
    {
        PLATFORM->lastViewedPost = PLATFORM->posts;
        PLATFORM->lastVeiwedEqualsLastPost = 1;
    }

    free(post->username);
    free(post->caption);
    while (post->comments != NULL)
    {
        Comment *_old_comment = post->comments;
        post->comments = post->comments->next;
        while (_old_comment->replies != NULL)
        {
            Reply *_old_reply = _old_comment->replies;
            _old_comment->replies = _old_comment->replies->next;
            free(_old_reply->username);
            free(_old_reply->content);
            free(_old_reply);
        }

        free(_old_comment->username);
        free(_old_comment->content);
        free(_old_comment);
    }

    free(post);

    PLATFORM->post_count--;

    return true;
}

// @brief Views nth recent post from the platform
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

// @brief Returns the current post
Post *currPost()
{
    if (PLATFORM->lastVeiwedEqualsLastPost)
    {
        PLATFORM->lastVeiwedEqualsLastPost = 0;
        return PLATFORM->posts;
    }
    return PLATFORM->lastViewedPost;
}

// @brief Returns the next post
Post *nextPost()
{
    if ( PLATFORM->posts == NULL  || PLATFORM->lastViewedPost == NULL) 
    return NULL  ; 

    PLATFORM->lastVeiwedEqualsLastPost = 0;

    if( PLATFORM->post_count == 1 ){
        PLATFORM->lastViewedPost = PLATFORM->posts ;
        return PLATFORM->posts ; 
    }

    Post *next_post = PLATFORM->lastViewedPost->next;
    if( next_post == NULL ){
        return PLATFORM->lastViewedPost ; 
    }
    if (PLATFORM->lastViewedPost->next != NULL)
        PLATFORM->lastViewedPost = next_post;
    return next_post;
}

// @brief Returns the previous post
Post *prevPost()
{

    if (PLATFORM->posts == NULL || PLATFORM->lastViewedPost == NULL)
        return NULL;

    PLATFORM->lastVeiwedEqualsLastPost = 0;

    if (PLATFORM->post_count == 1)
    {
        PLATFORM->lastViewedPost = PLATFORM->posts;
        return PLATFORM->posts;
    }

    Post *prev_post = PLATFORM->lastViewedPost->prev;
    if (prev_post == NULL)
    {
        return PLATFORM->lastViewedPost;
    }
    if (PLATFORM->lastViewedPost->prev != NULL)
        PLATFORM->lastViewedPost = prev_post;
    return prev_post;
}

// @brief Adds a comment to the current post
// @param username The username of the commenter
// @param content The content of the comment
bool addComment(char *username, char *content)
{
    if (PLATFORM->lastViewedPost == NULL)
        return false;
    Comment *new_comment = createComment(username, content);
    if (new_comment == NULL)
        return false;
    Comment *old_comment = PLATFORM->lastViewedPost->comments;
    if (old_comment == NULL)
    {
        PLATFORM->lastViewedPost->comments = new_comment;
    }
    else
    {
        while (old_comment->next != NULL)
        {
            old_comment = old_comment->next;
        }
        old_comment->next = new_comment;
    }
    PLATFORM->lastViewedPost->comment_count++;
    return true;
}

// @brief Deletes nth comment from the current post
bool deleteComment(int n)
{
    if (PLATFORM->lastViewedPost == NULL || PLATFORM->lastViewedPost->comments == NULL)
        return false;
    int m = PLATFORM->lastViewedPost->comment_count;
    if (n < 1 || m < n)
        return false;
    Comment *oldcomment = PLATFORM->lastViewedPost->comments;
    Comment *delete_comment = NULL;
    if (n == m)
    {
        PLATFORM->lastViewedPost->comments = oldcomment->next;
        delete_comment = oldcomment;
    }
    else
    {
        for (int i = 0; i < m - n - 1; i++)
        {
            oldcomment = oldcomment->next;
        }
        delete_comment = oldcomment->next;
        oldcomment->next = delete_comment->next;
    }

    while (delete_comment->replies != NULL)
    {
        Reply *_old_reply = delete_comment->replies;
        delete_comment->replies = delete_comment->replies->next;
        free(_old_reply);
    }

    free(delete_comment);
    PLATFORM->lastViewedPost->comment_count--;
    return true;
}

// @brief Returns the comments of the current post
Comment *viewComments()
{
    if (PLATFORM->lastViewedPost == NULL)
        return NULL;
    return PLATFORM->lastViewedPost->comments;
}

// @brief Adds a reply to nth comment of the current post
// @param username The username of the replier
// @param content The content of the reply
// @param n The nth recent comment
bool addReply(char *username, char *content, int n)
{
    if (PLATFORM->lastViewedPost == NULL)
        return false;
    Comment *comment = PLATFORM->lastViewedPost->comments;
    for (int i = 0; i < n - 1; i++)
    {
        comment = comment->next;
    }
    Reply *new_reply = createReply(username, content);
    if (new_reply == NULL)
        return false;
    Reply *old_reply = comment->replies;
    if (old_reply == NULL)
    {
        comment->replies = new_reply;
    }
    else
    {
        while (old_reply->next != NULL)
        {
            old_reply = old_reply->next;
        }
        old_reply->next = new_reply;
    }
    comment->reply_count++;
    return true;
}

// @brief Deletes mth reply from nth comment of the current post
// @param n The nth recent comment
// @param m The mth recent reply
bool deleteReply(int n, int m)
{
    if (PLATFORM->lastViewedPost == NULL)
        return false;
    Comment *comment = PLATFORM->lastViewedPost->comments;
    for (int i = 0; i < n - 1; i++)
    {
        comment = comment->next;
    }
    Reply *old_reply = comment->replies;
    if (old_reply == NULL)
        return false;
    Reply *delete_reply = NULL;
    if (m == comment->reply_count)
    {
        comment->replies = old_reply->next;
        delete_reply = old_reply;
    }
    else
    {
        for (int i = 0; i < comment->reply_count - m - 1; i++)
        {
            old_reply = old_reply->next;
        }
        delete_reply = old_reply->next;
        old_reply->next = delete_reply->next;
    }
    free(delete_reply);
    comment->reply_count--;
    return true;
}

// @brief Deletes the platform, free all memory to avoid leaks 
// when the user exits, the social networks ceases to exist :( 
void deletePlatform()
{

    Post *post = PLATFORM->posts;
    while (post != NULL)
    {
        Post *old_post = post;
        post = post->next;
        free(old_post->username);
        free(old_post->caption);
        Comment *comment = old_post->comments;
        while (comment != NULL)
        {
            Comment *old_comment = comment;
            comment = comment->next;
            free(old_comment->username);
            free(old_comment->content);
            Reply *reply = old_comment->replies;
            while (reply != NULL)
            {
                Reply *old_reply = reply;
                reply = reply->next;
                free(old_reply->username);
                free(old_reply->content);
                free(old_reply);
            }
            free(old_comment);
        }
        free(old_post);
    }
}