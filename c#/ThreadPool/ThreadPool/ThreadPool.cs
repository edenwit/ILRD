using System;
using System.Threading;
using System.Collections.Generic;

namespace ThreadPool
{
    class ThreadPool
    {
        public ThreadPool(int nThreads = 4)
        {
            _numOfThreads = nThreads;
            _waitingQueue = new WaitableQueue();
            s_sleepingSem = new Semaphore(0, 1000);
            s_sleepLock = new object();
            _workersDictionary = new Dictionary<int, WorkerThread>();

            AddWorker(_numOfThreads);
        }

        public void Pause()
        {
            PriorityTask sleeping_pill_task = new PriorityTask(SleepingPill, PRIORITY.DO_IT_NOW);

            for (int i = 0; i < _numOfThreads; ++i)
            {
                AddTask(sleeping_pill_task);
                Console.WriteLine("{0} sleeping pills added to queue", i + 1);
            }

            for (int i = 0; i < _numOfThreads; ++i)
            {
                s_sleepingSem.WaitOne();
                Console.WriteLine("{0} threads recieved sleeping pill", i + 1);
            }

            Console.WriteLine("All threads recieved sleeping pill");

            return;
        }
        public void AddTask(PriorityTask task)
        {
            _waitingQueue.Enqueue(task);
            Console.WriteLine("task added to queue");

            return;
        }

        public void Stop()
        {
            CloseWorker(_numOfThreads);
            return;
        }

        public void Resume()
        {
            Monitor.Enter(s_sleepLock);
            Monitor.PulseAll(s_sleepLock);
            Monitor.Exit(s_sleepLock);
            Console.WriteLine("Sleep lock pulsed. all workers should return to work.");

            return;
        }

        class WorkerThread
        {
            public WorkerThread(ref WaitableQueue waitingQueueRef)
            {
                _toRun = true;
                _waitingQueueRef = waitingQueueRef;
                t_thread = new Thread(()=>RunWorker());
                t_thread.Start();

            }
            public void RunWorker()
            {
                PriorityTask task;

                while (true == _toRun)
                {
                    task = _waitingQueueRef.Dequeue();
                    task.GetTask().Invoke();
                }

                return;
            }

            public int GetThreadNum()
            {
                return t_thread.ManagedThreadId;
            }
            public Thread GetThread()
            {
                return t_thread;
            }

            public void TurnOff()
            {
                _toRun = false;
                Console.WriteLine("Thread {0} turned off.", t_thread.ManagedThreadId);
            }

            private bool _toRun;
            private Thread t_thread;
            private WaitableQueue _waitingQueueRef;
        };

        public void SetNumOfThreads(int _newNum)
        {
            if (_newNum >= _numOfThreads)
            {
                AddWorker(_newNum - _numOfThreads);
            }
            else
            {
                CloseWorker(_numOfThreads - _newNum);
            }

            Console.WriteLine("Num of threads changed from {0} to {1}.", _numOfThreads, _newNum);

            _numOfThreads = _newNum;

            return;
        }

        private void BadApple()
        {
            _workersDictionary[Thread.CurrentThread.ManagedThreadId].TurnOff();
            _workersDictionary.Remove(Thread.CurrentThread.ManagedThreadId);
        }
        private void SleepingPill()
        {
            s_sleepingSem.Release();
            Monitor.Enter(s_sleepLock);
            Monitor.Wait(s_sleepLock);
            Monitor.Exit(s_sleepLock);
        }

        private void CloseWorker(int num_to_close)
        {
            PriorityTask bad_apple_task = new PriorityTask(BadApple, PRIORITY.DO_IT_NOW);

            for (int i = 0; i < num_to_close; ++i)
            {
                AddTask(bad_apple_task);
            }

        }

        private void AddWorker(int _workersToAdd)
        {
            for (int i = 0; i < _workersToAdd; ++i)
            {
                WorkerThread WT = new WorkerThread(ref this._waitingQueue);
                _workersDictionary.Add(WT.GetThreadNum(), WT);
                Console.WriteLine("Worker added with thread num {0}", WT.GetThreadNum());
            }    

            return;
        }

        private int _numOfThreads;
        private WaitableQueue _waitingQueue;
        private Dictionary<int, WorkerThread> _workersDictionary;
        private static Semaphore s_sleepingSem;
        private static object s_sleepLock;

    } // ThreadPool
}
