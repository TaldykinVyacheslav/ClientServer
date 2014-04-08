#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/ioctl.h>


#define SERVER_PORT 12345
#define BUFFER_SIZE 80

main (int argc, char *argv[])
{
	int len, error;
	int sockfd;
	char send_buf[80];
	struct sockaddr_in addr;

	if (argc != 3) {
		perror("wrong args");
		exit(-1);
	}

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
	{
		perror("socket");
		exit(-1);
	}


	memset(&addr, 0, sizeof(addr));
	addr.sin_family      = AF_INET;
	addr.sin_addr.s_addr = inet_addr(argv[1]);
	addr.sin_port        = htons(SERVER_PORT);
}