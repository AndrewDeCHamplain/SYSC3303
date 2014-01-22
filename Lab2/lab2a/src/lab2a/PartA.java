package lab2a;

/**
 * @author Andrew DeChamplain
 * @author Andrew Fleck
 */
public class PartA{

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		YappyThread yThread = new YappyThread(args);
		Thread sThread = new Thread(new SleepyThread(args));
		//SleepyThread sThread = new SleepyThread(args);
		yThread.start();
		sThread.start();
		System.out.print("done");
		// TODO Auto-generated method stub

	}

}

/*
1. The large majority of the time Y printed first (outlier cases where S came first or done was printed first).
We found the first created thread was usually but not necessarily the first to execute. The patterned was observed 
to be inconsistent with large stretches of the same thread executing (observed with 100 loops).

2. No, we found it to be random which thread ran first.

3. We saw that when increasing the sleep time, the YappyThread would have time to complete or nearly complete before 
SleepyThread could do it`s second loop.
*/