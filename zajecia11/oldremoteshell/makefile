server.out : server.c
	gcc -o server.out server.c -g -lpthread

client.out : client.c
	gcc -o client.out client.c -g -lpthread

all: client.out server.out

run :
	@$(MAKE) && ./server.out

