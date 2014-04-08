#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <pthread.h>

#define SERVER_PORT 12345
#define QUEUE_SIZE 5




void send_file(char* filename, int socket)
{
	int bytes_read;
	int bytes_written;
	char buffer[80];
	FILE* file = fopen(filename, "rb");

	// get file size
	fseek(file, 0L, SEEK_END);
	size_t size = ftell(file);
	fseek(file, 0L, SEEK_SET);

	// send file size
	write(socket, &size, sizeof(size_t));


	// send file
	do { 
	    bytes_read = fread(buffer, 1, sizeof(buffer), file);
    	bytes_written = write(socket, buffer, bytes_read);
	} while (bytes_read > 0);
	fclose(file);
}

void *thread_func(void *sock)
{
	int asock = *((int*)sock);
	char buffer[80];
	int error = recv(asock, buffer, sizeof(buffer), 0);

	// send file
	send_file(buffer, asock);
	close(asock);
}

void main (int argc, char *argv[])
{

}