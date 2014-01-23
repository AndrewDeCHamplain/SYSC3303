/**
 * 
 */

package Assignment1b;

/**
 * @author Andrew DeChamplain
 */
public class Assign1 {

	/**
	 * @param args
	 */
	public static long index;
	public static int collisions;
	//public static char[] log; 
	
	public static void main(String[] args) {
		
		//int loops = Integer.parseInt(args[1]);
		index = 10;
		
		System.out.print("Starting Threads\n");
		for (int i=0; i<Integer.parseInt(args[0]); i++){
			(new Thread(new NewThread((args)))).start();
			(new Thread(new NewThread((args)))).start();
		}
		try {
			Thread.sleep(10);
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		System.out.print(collisions+" collisions detected\n");
		System.out.print("Done Threads\n");
		
	}

}

