import java.lang.Thread;

public class Lab1 {

	public static void main(String[] args) {
		int i = 0;
		for(i=0;i<30;i++){
			System.out.println(args[0]);
	         try {
	            // thread to sleep for 2000 milliseconds
	            Thread.sleep(2000);
	         } catch (Exception e) {
	              System.out.println(e);
	           }			
		}
	}
}
