/* Creates a datagram server.  The port 
   number is passed as an argument.  This
   server runs forever */

#include <sys/types.h>
#include <stdlib.h>
#include <fcntl.h>
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
	int sock, length, n, k, flags;
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

	// set recv to nonblocking
	flags = fcntl(sock, F_GETFL);
	flags |= O_NONBLOCK;
	fcntl(sock, F_SETFL, flags);

   	length = sizeof(server);
   	bzero(&server,length);
   	server.sin_family=AF_INET;
   	server.sin_addr.s_addr=INADDR_ANY;
   	server.sin_port=htons(atoi(argv[1]));
   	if (bind(sock,(struct sockaddr *)&server,length)<0) 
       		error("binding");
   	fromlen = sizeof(struct sockaddr_in);
	memset(buf, 0, sizeof buf);
	
	/* 
   	Server runs forever, is 'busy' (sleeping) for 5 seconds, anything that
	was sent while server was 'busy' will have been put in the queue and 
	gets taken care of in order they were recieved. This proves the client
	can send data (asynchronously from user) even when the server is busy.  
	*/
	while (1) {
		k=0;
		// server is 'busy' for 10 seconds
		printf("Sleep started\n");
		sleep(30);
		printf("Done sleeping, checking Q now\n");

		// get messages from queue and print them.
		while((n = recvfrom(sock,buf,1024,0,(struct sockaddr *)&from,&fromlen)) >0){
       			write(1,"Received a datagram: ",21);
       			write(1,buf,n);
			k++;
		}
		if(k == 235) printf("Warning: Queue was filled, only 235 messages were recieved\n");
   	}
   	return 0;
}

