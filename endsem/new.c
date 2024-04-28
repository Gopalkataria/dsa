#include <stdio.h>

struct el{
	int val } ; 

struct Node {
	struct Node * next ; 
	struct Node * prev ; 
	int  val ; 
};



void insertbefore( struct Node * p , struct Node ** head , int val ) {

	if( head == *head ) return ; 

struct 	Node * ptr = * head ; 
       while( p!= ptr &&  ptr != NULL ) ptr = ptr->next ; 	

       if( ptr == NULL ) return ; 

	struct       Node * newnode = ( struct Node * ) malloc( 
       if( ptr->prev == *head ) 



int main() {


}
