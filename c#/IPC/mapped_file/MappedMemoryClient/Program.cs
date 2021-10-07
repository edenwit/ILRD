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

            String text;
            
            Semaphore sem_server = Semaphore.OpenExisting("sem_server");
            Semaphore sem_client = Semaphore.OpenExisting("sem_client");

            using (MemoryMappedFile mmf = MemoryMappedFile.OpenExisting("C://Users//edenw//source//Repos//eden-wittenberg//c#//IPC//mapped_file//file_fun1"))
            {
                using (MemoryMappedViewStream stream = mmf.CreateViewStream())
                {
                    for (int i = 0; i < 20; ++i)
                    {
                        sem_client.WaitOne();
                        BinaryReader reader = new BinaryReader(stream);
                        Console.WriteLine("Process A says: {0}", reader.ReadString());
                        BinaryWriter writer = new BinaryWriter(stream);
                        text = "pong" + i;
                        writer.Write(text);
                        sem_server.Release();
                    }
                }

            }

           
        }
    }
}
