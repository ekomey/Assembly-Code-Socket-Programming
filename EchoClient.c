/*Issam Al Komey*/
/*025577*/

#include<io.h>
#include<stdio.h>
#include<winsock2.h>
#include<string.h>

#define MY_PORT		8989
#define MAXBUF		256

int main(int argc , char *argv[])
{
        WSADATA wsa;
        SOCKET sockfd , clientfd;
    	struct sockaddr_in server;
	    char buffer[MAXBUF];

        printf("\nInitialising Winsock...");
    if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
    {
        printf("Failed. Error Code : %d",WSAGetLastError());
    return 1;
    }
        printf("Initialisation complete.\n");
    /*---create streaming socket---*/
     if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 )
	{
		perror("Socket");
		exit(errno);
	}

        printf("Socket created.\n");

       	/*---initialize address/port structure---*/
		server.sin_family = AF_INET;
		server.sin_port = htons(MY_PORT);
        server.sin_addr.s_addr = inet_addr("127.0.0.1");



       /*connect client to server.*/
    if ( connect(sockfd, (struct sockaddr *) &server, sizeof(server)) != 0 )
	{
		printf("failed to establish connection.ERROR CODE:%d\n",WSAGetLastError());
	}

        memset(&buffer[0],0,sizeof(buffer));


	while(2){
        printf("\nType message to be sent: ");
		scanf("%[^\n]", buffer);/*input for message to be sent.*/
		fflush(stdin);


    if(strcmp(buffer, "QUIT") == 0){/*If input is QUIT then terminate*/
         break;
	}
	   send(sockfd, buffer, sizeof(buffer), 0); /*message is sent to server file.*/
    if(send(sockfd, buffer, sizeof(buffer), 0) < 0){

        printf("ERROR!\t %d\n", WSAGetLastError());
    return 1;
		}
        memset(&buffer[0],0,sizeof(buffer));
		recv(sockfd, buffer, MAXBUF, 0);
    if  (recv(sockfd, buffer, MAXBUF, 0) < 0){
        /*input received by server.*/

        printf("ERROR!\t %d\n", WSAGetLastError());

    return 1;
		}

		printf("Server response\t %s\n", buffer);/*output produced by server.*/
		memset(&buffer[0],0,sizeof(buffer));
        }

        close(sockfd);


        WSACleanup();
    return 0;
        }
