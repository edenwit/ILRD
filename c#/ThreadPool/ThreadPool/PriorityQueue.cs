using System;
using System.Collections.Generic;
using System.Linq;

namespace ThreadPool
{
    public class IPrioritizable
    {
        public IPrioritizable(PRIORITY prior)
        {
            _priority = prior;
        }

        public PRIORITY GetPriority()
        {
            return _priority;
        }

        public void SetPriority(PRIORITY prior)
        {
            _priority = prior;
        }

        private PRIORITY _priority;
    }

    public sealed class PriorityQueue
    {
        public LinkedList<PriorityTask> Entries { get; } = new LinkedList<PriorityTask>();

        public int Count()
        {
            return Entries.Count;
        }

        public PriorityTask Dequeue()
        {
            if (Entries.Any())
            {
                PriorityTask itemTobeRemoved = Entries.First.Value;
                Entries.RemoveFirst();
                return itemTobeRemoved;
            }
            else
            {
                Console.WriteLine("Queue empty, cannot dequeue");
                return null;
            }
        }

        public void Enqueue(PriorityTask entry)
        {
            LinkedListNode< PriorityTask> value = new LinkedListNode<PriorityTask>(entry);
            if (Entries.First == null)
            {
                Entries.AddFirst(value);
            }
            else
            {
                LinkedListNode<PriorityTask> ptr = Entries.First;
                while ((ptr.Next != null) && (ptr.Value.GetPriority() < entry.GetPriority()))
                {
                    ptr = ptr.Next;
                }

                if (ptr.Value.GetPriority() <= entry.GetPriority())
                {
                    Entries.AddAfter(ptr, value);
                }
                else
                {
                    Entries.AddBefore(ptr, value);
                }
            }
        }
    }







}
