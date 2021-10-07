using System;
using System.Threading;

namespace circular_buffer
{
    class Program
    {
        static Mutex mutex_prod = new Mutex();
        static Mutex mutex_cons = new Mutex();

        public const int BSIZE = 50;
        public const int ARRSIZE = 100;
        public static int read_idx;
        public static int write_idx;
        public static byte[] buffer = new byte[BSIZE];
        public static byte[] arr = new byte[ARRSIZE];
        public static Semaphore sem_prod = new Semaphore(BSIZE, BSIZE);
        public static Semaphore sem_cons = new Semaphore(0, BSIZE);

        static void Main(string[] args)
        {
            Thread producer_thread1 = new Thread(() => Producer(1));
            Thread producer_thread2 = new Thread(() => Producer(2));
/*            Thread producer_thread3 = new Thread(() => Producer(3));
            Thread producer_thread4 = new Thread(() => Producer(4));
            Thread producer_thread5 = new Thread(() => Producer(5));
            Thread producer_thread6 = new Thread(() => Producer(6));*/

            Thread consumer_thread1 = new Thread(new ThreadStart(Consumer));
            Thread consumer_thread2 = new Thread(new ThreadStart(Consumer));
/*            Thread consumer_thread3 = new Thread(new ThreadStart(Consumer));
            Thread consumer_thread4 = new Thread(new ThreadStart(Consumer));
            Thread consumer_thread5 = new Thread(new ThreadStart(Consumer));
            Thread consumer_thread6 = new Thread(new ThreadStart(Consumer));*/

            producer_thread1.Start();
            producer_thread2.Start();
/*            producer_thread3.Start();
            producer_thread4.Start();
            producer_thread5.Start();
            producer_thread6.Start();*/

            consumer_thread1.Start();
            consumer_thread2.Start();
/*            consumer_thread3.Start();
            consumer_thread4.Start();
            consumer_thread5.Start();
            consumer_thread6.Start();*/

            producer_thread1.Join();
            producer_thread2.Join();
/*            producer_thread3.Join();
            producer_thread4.Join();
            producer_thread5.Join();
            producer_thread6.Join();*/

            consumer_thread1.Join();
            consumer_thread2.Join();
/*            consumer_thread3.Join();
            consumer_thread4.Join();
            consumer_thread5.Join();
            consumer_thread6.Join();*/

            for (int i = 0; i < ARRSIZE; ++i)
            {
                Console.WriteLine("Arr in index {0} wrong value. actual: {1}.\n", i, arr[i]);
            }

        }
        static public void Producer(int identifier)
        {
            for (byte i = 0; i < 100; ++i)
            {
                sem_prod.WaitOne();

                mutex_prod.WaitOne();

                buffer[write_idx] = i;
                write_idx = (write_idx + 1) % BSIZE;
                ++i;

                mutex_prod.ReleaseMutex();

                sem_cons.Release();
            }
        }
        static public void Consumer()
        {
            for (byte i = 0; i < 100; ++i)
            {
                sem_cons.WaitOne();

                mutex_cons.WaitOne();

                arr[i] = buffer[read_idx];
                buffer[write_idx] = 0;
                read_idx = (read_idx + 1) % BSIZE;
                ++i;

                mutex_cons.ReleaseMutex();

                sem_prod.Release();
            }
        }
    }
}
