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

bool delPost( int n ) ;

Post * viewPost( int  n ) ; 

Post * currPost( ) ; 

Post * nextPost() ; 
Post * prevPost() ; 

#endif
