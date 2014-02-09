import java.util.concurrent.ExecutionException;
import java.util.concurrent.TimeUnit;

public class TestDriver {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		
		try {
			Executor.execute();
		} catch (InterruptedException | ExecutionException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}	
	}
}
