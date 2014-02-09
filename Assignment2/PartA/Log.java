public class Log {

	int nWorkers;
	
	public synchronized void addWorker(){
		nWorkers++;
	}
	
	public synchronized void removeWorker(){
		nWorkers--;
	}
}
