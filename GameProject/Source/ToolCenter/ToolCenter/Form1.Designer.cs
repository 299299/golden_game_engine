namespace ToolCenter
{
    partial class Form1
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.notifyIcon1 = new System.Windows.Forms.NotifyIcon(this.components);
            this.contextMenuStrip1 = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.toolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem2 = new System.Windows.Forms.ToolStripMenuItem();
            this.button_maya = new System.Windows.Forms.Button();
            this.button_vs = new System.Windows.Forms.Button();
            this.button_animfsm = new System.Windows.Forms.Button();
            this.button_testgame = new System.Windows.Forms.Button();
            this.button_previewer = new System.Windows.Forms.Button();
            this.button_editor = new System.Windows.Forms.Button();
            this.button_html = new System.Windows.Forms.Button();
            this.button_toolcopy = new System.Windows.Forms.Button();
            this.button_dumpscript = new System.Windows.Forms.Button();
            this.button_buildms = new System.Windows.Forms.Button();
            this.Button_MakeFile = new System.Windows.Forms.Button();
            this.button_updatedoc = new System.Windows.Forms.Button();
            this.contextMenuStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // notifyIcon1
            // 
            this.notifyIcon1.ContextMenuStrip = this.contextMenuStrip1;
            this.notifyIcon1.Icon = ((System.Drawing.Icon)(resources.GetObject("notifyIcon1.Icon")));
            this.notifyIcon1.Text = "Naga ToolCenter";
            this.notifyIcon1.Visible = true;
            this.notifyIcon1.MouseDoubleClick += new System.Windows.Forms.MouseEventHandler(this.notifyIcon1_MouseDoubleClick);
            // 
            // contextMenuStrip1
            // 
            this.contextMenuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripMenuItem1,
            this.toolStripMenuItem2});
            this.contextMenuStrip1.Name = "contextMenuStrip1";
            this.contextMenuStrip1.Size = new System.Drawing.Size(108, 48);
            // 
            // toolStripMenuItem1
            // 
            this.toolStripMenuItem1.Name = "toolStripMenuItem1";
            this.toolStripMenuItem1.Size = new System.Drawing.Size(107, 22);
            this.toolStripMenuItem1.Text = "Show";
            this.toolStripMenuItem1.Click += new System.EventHandler(this.toolStripMenuItem1_Click);
            // 
            // toolStripMenuItem2
            // 
            this.toolStripMenuItem2.Name = "toolStripMenuItem2";
            this.toolStripMenuItem2.Size = new System.Drawing.Size(107, 22);
            this.toolStripMenuItem2.Text = "Exit";
            this.toolStripMenuItem2.Click += new System.EventHandler(this.toolStripMenuItem2_Click);
            // 
            // button_maya
            // 
            this.button_maya.Location = new System.Drawing.Point(28, 31);
            this.button_maya.Name = "button_maya";
            this.button_maya.Size = new System.Drawing.Size(109, 46);
            this.button_maya.TabIndex = 1;
            this.button_maya.Text = "Maya";
            this.button_maya.UseVisualStyleBackColor = true;
            this.button_maya.Click += new System.EventHandler(this.button_maya_Click);
            // 
            // button_vs
            // 
            this.button_vs.Location = new System.Drawing.Point(150, 31);
            this.button_vs.Name = "button_vs";
            this.button_vs.Size = new System.Drawing.Size(109, 46);
            this.button_vs.TabIndex = 2;
            this.button_vs.Text = "VS Proj";
            this.button_vs.UseVisualStyleBackColor = true;
            this.button_vs.Click += new System.EventHandler(this.button_vs_Click);
            // 
            // button_animfsm
            // 
            this.button_animfsm.Location = new System.Drawing.Point(150, 85);
            this.button_animfsm.Name = "button_animfsm";
            this.button_animfsm.Size = new System.Drawing.Size(109, 46);
            this.button_animfsm.TabIndex = 4;
            this.button_animfsm.Text = "Animation";
            this.button_animfsm.UseVisualStyleBackColor = true;
            this.button_animfsm.Click += new System.EventHandler(this.button_animfsm_Click);
            // 
            // button_testgame
            // 
            this.button_testgame.Location = new System.Drawing.Point(28, 85);
            this.button_testgame.Name = "button_testgame";
            this.button_testgame.Size = new System.Drawing.Size(109, 46);
            this.button_testgame.TabIndex = 3;
            this.button_testgame.Text = "Test Game";
            this.button_testgame.UseVisualStyleBackColor = true;
            this.button_testgame.Click += new System.EventHandler(this.button_testgame_Click);
            // 
            // button_previewer
            // 
            this.button_previewer.Location = new System.Drawing.Point(150, 143);
            this.button_previewer.Name = "button_previewer";
            this.button_previewer.Size = new System.Drawing.Size(109, 46);
            this.button_previewer.TabIndex = 6;
            this.button_previewer.Text = "Previewer";
            this.button_previewer.UseVisualStyleBackColor = true;
            this.button_previewer.Click += new System.EventHandler(this.button_previewer_Click);
            // 
            // button_editor
            // 
            this.button_editor.Location = new System.Drawing.Point(28, 143);
            this.button_editor.Name = "button_editor";
            this.button_editor.Size = new System.Drawing.Size(109, 46);
            this.button_editor.TabIndex = 5;
            this.button_editor.Text = "Engine Editor";
            this.button_editor.UseVisualStyleBackColor = true;
            this.button_editor.Click += new System.EventHandler(this.button_editor_Click);
            // 
            // button_html
            // 
            this.button_html.Location = new System.Drawing.Point(28, 206);
            this.button_html.Name = "button_html";
            this.button_html.Size = new System.Drawing.Size(109, 46);
            this.button_html.TabIndex = 7;
            this.button_html.Text = "Engine HTML";
            this.button_html.UseVisualStyleBackColor = true;
            this.button_html.Click += new System.EventHandler(this.button_html_Click);
            // 
            // button_toolcopy
            // 
            this.button_toolcopy.Location = new System.Drawing.Point(150, 206);
            this.button_toolcopy.Name = "button_toolcopy";
            this.button_toolcopy.Size = new System.Drawing.Size(109, 46);
            this.button_toolcopy.TabIndex = 8;
            this.button_toolcopy.Text = "Copy Tools";
            this.button_toolcopy.UseVisualStyleBackColor = true;
            this.button_toolcopy.Click += new System.EventHandler(this.button_toolcopy_Click);
            // 
            // button_dumpscript
            // 
            this.button_dumpscript.Location = new System.Drawing.Point(28, 267);
            this.button_dumpscript.Name = "button_dumpscript";
            this.button_dumpscript.Size = new System.Drawing.Size(109, 46);
            this.button_dumpscript.TabIndex = 9;
            this.button_dumpscript.Text = "Dump Script";
            this.button_dumpscript.UseVisualStyleBackColor = true;
            this.button_dumpscript.Click += new System.EventHandler(this.button_dumpscript_Click);
            // 
            // button_buildms
            // 
            this.button_buildms.Location = new System.Drawing.Point(150, 267);
            this.button_buildms.Name = "button_buildms";
            this.button_buildms.Size = new System.Drawing.Size(109, 46);
            this.button_buildms.TabIndex = 10;
            this.button_buildms.Text = "Engine Build";
            this.button_buildms.UseVisualStyleBackColor = true;
            this.button_buildms.Click += new System.EventHandler(this.button_buildms_Click);
            // 
            // Button_MakeFile
            // 
            this.Button_MakeFile.Location = new System.Drawing.Point(28, 330);
            this.Button_MakeFile.Name = "Button_MakeFile";
            this.Button_MakeFile.Size = new System.Drawing.Size(109, 46);
            this.Button_MakeFile.TabIndex = 11;
            this.Button_MakeFile.Text = "Dev MakeFile";
            this.Button_MakeFile.UseVisualStyleBackColor = true;
            this.Button_MakeFile.Click += new System.EventHandler(this.Button_MakeFile_Click);
            // 
            // button_updatedoc
            // 
            this.button_updatedoc.Location = new System.Drawing.Point(150, 330);
            this.button_updatedoc.Name = "button_updatedoc";
            this.button_updatedoc.Size = new System.Drawing.Size(109, 46);
            this.button_updatedoc.TabIndex = 12;
            this.button_updatedoc.Text = "Update Doc";
            this.button_updatedoc.UseVisualStyleBackColor = true;
            this.button_updatedoc.Click += new System.EventHandler(this.button_updatedoc_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoSize = true;
            this.ClientSize = new System.Drawing.Size(300, 472);
            this.Controls.Add(this.button_updatedoc);
            this.Controls.Add(this.Button_MakeFile);
            this.Controls.Add(this.button_buildms);
            this.Controls.Add(this.button_dumpscript);
            this.Controls.Add(this.button_toolcopy);
            this.Controls.Add(this.button_html);
            this.Controls.Add(this.button_previewer);
            this.Controls.Add(this.button_editor);
            this.Controls.Add(this.button_animfsm);
            this.Controls.Add(this.button_testgame);
            this.Controls.Add(this.button_vs);
            this.Controls.Add(this.button_maya);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.Name = "Form1";
            this.Text = "Naga Tool Center";
            this.Resize += new System.EventHandler(this.Form1_Resize);
            this.contextMenuStrip1.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.NotifyIcon notifyIcon1;
        private System.Windows.Forms.ContextMenuStrip contextMenuStrip1;
        private System.Windows.Forms.ToolStripMenuItem toolStripMenuItem1;
        private System.Windows.Forms.ToolStripMenuItem toolStripMenuItem2;
        private System.Windows.Forms.Button button_maya;
        private System.Windows.Forms.Button button_vs;
        private System.Windows.Forms.Button button_animfsm;
        private System.Windows.Forms.Button button_testgame;
        private System.Windows.Forms.Button button_previewer;
        private System.Windows.Forms.Button button_editor;
        private System.Windows.Forms.Button button_html;
        private System.Windows.Forms.Button button_toolcopy;
        private System.Windows.Forms.Button button_dumpscript;
        private System.Windows.Forms.Button button_buildms;
        private System.Windows.Forms.Button Button_MakeFile;
        private System.Windows.Forms.Button button_updatedoc;

    }
}

