/*Issam Al Komey*/
/*025577*/

#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <string.h>

#define MY_PORT		8989
#define MAXBUF		256

int main(int argc , char *argv[])
{
    WSADATA wsa;
    SOCKET sockfd , clientfd;
    struct sockaddr_in self;

	char buffer[MAXBUF] = {};
	/*initialises an empty string*/

    printf("\nInitialising Winsock...");
    if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
    {
        printf("Failed. Error Code : %d",WSAGetLastError());
        return 1;
    }

    printf("Initialised.\n");

	/*---create streaming socket---*/
    if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 )
	{
		perror("Socket");
		exit(errno);
	}

        printf("Socket created.\n");

	/*---initialize address/port structure---*/
	/* bzero(&self, sizeof(self));*/
	self.sin_family = AF_INET;
	self.sin_port = htons(MY_PORT);
	self.sin_addr.s_addr = INADDR_ANY;

	/*---assign a port number to the socket---*/
    if ( bind(sockfd, (struct sockaddr*)&self, sizeof(self)) != 0 )
	{
		perror("socket--bind");
		exit(errno);
	}

        puts("Bind done");

	/*---make it a "listening socket"---*/
	if ( listen(sockfd, 20) != 0 )
	{
		perror("socket--listen");
		exit(errno);
	}

        puts("Waiting for incoming connections...");


	/*---forever... ---*/
	while (1)
	{	struct sockaddr_in client_addr;
		int addrlen=sizeof(client_addr);

		/*---accept a connection (creating a data pipe)---*/
		clientfd = accept(sockfd, (struct sockaddr*)&client_addr, &addrlen);

		send(clientfd, strupr(strrev(buffer)), recv(clientfd, buffer, MAXBUF, 0), 0);

        /*reverses the message (strrev) and then converts all characters in the message to uppercase (strupr)*/
        /*strupr(strrev(buffer));*/

		/*---close connection---*/
		close(clientfd);
	}

	/*---clean up (should never get here!)---*/
	close(sockfd);
        WSACleanup();
	return 0;
}
