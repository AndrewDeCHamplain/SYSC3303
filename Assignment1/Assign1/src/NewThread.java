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
			
			int j=0;
			//System.out.print(Assign1.index);
			
			Assign1.index--;
			if (Assign1.index!=compare)
				System.out.print("COLLISION\n");
				//break;
		}
		//for (int i=0; i<count; i++){
			/*
			try {
				Thread.sleep(10);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			*/
			//PartB.log[PartB.index]= 'S';
			//PartB.index++;
			//System.out.print("S");
	}
}
