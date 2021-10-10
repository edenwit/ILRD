using System;
using System.Threading.Tasks;

namespace ThreadPool
{
    public class PriorityTask : IPrioritizable
    {
        private Task ttask;
        public PriorityTask(Task t, PRIORITY p)
        {
            this.Priority = p;
            this.ttask = t;
        }

        public PRIORITY Priority 
        {
            get
            {
                return Priority;
            }
            set
            {
                Priority = value;
            }
        }

        public Task GetTask()
        {
            return ttask;
        }
    }
}
