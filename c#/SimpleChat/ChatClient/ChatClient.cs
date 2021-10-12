using System;
using System.Text;
using System.Net.Sockets;
using System.Net;
using System.Threading;

namespace ChatClient
{
    class Program
    {
        static void Main(string[] args)
        {
            IPAddress ip = IPAddress.Parse("127.0.0.1");
            int port = 5000;
            TcpClient client = new TcpClient();
            Console.WriteLine("Insert user name: ");
            String userName = Console.ReadLine();
            client.Connect(ip, port);
            Console.WriteLine("client {0} connected!!", userName);
            NetworkStream ns = client.GetStream();

            byte[] userNameBuffer = Encoding.ASCII.GetBytes(userName);
            ns.Write(userNameBuffer, 0, userNameBuffer.Length);

            string s;

            Thread sender = new Thread( ()=> GetAndSendUser(ref ns));
            sender.Start();
            Thread reciever = new Thread(()=> ReadFromServer(ref ns));
            reciever.Start();

            sender.Join();
            reciever.Join();

            ns.Close();
            client.Close();
            Console.WriteLine("Client {0} disconnect from server!!", userName);
            Console.ReadKey();
        }

        public static void GetAndSendUser(ref NetworkStream ns)
        {
            string s;

            while (true)
            {
                Console.Write(">>");
            
                s = Console.ReadLine();
                byte[] buffer = Encoding.ASCII.GetBytes(s);
                ns.Write(buffer, 0, buffer.Length);
            }
        }

        public static void ReadFromServer(ref NetworkStream ns)
        {
            byte[] receivedBytes = new byte[1024];

            while (true)
            {
                int byte_count = ns.Read(receivedBytes, 0, receivedBytes.Length);
                byte[] formated = new byte[byte_count];
                //handle  the null characteres in the byte array
                Array.Copy(receivedBytes, formated, byte_count);
                string data = Encoding.ASCII.GetString(formated);
                Console.WriteLine(data);
            }
        }
    }
}
