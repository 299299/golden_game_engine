using System;
using System.Windows.Forms;

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

            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new Form1());

            mutex.Close();
        }
    }
}
