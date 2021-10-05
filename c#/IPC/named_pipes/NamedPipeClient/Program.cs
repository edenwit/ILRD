using System;
using System.IO;
using System.IO.Pipes;
using System.Text;
using System.Threading;

class Program
{

    static void Main(string[] args)
    {
        Console.WriteLine("Client started.");

        using (var client = new NamedPipeClientStream("pipe_to_server"))
        {
            using (var server = new NamedPipeServerStream("pipe_to_client"))
            {
                client.Connect();
                Console.WriteLine("Client connected to server.");

                server.WaitForConnection();
                Console.WriteLine("Server connected to client server.");

                using (var writer = new StreamWriter(client))
                {
                    using (var reader = new StreamReader(server))
                    {
                        for (int i = 0; i < 3; ++i)
                        {
                          writer.AutoFlush = true;
                          Thread.Sleep(1000);
                          writer.WriteLine("Ping");
                          client.WaitForPipeDrain();
                          string line = reader.ReadLine();
                          Console.WriteLine("client recieved: {0}", line);

                        }
                    }
                }
            }
        }

    }
}