using System;
using System.Net;


namespace DownloadWebPage
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Insert Webpage url: ");
            String _url = Console.ReadLine();
            if (string.IsNullOrEmpty(_url))
            {
                _url = "https://ebin.ort.org.il/category/about/";
                Console.WriteLine("No url inserted. Default: {0}", _url);

            }
            Console.WriteLine("Insert file address: ");
            String _path = Console.ReadLine();
            if (string.IsNullOrEmpty(_path))
            {
                _path = "C://Users//edenw//source//Repos//eden-wittenberg//c#//DownloadWebPage//downloads//file.html";
                Console.WriteLine("No path inserted. Default: {0}", _path);
            }

            DownloadFile(_url, _path);
        }
        
        static void DownloadFile(string remoteFilename, string localFilename)
        {
            WebClient client = new WebClient();
            client.DownloadFile(remoteFilename, localFilename);
        }

    }
    

}

