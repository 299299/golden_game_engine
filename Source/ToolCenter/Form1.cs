using System;
using System.Windows.Forms;
using System.IO;
using System.Diagnostics;

namespace ToolCenter
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            Utils.LoadSetting("tool_center.ini");
        }

        private void Form1_Resize(object sender, EventArgs e)
        {
            if (WindowState == FormWindowState.Minimized)
            {
                this.Hide();
                this.ShowInTaskbar = false;
            }
        }

        private void notifyIcon1_MouseDoubleClick(object sender, MouseEventArgs e)
        {
            this.Show();
            this.WindowState = FormWindowState.Normal;
            this.ShowInTaskbar = true;
        }

        private void toolStripMenuItem1_Click(object sender, EventArgs e)
        {
            this.Show();
            this.WindowState = FormWindowState.Normal;
            this.ShowInTaskbar = true;
        }

        private void toolStripMenuItem2_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void button_maya_Click(object sender, EventArgs e)
        {
            Utils.Lunch(Utils.getMayaDir() + "bin\\maya.exe");
        }

        private void button_vs_Click(object sender, EventArgs e)
        {
            Utils.Lunch(Utils.getNagaDir() + "Source\\Game.sln");
        }

        private void button_testgame_Click(object sender, EventArgs e)
        {
            Utils.Run(Utils.getApplicationDir(), "Game_Debug.exe", "-m 1 --level world0/Level_Test", false);
        }

        private void button_toolcopy_Click(object sender, EventArgs e)
        {
            Utils.Run(Utils.getPipelieDir(), "pipeline_copy.bat");
        }

        private void button_buildms_Click(object sender, EventArgs e)
        {
            Utils.run_application(Utils.getPipelieDir(), "project_build.bat", "", "Engine Source Build");
        }

        private void button_hash_Click(object sender, EventArgs e)
        {
            new HashForm().Show();
        }

        private void button_batchExport_Click(object sender, EventArgs e)
        {
            new MayaExportForm().Show();
        }

        private void do_build()
        {
            Stopwatch watch = new Stopwatch();
            watch.Start();
            string args = "-t 4 -i " + Utils.getDCCExportDir() + "Havok" + " --slient";
            int hRetCode = Utils.Run(Utils.getApplicationDir(), "HavokConverter.exe", args);
            args = "-i intermediate/ -m 0 -t 4 --slient";
            int dRetCode = Utils.Run(Utils.getApplicationDir(), "DataCompiler.exe", args);
            watch.Stop();
            float time = (float)watch.ElapsedMilliseconds / 1000;
            string msg = "Build Total Time = " + time.ToString() + " seconds\n";
            if(hRetCode != 0)
            {
                msg += "HavokConvert error ";
                if(hRetCode < 0)
                {
                    msg += "occurs = " + (-hRetCode).ToString() + "\n";
                }
                else
                {
                    string[] errorMsg = 
                    {
                        "havok load error",
                        "input argument error",
                        "save output error"
                    };
                    msg += errorMsg[hRetCode];
                }
            }

            if( dRetCode != 0) 
            {
                msg += "DataCompiler error ";
                if( dRetCode < 0)
                {
                    msg += "occurs = " + (-dRetCode).ToString();
                }
                else
                {
                    string[] errorMsg = 
                    {
                        "input argument error",
                    };
                    msg += errorMsg[hRetCode];
                }
            }
            
            MessageBox.Show(msg, "TOOL_CENTER");
        }

        private void do_clean()
        {
            //remove all intermediate folders do not named core.
            string[] intermediaFolders = Directory.GetDirectories(Utils.getIntermediateDir());
            foreach (string folder in intermediaFolders)
            {
                int index = folder.IndexOf("intermediate\\core");
                if (index >= 0)
                    continue;
                string[] subFolders = Directory.GetDirectories(folder);
                foreach (string subFolder in subFolders)
                {
                    Utils.DeleteFolder(subFolder);
                }
            }
            Utils.DeleteFolder(Utils.getIntermediateDir() + "core\\entity");
            Utils.DeleteFolder(Utils.getApplicationDir() + "data");
            Utils.DeleteFile("data_compiler_database.txt");
            Utils.DeleteFile("havok_convert_database");
            Utils.DeleteFolder(Utils.getApplicationDir() + "Keyboard");
            Utils.DeleteFolder(Utils.getPipelieDir() + "Keyboard");
        }

        private void button_fullBuild_Click(object sender, EventArgs e)
        {
            do_build();
        }

        private void button_clean_Click(object sender, EventArgs e)
        {
            do_clean();
        }

        private void button_rebuild_Click(object sender, EventArgs e)
        {
            if (MessageBox.Show(this, "Are you sure ?", "Confirm", MessageBoxButtons.YesNo) == DialogResult.No)
                return;
            do_clean();
            do_build();
        }

        private void button_console_Click(object sender, EventArgs e)
        {
            new ConsoleForm().Show();
        }
    }
}
