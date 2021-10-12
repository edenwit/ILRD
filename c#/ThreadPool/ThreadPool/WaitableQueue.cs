using System.Threading;
using System;

namespace ThreadPool
{
    class WaitableQueue
    {
        public WaitableQueue()
        {
            _tasks = new PriorityQueue();
            _lock = new object();
        }

        public void Enqueue(PriorityTask _taskToInsert)
        {
            Monitor.Enter(_lock);
            _tasks.Enqueue(_taskToInsert);
            Monitor.Pulse(_lock);
            Monitor.Exit(_lock);
        }
        public PriorityTask Dequeue()
        {
            Monitor.Enter(_lock);

            while (_tasks.Count() == 0)
            {
                Console.WriteLine("thread {0} 'tasks' queue empty. waiting.", Thread.CurrentThread.ManagedThreadId);
                Monitor.Wait(_lock);
            }

            PriorityTask task = _tasks.Dequeue();
            
            Monitor.Exit(_lock);

            return task;
        }
        private PriorityQueue _tasks;
        private object _lock;
    }
}
