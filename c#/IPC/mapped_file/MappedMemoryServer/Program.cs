using System;
using System.IO;
using System.IO.MemoryMappedFiles;
using System.Threading;

namespace MappedMemoryServer
{

    class Program
    {
        // Process A:
        static void Main(string[] args)
        {
            Console.WriteLine("First process started.");

            using (MemoryMappedFile mmf = MemoryMappedFile.CreateNew("C://Users//edenw//source//Repos//eden-wittenberg//c#//IPC//mapped_file//file_fun", 10000))
            {
                Mutex server_write_mutex = new Mutex(true, "ping_pong_server_write_mutex");
                Mutex server_read_mutex;

                while (false == Mutex.TryOpenExisting("ping_pong_server_read_mutex", out server_read_mutex))
                {
                    Thread.Sleep(2000);
                    Console.WriteLine("waiting for mutex creation.");
                }

                for (int i = 0; i < 5; ++i)
                {
                    Thread.Sleep(2000);

                    server_write_mutex.WaitOne();
                    //Console.WriteLine("Process A locked mutex 1");
                    

                    using (MemoryMappedViewStream stream = mmf.CreateViewStream())
                    {
                        BinaryWriter writer = new BinaryWriter(stream);
                        writer.Write("ping");
                    }

                    server_read_mutex.WaitOne();
                    //Console.WriteLine("Process A locked mutex 2");


                    server_write_mutex.ReleaseMutex();
                    //Console.WriteLine("Process A released mutex 1");


                    using (MemoryMappedViewStream stream = mmf.CreateViewStream())
                    {
                        BinaryReader reader = new BinaryReader(stream);
                        Console.WriteLine("Process B says: {0}", reader.ReadString());
                    
                    }

                    server_read_mutex.ReleaseMutex();
                    //Console.WriteLine("Process A released mutex 2");



                }
            }
        }
    }
}
