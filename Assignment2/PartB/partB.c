// @author Andrew DeChamplain

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/mman.h>
#include <rtdk.h>
#include <string.h>
#include <time.h>

#include <native/task.h>
#include <native/timer.h>
#include <native/mutex.h>

#define BUFFERSIZE 900

RT_TASK fusThread, accThread, gyroThread;
RT_MUTEX mutex_gyro, mutex_acc;
int isRunning, acc_sample, gyro_sample[BUFFERSIZE], gyroIndex, printlog[20000],logIndex;

/* NOTE: error handling omitted for now. */

void accelerometer(void *arg)
{
	RTIME now;
	int acceptable;
        /*
         * Arguments: &task (NULL=self), start time, period 
         */
        rt_task_set_periodic(NULL, TM_NOW, 33333333);

	while (isRunning) {
		
                rt_task_wait_period(NULL);
		acceptable = 0;
		//acceptable = rand() % (800 - 0 + 1) + 0; // acceleration between 0-50 
		acceptable = rand_lim(20);
		rt_mutex_acquire(&mutex_acc,TM_INFINITE);
		
		if(acceptable > acc_sample)
			acc_sample = acc_sample + 1;

		else if(acceptable < acc_sample)
			acc_sample = acc_sample - 1;
		
		rt_mutex_release(&mutex_acc);
	}
}

void gyroscope(void *arg)
{
	RTIME now;
	int randG, i, prev;
	gyroIndex = 0;

        /*
         * Arguments: &task (NULL=self), start time, period 
         */
        rt_task_set_periodic(NULL, TM_NOW, 3333333);

	while (isRunning) {
		for(i=0; i<BUFFERSIZE; i++){
                	rt_task_wait_period(NULL);
			//randG = rand() % (361 - 0 + 1) + 0; // angle between 0-361
			randG = rand_lim(360);
			
			rt_mutex_acquire(&mutex_gyro,TM_INFINITE);
			//printf("Random: %d\n", randG);
			prev = gyroIndex;
			gyroIndex++;
			
			if(gyro_sample[prev] >= 360 && randG > gyro_sample[prev])
				gyro_sample[gyroIndex] = 1;

			else if(gyro_sample[prev] <= 1 && randG < gyro_sample[prev])
				gyro_sample[gyroIndex] = 360;

			else if(randG > gyro_sample[prev])
				gyro_sample[gyroIndex] = gyro_sample[prev] + 5;

			else if(randG < gyro_sample[prev])
				gyro_sample[gyroIndex] = gyro_sample[prev] - 5;

			else 
				gyro_sample[gyroIndex] = gyro_sample[prev];
			
			rt_mutex_release(&mutex_gyro);
			
		}
		
		rt_mutex_acquire(&mutex_gyro,TM_INFINITE);
		gyroIndex = 0;
		rt_mutex_release(&mutex_gyro);
	}
}

void sensor_fusion(void *arg)
{
	RTIME now;
	int i,sum, print,k, count;
        /*
         * Arguments: &task (NULL=self), start time, period 
         */
        rt_task_set_periodic(NULL, TM_NOW, 16666666);
	count =0;
	while (isRunning) {
		count++;
                rt_task_wait_period(NULL);
		rt_mutex_acquire(&mutex_acc,TM_INFINITE);
		rt_mutex_acquire(&mutex_gyro,TM_INFINITE);
		k=gyroIndex;
		sum=0; print = 0;
   		for (i=0; i<5; i++){
	 		sum = sum + gyro_sample[k];
			k--;
		}

		print = ((sum/5) + acc_sample)/2;

		rt_mutex_release(&mutex_gyro);
		rt_mutex_release(&mutex_acc);
		
		printlog[logIndex] = print;
		logIndex++;

		if(count == 50)
			isRunning = 0;
	}
}

int rand_lim(int limit) {
/* return a random number between 0 and limit inclusive.
 */

    int divisor = RAND_MAX/(limit+1);
    int retval;

    do { 
        retval = rand() / divisor;
    } while (retval > limit);

    return retval;
}

void catch_signal(int sig)
{
	rt_mutex_delete(&mutex_acc);
	rt_mutex_delete(&mutex_gyro);
}

int main(int argc, char* argv[])
{
        signal(SIGTERM, catch_signal);
        //signal(SIGINT, catch_signal);
	
	int statusA, statusG, statusF, mutexacc, mutexgyro, i,j;

	logIndex = 0;
	// enable rt_task_print
	rt_print_auto_init(1);
	
        /* Avoids memory swapping for this program */
        mlockall(MCL_CURRENT|MCL_FUTURE);


	// Create mutexs
	mutexgyro = rt_mutex_create(&mutex_gyro,NULL);
	if(mutexgyro!=0){
		fprintf(stderr, "Unable to create gyroscope mutex! Exiting...\n");
      		exit(EXIT_FAILURE);
	}
	mutexacc = rt_mutex_create(&mutex_acc,NULL);
	if(mutexacc!=0){
		fprintf(stderr, "Unable to create accelorometer mutex! Exiting...\n");
      		exit(EXIT_FAILURE);
	}
	isRunning = 1;
        /*
         * Arguments: &task, name, stack size (0=default), priority,
         *            mode (FPU, start suspended, ...)
         */
	statusA = rt_task_create(&accThread, NULL, 0, 0, T_JOINABLE);
	statusG = rt_task_create(&gyroThread, NULL, 0, 0, T_JOINABLE);
	statusF = rt_task_create(&fusThread, NULL, 0, 0, T_JOINABLE);

        /*
         * Arguments: &task, task function, function argument
         */

	statusA = rt_task_start(&accThread, &accelerometer, NULL);
	statusG = rt_task_start(&gyroThread, &gyroscope, NULL);
	statusF = rt_task_start(&fusThread, &sensor_fusion, NULL);
	
	
	// threads in infinite loop, therefore this prevents the main from finishing
	// (and killing its threads)
	statusA = rt_task_join(&gyroThread);
        statusF = rt_task_join(&fusThread);
	statusG = rt_task_join(&accThread);
	printlog[logIndex] = 4000;
	
	
	for (i = 0; i < 50; i++) {
		printf("Fusion%d: %d\n", i, printlog[i]);
    	}

	rt_mutex_delete(&mutex_acc);
	rt_mutex_delete(&mutex_gyro);

}

