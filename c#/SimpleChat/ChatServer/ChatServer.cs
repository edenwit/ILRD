using System;
using System.Threading;
using System.Net.Sockets;
using System.Text;
using System.Collections.Generic;
using System.Net;


class ChatServer
{
    static void Main(string[] args)
    {
        Dictionary<int, TcpClient> list_clients = new Dictionary<int, TcpClient>();

        int count = 1;

        TcpListener ServerSocket = new TcpListener(IPAddress.Any, 5000);
        ServerSocket.Start();

        Console.WriteLine("[SERVER Started.]");


        while (true)
        {
            TcpClient client = ServerSocket.AcceptTcpClient();
            list_clients.Add(count, client);
            Console.WriteLine("[CLIENT {0}] connected!!", count);
            Box box = new Box(client, list_clients, count);
            count++;

            Thread t = new Thread(handle_clients);
            t.Start(box);
        }

    }

    public static void handle_clients(object o)
    {
        Box box = (Box)o;
        Dictionary<int, TcpClient> list_connections = box.list;

        while (true)
        {
            NetworkStream stream = box.c.GetStream();
            byte[] buffer = new byte[1024];
            int byte_count = stream.Read(buffer, 0, buffer.Length);
            byte[] formated = new Byte[byte_count];
            //handle  the null characteres in the byte array
            Array.Copy(buffer, formated, byte_count);
            string data = "[CLIENT " + box.userName + "] : " + Encoding.ASCII.GetString(formated);
            broadcast(box.userName, list_connections, data);
            Console.WriteLine(data);
        }
    }

    public static void broadcast(int userNum, Dictionary<int, TcpClient> conexoes, string data)
    {
        foreach (KeyValuePair<int, TcpClient> c in conexoes)
        {
            if (c.Key != userNum)
            {
                NetworkStream stream = c.Value.GetStream();

                byte[] buffer = Encoding.ASCII.GetBytes(data);
                stream.Write(buffer, 0, buffer.Length);
            }
        }
    }

}
class Box
{
    public TcpClient c;
    public Dictionary<int, TcpClient> list;
    public int userName;

    public Box(TcpClient c, Dictionary<int, TcpClient> list, int userNum)
    {
        this.c = c;
        this.list = list;
        this.userName = userNum;
    }

}