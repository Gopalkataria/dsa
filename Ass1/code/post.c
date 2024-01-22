#include "post.h"
#include <stdlib.h>
#include <string.h>

Post *createPost(char *username, char *caption){
    Post * newPost  = (Post*) malloc(sizeof(Post)) ;
    newPost->username = initializeString(username) ; 
    newPost->caption = initializeString(caption) ; 
    newPost->comments = NULL ; 
    newPost->next = NULL; 
    newPost->prev = NULL ; 
    newPost->comment_count = 0 ; 
    return newPost ; 
}
