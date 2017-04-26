import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Semaphore;
import java.util.concurrent.TimeUnit;
//solved with MUTEX FULL EMPTY
public class SemaphoreTest
{
	int in = 0;
	int out = 0;
	int[] buffer = new int[4];
	Semaphore FULL;
	Semaphore MUTEX;
	Semaphore EMPTY;
	public SemaphoreTest()
	{
		FULL = new Semaphore(0);
		MUTEX = new Semaphore(1);
		EMPTY = new Semaphore(4);
	}
	public static void main(String[]args)
	{
		
	
		SemaphoreTest semTest = new SemaphoreTest();
		Thread producer = new Thread(new Producer(semTest));
		Thread consumer = new Thread(new Consumer(semTest));
		producer.start();
		consumer.start();
		
		//ExecutorService executor = Executors.newFixedThreadPool(100);
	}
}
class Consumer extends Thread
{
	SemaphoreTest sem;
	public Consumer(SemaphoreTest _sem)
	{
		sem = _sem;
	}
	public void run()
	{
		int i = 0;
		while(i < 10)
		{
			try {
				sem.FULL.acquire();
				sem.MUTEX.acquire();
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			
			System.out.println("read from "+sem.out+" : "+sem.buffer[sem.out]);
			sem.out = (sem.out + 1) % 4;
			i++;
			sem.EMPTY.release();
			sem.MUTEX.release();
		}
		System.out.println("finish Consumer");
	}
}
class Producer extends Thread
{
	SemaphoreTest sem;
	public Producer(SemaphoreTest _sem)
	{
		sem = _sem;
	}
	public void run()
	{
	
		int i = 0;
		while(i < 10)
		{
			try
			{
			sem.EMPTY.acquire();
			sem.MUTEX.acquire();
			} catch(Exception e)
			{
				
			}
			sem.buffer[sem.in] =(int)( Math.random() * 10.0);
			System.out.println("write "+sem.in + " : "+sem.buffer[sem.in]);
			sem.in = (sem.in + 1) % 4;
			i++;
			sem.FULL.release();
			sem.MUTEX.release();
		}
		System.out.println("finish Producer");
	}
}
