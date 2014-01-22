package lab2a;

class SleepyThread implements Runnable{
	public int count;
	
	public SleepyThread(String[] args){
		count = Integer.parseInt(args[0]);
	}
	
	public void run(){
		for (int i=0; i<count; i++){
			int x = 4;
			x = x/1;
			x = x*1;
			System.out.print("S");
		}
	}
}
