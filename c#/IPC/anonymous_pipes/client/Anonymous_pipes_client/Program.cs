using System;
using System.IO;
using System.IO.Pipes;

class PipeClient
{
    static void Main(string[] args)
    {
        if (args.Length > 1)
        {
            Console.WriteLine("args: {0}", args.Length);


            using (PipeStream pipeClient =
                new AnonymousPipeClientStream(PipeDirection.In, args[0]))
            {
                using (PipeStream pipeClientOut =
                    new AnonymousPipeClientStream(PipeDirection.Out, args[1]))
                {
                    Console.WriteLine(args[0] + " " + args[1]);
                    using (StreamReader sr = new StreamReader(pipeClient))
                    {
                        using (StreamWriter sw = new StreamWriter(pipeClientOut))
                        {
                            sw.AutoFlush = true;

                            // Display the read text to the console
                            string temp;

                            // Wait for 'sync message' from the server.
                            /*do
                            {
                                Console.WriteLine("[CLIENT] Wait for sync...");
                                temp = sr.ReadLine();
                                Console.WriteLine("temp is: {0}", temp);
                            }
                            while (!temp.StartsWith("HI"));*/

                            // Read the server data and echo to the console.
                            for (int i = 0; i < 10; ++i)
                            {
                                temp = sr.ReadLine();
                                
                                Console.WriteLine("[CLIENT] Echo: " + temp);
                                
                                sw.WriteLine("pong");

                            }
                        }
                    }
                }
            }
        }
        Console.Write("[CLIENT] Press Enter to continue...");
        Console.ReadLine();
    }
}