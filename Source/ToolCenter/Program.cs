using System;
using System.Windows.Forms;
using System.IO;

namespace ToolCenter
{
    static class Program
    {
        /// <summary>
        /// 应用程序的主入口点。
        /// </summary>
        [STAThread]
        static void Main()
        {
            bool mutexCreated = false;
            System.Threading.Mutex mutex = new System.Threading.Mutex(true, @"Local\EngineToolCenter.exe", out mutexCreated);

            if (!mutexCreated)
            {
                MessageBox.Show("Tool center already-run", "TOOL_CENTER");
                mutex.Close();
                return;
            }

            string ret = Environment.GetEnvironmentVariable("NAGA_DIR");
            if (ret == null)
            {
                string nagaDir = Directory.GetCurrentDirectory();
                int index = nagaDir.LastIndexOf('\\');
                nagaDir = nagaDir.Substring(0, index + 1);
                MessageBox.Show("can not find NAGA_DIR registry,please set it to " + nagaDir);
                mutex.Close();
                return;
            }

            Environment.GetEnvironmentVariable("MAYA_DIR");
            if (ret == null)
            {
                string nagaDir = Directory.GetCurrentDirectory();
                int index = nagaDir.LastIndexOf('\\');
                nagaDir = nagaDir.Substring(0, index + 1);
                MessageBox.Show("can not find MAYA_DIR registry,please set it to autodesk maya install dir");
                mutex.Close();
                return;
            }

            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new Form1());

            mutex.Close();
        }
    }
}
