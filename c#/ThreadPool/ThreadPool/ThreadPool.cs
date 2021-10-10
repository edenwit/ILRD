using System.Threading;

namespace ThreadPool
{
    class ThreadPool
    {
        public ThreadPool(int n_threads = 4)
        {
            num_of_threads = n_threads;
            WQ = new WaitableQueue();
            sleeping_sem = new Semaphore(num_of_threads, 1000);

            AddWorker(num_of_threads);

        }

        public void Pause()
        {
            PriorityTask sleeping_pill_task = new PriorityTask(SleepingPill, PRIORITY.VERY_HIGH);

            for (int i = 0; i < num_of_threads; ++i)
            {
                AddTask(ptr);
            }

            for (int i = 0; i < num_of_threads; ++i)
            {
                m_message_que.Deque(dymmy);
            }

            return;
        }
        public void AddTask(PriorityTask task)
        {
            WQ.Enqueue(task);
        }

        public void Stop()
        {
            CloseWorker(num_of_threads);

            return;
        }

        public void Resume()
        {
            //WQ.

            return;
        }

        class WorkerThread
        {
            public WorkerThread()
            {
                m_run = true;
                thread = new Thread(()->RunWorker(ref ThreadPool));

            }
            public void RunWorker(ref ThreadPool TP)
            {
                PriorityTask task;

                while (true == m_run)
                {
                    task = TP.WQ.Dequeue();
                    task.GetTask().Start();

                }

                return;
            }

            private bool m_run;
            private Thread thread;
        };

        public void SetNumOfThreads(int new_num)
        {
            if (new_num >= num_of_threads)
            {
                AddWorker(new_num - num_of_threads);
            }
            else
            {
                CloseWorker(num_of_threads - new_num);
            }

            return;
        }



        private static void BadApple(ThreadPool TP);
        private static void SleepingPill(ThreadPool TP);
        private void CloseWorker(int num_to_close)
        {
            PriorityTask bad_apple_task = new PriorityTask(BadApple, PRIORITY.VERY_HIGH);

            for (int i = 0; i < num_to_close; ++i)
            {
                AddTask(bad_apple_task);
            }

            for (int i = 0; i < num_to_close; ++i)
            {
                CleanUpWorker();
            }
        }

        private void AddWorker(int num_to_add)
        {
            for (int i = 0; i < num_to_add; ++i)
            {
                WorkerThread WT = new WorkerThread();
                //std::shared_ptr<WorkerThread> new_worker(new WorkerThread(this));
               // m_worker_map[new_worker->GetId()] = new_worker;
            }    

            return;
        }

        private int num_of_threads;
        private WaitableQueue WQ;
        private Semaphore sleeping_sem;


    } // ThreadPool
}
