package lab2a;

class YappyThread extends Thread{
	public YappyThread(String[] arg){
		count = Integer.parseInt(arg[0]);
	}
	public int count;
	public void run(){
		for (int y=0; y<count; y++)
			System.out.print("Y");
	}
}
