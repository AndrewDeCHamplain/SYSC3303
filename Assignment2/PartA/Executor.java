import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;
import java.util.concurrent.TimeUnit;

public class Executor {
	
	public static void execute() throws InterruptedException, ExecutionException {
		//creates cached thread pool
				ExecutorService worker = Executors.newCachedThreadPool();
		        
		      //Callable thread starts to execute
				Future<Integer> future=worker.submit(new CallableThread());
	}
}
