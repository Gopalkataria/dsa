#include "reply.h"

Reply *createReply(char *username, char *content){
    Reply * newReply = ( Reply * )malloc( sizeof(Reply) ) ; 
    newReply->username = initializeString(username) ; 
    newReply->content = initializeString(content) ; 
    newReply->next = NULL ; 
    return newReply ; 
}


