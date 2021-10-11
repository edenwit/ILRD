using System;
using System.Threading;
using System.Threading.Tasks;

namespace ThreadPool
{
    class Program
    {
        static void Main(string[] args)
        {
            /*tests test = new tests();
            test.TestWaitableQueue();*/

            ThreadPool TP = new ThreadPool(4);

            TP.AddTask(new PriorityTask(Task1, PRIORITY.VERY_HIGH));
            TP.AddTask(new PriorityTask(Task2, PRIORITY.VERY_LOW));
            TP.AddTask(new PriorityTask(Task3, PRIORITY.MEDIUM));
            TP.AddTask(new PriorityTask(Task3, PRIORITY.VERY_HIGH));
            TP.AddTask(new PriorityTask(Task1, PRIORITY.MEDIUM));

            Thread.Sleep(5000);

            TP.AddTask(new PriorityTask(Task3, PRIORITY.VERY_HIGH));
            TP.AddTask(new PriorityTask(Task1, PRIORITY.MEDIUM));

            TP.Pause();

            TP.AddTask(new PriorityTask(Task1, PRIORITY.VERY_HIGH));
            TP.AddTask(new PriorityTask(Task2, PRIORITY.VERY_LOW));
            TP.AddTask(new PriorityTask(Task3, PRIORITY.MEDIUM));
            TP.AddTask(new PriorityTask(Task3, PRIORITY.VERY_HIGH));
            TP.AddTask(new PriorityTask(Task1, PRIORITY.MEDIUM));

            TP.SetNumOfThreads(1);
            TP.Resume();

            TP.AddTask(new PriorityTask(Task1, PRIORITY.VERY_HIGH));
            TP.AddTask(new PriorityTask(Task2, PRIORITY.VERY_LOW));
            TP.AddTask(new PriorityTask(Task3, PRIORITY.MEDIUM));

            TP.SetNumOfThreads(8);

            TP.AddTask(new PriorityTask(Task1, PRIORITY.VERY_HIGH));
            TP.AddTask(new PriorityTask(Task2, PRIORITY.VERY_LOW));
            TP.AddTask(new PriorityTask(Task3, PRIORITY.MEDIUM));
            TP.AddTask(new PriorityTask(Task3, PRIORITY.VERY_HIGH));
            TP.AddTask(new PriorityTask(Task1, PRIORITY.MEDIUM));
            TP.AddTask(new PriorityTask(Task1, PRIORITY.VERY_HIGH));
            TP.AddTask(new PriorityTask(Task2, PRIORITY.VERY_LOW));
            TP.AddTask(new PriorityTask(Task3, PRIORITY.MEDIUM));
            TP.AddTask(new PriorityTask(Task3, PRIORITY.VERY_HIGH));
            TP.AddTask(new PriorityTask(Task1, PRIORITY.MEDIUM));
            TP.AddTask(new PriorityTask(Task4));



            //Thread.Sleep(120000);



            TP.Stop();

        }

        public static void Task1()
        {
            Console.WriteLine("thread {0} : hi im function #1 that will take 5 second", Thread.CurrentThread.ManagedThreadId);
            Thread.Sleep(5000);
        }

        public static void Task2()
        {
            Console.WriteLine("thread {0} : hi im function #2 that will take 10 seconds", Thread.CurrentThread.ManagedThreadId);
            Thread.Sleep(10000);

        }

        public static void Task3()
        {
            Console.WriteLine("thread {0} : hi im function #3  that will take 20 seconds", Thread.CurrentThread.ManagedThreadId);
            Thread.Sleep(20000);
        }

        public static void Task4()
        {
            Console.WriteLine("thread {0} : hi im function #3  that will take 90 seconds", Thread.CurrentThread.ManagedThreadId);
            Thread.Sleep(90000);
        }

    }

    class tests
    {
        public tests()
        {
            WQ = new WaitableQueue();
            count = 0;
        }
        public void TestWaitableQueue()
        {

            PriorityTask t1 = new PriorityTask(prints, PRIORITY.LOW);
            PriorityTask t2 = new PriorityTask(prints, PRIORITY.MEDIUM);
            PriorityTask t3 = new PriorityTask(prints, PRIORITY.LOW);
            PriorityTask t4 = new PriorityTask(prints, PRIORITY.MEDIUM);
            PriorityTask t5 = new PriorityTask(prints2, PRIORITY.VERY_LOW);
            PriorityTask t6 = new PriorityTask(prints3, PRIORITY.VERY_HIGH);

            WQ.Enqueue(t1);
            WQ.Enqueue(t2);
            WQ.Enqueue(t3);
            WQ.Enqueue(t4);
            WQ.Enqueue(t5);
            WQ.Enqueue(t6);

            Thread thread1 = new Thread(new ThreadStart(GenTest));
            /*            Thread thread2 = new Thread(new ThreadStart(GenTest));
                        Thread thread3 = new Thread(new ThreadStart(GenTest));
                        Thread thread4 = new Thread(new ThreadStart(GenTest));
                        Thread thread5 = new Thread(new ThreadStart(GenTest));
                        Thread thread6 = new Thread(new ThreadStart(GenTest));*/

            thread1.Start();
            /*            thread6.Start();
                        thread2.Start();
                        thread3.Start();
                        thread4.Start();
                        thread5.Start();*/



        }

        public void GenTest()
        {
            {
                Action t = WQ.Dequeue().GetTask();
                t.Invoke();
            }

        }
        public void prints()
        {
            ++count;
            Console.WriteLine("global: {0}", count);
        }

        public void prints2()
        {
            Console.WriteLine("global: 1000");
        }

        public void prints3()
        {
            Console.WriteLine("global: -30");
        }

        WaitableQueue WQ;
        private int count;
    }
}