using System;
using System.IO;
using System.IO.Pipes;
using System.Threading;

using System.Text;
class Program
{

    static void Main(string[] args)
    {
        Console.WriteLine("Server started.");

            using (var server = new NamedPipeServerStream("pipe_to_server"))
            {
                using (var client = new NamedPipeClientStream("pipe_to_client"))
                {
                    server.WaitForConnection();
                    Console.WriteLine("Client connected to server.");
                    client.Connect();
                    Console.WriteLine("Server connected to client server.");

                using (var reader = new StreamReader(server))
                    {
                        using (var writer = new StreamWriter(client))
                        {
                            for (int i = 0; i < 3; ++i)
                            {
                                string line = reader.ReadLine();
                                Console.WriteLine("server recieved: {0}", line);

                                
                                writer.AutoFlush = true;
                                Thread.Sleep(1000);
                                writer.WriteLine("Pong");
                                client.WaitForPipeDrain();

                        }
                    }

                    }

                }

            }
    }
}