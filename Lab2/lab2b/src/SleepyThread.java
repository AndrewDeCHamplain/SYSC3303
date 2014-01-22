

class SleepyThread implements Runnable{
	public int count;
	
	public SleepyThread(String[] args){
		count = Integer.parseInt(args[0]);
	}
	
	public void run(){
		for (int i=0; i<count; i++){
			/*
			try {
				Thread.sleep(10);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			*/
			PartB.log[PartB.index]= 'S';
			PartB.index++;
			//System.out.print("S");
		}
	}
}
