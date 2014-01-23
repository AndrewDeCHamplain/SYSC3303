#include <signal.h>
#include <unistd.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/shm.h>

//#include <native/task.h>
//#include <native/timer.h>

void catch_signal(int sig)
{	
}

int main(int argc, char* argv[])
{
		
	int i;
	for(i=0;i<30;i++){
		signal(SIGTERM, catch_signal);
		signal(SIGINT, catch_signal);

		printf("%s\n", argv[1]);
		fflush(stdout);
		sleep(2); 	
	}
	/* Avoids memory swapping for this program */
	mlockall(MCL_CURRENT|MCL_FUTURE);

	printf("Hello\n");
}
