#include "platform.h"

#define MAX_INP_SIZE 100

void displayComm(Comment *comm)
{
    printf("    %s [%d]: %s \n", comm->username, comm->reply_count, comm->content);
    Reply *rep = comm->replies;
    for (int i = 0; i < comm->reply_count; i++)
    {
        printf("         %s : %s \n", rep->username, rep->content);
        rep = rep->next;
    }
}

void displayPost(Post *post)
{
    printf("\n %s [%d]: %s \n", post->username, post->comment_count, post->caption);
    Comment *comm = post->comments;
    for (int i = 0; i < post->comment_count; i++)
    {
        displayComm(comm);
        comm = comm->next;
    }
    printf("\n\n");
}

void display()
{
    Post *post = PLATFORM->posts;
    for (int i = 0; i < PLATFORM->post_count; i++)
    {
        displayPost(post);
        if (post->next != NULL)
        {
            post = post->next;
        }
    }
    for (int i = 0; i < PLATFORM->post_count; i++)
    {
        displayPost(post);
        post = post->prev;
    }
}

int main()
{
    printf("Welcome to Social Media Platform ADT\n");
    printf("Enter help for a list of available commands \n\n:");

    char inp[MAX_INP_SIZE];
    // while (PLATFORM == NULL)
    // {
    //     scanf("%s", inp);
    //     if (strcmp(inp, "create_platform") == 0)
    //     {
    //         createPlatform();
    //         printf("Created platform\n:");
    //         break;
    //     }
    //     if (strcmp(inp, "help") == 0)
    //     {
    //         printhelp();
    //     }
    //     else
    //     {
    //         printf("Create a platform first,  enter \"help\" for a list of commands \n:");
    //     }
    // }
    createPlatform();

    char username[MAX_INP_SIZE];
    char caption[MAX_INP_SIZE];
    int n;
    int m;
    Post *req_post;
    while (1)
    {
        scanf("%s", inp);
        if (strcmp(inp, "help") == 0)
        {
            printhelp();
        }
        else if (strcmp(inp, "add_post") == 0)
        {
            inpUserAndCaption(username, caption);
            addPost(username, caption);
            printf("\n:");
        }
        else if (strcmp(inp, "delete_post") == 0)
        {
            scanf("%d", &n);
            if (deletePost(n))
            {
                printf("deleted post sucessfully \n:");
            }
            else
            {
                printf("Post doesn't exist\n:");
            }
        }
        else if (strcmp(inp, "curr_post") == 0)
        {
            req_post = currPost();
            if (req_post != NULL)
            {
                displayPost(req_post);
                printf("\n:");
            }
            else
            {
                printf("No Posts yet.. \n:");
            }
        }
        else if (strcmp(inp, "prev_post") == 0)
        {
            req_post = prevPost();
            if (req_post != NULL)
            {
                displayPost(req_post);
                printf("\n:");
            }
            else
            {
                printf("No prev Post.. \n:");
            };
        }
        else if (strcmp(inp, "next_post") == 0)
        {
            req_post = nextPost();
            if (req_post != NULL)
            {
                displayPost(req_post);
                printf("\n:");
            }
            else
            {
                printf("No next Post.. \n:");
            };
        }
        else if (strcmp(inp, "disp") == 0)
        {
            display();
            printf("\n:");
        }
        else if (strcmp(inp, "add_comment") == 0)
        {
            inpUserAndCaption(username, caption);
            if (!addComment(username, caption))
            {
                printf("No recent posts to comment on\n:");
            }
            else
            {
                printf("\n:");
            }
        }
        else if (strcmp(inp, "del_comment") == 0)
        {
            scanf("%d", &n);
            if (!deleteComment(n))
            {
                if (PLATFORM->lastViewedPost == NULL)
                    printf("No recent posts to delete comment on\n:");
                else
                    printf("No such comment exists\n:");
            }
            else
            {
                printf("\n:");
            }
        }
        else if (strcmp(inp, "add_reply") == 0)
        {
            inpUserAndCaption(username, caption);

            scanf("%d", &n);
            if (!addReply(username, caption, n))
            {
                if (PLATFORM->lastViewedPost == NULL)
                {
                    printf("No post to comment on \n:");
                }
                else if (PLATFORM->lastViewedPost->comments == NULL)
                {
                    printf("No comment exists on lastviewed post \n:");
                }
                else
                {
                    printf("No such comment exists \n:");
                }
            }
            else
            {
                printf("\n:");
            }
        }
        else if (strcmp(inp, "del_reply") == 0)
        {
            inpUserAndCaption(username, caption);

            scanf("%d %d", &n , &m);
            if (!deleteReply( n , m ))
            {
                if (PLATFORM->lastViewedPost == NULL)
                {
                    printf("No post to comment on \n:");
                }
                else if (PLATFORM->lastViewedPost->comments == NULL)
                {
                    printf("No comment exists on lastviewed post \n:");
                }
                else
                {
                    printf("No such replt exists \n:");
                }
            }
            else
            {
                printf("\n:");
            }
        }
        else if(strcmp(inp , "exit") == 0) {
            printf("exiting\n") ;
            break ; 
        }
        else
        {
            printf("Invalid Command %s, enter \"help\" for a list of commands \n:", inp);
        }
    }

    deletePlatform();

    return 0;
}
