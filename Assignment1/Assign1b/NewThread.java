/**
 * 
 */

/**
 * @author Andrew
 *
 */
public class NewThread implements Runnable{
	//public long compare;
	public int loops;
	
	public NewThread(String[] args){
		loops = Integer.parseInt(args[1]);
	}
	
	public void run(){
		for (int i=0; i<loops;i++){
			long compare;
			
			compare = Assign1.index;
			Assign1.index++;			
			Assign1.index--;
			
			if (Assign1.index!=compare)
				Assign1.collisions++;
		}
	}
}
