import java.util.concurrent.ExecutionException;

public class TestDriver {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		
		try {
			Executor.execute(Integer.parseInt(args[0]));
		} catch (InterruptedException | ExecutionException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}	
	}
}
