using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Diagnostics;

namespace ToolCenter
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
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

        private string getMayaDir()
        {
            string ret = Environment.GetEnvironmentVariable("MAYA_DIR");
            if (!ret.EndsWith("\\"))
                ret += "\\";
            return ret;
        }

        private string getNagaDir()
        {
            string ret = Environment.GetEnvironmentVariable("NAGA_DIR");
            if (!ret.EndsWith("\\"))
                ret += "\\";
            return ret;
        }

        private void Lunch(string exeFile, string arguments = "")
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

        private void Run(string workdingDir, string exeFile,string arguments = "")
        {
            Process proce = new Process();
            proce.StartInfo.FileName = exeFile;
            proce.StartInfo.Arguments = arguments;
            proce.StartInfo.WorkingDirectory = workdingDir;
            try
            {
                proce.Start();
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(workdingDir + exeFile, ex.Message);
            }
        }

        private void button_maya_Click(object sender, EventArgs e)
        {
            Lunch(getMayaDir() + "bin/maya.exe");
        }

        private void button_vs_Click(object sender, EventArgs e)
        {
            Lunch(getNagaDir() + "../Build/Urho3D.sln");
        }

        private void button_testgame_Click(object sender, EventArgs e)
        {
            Run(getNagaDir(), "naga_animation.bat");
        }

        private void button_animfsm_Click(object sender, EventArgs e)
        {
            Run(getNagaDir(), "naga_animation_fsm.bat");
        }

        private void button_editor_Click(object sender, EventArgs e)
        {
            Run(getNagaDir(), "naga_editor.bat");
        }

        private void button_previewer_Click(object sender, EventArgs e)
        {
            Run(getNagaDir(), "hkxSceneViewer.bat");
        }

        private void button_html_Click(object sender, EventArgs e)
        {
            Lunch(getNagaDir() + "/Tool/app/index.html");
        }

        private void button_toolcopy_Click(object sender, EventArgs e)
        {
            Run(getNagaDir() + "Pipeline", "pipeline_copy.bat");
        }

        private void button_dumpscript_Click(object sender, EventArgs e)
        {
            Run(getNagaDir(), "DumpScript.bat");
        }

        private void button_buildms_Click(object sender, EventArgs e)
        {
            Lunch(getNagaDir() + "../naga_build.bat");
        }

        private void Button_MakeFile_Click(object sender, EventArgs e)
        {
            string naga_dir = getNagaDir();
            int len = naga_dir.LastIndexOf('\\');
            naga_dir = naga_dir.Substring(0,len);
            len = naga_dir.LastIndexOf('\\');
            naga_dir = naga_dir.Substring(0,len);
            naga_dir += "\\";
            Run(naga_dir, "naga_make.bat");
        }

        private void button_updatedoc_Click(object sender, EventArgs e)
        {
            Run(getNagaDir(), "UpdateDocument.bat");
        }
    }
}
