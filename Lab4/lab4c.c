// @author Andrew DeChamplain

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/mman.h>
#include <rtdk.h>
#include <string.h>

#include <native/task.h>
#include <native/timer.h>
#include <native/mutex.h>

RT_TASK yappy_task, sleepy_task, yappy_task2, sleepy_task2;
RT_MUTEX mutex_desc;
char array_logs[4001];
int i;

typedef struct{
	int loops;
} cookies;

/* NOTE: error handling omitted. */

void yappy(void *arg)
{
	int p, j, x, loops;
	
	cookies * cookie;
	cookie = (cookies*)arg;

	for(p=0; p<cookie->loops; p++){
		rt_mutex_acquire(&mutex_desc,TM_INFINITE);
		array_logs[i] = 'Y';
		i++;
		rt_mutex_release(&mutex_desc);

		//spin
		for (j=0; j<500; j++){
			x = 4;
			x = x/1;
			x = x*1;
		}
        }
}

void sleepy(void *arg)
{
	int p, loops;

	cookies * cookie;
	cookie = (cookies*)arg;

	for(p=0; p<cookie->loops; p++){
		rt_mutex_acquire(&mutex_desc,TM_INFINITE);
		array_logs[i] = 'S';
		i++;
		rt_mutex_release(&mutex_desc);
		rt_task_sleep(3000); // 
        }
}

void catch_signal(int sig)
{

}

int main(int argc, char* argv[])
{
        //signal(SIGTERM, catch_signal);
        //signal(SIGINT, catch_signal);
	int statusY, statusS, statusY2, statusS2, err, max;
	cookies yappy_cookies, sleepy_cookies, yappy_cookies2, sleepy_cookies2;

	rt_print_auto_init(1);
	i=0;

	if(atoi(argv[1]) > 1000){
		rt_printf("Too many loops, enter a number less than or equal to 1000\n");
		exit(1);
	}
	max = atoi(argv[1])*4;
	yappy_cookies.loops = atoi(argv[1]);
	sleepy_cookies.loops = atoi(argv[1]);
	yappy_cookies2.loops = atoi(argv[1]);
	sleepy_cookies2.loops = atoi(argv[1]);
	
        /* Avoids memory swapping for this program */
        mlockall(MCL_CURRENT|MCL_FUTURE);

	err = rt_mutex_create(&mutex_desc,"MyMutex");

        /*
         * Arguments: &task, name, stack size (0=default), priority,
         *            mode (FPU, start suspended, ...)
         */
        statusY = rt_task_create(&yappy_task, NULL, 0, 0, T_JOINABLE);
	statusS = rt_task_create(&sleepy_task, NULL, 0, 0, T_JOINABLE);
	
        /*
         * Arguments: &task, task function, function argument
         */
        statusY = rt_task_start(&yappy_task, &yappy, &yappy_cookies);
	statusS = rt_task_start(&sleepy_task, &sleepy, &sleepy_cookies);

	//start second set of threads
	statusY2 = rt_task_create(&yappy_task2, NULL, 0, 0, T_JOINABLE);
	statusS2 = rt_task_create(&sleepy_task2, NULL, 0, 0, T_JOINABLE);

	statusY2 = rt_task_start(&yappy_task2, &yappy, &yappy_cookies2);
	statusS2 = rt_task_start(&sleepy_task2, &sleepy, &sleepy_cookies2);


        statusY = rt_task_join(&yappy_task);
	statusS = rt_task_join(&sleepy_task);
	statusY2 = rt_task_join(&yappy_task2);
	statusS2 = rt_task_join(&sleepy_task2);
	
	rt_mutex_delete(&mutex_desc);
	array_logs[4001] = '\0';
	rt_printf("%s", array_logs);
	rt_printf("\n\nNumber fo Entries: %d\n", max);
	rt_printf("log is %d (%d)\nDone\n", strlen(array_logs), max);

}

