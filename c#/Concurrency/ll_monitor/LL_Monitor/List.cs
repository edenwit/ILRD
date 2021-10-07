namespace ws2
{

    internal class Node
    {
        internal object data;
        internal Node _next;
        public Node(object _data = null)
        {
            data = _data;
            _next = null;
        }
        public Node Next()
        {
            return _next;
        }
    };


    partial class List 
    {

        internal Node head;

        internal int size;

        public List()
        /// <summary>
        /// Inits the List.
        /// </summary>
        
        ///<remarks>
        ///create new node as dummy head, init size to 0, nullise the _next member.
        ///</remarks>
        
        ///<returns>
        ///ctors do not return.
        /// </returns>
        {
            head = new Node(null);
            head._next = null;

            size = 0;
        }
        public bool IsEmpty()
        /// <summary>
        /// check if list is empty
        /// </summary>
        
        ///<remarks>
        /// call the "count" method to check if list is empty
        ///</remarks>
        
        ///<returns>
        ///returns "true" if list is empty, otherwise returns "false".
        /// </returns>
        {
            return Count() == 0;
        }

        public void Clear()
        /// <summary>
        /// clears the list
        /// </summary>

        ///<remarks>
        /// assign null to heads next member. release of nodes will happen automatically.
        ///</remarks>

        ///<returns>
        /// function does not return anything.
        /// </returns>
        {
            size = 0;
            head._next = null;
            return;
        }

        public int Count()
        /// <summary>
        /// counts the nodes in list without the head.
        /// </summary>

        ///<remarks>
        /// returns the "size" member
        ///</remarks>

        ///<returns>
        /// returns value of "size" member
        /// </returns>
        {
            return size;
        }

        public void Push(object _data)
        /// <summary>
        /// add node to end of list
        /// </summary>

        ///<remarks>
        /// create a new node, fill it with recieved data, iterate until last node, attach new node and increment size.
        ///</remarks>

        ///<returns>
        /// function does not return anything.
        /// </returns>
        {
            Node cur = head;
            Node new_node = new Node(_data);
            while (cur._next != null)
            {
                cur = cur.Next();
            }
            cur._next = new_node;
            ++size;
            return;
        }

        public object Pop()
        /// <summary>
        /// removes node from begining of list 
        /// </summary>

        ///<remarks>
        /// create new node, save data of first node, attach next node to head, decrement size and return value of removed node.
        ///</remarks>

        ///<returns>
        /// returns object in beginning of list.
        /// </returns>
        {
            Node head_next_next = null;
            object head_next = head._next;
            if (head_next != null)
            {
                head_next_next = head._next._next;
                head._next = head_next_next;
                head_next = ((Node)head_next).data;
                --size;
            }
            return head_next;
        }


        public object Peek()
        /// <summary>
        /// get first object in list 
        /// </summary>

        ///<remarks>
        /// check if list is not empty, and if it isn't, return value of first node.
        ///</remarks>

        ///<returns>
        /// returns the value of first node.
        /// </returns>
        {
            if (!IsEmpty())
            {
                return head._next.data;
            }
            return null;
        }

        public Node this[int i] => FindNode(i);

        private Node FindNode(int i)
        /// <summary>
        /// iterate list and returns the i member
        /// </summary>

        ///<remarks>
        /// iterate the list, find the i member and return it.
        ///</remarks>

        ///<returns>
        /// returns i element in the list. if it doesn't exist, return null.
        /// </returns>
        {
            int j = 0;
            Node cur = head;
            Node new_node = null;

            while (j < this.Count() && cur._next != null)
            {
                cur = cur.Next();
                if (j == i)
                {
                    new_node = new Node(cur.data);
                    break;
                }
                ++j;
            }

            return new_node;
        }

        public ListNode GetEnumerator()
        /// <summary>
        /// creates and returns iterable list
        /// </summary>

        ///<remarks>
        /// creates and returns iterable list
        ///</remarks>

        ///<returns>
        ///  returns iterable list.
        /// </returns>
        {
            return new ListNode(this);
        }
    }
}
