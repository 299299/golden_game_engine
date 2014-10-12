using System;
using System.IO;
using System.Diagnostics;
using System.Windows.Forms;
using System.Collections.Generic;
using System.Text;
using System.Runtime.InteropServices;

namespace ToolCenter
{
    class Utils
    {
        static public string getNagaDir()
        {
            return getParentDir(Directory.GetCurrentDirectory());
        }

        static public string getApplicationDir()
        {
            return getNagaDir() + "Application\\";
        }

        static public string getPipelineDir()
        {
            return getNagaDir() + "Pipeline\\";
        }

        static public string getDCCExportDir()
        {
            return getNagaDir() + "DCC_Export\\";
        }

        static public string getIntermediateDir()
        {
            return getApplicationDir() + "intermediate\\";
        }

        static public string getMayaDir()
        {
            string ret = Environment.GetEnvironmentVariable("MAYA_DIR");
            if (!ret.EndsWith("\\"))
                ret += "\\";
            return ret;
        }

        static public string getParentDir(string dir)
        {
            int len = dir.LastIndexOf('\\');
            dir = dir.Substring(0, len);
            //len = dir.LastIndexOf('\\');
            //dir = dir.Substring(0, len);
            dir += "\\";
            return dir;
        }

        static public void Lunch(string exeFile, string arguments = "")
        {
            try
            {
                Process.Start(exeFile, arguments);
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(exeFile, ex.Message);
            }
        }

        static public int Run(string workdingDir, string exeFile, string arguments = "", bool bWait = true)
        {
            Process process = new Process();
            try
            {
                process.StartInfo.FileName = exeFile;
                process.StartInfo.Arguments = arguments;
                process.StartInfo.WorkingDirectory = workdingDir;
                process.Start();
                if (bWait) process.WaitForExit();
            }
            catch (Exception ex)
            {
                MessageBox.Show(workdingDir + exeFile, ex.Message);
            }
            if (process == null || !bWait) return 0;
            if (!process.HasExited) return 0;
            return process.ExitCode;
        }

        static public void showTimeCost(Stopwatch watch, String text)
        {
            watch.Stop();
            float time = (float)watch.ElapsedMilliseconds / 1000;
            MessageBox.Show(text + " Total Time = " + time.ToString() + " seconds", "TOOL_CENTER");
        }

        static public void run_application(string folder, string exe, string args, string text)
        {
            Stopwatch watch = new Stopwatch();
            watch.Start();
            Run(folder, exe, args);
            showTimeCost(watch, text);
        }

        static public void DeleteFolder(string folderToDelete)
        {
            if (!Directory.Exists(folderToDelete))
                return;
            Directory.Delete(folderToDelete, true);
        }

        static public void DeleteFile(string fileToDelete)
        {
            if (!File.Exists(fileToDelete))
                return;
            File.Delete(fileToDelete);
        }

        static public string LoadString(string fileName)
        {
            System.IO.StreamReader file;
            try
            {
                file = new System.IO.StreamReader(fileName);
            }
            catch (System.IO.FileNotFoundException e)
            {
                Console.WriteLine(e.Message);
                return "";
            }
            return file.ReadToEnd();
        }

        static public string GetSetting(string key)
        {
            StringBuilder MyString = new StringBuilder(256);
            GetProfileString("NAGA_TOOL_CENTER", key, "", MyString, 256);
            return MyString.ToString();
        }

        static public void SetSetting(string key, string value)
        {
            WriteProfileString("NAGA_TOOL_CENTER", key, value);
        }

        [DllImport("kernel32")]
        public static extern bool GetProfileString(string lpApplicationName, string lpKeyName, string lpDefault, StringBuilder lpReturnedString, int nSize);
        [DllImport("kernel32")]
        public static extern bool WriteProfileString(string lpApplicationName, string lpKeyName, string lpString);
    }
}
