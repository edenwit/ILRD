using System;
using System.IO;
using System.IO.MemoryMappedFiles;
using System.Threading;

namespace MappedMemoryClient
{

    class Program
    {
        // Process B:
        static void Main(string[] args)
        {
            Console.WriteLine("Second process started.");
            
            using (MemoryMappedFile mmf = MemoryMappedFile.OpenExisting("C://Users//edenw//source//Repos//eden-wittenberg//c#//IPC//mapped_file//file_fun"))
                {
                    Mutex server_write_mutex;
                    Mutex server_read_mutex = new Mutex(true, "ping_pong_server_read_mutex");

                    while (false == Mutex.TryOpenExisting("ping_pong_server_write_mutex", out server_write_mutex))
                    {
                        Thread.Sleep(2000);
                        Console.WriteLine("waiting for mutex creation.");
                    }

                    for (int i = 0; i < 5; ++i)
                    {

                        server_write_mutex.WaitOne();
                        //Console.WriteLine("Process B locked mutex 1");

                        server_read_mutex.WaitOne();
                        //Console.WriteLine("Process B locked mutex 2");
                    
                        

                        using (MemoryMappedViewStream stream = mmf.CreateViewStream())
                        {
                            BinaryReader reader = new BinaryReader(stream);
                            Console.WriteLine("Process A says: {0}", reader.ReadString());
                            BinaryWriter writer = new BinaryWriter(stream);
                            writer.Write("pong");

                        }

                        server_read_mutex.ReleaseMutex();
                        //Console.WriteLine("Process B released mutex 2");

                        server_write_mutex.ReleaseMutex();
                        //Console.WriteLine("Process B released mutex 1");


                    }
                }

           
        }
    }
}
