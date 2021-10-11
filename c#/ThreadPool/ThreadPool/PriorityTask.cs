using System;

namespace ThreadPool
{
    public class PriorityTask : IPrioritizable
    {
        private Action _task;
        public PriorityTask(Action t, PRIORITY p = PRIORITY.MEDIUM) : base(p)
        {
            _task = t;
        }

        public Action GetTask()
        {
            return _task;
        }

        public PRIORITY Priority()
        {
            return GetPriority();
        }
    }
}
