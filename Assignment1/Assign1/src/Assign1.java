/**
 * 
 */
//import java.util.Arrays;

/**
 * @author Andrew DeChamplain
 */
public class Assign1 {

	/**
	 * @param args
	 */
	public static long index;
	//public static char[] log; 
	
	public static void main(String[] args) {
		
		//int loops = Integer.parseInt(args[1]);
		index = 10;
		
		System.out.print("Starting Threads\n");
		for (int i=0; i<Integer.parseInt(args[0]); i++){
			(new Thread(new NewThread((args)))).start();
		}
		
		System.out.print("\nDone Threads");
		//System.out.print("done");
		/*
		try {
			aThread.join();
			bThread.join();
		
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		*/
		//System.out.print(Arrays.toString(log));
		// TODO Auto-generated method stub
		// TODO Auto-generated method stub

	}

}

