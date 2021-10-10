using System.Threading;

namespace ThreadPool
{
    class WaitableQueue
    {
        public WaitableQueue()
        {
            tasks = new PriorityQueue<PriorityTask>();
            alock = new object();
        }

        public void Enqueue(PriorityTask task_to_insert)
        {
            Monitor.Enter(alock);
            tasks.Enqueue(task_to_insert);
            Monitor.PulseAll(alock);
            Monitor.Exit(alock);
        }
        public PriorityTask Dequeue()
        {
            Monitor.Enter(alock);

            if (tasks.Count() == 0)
            {
                Monitor.Wait(alock);
            }

            PriorityTask task = tasks.Dequeue();
            
            Monitor.Exit(alock);

            return task;

        }

        private PriorityQueue<PriorityTask> tasks;
        private object alock;
    }
}
