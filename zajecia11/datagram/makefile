server.out : server.c
	gcc -o server.out server.c -g -lpthread

datagram.out : datagram.c
	gcc -o datagram.out datagram.c -g -lpthread
all: datagram.out server.out

run :
	@$(MAKE) && ./server.out

