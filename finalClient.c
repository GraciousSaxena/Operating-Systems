/*
 * 	Client Side
 * 		Please pass ip address and port no as command line arguments in the same sequence.
 * 		*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h> 

#define PORT 8000

void error(const char *msg)
{
	perror(msg);
	exit(0);
}

int main()
{
	int clientSocket, ret;
	struct sockaddr_in serverAddr;
	char buffer[1024];

	clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (clientSocket < 0) 
		error("[-]ERROR opening socket");
	printf("[+]CLient Socket is created.\n");
	
	bzero(&serverAddr, sizeof(serverAddr));

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	//192.168.43.233
	ret = connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	if(ret < 0)
		error("[-]Error in recieving data.\n");
	printf("[+]Connected to Server.\n");

	while(1){
		printf("Client : ");
		scanf("%s",&buffer[0]);
		send(clientSocket, buffer, strlen(buffer), 0);
		
		if(strcmp(buffer, ":exit")==0){
			close(clientSocket);
			printf("[-]Disconnected from server.\n");
			exit(1);
		}
		if(recv(clientSocket, buffer, 1024, 0) < 0)
			error("[-]Error in recieving data.\n");
		else
			printf("Server : %s\n", buffer);
	}
	return 0;
}
