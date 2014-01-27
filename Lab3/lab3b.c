// @author Andrew DeChamplain

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/mman.h>
#include <rtdk.h>

#include <native/task.h>
#include <native/timer.h>

RT_TASK yappy_task;
RT_TASK sleepy_task;
char array_logs[2001];
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
		array_logs[i] = 'Y';
		i++;

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
		array_logs[i] = 'S';
		i++;
		rt_task_sleep(30000000); // 1 ms sleep
        }
}

void catch_signal(int sig)
{
	
}

int main(int argc, char* argv[])
{
        //signal(SIGTERM, catch_signal);
        //signal(SIGINT, catch_signal);
	int statusY, statusS;
	cookies yappy_cookies, sleepy_cookies;

	rt_print_auto_init(1);
	i=0;
	yappy_cookies.loops = atoi(argv[1]);
	sleepy_cookies.loops = atoi(argv[1]);

        /* Avoids memory swapping for this program */
        mlockall(MCL_CURRENT|MCL_FUTURE);

        /*
         * Arguments: &task,
         *            name,
         *            stack size (0=default),
         *            priority,
         *            mode (FPU, start suspended, ...)
         */
        statusY = rt_task_create(&yappy_task, NULL, 0, 0, T_JOINABLE);
	statusS = rt_task_create(&sleepy_task, NULL, 0, 0, T_JOINABLE);
        /*
         * Arguments: &task,
         *            task function,
         *            function argument
         */
        statusY = rt_task_start(&yappy_task, &yappy, &yappy_cookies);
	statusS = rt_task_start(&sleepy_task, &sleepy, &sleepy_cookies);

        statusY = rt_task_join(&yappy_task);
	statusS = rt_task_join(&sleepy_task);
	
	
	array_logs[2001] = '\0';
	rt_printf("%s", array_logs);
}
