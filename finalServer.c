#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<pthread.h>
#include<fcntl.h>

#define PORT 8000

char buffer[1024];
struct sockaddr_in newAddr;
void* client(void* param);

void error(const char *msg){
	perror(msg);
	exit(1);
}

int main(){

	pthread_t tid;

//	Socket used to listen to the new clients
	int sockfd, ret;
	
	struct sockaddr_in serverAddr;
	
//	Socket used to send and recieve from the connected client
	int newSocket, re;
	
	socklen_t addr_size;
	pid_t childpid;
	
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	
	if(sockfd<0)
		error("[-]Error in connection.");
	printf("[+] Server Socket is created.\n");
	
	memset(&serverAddr, '\0', sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;	
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = INADDR_ANY;

	ret = bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	if(ret<0)
		error("[-]Error in binding\n");
	printf("[+]Bind to port %d\n",PORT);
	
	if(listen(sockfd, 10) == 0)
		printf("[+]Listening...\n");
	else
		printf("[-]Error in binding.\n");

	while(1){
		newSocket = accept(sockfd, (struct sockaddr*)&newAddr, &addr_size);
		if(newSocket<0)
			error("NewSocket < 0");
		printf("Connection accepted from %s:%d\n.", inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));
		re = pthread_create(&tid, NULL, client, (void*)&newSocket);
//		pthread_join(tid, NULL);
		if(re)
			error("\nError from pthread");
	}
	return 0;
}

void* client (void* param){
	
	int newSocket = *((int*)param);
	while(1){
		recv(newSocket, buffer, 1024,0);
		if(strcmp(buffer, ":exit") == 0){
			printf("[-]Disconnected from %s : %d\n", inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));
			break;
		}
		else{	
			printf("%s : %d Client : %s\n",inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port), buffer);	
			send(newSocket, buffer, strlen(buffer), 0);
			bzero(buffer, 1024);
		}
	}
	close(newSocket);
//	pthread_exit(0);
}
