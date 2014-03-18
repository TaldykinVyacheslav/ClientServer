CC := $(CROSS_COMPILE)gcc

all:
	$(CC) -o client client.c -lpthread
	$(CC) -o server server.c -lpthread
clean:
	rm -f client client.o
	rm -f server server.o
