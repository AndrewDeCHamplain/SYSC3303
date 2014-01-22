/**
 * 
 */
import java.util.Arrays;

/**
 * @author Andrew DeChamplain
 * @author Andrew Fleck
 */
public class PartB {

	/**
	 * @param args
	 */
	public static int index;
	public static char[] log; 
	
	public static void main(String[] args) {
		
		index = 0;
		log = new char[Integer.parseInt(args[0]) * 2];
		
		
		YappyThread yThread = new YappyThread(args);
		Thread sThread = new Thread(new SleepyThread(args));
		
		yThread.start();
		sThread.start();
		System.out.print("done");
		
		try {
			yThread.join();
			sThread.join();
		
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		System.out.print(Arrays.toString(log));
		// TODO Auto-generated method stub
		// TODO Auto-generated method stub

	}

}
