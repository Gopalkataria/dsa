#include "helper.h"

char *initializeString(char *strn)
{
    char *new = (char *)malloc(sizeof(char) * MAX_STR_LEN);
    strncpy(new, strn, MAX_STR_LEN);
    return new;
}

// void printhelp() {
//     printf("chipi chipi \nchapa chapa \ndubi dubi\ndaba daba \namigo ni magic pony \nboom boom bom\n:");
// }

// @brief helper function to print the available commands

void printhelp()
{
    printf("Enter commands to perform various operations on the social media platform:\n\n");
    printf("help: Display a list of available commands.\n");
    printf("create_platform: Create a new instance of the platform, must be the first command before any other command is run.\n");
    printf("add_post: Add a new post to the platform.\n");
    printf("delete_post: Delete a post from the platform.\n");
    printf("curr_post or current_post: Display the current post.\n");
    printf("prev_post or previous_post : Display the previous post.\n");
    printf("next_post: Display the next post.\n");
    printf("view_post: View a specific post with its comments and replies.\n");
    printf("display: Display all posts, comments, and replies on the platform.\n");
    printf("add_comment: Add a comment to a post.\n");
    printf("view_comments or view_all_comments: View all comments (with replies) on the current post.\n");
    printf("delete_comment: Delete a comment from a post.\n");
    printf("add_reply: Add a reply to a comment.\n");
    printf("delete_reply: Delete a reply from a comment.\n");
    printf("exit: Exit the program.\n");
    printf("\n:");
}

// @brief helper function to get username and caption from user
// @param username The username of poster
// @param caption The caption of the post
void inpUserAndCaption(char *username, char *caption)
{
    printf("Enter username: ");
    scanf(" %[^\n]s", username);
    printf("Enter content: ");
    scanf(" %[^\n]s", caption);
}