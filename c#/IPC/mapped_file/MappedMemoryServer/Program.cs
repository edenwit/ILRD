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
            Semaphore sem_server = new Semaphore(initialCount: 0, maximumCount: 1, name: "sem_server");
            Semaphore sem_client = new Semaphore(initialCount: 0, maximumCount: 1, name: "sem_client");

            Console.WriteLine("First process started.");


            using (MemoryMappedFile mmf = MemoryMappedFile.CreateNew("C://Users//edenw//source//Repos//eden-wittenberg//c#//IPC//mapped_file//file_fun1", 10000))
            {
                Thread.Sleep(10000);

                String text;

                using (MemoryMappedViewStream stream = mmf.CreateViewStream())
                {
                    BinaryWriter writer = new BinaryWriter(stream);
                    text = "first ping";
                    writer.Write(text);
                

                Console.WriteLine("server first write");

                sem_client.Release();

                Console.WriteLine("after wait");

                
                    for (int i = 0; i < 20; ++i)
                    {
                        sem_server.WaitOne();

                        Thread.Sleep(2000);

                            BinaryReader reader = new BinaryReader(stream);
                            Console.WriteLine("Process B says: {0}", reader.ReadString());
                            text = "ping" + i;
                            writer.Write(text);
                            sem_client.Release();
                    }

                }


            }
          }
    }
}
