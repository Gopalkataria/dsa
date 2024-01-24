 #include "helper.h"

char *initializeString(char * strn ) {
    char *new = (char *)malloc(sizeof(char) * MAX_STR_LEN); 
    strncpy(new , strn , MAX_STR_LEN) ;
    return new ; 
} 

// void printhelp() {
//     printf("chipi chipi \nchapa chapa \ndubi dubi\ndaba daba \namigo ni magic pony \nboom boom bom\n:"); 
// }

void printhelp() {
    printf("Available commands:\n\n");
    printf("help: Display the available commands.\n\n");
    printf("add_post: Add a new post. You will be prompted to enter the username and the caption.\n\n");
    printf("delete_post: Delete a post. You will be prompted to enter the post number.\n\n");
    printf("add_comment: Add a new comment to a post. You will be prompted to enter the username, the comment, and the post number.\n\n");
    printf("delete_comment: Delete a comment from a post. You will be prompted to enter the comment number and the post number.\n\n");
    printf("view_comments: View the comments of a post. You will be prompted to enter the post number.\n\n");
    printf("add_reply: Add a reply to a comment. You will be prompted to enter the username, the reply, the comment number, and the post number.\n\n");
    printf("delete_reply: Delete a reply from a comment. You will be prompted to enter the reply number, the comment number, and the post number.\n\n");
    printf("exit: Exit the program.\n\n:");
}

void inpUserAndCaption(char * username , char * caption ) {
    scanf("%s" , username) ; 
     scanf("%[^\n]s", caption) ; 
}