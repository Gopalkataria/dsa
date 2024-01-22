#ifndef PLATFORM_H
#define PLATFORM_H

#include "post.h"
#include "comment.h"



typedef struct  Platform {
    Post * posts ; 
    Post * lastViewedPost ; 
    int lastVeiwedEqualsLastPost  ;
    int post_count ; 

} Platform ; 

extern Platform * PLATFORM ; 

Platform * createPlatform() ;

bool addPost( char * username  , char * caption ) ; 

bool deletePost( int n ) ;

Post * viewPost( int  n ) ; 

Post * currPost( ) ; 

Post * nextPost() ; 
Post * prevPost() ;

bool addComment( char * username , char * content ) ;

bool deleteComment( int n) ; 

Comment * viewComments( ) ; 

bool addReply(char * username , char * content , int n ) ; 

bool deleteReply( int n , int m ) ; 

#endif
