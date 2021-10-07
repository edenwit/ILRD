using System;
using System.Threading;
using ws2;

namespace LL_Monitor
{
    class Program
    {
        static object alock = new object();
        static List poor_list = new List();
        static Semaphore sem = new Semaphore(0, 100000);

        static void Main(string[] args)
        {

            Thread producer_thread1 = new Thread(() => Producer(1));
            Thread producer_thread2 = new Thread(() => Producer(2));
            Thread producer_thread3 = new Thread(() => Producer(3));
            Thread producer_thread4 = new Thread(() => Producer(4));
            Thread producer_thread5 = new Thread(() => Producer(5));
            Thread producer_thread6 = new Thread(() => Producer(6));

            Thread consumer_thread1 = new Thread(() => Consumer(1));
            Thread consumer_thread2 = new Thread(() => Consumer(2));
            Thread consumer_thread3 = new Thread(() => Consumer(3));
            Thread consumer_thread4 = new Thread(() => Consumer(4));
            Thread consumer_thread5 = new Thread(() => Consumer(5));
            Thread consumer_thread6 = new Thread(() => Consumer(6));

            producer_thread1.Start();
            producer_thread2.Start();
            producer_thread3.Start();
            producer_thread4.Start();
            producer_thread5.Start();
            producer_thread6.Start();

            consumer_thread1.Start();
            consumer_thread2.Start();
            consumer_thread3.Start();
            consumer_thread4.Start();
            consumer_thread5.Start();
            consumer_thread6.Start();

            producer_thread1.Join();
            producer_thread2.Join();
            producer_thread3.Join();
            producer_thread4.Join();
            producer_thread5.Join();
            producer_thread6.Join();

            consumer_thread1.Join();
            consumer_thread2.Join();
            consumer_thread3.Join();
            consumer_thread4.Join();
            consumer_thread5.Join();
            consumer_thread6.Join();

            Console.WriteLine("List size at end: {0}", poor_list.Count());
        }
        static public void Producer(int identifier)
        {
            for (int i = 0; i < 10; ++i)
            {
                Monitor.Enter(alock);

                String insert_str = "producer " + identifier + " : " + i;

                poor_list.Push(insert_str);
                sem.Release();
                Console.WriteLine(insert_str);
                Monitor.PulseAll(alock);
                Monitor.Exit(alock);

            }

        }
        static public void Consumer(int identifier)
        {
            for (int i = 0; i < 10; ++i)
            {
                Monitor.Enter(alock);

                sem.WaitOne();

                Console.WriteLine("consumer {0} poped: {1}",identifier, poor_list.Pop());


                Monitor.Exit(alock);

            }
        }
    }
}


