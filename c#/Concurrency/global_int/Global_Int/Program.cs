using System;
using System.Threading;

namespace Global_Int
{ 
    class Program
    {
        static bool flag = false;
        static void Main(string[] args)
        {
            Thread producer_thread = new Thread(new ThreadStart(Producer));
            Thread consumer_thread = new Thread(new ThreadStart(Consumer));

            producer_thread.Start();
            consumer_thread.Start();
        }
        static public void Producer()
        {
            for (int i = 0; i < 100; ++i)
            {
                while (flag)
                {
                    Console.ForegroundColor = ConsoleColor.White;
                    Console.WriteLine("[PRODUCER] : waiting");
                }
                Console.ForegroundColor = ConsoleColor.Red;
                Console.WriteLine("[PRODUCER] : Ping");
                flag = true;
            }

        }
        static public void Consumer()
        {
            for (int i = 0; i < 100; ++i)
            {
                while (!flag)
                {
                    Console.ForegroundColor = ConsoleColor.White;
                    Console.WriteLine("[CONSUMER] : waiting");
                }
                Console.ForegroundColor = ConsoleColor.Blue;
                Console.WriteLine("[CONSUMER] : Pong");
                flag = false;
            }
        }
    }
}


