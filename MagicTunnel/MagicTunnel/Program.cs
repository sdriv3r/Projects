using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net.Sockets;

namespace MagicTunnel
{
    class Program
    {
        

        static void Main(string[] args)
        {
            TcpListener server = new TcpListener(System.Net.IPAddress.Parse("127.0.0.1"), 9999);

            server.Start();

            Byte[] bytes = new Byte[256];
            String data = null;

            while (true)
            {
                TcpClient client = server.AcceptTcpClient();

                data = null;

                NetworkStream stream = client.GetStream();

                int i;

                while ((i = stream.Read(bytes, 0, bytes.Length)) != 0)
                {
                    // Translate data bytes to a ASCII string.
                    data = System.Text.Encoding.ASCII.GetString(bytes, 0, i);
                    Console.WriteLine("Received: {0}", data);

                    // Process the data sent by the client.
                    data = string.Empty;
                    data = "HTTP/1.1 200 OK";

                    byte[] msg = System.Text.Encoding.ASCII.GetBytes(data);

                    // Send back a response.
                    stream.Write(msg, 0, msg.Length);
                    Console.WriteLine("Sent: {0}", data);
                }
            }
        }
    }
}
