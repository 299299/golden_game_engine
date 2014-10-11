using System;
using System.Windows.Forms;
using System.IO;
using System.Diagnostics;

namespace ToolCenter
{
    public partial class MayaExportForm : Form
    {
        public MayaExportForm()
        {
            InitializeComponent();

            string[] folders = Directory.GetDirectories(Utils.getIntermediateDir());
            foreach (string path in folders)
            {
                string folderName = Path.GetFileNameWithoutExtension(path);
                if(folderName == "core" || folderName == "preview")
                    continue;
                comboBox_Package.Items.Add(folderName);
            }
            comboBox_Package.SelectedIndex = 0;

            /*
            string[] files = Directory.GetFiles(Utils.getPipelineDir() + "\\hko\\", "*.hko", SearchOption.TopDirectoryOnly);
            foreach (string file in files)
            {
                string fileName = Path.GetFileNameWithoutExtension(file);
                comboBox_Type.Items.Add(file);
            }
            comboBox_Type.SelectedIndex = 0;
             */
        }

        private void button_folder_Click(object sender, EventArgs e)
        {
            FolderBrowserDialog dlg = new FolderBrowserDialog();
            string path = Utils.GetSetting("maya_folder");
            if(path == "")
                path = "C:\\Project\\NagaGame\\Arts";
            dlg.SelectedPath = path;
            if (dlg.ShowDialog() != DialogResult.OK)
                return;
            textBox_Folder.Text = dlg.SelectedPath;
            Utils.SetSetting("maya_folder", dlg.SelectedPath);
            Utils.SaveSetting("tool_center.ini");
        }

        private void button_startExport_Click(object sender, EventArgs e)
        {
            string folder = textBox_Folder.Text;
            if (folder.Length == 0)
            {
                return;
            }

            string package = comboBox_Package.SelectedItem.ToString();
            if (package.Length == 0)
            {
                return;
            }

            string mayaPy = Utils.getMayaDir() + "bin\\mayapy.exe";
            string docFolder = Environment.GetFolderPath(Environment.SpecialFolder.MyDocuments);
            string args = Utils.getPipelineDir() + "MayaBatchExport.py ";
            args += folder;
            args += " ";
            args += package;

            Stopwatch watch = new Stopwatch();
            watch.Start();
            Utils.Run("", mayaPy, args);
            watch.Stop();
            float time = (float)watch.ElapsedMilliseconds / 1000;
            MessageBox.Show(this, "maya batch export total Time = " + time.ToString() + " seconds", "TOOL_CENTER");
            Utils.DeleteFolder(Utils.getApplicationDir() + "Keyboard");
        }
    }
}
