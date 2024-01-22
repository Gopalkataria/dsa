#include "platform.h"

Platform *PLATFORM = NULL;

Platform *createPlatform()
{

    PLATFORM = (Platform *)malloc(sizeof(Platform));
    PLATFORM->posts = NULL;
    PLATFORM->lastViewedPost = NULL;
    PLATFORM->lastVeiwedEqualsLastPost = 1;
    PLATFORM->post_count = 0;
    return PLATFORM;
}

bool addPost(char *username, char *caption)
{
    Post *new_post = createPost(username, caption);
    assert(new_post != NULL);
    Post *post = PLATFORM->posts;
    if (post != NULL)
        post->prev = new_post;
    PLATFORM->posts = new_post;
    new_post->next = post;

    if (PLATFORM->lastVeiwedEqualsLastPost)
    {
        PLATFORM->lastViewedPost = PLATFORM->posts;
    }
    PLATFORM->post_count++;
    return true;
}

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
    prev_post->next = next_post;
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
            while (_old_comment->replies != NULL)
            {
                Reply *_old_reply = _old_comment->replies;
                _old_comment->replies = _old_comment->replies->next;
                free(_old_reply);
            }
        {
            Reply *_old_reply = _old_comment->replies;
            _old_comment->replies = _old_comment->replies->next;
            free(_old_reply);
        }

        free(_old_comment);
    }

    free(post);

    PLATFORM->post_count--;

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

Post *prevPost()
{
    Post *prev_post = PLATFORM->lastViewedPost->prev;
    if (prev_post != NULL)
        PLATFORM->lastViewedPost = prev_post;
    return prev_post;
}

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

bool deleteComment(int n)
{
    int m = PLATFORM->lastViewedPost->comment_count;
    if (n < 1 || m < n)
        return false;
    // 10 9 8 7 6 5 4 3 2 1
    // n = 7
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

    PLATFORM->lastViewedPost->comment_count--;
    return true;
}


Comment * viewComments(){
    if ( PLATFORM->lastViewedPost == NULL ) 
    return NULL ; 
    return PLATFORM->lastViewedPost->comments ; 
}


bool addReply( char * username , char * content  , int n ){
    if ( PLATFORM->lastViewedPost == NULL ) 
    return false ; 
    Comment * comment = PLATFORM->lastViewedPost->comments ; 
    for ( int i = 0 ; i < n - 1 ; i++ ){
        comment = comment->next ; 
    }
    Reply * new_reply = createReply( username , content ) ; 
    if ( new_reply == NULL ) 
    return false ; 
    Reply * old_reply = comment->replies ; 
    if ( old_reply == NULL ) {
        comment->replies = new_reply ; 
    } else {
        while ( old_reply->next != NULL ){
            old_reply = old_reply->next ; 
        }
        old_reply->next = new_reply ; 
    }
    comment->reply_count++ ; 
    return true ;

}

bool deleteReply( int n , int m ){
    if ( PLATFORM->lastViewedPost == NULL ) 
    return false ; 
    Comment * comment = PLATFORM->lastViewedPost->comments ; 
    for ( int i = 0 ; i < n - 1 ; i++ ){
        comment = comment->next ; 
    }
    Reply * old_reply = comment->replies ; 
    if ( old_reply == NULL ) 
    return false ; 
    Reply * delete_reply = NULL ; 
    if ( m == comment->reply_count ){
        comment->replies = old_reply->next ; 
        delete_reply = old_reply ; 
    } else {
        for ( int i = 0 ; i < comment->reply_count - m - 1 ; i++ ){
            old_reply = old_reply->next ; 
        }
        delete_reply = old_reply->next ; 
        old_reply->next = delete_reply->next ; 
    }
    free(delete_reply) ; 
    comment->reply_count-- ; 
    return true ;

}