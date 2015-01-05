namespace ToolCenter
{
    partial class MayaExportForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.button_folder = new System.Windows.Forms.Button();
            this.textBox_Folder = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.comboBox_Package = new System.Windows.Forms.ComboBox();
            this.button_startExport = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // button_folder
            // 
            this.button_folder.Location = new System.Drawing.Point(381, 28);
            this.button_folder.Name = "button_folder";
            this.button_folder.Size = new System.Drawing.Size(29, 23);
            this.button_folder.TabIndex = 1;
            this.button_folder.Text = "+";
            this.button_folder.UseVisualStyleBackColor = true;
            this.button_folder.Click += new System.EventHandler(this.button_folder_Click);
            // 
            // textBox_Folder
            // 
            this.textBox_Folder.Enabled = false;
            this.textBox_Folder.Location = new System.Drawing.Point(12, 28);
            this.textBox_Folder.Name = "textBox_Folder";
            this.textBox_Folder.Size = new System.Drawing.Size(357, 21);
            this.textBox_Folder.TabIndex = 0;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(13, 56);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(83, 12);
            this.label1.TabIndex = 2;
            this.label1.Text = "package name:";
            // 
            // comboBox_Package
            // 
            this.comboBox_Package.FormattingEnabled = true;
            this.comboBox_Package.Location = new System.Drawing.Point(128, 56);
            this.comboBox_Package.Name = "comboBox_Package";
            this.comboBox_Package.Size = new System.Drawing.Size(162, 20);
            this.comboBox_Package.TabIndex = 3;
            // 
            // button_startExport
            // 
            this.button_startExport.Location = new System.Drawing.Point(15, 91);
            this.button_startExport.Name = "button_startExport";
            this.button_startExport.Size = new System.Drawing.Size(405, 80);
            this.button_startExport.TabIndex = 4;
            this.button_startExport.Text = "START";
            this.button_startExport.UseVisualStyleBackColor = true;
            this.button_startExport.Click += new System.EventHandler(this.button_startExport_Click);
            // 
            // MayaExportForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoSize = true;
            this.ClientSize = new System.Drawing.Size(432, 183);
            this.Controls.Add(this.button_startExport);
            this.Controls.Add(this.comboBox_Package);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.button_folder);
            this.Controls.Add(this.textBox_Folder);
            this.Name = "MayaExportForm";
            this.Text = "MayaExport";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button button_folder;
        private System.Windows.Forms.TextBox textBox_Folder;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ComboBox comboBox_Package;
        private System.Windows.Forms.Button button_startExport;
    }
}