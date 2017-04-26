import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Semaphore;
import java.util.concurrent.TimeUnit;
public class SemaphoreTest
{
	int cnt = 4;
	public static void main(String[]args)
	{
		int size = 400;
		Semaphore sem = new Semaphore(1);
		ExecutorService executor = Executors.newFixedThreadPool(100);
		SemaphoreTest semTest = new SemaphoreTest();
		for(int i = 0; i < size; ++i)
		{
			final int k = i;
			executor.submit(new Runnable()
					{
						public void run()
						{
							try {
								sem.acquire();
							} catch (InterruptedException e) {
								// TODO Auto-generated catch block
								e.printStackTrace();
							}
							if(k % 2 == 0)
							{
								semTest.increment();
							}
							else
							{
								semTest.decrement();
							}
							sem.release();
						}
					});
		}
		executor.shutdown();
		try {
			executor.awaitTermination(1000, TimeUnit.MILLISECONDS);
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		System.out.println(semTest.cnt);
	}
	public void increment()
	{
		cnt++;
	}
	public void decrement()
	{
		cnt--;
	}
}
