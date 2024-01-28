CC = gcc
CFLAGS = -Wall

all: social_network

social_network: code/main.c
	$(CC) $(CFLAGS) -o social_network code/main.c code/platform.c code/post.c code/comment.c code/reply.c code/helper.c

clean:
	rm -f social_network
	
