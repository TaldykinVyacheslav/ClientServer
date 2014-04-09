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
		perror("wrong args"); //Функция perror() преобразует значение глобальной переменной errno в строку и записывает эту строку в поток ошибок stderr. 
		exit(-1);
	}

	sockfd = socket(AF_INET, SOCK_STREAM, 0); //- SOCK_STREAM: посылаются потоки байтов, понятие "сообщения" не вводится. Используемый протокол связи надежен, с установлением виртуального соединения, как TCP в области AF_INET; 
	if (sockfd < 0)
	{
		perror("socket");
		exit(-1);
	}

	/*
	 socket(2) creates a socket, connect(2) connects a socket	 to  a	remote
       socket  address,	 the bind(2) function binds a socket to a local socket
       address, listen(2) tells the  socket  that  new	connections  shall  be
       accepted, and accept(2) is used to get a new socket with a new incoming
       connection.  socketpair(2)  returns  two	 connected  anonymous  sockets
       (only implemented for a few local families like PF_UNIX)
	*/

	memset(&addr, 0, sizeof(addr));
	addr.sin_family      = AF_INET;
	addr.sin_addr.s_addr = inet_addr(argv[1]); //The inet_addr function converts a string containing an IPv4 dotted-decimal address into a proper address for the IN_ADDR structure.
	addr.sin_port        = htons(SERVER_PORT); //преобразовать короткое целое из формата локального хоста в сетевой формат

	error = connect(sockfd,
					(struct sockaddr *)&addr,
					sizeof(struct sockaddr_in));
	if (error < 0)
	{
		perror("connect");
		close(sockfd);
		exit(-1);
	}

	len = send(sockfd, argv[2], strlen(argv[2]) + 1, 0);
	if (len != strlen(argv[2]) + 1)
	{
		perror("send");
		close(sockfd);
		exit(-1);
	}

	char buffer[BUFFER_SIZE];
	size_t size;
	int bytes_read;
	int bytes_written;
	char dest_filename[100];
	strcpy (dest_filename, argv[2]);
	//strcat (dest_filename, "_copy");
	FILE* file = fopen(dest_filename, "wb");

	// retrieve file name
	read(sockfd, &size, sizeof(size_t));

	size_t remains = size;
	while (remains > 0) {
		size_t buff_size = BUFFER_SIZE;
		if (remains < BUFFER_SIZE) {
			buff_size = remains;
		}

		bytes_read = read(sockfd, buffer, buff_size);
		bytes_written = fwrite(buffer, 1, bytes_read, file);
		remains -= buff_size;
	}

	fclose(file);
	close(sockfd);
}
