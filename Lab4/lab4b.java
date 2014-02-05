
import java.util.ArrayList;

public class lab4b
{

	public static void main(String[] args) 
	{
		ArrayList<Character> log = new ArrayList<Character>();
		ArrayList<Character> slog = new ArrayList<Character>();
		
		Sleepy s = new Sleepy(log, slog);
		Yappy y = new Yappy(log, slog);
		s.start();
		y.start();
		Sleepy s2 = new Sleepy(log, slog);
		Yappy y2 = new Yappy(log, slog);
		s2.start();
		y2.start();
		
		try {
			s.join();
			y.join();
			s2.join();
			y2.join();
		} catch (Exception e) {}
	
		int i = 0;
		for (Character entry : log) 
		{ System.out.print(entry); 
		  if (++i %80 == 0) System.out.println(); 
		}
		System.out.println ("\nNumber of entries is " + i);
		
		int max;
		if (log.size() < slog.size()) 
			max = log.size(); 
		else 
			max = slog.size();
		System.out.println ("log is " + log.size() + " and slog is " + slog.size() + "(" + max + ")");
		
		for (i=0;i<max;i++)
		{ 
			try {
				if ( !log.get(i).equals(slog.get(i) ))
					System.out.println( i + " : " + log.get(i) 	+ " " + slog.get(i)); 
			} catch (NullPointerException e) { System.out.println("NullPointer at " + i); }
		}
		System.out.println ( "\nDone");
		
	}

}

class Sleepy extends Thread
{
	ArrayList<Character> log;
	ArrayList<Character> slog;
	Sleepy(ArrayList<Character> log, ArrayList<Character> slog)
	{
		this.log = log;
		this.slog = slog;
	}
	public void run()
	{
		for (int i=0;i<1000;i++)
		{
			try { Thread.sleep(7); } catch (Exception e) {}
     		synchronized (log) { log.add('s'); }
     		slog.add('s'); 
		}
	}
}

class Yappy extends Thread
{
	ArrayList<Character> log;
	ArrayList<Character> slog;
	Yappy( ArrayList<Character> log, ArrayList<Character> slog)
	{
		this.log = log;
		this.slog = slog;
	}
	public void run()
	{
		for (int i=0;i<1000;i++)
		{
			for (long j=0;j<9999999;j++) { j = j / 1 * 1 + 0 - 0; }
			synchronized (log) { log.add('y'); }
			slog.add('y'); 
		}
	}
}
