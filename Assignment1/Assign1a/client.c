/* UDP client in the internet domain */
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

void error(const char *);
void my_handler();

char buffer[256];
int sock, n;
unsigned int length;
struct sockaddr_in server;

int main(int argc, char *argv[])
{
   	struct hostent *hp;
	struct sigaction sigIntHandler;
   
	// checking if a port was entered
   	if (argc != 3) { fprintf(stderr, "ERROR, no port provided\n");
        	exit(1);
   	}
   	sock= socket(AF_INET, SOCK_DGRAM, 0); // set socket to UDP
   	if (sock < 0) error("socket");

   	server.sin_family = AF_INET;
   	hp = gethostbyname(argv[1]);	// check if valid port
   	if (hp==0) error("Unknown host");

   	bcopy((char *)hp->h_addr, 
   	     	(char *)&server.sin_addr,
   	      	hp->h_length);
   	server.sin_port = htons(atoi(argv[2]));
   	length=sizeof(struct sockaddr_in);
	
	// catch ctrl+C 
	sigIntHandler.sa_handler = my_handler;
   	sigemptyset(&sigIntHandler.sa_mask);
   	sigIntHandler.sa_flags = 0;
	sigaction(SIGINT, &sigIntHandler, NULL);

	// User entered message
	while(1){
   		printf("Please enter the message: ");
		
   		bzero(buffer,256); // empty buffer
   		fgets(buffer,255,stdin); // get user input
   		n=sendto(sock,buffer,strlen(buffer),0,(const struct sockaddr *)&server,length);
   		if (n < 0) error("Sendto");
	}
   	close(sock);
   	return 0;
}

// when ctrl+c is pressed, sends 500 messages to the server
void my_handler(){
	int i;
        for(i = 0; i<500; i++){
		bzero(buffer,256);
		strncpy(buffer, "Filling buffer\n", sizeof(buffer));
		n=sendto(sock,buffer,strlen(buffer),0,(const struct sockaddr *)&server,length);
	}
	printf("\n");
}

void error(const char *msg)
{
    	perror(msg);
    	exit(0);
}
