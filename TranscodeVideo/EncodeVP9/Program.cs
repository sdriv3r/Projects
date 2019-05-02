using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Diagnostics;
using System.IO;

namespace EncodeVP9
{

    class Program
    {
        static string MainDir = "X:\\TV";

        static string FinalExtention = ".mkv";

        static bool Freeze = false;

        static int Numb = 1;

        static int Par = 1;

        static Dictionary<Process, string> ffmpegList = new Dictionary<Process, string>();

        static List<string> sAllFiles;

        static int iEncodeCount = 0;

        static AutoResetEvent exitEvent = new AutoResetEvent(false);

        static string[] FileFormats =
        {
            "*.3gp",
            "*.asf",
            "*.wmv",
            "*.avi",
            "*.mkv",
            "*.mov",
            "*.mp4",
            "*.vob",
            "*.ts"
        };

        static void Main(string[] args)
        {
            for (int i = 0; i < args.Length; ++i)
            {
                switch (args[i])
                {
                    case "-dir":
                        MainDir = args[i + 1];
                        break;

                    case "-extout":
                        FinalExtention = args[i + 1];
                        break;

                    case "-n":
                        Numb = Convert.ToInt32(args[i + 1]);
                        break;

                    case "-p":
                        Par = Convert.ToInt32(args[i + 1]);
                        break;

                    case "-h":
                        Console.WriteLine("EncodeVP9");
                        Console.WriteLine("Application written by Lukasz Bialowas");
                        Console.WriteLine();
                        Console.WriteLine("Application can be used to scan throught a directory for all video files. It will re-encode a non-h265 file into h265. If all files are already h265 or no video file is found, the application simply exits. Needs ffmpeg and ffprobe.");
                        Console.WriteLine();
                        Console.WriteLine("-dir     Directory to scan throught for files to convert. Default: D:\\TV");
                        Console.WriteLine("-extout  Extention of the converted file. Default: .mkv");
                        Console.WriteLine("-dest    Where to put converted file. Default: D:\\Finished Torrents\\");
                        Console.WriteLine("-p       Number of clips to convert at the same time");
                        Console.WriteLine("-n       Number encodes to do");
                        return;
                }
            }

            sAllFiles = FindVideos();

            var sAllFiles_copy = new List<string>(sAllFiles);
            foreach (string file in sAllFiles_copy)
            {
                string comment = GetComment(file);

                FileInfo fileInfo = new FileInfo(file);

                if (comment != "Encoded Kutayz V2\r\n")
                {
                    var process = new Process();
                    ffmpegList.Add(process, file);
                    process.StartInfo = new ProcessStartInfo("ffmpeg.exe");
                    process.StartInfo.UseShellExecute = false;
                    //process.StartInfo.RedirectStandardOutput = true;
                    //process.StartInfo.RedirectStandardError = true;
                    process.EnableRaisingEvents = true;
                    process.Exited += new EventHandler(ffmpeg_exit);

                    EncodeVideo(process, file);

                    Console.WriteLine("Starting Encode for " + file);

                    iEncodeCount++;

                    if (iEncodeCount >= Numb)
                    {
                        break;
                    }
                }

                sAllFiles.Remove(file);

                if (ffmpegList.Count == Par)
                {
                    break;
                }
            }

            exitEvent.WaitOne();

        }

        static List<string> FindVideos()
        {
            List<string> sAllFiles = new List<string>();
            foreach (string extention in FileFormats)
            {
                string[] sArrayTmp = Directory.GetFiles(MainDir, extention, SearchOption.AllDirectories);
                int sAllFilesLenght = sAllFiles.Count;
                sAllFiles.AddRange(sArrayTmp);
            }
            return sAllFiles;
        }

        static string GetComment(string file)
        {
            var ffprobe = new Process();
            ffprobe.StartInfo = new ProcessStartInfo("ffprobe.exe");
            ffprobe.StartInfo.RedirectStandardOutput = true;
            ffprobe.StartInfo.RedirectStandardError = true;
            ffprobe.StartInfo.UseShellExecute = false;

            string comment = "", error;
            try
            {
                ffprobe.StartInfo.Arguments = "-v error -show_entries format_tags=comment -of default=noprint_wrappers=1:nokey=1 \"" + file + "\"";
                ffprobe.Start();

                comment = ffprobe.StandardOutput.ReadToEnd();
                error = ffprobe.StandardError.ReadToEnd();

                ffprobe.WaitForExit();
            }
            catch
            {
                Console.WriteLine("Unable to start ffprobe. Press any key to close.");
                Console.ReadLine();
                Environment.Exit(0);
            }
            return comment;
        }

        static void EncodeVideo(Process ffmpeg, string file)
        {
            string newfile = string.Empty;

            var newfilearray = file.Split(new Char[] { '.' });

            for (int i = 0; i < newfilearray.Length - 1; ++i)
            {
                if (i > 0)
                {
                    newfile += ".";
                }

                newfile += newfilearray[i];
            }

            newfile += "+++encoding+++" + FinalExtention;

            ffmpeg.StartInfo.Arguments = "-i \"" + file + "\" -c:v libvpx-vp9 -crf 30 -b:v 0 -g 360 -c:a libvorbis -q:a 4.0 -sn -metadata comment=\"Encoded Kutayz V2\" " + "\"" + newfile + "\"";

            try
            {
                ffmpeg.Start();
            }
            catch
            {
                Console.WriteLine("Unable to start ffmpeg. Press any key to close.");
                Console.ReadLine();
                Environment.Exit(0);
            }
        }

        static void ffmpeg_exit(object sender, System.EventArgs e)
        {
            Process process = sender as Process;
            File.Delete(ffmpegList[process]);

            string filename = string.Empty;
            var filenamearray = ffmpegList[process].Split(new Char[] { '.' });

            for (int j = 0; j < filenamearray.Length - 1; ++j)
            {
                if (j > 0)
                {
                    filename += ".";
                }

                filename += filenamearray[j];
            }

            File.Move(filename + "+++encoding+++" + FinalExtention, filename + FinalExtention);
            ffmpegList.Remove(process);

            Console.WriteLine("Finished encoding " + filename);

            if (iEncodeCount >= Numb)
            {
                if (ffmpegList.Count == 0)
                {
                    exitEvent.Set();
                }
                return;
            }

            var sAllFiles_copy = new List<string>(sAllFiles);
            foreach (string file in sAllFiles_copy)
            {
                string comment = GetComment(file);

                FileInfo fileInfo = new FileInfo(file);

                if (comment != "Encoded Kutayz V2\r\n")
                {
                    process = new Process();
                    ffmpegList.Add(process, file);
                    process.StartInfo = new ProcessStartInfo("ffmpeg.exe");
                    process.StartInfo.UseShellExecute = false;
                    //process.StartInfo.RedirectStandardOutput = true;
                    //process.StartInfo.RedirectStandardError = true;
                    process.EnableRaisingEvents = true;
                    process.Exited += new EventHandler(ffmpeg_exit);

                    EncodeVideo(process, file);

                    iEncodeCount++;

                    Console.WriteLine("Starting Encode for " + file);

                    sAllFiles.Remove(file);

                    break;
                }

                sAllFiles.Remove(file);
            }
        }
    }
}
