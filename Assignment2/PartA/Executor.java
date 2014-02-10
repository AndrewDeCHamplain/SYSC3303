import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;

public class Executor {
	
	public static void execute(int jobs) throws InterruptedException, ExecutionException {
		int[][] workersInfo = new int[jobs][3];
		
		for(int i=0;i<jobs;i++){
			int workTime;
			workTime = randomInt(1000,10000);
				
			// first column is the job #
			workersInfo[i][0] = i;
			// second column is the expected execution time
			workersInfo[i][1] = workTime;
			
			System.out.println("Worker"+workersInfo[i][0] + " started");	// for testing purposes
					
			//creates cached thread pool
			ExecutorService worker = Executors.newCachedThreadPool();
		        
			//Callable thread starts to execute
			Future<Integer> future=worker.submit(new CallableThread(workTime));		
			
			//get workers actual execution times
			workersInfo[i][2] = future.get();
		}
		for (int i = 0; i<jobs; i++){
		    System.out.println("Worker"+workersInfo[i][0] + ", Expected: " + workersInfo[i][1] +" Actual: " +workersInfo[i][2]);
		}
	}
	
	// creates random number between a min and max value
	public static int randomInt(int min, int max)
	{
	   int range = (max - min) + 1;     
	   return (int)(Math.random() * range) + min;
	}
}
