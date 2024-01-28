# DSA assignment 1 
<b>
<I> Gopal Kataria - 2023 112 006 </I>
</b>

A simple social media like platform implemented in a REPL in C

## Table of Contents

- [Description](#description)
- [Compilation](#compilation)
- [Usage](#usage)

## Description

This project implements a Social Media Platform ADT in C. The ADT manages posts, comments, and replies through a set of terminal commands. Users can interact with the platform to add posts, delete posts, add comments, delete comments, add replies, delete replies, and view posts and comments.

## Compilation
To compile the project, follow these steps:

Ensure you have a C compiler installed on your system.
Compile the source files using make. 
To compile code, run
`make` inside this folder with README.
It will generate a single executable social_network over here.

To remove the compiled binary, simply run 
`make clean`

## Assumptions
* first command would always be create_platform
* All commands will be entered in individual lines
* Maximum input size is 100 chars per line
* Displaying a post will also display its comments and replies
* Similarly, displaying a comment would also display its time.
* Comments, replies and posts are sorted chronoloically with latest one being first, then 2nd last being second ...
* Error handling for invalid commands is implemented 


## Usage
Enter commands to perform various operations on the social media platform:


`help`: Display a list of available commands.

`create_platform`: Create a new instance of the platfarm, must be the first command before any other command is run.

`add_post`: Add a new post to the platform.

`delete_post`: Delete a post from the platform.

`curr_post` or `current_post`: Display the current post.

`prev_post` or `previous_post`: Display the previous post.

`next_post`: Display the next post.

`view_post`: View a specific post. With its comments and replies

`display`: Display all posts, comments and replies on the platform

`add_comment`: Add a comment to a post.

`view_comments` or `view_all_comments` : View all comments ( with replies ) on the current post.

`delete_comment`: Delete a comment from a post.

`add_reply`: Add a reply to a comment.

`delete_reply`: Delete a reply from a comment.

`exit`: Exit the program.