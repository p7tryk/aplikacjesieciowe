all: client.out server.out

server.out : server.c define.h
	gcc -o server.out server.c -g -lpthread

client.out : client.c define.h
	gcc -o client.out client.c -g -lpthread



run :
	@$(MAKE) && ./server.out

