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
#define PORT 2000


void error(const char *msg)
{
	perror(msg);
	exit(0);
}

int main(int argc, char *argv[])
{
	int clientSocket, ret;
//	int sockfd, portno, n;
	struct sockaddr_in serverAddr;
//	struct hostent *server;
	char buffer[1024];

	if (argc < 3)
	{
		fprintf(stderr,"usage %s hostname port\n", argv[0]);
		exit(0);
	}
//	portno = atoi(argv[2]);
	clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (clientSocket < 0) 
		error("[-]ERROR opening socket");
	printf("[+]CLient Socket is created.\n");

	server = gethostbyname(argv[1]);
	
	if (server == NULL) {
		fprintf(stderr,"ERROR, no such host\n");
		exit(0);
	}
	
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char *)server->h_addr,(char *)&serv_addr.sin_addr.s_addr,server->h_length);
	serv_addr.sin_port = htons(portno);
	if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
		error("ERROR connecting");
	
	while(1){
		bzero(buffer, 255);
		fgets(buffer, 255, stdin);
		n = write(sockfd, buffer, strlen(buffer));
		if(n<0)
			error("Error on writing");
//		printf("0");
		bzero(buffer, 255);
		n= read(sockfd, buffer, 255);
		if(n<0)
			error("Error on reading");
//		printf("1");
		printf("Server : %s", buffer);

		int i = strncmp("Bye", buffer, 3);
		if(i==0)
			break;
	}
	close(sockfd);
	return 0;
/*
	int num1 ;
	int num2 ;
	int ans;
	int choice;
	
	
	
	S:bzero(buffer,256);						
 	n = read(sockfd,buffer,255);				//Read Server String
     	if (n < 0) 
		error("ERROR reading from socket");
	printf("Server - %s\n",buffer);
     	scanf("%d" , &num1);						//Enter No 1
      	write(sockfd, &num1, sizeof(int));     			//Send No 1 to Server
	bzero(buffer,256);
	n = read(sockfd,buffer,255);				//Read Server String	if (n < 0) 
		error("ERROR reading from socket");
	printf("Server - %s\n",buffer);
	scanf("%d" , &num2);						//Enter No 2
	write(sockfd, &num2, sizeof(int));     			//Send No 2 to Server
  
  
  
	bzero(buffer,256);						
	n = read(sockfd,buffer,255);				//Read Server String
	if (n < 0) 
		error("ERROR reading from socket");
	printf("Server - %s",buffer);
	scanf("%d" , &choice);						//Enter choice
	write(sockfd, &choice, sizeof(int));     			//Send choice to Server

 
	if (choice == 5)
		goto Q;

 
	read(sockfd , &ans , sizeof(int));				//Read Answer from Server
	printf("Server - The answer is : %d\n" , ans);		//Get Answer from server
  
	if(choice != 5)
	       	goto S;
  
	Q:  printf("You chose to exit, Thank You so much.");
        
   	close(sockfd);
    	return 0;
*/
}
