
using System;

namespace StackImplementation
{
    class Stack
    {
        public Stack(int size = 100)
        {
            top = 0;
            MAX = size;
            stack = new object[MAX];
        }
        public bool Push(object data)
        {
            if (top > MAX)
            {
                Console.WriteLine("Stack Overflow");
                return false;
            }
            else
            {
                stack[++top] = data;
                return true;
            }
        }

        public object Pop()
        {
            if (top <= 0)
            {
                Console.WriteLine("Stack Underflow");
                return 0;
            }
            else
            {
                object value = stack[top--];
                return value;
            }
        }

        public void Peek()
        {
            if (top <= 0)
            {
                Console.WriteLine("Stack Underflow");
                return;
            }
            else
                Console.WriteLine("The topmost element of Stack is : {0}", stack[top]);
        }
        public bool IsEmpty()
        {
            return (top <= 0);
        }

        public void PrintStack()
        {
            if (top <= 0)
            {
                Console.WriteLine("Stack Underflow");
                return;
            }
            else
            {
                Console.WriteLine("size of the stack is: ");
                Console.WriteLine(MAX);

                Console.WriteLine("Items in the Stack are :");
                for (int i = top; i >= 0; i--)
                {
                    Console.WriteLine(stack[i]);
                }
            }
        }

        public void Clear()
        {
            if (top > 0)
            {
                Array.Clear(stack, 0, top);
                top = 0;

            }
        }

        readonly int MAX;
        int top;
        object[] stack;
    }

    class Program
    {
        static void Main(string[] args)
        {
            Stack myStack = new Stack(500);

            myStack.Push(10);
            myStack.Push(20);
            myStack.Push(30);
            myStack.Push(40);
            myStack.Push("hello");
            myStack.Push(2.5);
            myStack.PrintStack();
            myStack.Peek();
            myStack.Clear();
            Console.WriteLine("Called clear");
            myStack.Peek();
            Console.WriteLine("Item popped from Stack : {0}", myStack.Pop());
            myStack.Push(30);
            myStack.Push(430);
            myStack.Push(3540);
            myStack.Push(4640);
            myStack.Push(3640);
            myStack.Push(470);
            myStack.Push(3870);
            myStack.Push(4870);
            myStack.Peek();
            Console.WriteLine("Item popped from Stack : {0}", myStack.Pop());
            myStack.Peek();
            Console.WriteLine("Item popped from Stack : {0}", myStack.Pop());
            myStack.Peek();
            Console.WriteLine("Item popped from Stack : {0}", myStack.Pop());
            myStack.Peek();
            Console.WriteLine("Item popped from Stack : {0}", myStack.Pop());
            myStack.Peek();
            Console.WriteLine("Item popped from Stack : {0}", myStack.Pop());
            myStack.Peek();
            Console.WriteLine("Item popped from Stack : {0}", myStack.Pop());
            myStack.Peek();
            Console.WriteLine("Item popped from Stack : {0}", myStack.Pop());
            myStack.Peek();
            Console.WriteLine("Item popped from Stack : {0}", myStack.Pop());
            myStack.PrintStack();


        }
    }
}