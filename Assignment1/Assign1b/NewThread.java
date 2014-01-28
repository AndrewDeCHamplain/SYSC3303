/**
 * Thread class that will read-modity-write a global variable in a non-safe way.
 * Goal: Create data collisions when multiple threads run at the same time.
 */

/**
 * @author Andrew
 *
 */
public class NewThread implements Runnable{
	//public long compare;
	public int loops;
	
	// constructor
	public NewThread(String[] args){
		loops = Integer.parseInt(args[1]);
	}
	
	// thread runs pointless operation as many times a specified in arg
	public void run(){
		for (int i=0; i<loops;i++){
			long compare;
			
			compare = Assign1.index;
			Assign1.index++;			
			Assign1.index--;
			
			// if thread was safe, then the result would always be equal but
			// since it isn't we can check collisions if they are not equal.
			if (Assign1.index!=compare)
				Assign1.collisions++;
		}
	}
}
