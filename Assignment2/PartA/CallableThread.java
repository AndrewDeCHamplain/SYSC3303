import java.util.concurrent.Callable;

class CallableThread implements Callable<Integer> {
	
	private final int workTime;
	
	public CallableThread(int workTime){
		this.workTime = workTime;
	}
	
    @Override
    public Integer call() {
    	return Worker.execute(workTime);
    }
}
