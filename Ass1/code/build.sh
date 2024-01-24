#!/usr/bin/bash
gcc main.c platform.c post.c comment.c reply.c helper.c -Wall -g -o social_network.out && ./social_network.out 
