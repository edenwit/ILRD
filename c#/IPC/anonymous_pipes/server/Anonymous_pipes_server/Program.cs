using System;
using System.IO;
using System.IO.Pipes;
using System.Diagnostics;

class PipeServer
{
    static void Main()
    {
        Process pipeClient = new Process();

        pipeClient.StartInfo.FileName = "C://Users//edenw//source//Repos//eden-wittenberg//c#//IPC//anonymous_pipes//client//Anonymous_pipes_client//bin//Debug//net5.0//Anonymous_pipes_client.exe";

        using (AnonymousPipeServerStream pipeServer = new AnonymousPipeServerStream(PipeDirection.Out, HandleInheritability.Inheritable))
        {

            using (AnonymousPipeServerStream pipeServerIn = new AnonymousPipeServerStream(PipeDirection.In, HandleInheritability.Inheritable))
            {

                Console.WriteLine("[SERVER] Current TransmissionMode: {0}.",
                pipeServer.TransmissionMode);

                String args_to_pass = pipeServer.GetClientHandleAsString() + " " + pipeServerIn.GetClientHandleAsString();

                Console.WriteLine(args_to_pass);

                // Pass the client process a handle to the server.
                pipeClient.StartInfo.Arguments = args_to_pass;
                pipeClient.StartInfo.UseShellExecute = false;
                pipeClient.Start();

                pipeServer.DisposeLocalCopyOfClientHandle();
                pipeServerIn.DisposeLocalCopyOfClientHandle();

                try
                {

                    // Read user input and send that to the client process.
                    using (StreamWriter sw = new StreamWriter(pipeServer))
                    {
                        using (StreamReader sr = new StreamReader(pipeServerIn))
                        {
                            sw.AutoFlush = true;
                            // Send a 'sync message' and wait for client to receive it.
                            Console.WriteLine("server try");
                            sw.WriteLine("HI");

                            // Send the console input to the client process.
                            String temp;

                            for (int i = 0; i < 10; ++i)
                            {
                                temp = sr.ReadLine();
                                
                                Console.WriteLine("[SERVER] Echo: " + temp);

                                sw.WriteLine("ping");
                            }


                        }

                    }
                }
                // Catch the IOException that is raised if the pipe is broken
                // or disconnected.
                catch (IOException e)
                {
                    Console.WriteLine("[SERVER] Error: {0}", e.Message);
                }
            }
        }

        pipeClient.WaitForExit();
        pipeClient.Close();
        Console.WriteLine("[SERVER] Client quit. Server terminating.");
    }
}