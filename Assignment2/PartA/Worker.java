public class Worker {
	
	public static int exeTime;

	public static int execute(int workTime) {
		// start execution timer
		final long startTime = System.currentTimeMillis();
		
		//worker working
		Log.addWorker();
		
		// doing "work" that takes a random amount of time
		try {
			Thread.sleep(workTime);
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		// pointless spin to make actual longer than expected
		for(int i=0;i<100000;i++)
		
		// worker done working
		Log.removeWorker();
		
		//get execution time
		final long endTime = System.currentTimeMillis();
		return exeTime = (int) (endTime-startTime);
	}
}
