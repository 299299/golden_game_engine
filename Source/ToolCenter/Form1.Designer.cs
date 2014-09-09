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
            this.button_testgame = new System.Windows.Forms.Button();
            this.button_toolcopy = new System.Windows.Forms.Button();
            this.button_buildms = new System.Windows.Forms.Button();
            this.button_hash = new System.Windows.Forms.Button();
            this.button_batchExport = new System.Windows.Forms.Button();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.button_rebuild = new System.Windows.Forms.Button();
            this.button_fullBuild = new System.Windows.Forms.Button();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.button_clean = new System.Windows.Forms.Button();
            this.groupBox4 = new System.Windows.Forms.GroupBox();
            this.button_console = new System.Windows.Forms.Button();
            this.contextMenuStrip1.SuspendLayout();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.groupBox4.SuspendLayout();
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
            this.button_maya.Location = new System.Drawing.Point(7, 15);
            this.button_maya.Name = "button_maya";
            this.button_maya.Size = new System.Drawing.Size(130, 46);
            this.button_maya.TabIndex = 1;
            this.button_maya.Text = "Maya";
            this.button_maya.UseVisualStyleBackColor = true;
            this.button_maya.Click += new System.EventHandler(this.button_maya_Click);
            // 
            // button_vs
            // 
            this.button_vs.Location = new System.Drawing.Point(6, 20);
            this.button_vs.Name = "button_vs";
            this.button_vs.Size = new System.Drawing.Size(128, 46);
            this.button_vs.TabIndex = 2;
            this.button_vs.Text = "VS Proj";
            this.button_vs.UseVisualStyleBackColor = true;
            this.button_vs.Click += new System.EventHandler(this.button_vs_Click);
            // 
            // button_testgame
            // 
            this.button_testgame.Location = new System.Drawing.Point(6, 20);
            this.button_testgame.Name = "button_testgame";
            this.button_testgame.Size = new System.Drawing.Size(130, 46);
            this.button_testgame.TabIndex = 3;
            this.button_testgame.Text = "Test Game";
            this.button_testgame.UseVisualStyleBackColor = true;
            this.button_testgame.Click += new System.EventHandler(this.button_testgame_Click);
            // 
            // button_toolcopy
            // 
            this.button_toolcopy.Location = new System.Drawing.Point(166, 15);
            this.button_toolcopy.Name = "button_toolcopy";
            this.button_toolcopy.Size = new System.Drawing.Size(128, 46);
            this.button_toolcopy.TabIndex = 8;
            this.button_toolcopy.Text = "Copy Maya Scrips";
            this.button_toolcopy.UseVisualStyleBackColor = true;
            this.button_toolcopy.Click += new System.EventHandler(this.button_toolcopy_Click);
            // 
            // button_buildms
            // 
            this.button_buildms.Location = new System.Drawing.Point(156, 20);
            this.button_buildms.Name = "button_buildms";
            this.button_buildms.Size = new System.Drawing.Size(130, 46);
            this.button_buildms.TabIndex = 10;
            this.button_buildms.Text = "Code Build";
            this.button_buildms.UseVisualStyleBackColor = true;
            this.button_buildms.Click += new System.EventHandler(this.button_buildms_Click);
            // 
            // button_hash
            // 
            this.button_hash.Location = new System.Drawing.Point(6, 73);
            this.button_hash.Name = "button_hash";
            this.button_hash.Size = new System.Drawing.Size(130, 46);
            this.button_hash.TabIndex = 15;
            this.button_hash.Text = "Hash Lookup";
            this.button_hash.UseVisualStyleBackColor = true;
            this.button_hash.Click += new System.EventHandler(this.button_hash_Click);
            // 
            // button_batchExport
            // 
            this.button_batchExport.Location = new System.Drawing.Point(6, 20);
            this.button_batchExport.Name = "button_batchExport";
            this.button_batchExport.Size = new System.Drawing.Size(130, 46);
            this.button_batchExport.TabIndex = 16;
            this.button_batchExport.Text = "Maya Batch Export";
            this.button_batchExport.UseVisualStyleBackColor = true;
            this.button_batchExport.Click += new System.EventHandler(this.button_batchExport_Click);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.button_toolcopy);
            this.groupBox1.Controls.Add(this.button_maya);
            this.groupBox1.Location = new System.Drawing.Point(21, 16);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(308, 100);
            this.groupBox1.TabIndex = 17;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Maya";
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.button_rebuild);
            this.groupBox2.Controls.Add(this.button_fullBuild);
            this.groupBox2.Controls.Add(this.button_batchExport);
            this.groupBox2.Location = new System.Drawing.Point(24, 131);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(305, 136);
            this.groupBox2.TabIndex = 18;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Pipeline";
            // 
            // button_rebuild
            // 
            this.button_rebuild.Location = new System.Drawing.Point(6, 72);
            this.button_rebuild.Name = "button_rebuild";
            this.button_rebuild.Size = new System.Drawing.Size(130, 46);
            this.button_rebuild.TabIndex = 18;
            this.button_rebuild.Text = "Force ReBuild";
            this.button_rebuild.UseVisualStyleBackColor = true;
            this.button_rebuild.Click += new System.EventHandler(this.button_rebuild_Click);
            // 
            // button_fullBuild
            // 
            this.button_fullBuild.Location = new System.Drawing.Point(161, 20);
            this.button_fullBuild.Name = "button_fullBuild";
            this.button_fullBuild.Size = new System.Drawing.Size(130, 46);
            this.button_fullBuild.TabIndex = 17;
            this.button_fullBuild.Text = "Build";
            this.button_fullBuild.UseVisualStyleBackColor = true;
            this.button_fullBuild.Click += new System.EventHandler(this.button_fullBuild_Click);
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.button_clean);
            this.groupBox3.Controls.Add(this.button_hash);
            this.groupBox3.Controls.Add(this.button_vs);
            this.groupBox3.Controls.Add(this.button_buildms);
            this.groupBox3.Location = new System.Drawing.Point(28, 282);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(298, 125);
            this.groupBox3.TabIndex = 19;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "Programmer";
            // 
            // button_clean
            // 
            this.button_clean.Location = new System.Drawing.Point(156, 73);
            this.button_clean.Name = "button_clean";
            this.button_clean.Size = new System.Drawing.Size(130, 46);
            this.button_clean.TabIndex = 4;
            this.button_clean.Text = "Resource Clean";
            this.button_clean.UseVisualStyleBackColor = true;
            this.button_clean.Click += new System.EventHandler(this.button_clean_Click);
            // 
            // groupBox4
            // 
            this.groupBox4.Controls.Add(this.button_console);
            this.groupBox4.Controls.Add(this.button_testgame);
            this.groupBox4.Location = new System.Drawing.Point(30, 425);
            this.groupBox4.Name = "groupBox4";
            this.groupBox4.Size = new System.Drawing.Size(297, 112);
            this.groupBox4.TabIndex = 20;
            this.groupBox4.TabStop = false;
            this.groupBox4.Text = "Test";
            // 
            // button_console
            // 
            this.button_console.Location = new System.Drawing.Point(154, 20);
            this.button_console.Name = "button_console";
            this.button_console.Size = new System.Drawing.Size(130, 46);
            this.button_console.TabIndex = 4;
            this.button_console.Text = "Console";
            this.button_console.UseVisualStyleBackColor = true;
            this.button_console.Click += new System.EventHandler(this.button_console_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoSize = true;
            this.ClientSize = new System.Drawing.Size(360, 549);
            this.Controls.Add(this.groupBox4);
            this.Controls.Add(this.groupBox3);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.Name = "Form1";
            this.Text = "Naga Tool Center";
            this.Resize += new System.EventHandler(this.Form1_Resize);
            this.contextMenuStrip1.ResumeLayout(false);
            this.groupBox1.ResumeLayout(false);
            this.groupBox2.ResumeLayout(false);
            this.groupBox3.ResumeLayout(false);
            this.groupBox4.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.NotifyIcon notifyIcon1;
        private System.Windows.Forms.ContextMenuStrip contextMenuStrip1;
        private System.Windows.Forms.ToolStripMenuItem toolStripMenuItem1;
        private System.Windows.Forms.ToolStripMenuItem toolStripMenuItem2;
        private System.Windows.Forms.Button button_maya;
        private System.Windows.Forms.Button button_vs;
        private System.Windows.Forms.Button button_testgame;
        private System.Windows.Forms.Button button_toolcopy;
        private System.Windows.Forms.Button button_buildms;
        private System.Windows.Forms.Button button_hash;
        private System.Windows.Forms.Button button_batchExport;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.GroupBox groupBox4;
        private System.Windows.Forms.Button button_fullBuild;
        private System.Windows.Forms.Button button_clean;
        private System.Windows.Forms.Button button_rebuild;
        private System.Windows.Forms.Button button_console;

    }
}

