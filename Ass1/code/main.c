#include "platform.h"

// social media code less go

void displayComm( Comment * comm ){
    printf("    %s : %s \n", comm->username , comm->content) ; 
    Reply * rep = comm->replies ; 
    for( int i = 0 ; i < comm->reply_count ; i++ ){
        printf("         %s : %s \n", rep->username , rep->content) ; 
        rep = rep->next ; 
    }
}

void displayPost( Post * post ) {
    printf("\n %s : %s \n" ,post->username , post->caption ) ; 
    Comment * comm = post->comments ; 
    for (int i = 0; i < post->comment_count; i++)
    {
        displayComm( comm ) ; 
        comm = comm->next ; 
    }
    printf("\n\n") ; 
    
}

void display(){
   Post * post = PLATFORM->posts ; 
    for (int i = 0; i < PLATFORM->post_count; i++)
    {
        displayPost(post)  ; 
        post = post->next ;  
    }
    
}



int main() {


    createPlatform() ;
    addPost("bropal", "padhle bsdk");
    addComment("bropal", "bhai sachme padhle") ; 
    addPost("jhopal" , "yeh toh scam hain" ); 
    addComment("yopal", "soja bhai") ; 
    // deletePost(1) ;
    
    
    display() ; 
    // printf("%d", PLATFORM->post_count) ; 
    

    return 0 ; 
}
