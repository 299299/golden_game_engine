using System;
using System.IO;
using System.Diagnostics;
using System.Windows.Forms;
using System.Collections.Generic;

namespace ToolCenter
{
    class Utils
    {
        static Dictionary<string,string> m_toolSetting;

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

        static public void LoadSetting(string settingFile)
        {
            m_toolSetting = new Dictionary<string, string>();
            System.IO.StreamReader file;
            try
            {
                file = new System.IO.StreamReader(settingFile);
            }
            catch (System.IO.FileNotFoundException e)
            {
                Console.WriteLine(e.Message);
                return;
            }
            string line;
            while ((line = file.ReadLine()) != null)
            {
                string[] keyValue = line.Split('=');
                m_toolSetting.Add(keyValue[0], keyValue[1]);
            }
            file.Close();
        }

        static public void SaveSetting(string settingFile)
        {
            System.IO.StreamWriter file = new System.IO.StreamWriter(settingFile);
            foreach(KeyValuePair<string, string> entry in m_toolSetting)
            {
                file.WriteLine(entry.Key + "=" + entry.Value);
            }
            file.Close();
        }

        static public string GetSetting(string key)
        {
            if (!m_toolSetting.ContainsKey(key))
                return "";
            return m_toolSetting[key];
        }

        static public void SetSetting(string key, string value)
        {
            m_toolSetting[key] = value;
        }
    }
}
