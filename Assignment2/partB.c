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

RT_TASK fusThread, accThread, gyroThread;
RT_MUTEX mutex_30, mutex_60, mutex_300;


/* NOTE: error handling omitted for now. */

void accelerometer(void *arg)
{
	rt_mutex_acquire(&mutex_30,TM_INFINITE);
		// critical section
	rt_mutex_release(&mutex_30);
}

void gyroscope(void *arg)
{
	rt_mutex_acquire(&mutex_300,TM_INFINITE);
		// critical section
	rt_mutex_release(&mutex_300);
}

void sensor_fusion(void *arg)
{
	rt_mutex_acquire(&mutex_60,TM_INFINITE);
		// critical section
	rt_mutex_release(&mutex_60);
}

void catch_signal(int sig)
{

}

int main(int argc, char* argv[])
{
        //signal(SIGTERM, catch_signal);
        //signal(SIGINT, catch_signal);

	int statusA, statusG, statusF, mutex30, mutex60, mutex300;

	// enable rt_task_print
	rt_print_auto_init(1);
	
        /* Avoids memory swapping for this program */
        mlockall(MCL_CURRENT|MCL_FUTURE);

	mutex30 = rt_mutex_create(&mutex_30,"30Hz");
	mutex60 = rt_mutex_create(&mutex_60,"60Hz");
	mutex300 = rt_mutex_create(&mutex_300,"300Hz");

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
	
	
	rt_mutex_delete(&mutex_desc);

}

