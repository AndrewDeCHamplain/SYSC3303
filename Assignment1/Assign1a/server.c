/* Creates a datagram server.  The port 
   number is passed as an argument.  This
   server runs forever */

#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <netdb.h>
#include <stdio.h>

void error(const char *msg)
{
    	perror(msg);
	exit(0);
}

int main(int argc, char *argv[])
{
	int sock, length, n;
   	socklen_t fromlen;
   	struct sockaddr_in server;
   	struct sockaddr_in from;
   	char buf[1024];
	
	// make sure user sets port
   	if (argc < 2) {
     		fprintf(stderr, "ERROR, no port provided\n");
      		exit(0);
   	}
   
	// configure UDP server
   	sock=socket(AF_INET, SOCK_DGRAM, 0);
   	if (sock < 0) error("Opening socket");
   	length = sizeof(server);
   	bzero(&server,length);
   	server.sin_family=AF_INET;
   	server.sin_addr.s_addr=INADDR_ANY;
   	server.sin_port=htons(atoi(argv[1]));
   	if (bind(sock,(struct sockaddr *)&server,length)<0) 
       		error("binding");
   	fromlen = sizeof(struct sockaddr_in);
	
	/* 
   	Server runs forever, is 'busy' (sleeping) for 5 seconds, anything that
	was sent while server was 'busy' will have been put in the queue and 
	gets taken care of in order they were recieved. This proves the client
	can send data (asynchronously from user) even when the server is busy.  
	*/
	while (1) {
		printf("Sleep started\n");
		sleep(10);
		printf("Done sleeping, checking Q now\n");

        	n = recvfrom(sock,buf,1024,0,(struct sockaddr *)&from,&fromlen);
		printf("%d",n);
       		if (n < 0) error("recvfrom");
       		write(1,"Received a datagram: ",21);
       		write(1,buf,n);
       		n = sendto(sock,"Got your message\n",17,
        	0,(struct sockaddr *)&from,fromlen);
       		if (n  < 0) error("sendto");
   	}
   	return 0;
}

