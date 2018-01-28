using System;
using System.Linq;
using System.IO;

namespace CreateHTML
{
    class Program
    {
        static string JS = "D:\\Web\\scripts.js";

        static string tvPath = "D:\\TV";

        static void Main(string[] args)
        {
            for (int i = 0; i < args.Length; ++i)
            {
                switch (args[i])
                {
                    case "-js":
                        JS = args[i + 1];
                        break;

                    case "-tv":
                        tvPath = args[i + 1];
                        break;
                }
            }

            string[] Shows = Directory.GetDirectories(tvPath);

            for (int i = 0; i < Shows.Length; ++i)
            {
                Shows[i] = Shows[i].Split(new Char[] { '\\' }).Last();
            }

            string[] lines = File.ReadAllLines(JS);


            System.IO.StreamWriter file = new System.IO.StreamWriter(JS + ".new");

            foreach (string line in lines)
            {
                if (line == "/********TAG********/")
                {
                    break;
                }
                file.WriteLine(line);
            }

            file.WriteLine();
            file.WriteLine();
            file.WriteLine("/********TAG********/");
            file.WriteLine();
            file.WriteLine("var shows = [");
            for (int i = 0; i < Shows.Length - 1; ++i)
            {
                file.WriteLine("\t\"" + Shows[i] + "\",");
            }
            file.WriteLine("\t\"" + Shows.Last() + "\"");
            file.WriteLine("];");
            file.WriteLine();
            file.WriteLine("var showMap = new Map([");
            for( int i = 0; i < Shows.Length; ++i)
            {
                string[] episodes = Directory.GetFiles(tvPath + "\\" + Shows[i], "*.mkv", SearchOption.AllDirectories);
                file.Write("[\"" + Shows[i] + "\", [");
                for(int j = 0; j < episodes.Length; ++j)
                {
                    string temp = episodes[j].Split(new Char[] { '\\' }).Last();
                    temp = temp.Replace(".mkv", "");
                    string toWrite = temp.Split(new Char[] { '-' })[1] + "-" + temp.Split(new Char[] { '-' })[2];
                    toWrite = toWrite.TrimStart(' ');
                    if (j < episodes.Length - 1)
                    {
                        file.Write("\"" + toWrite + "\", ");
                    }
                    else
                    {
                        file.Write("\"" + toWrite + "\"");
                    }
                }
                if (i < Shows.Length - 1)
                {
                    file.WriteLine("]],");
                }
                else
                {
                    file.WriteLine("]]");
                }

            }
            file.WriteLine("]);");
            file.Flush();
            file.Close();

            File.Delete(JS);
            File.Move(JS + ".new", JS);

            Console.WriteLine("Completed");
        }
    }
}
