/**
 * Create a pair of threads specified by the user to be run a specified number
 * of times by the user. Once all threads have finished, the number of recorded
 * collisions are printed to the user for proof that the threads are un-safe.
 */

/**
 * @author Andrew DeChamplain
 */
public class Assign1 {

	/**
	 * @param args
	 */
	public static long index;
	public static int collisions;
	
	public static void main(String[] args) {
		
		index = 10;
		collisions = 0;
		
		System.out.print("Starting Threads\n");
		// create the number of pairs of threads based on the argument.
		for (int i=0; i<Integer.parseInt(args[0]); i++){
			(new Thread(new NewThread((args)))).start();
			(new Thread(new NewThread((args)))).start();
		}
		
		// sleep for 1 sec to let threads finish.
		try {
			Thread.sleep(1);
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		System.out.print(collisions+" collisions detected\n");
		System.out.print("Done Threads\n");
		
	}

}

