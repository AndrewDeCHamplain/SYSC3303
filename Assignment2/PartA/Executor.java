import java.util.concurrent.ExecutionException;
import java.util.concurrent.ThreadPoolExecutor;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;
import java.util.concurrent.TimeUnit;

public class Executor {
	
	public static void execute(int jobs) throws InterruptedException, ExecutionException {
		int[][] workersInfo = new int[jobs][3];
		Object future[] = new Object[jobs];
		
		//creates cached thread pool
		ExecutorService worker = Executors.newCachedThreadPool();
		((ThreadPoolExecutor) worker).setKeepAliveTime(10, TimeUnit.SECONDS); 
		System.out.println("Number of active threads before execution: "+((ThreadPoolExecutor) worker).getActiveCount()); 
		
		for(int i=0;i<jobs;i++){
			int workTime;
			workTime = randomInt(1000,10000);
				
			// first column is the job #
			workersInfo[i][0] = i;
			// second column is the expected execution time
			workersInfo[i][1] = workTime;
			
			System.out.println("Worker"+workersInfo[i][0] + " started");	// for testing purposes
			
			//Callable thread starts to execute
			future[i]=worker.submit(new CallableThread(workTime));		
		}
		System.out.println("Number of active threads: "+((ThreadPoolExecutor) worker).getActiveCount());
		for (int i = 0; i<jobs; i++){
			//get workers actual execution times
			Object obj = future[i];
			try { 
				if (obj instanceof Future) {
					@SuppressWarnings({ "rawtypes", "unchecked" })
					Future f = (Future<Integer>)obj; 
					workersInfo[i][2] = (int) f.get();
					System.out.println("Worker"+workersInfo[i][0] + ", Expected: " + workersInfo[i][1] +" Actual: " +workersInfo[i][2]);
				}
			} catch (Exception e) { }
		}
		System.out.println("\nNumber of active threads after execution: "+((ThreadPoolExecutor) worker).getActiveCount());
		System.out.println("Number of cached threads currently in pool: "+((ThreadPoolExecutor) worker).getPoolSize());
		System.out.println("\nWaiting 10 seconds for idle workers to be decommissioned...\n");
		try {
			Thread.sleep(10000);
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} 
		System.out.println("Number of cached threads currently in pool: "+((ThreadPoolExecutor) worker).getPoolSize());
	}
	
	// creates random number between a min and max value
	public static int randomInt(int min, int max)
	{
	   int range = (max - min) + 1;     
	   return (int)(Math.random() * range) + min;
	}
}
