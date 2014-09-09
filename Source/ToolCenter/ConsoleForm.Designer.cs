namespace ToolCenter
{
    partial class ConsoleForm
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
            this.richTextBox_log = new System.Windows.Forms.RichTextBox();
            this.checkBox_watch = new System.Windows.Forms.CheckBox();
            this.textBox_Host = new System.Windows.Forms.TextBox();
            this.buttonConnect = new System.Windows.Forms.Button();
            this.textBox_input = new System.Windows.Forms.TextBox();
            this.comboBox_type = new System.Windows.Forms.ComboBox();
            this.SuspendLayout();
            // 
            // richTextBox_log
            // 
            this.richTextBox_log.Location = new System.Drawing.Point(21, 59);
            this.richTextBox_log.Name = "richTextBox_log";
            this.richTextBox_log.ReadOnly = true;
            this.richTextBox_log.Size = new System.Drawing.Size(686, 179);
            this.richTextBox_log.TabIndex = 0;
            this.richTextBox_log.Text = "";
            // 
            // checkBox_watch
            // 
            this.checkBox_watch.AutoSize = true;
            this.checkBox_watch.Location = new System.Drawing.Point(305, 25);
            this.checkBox_watch.Name = "checkBox_watch";
            this.checkBox_watch.Size = new System.Drawing.Size(150, 16);
            this.checkBox_watch.TabIndex = 1;
            this.checkBox_watch.Text = "Enable Resource Watch";
            this.checkBox_watch.UseVisualStyleBackColor = true;
            this.checkBox_watch.CheckedChanged += new System.EventHandler(this.checkBox_watch_CheckedChanged);
            // 
            // textBox_Host
            // 
            this.textBox_Host.Location = new System.Drawing.Point(21, 23);
            this.textBox_Host.Name = "textBox_Host";
            this.textBox_Host.Size = new System.Drawing.Size(160, 21);
            this.textBox_Host.TabIndex = 2;
            this.textBox_Host.Text = "127.0.0.1:6161";
            // 
            // buttonConnect
            // 
            this.buttonConnect.Location = new System.Drawing.Point(197, 21);
            this.buttonConnect.Name = "buttonConnect";
            this.buttonConnect.Size = new System.Drawing.Size(75, 23);
            this.buttonConnect.TabIndex = 3;
            this.buttonConnect.Text = "connect";
            this.buttonConnect.UseVisualStyleBackColor = true;
            this.buttonConnect.Click += new System.EventHandler(this.buttonConnect_Click);
            // 
            // textBox_input
            // 
            this.textBox_input.Location = new System.Drawing.Point(112, 244);
            this.textBox_input.Name = "textBox_input";
            this.textBox_input.Size = new System.Drawing.Size(595, 21);
            this.textBox_input.TabIndex = 4;
            this.textBox_input.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.textBox_input_KeyPress);
            // 
            // comboBox_type
            // 
            this.comboBox_type.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBox_type.FormattingEnabled = true;
            this.comboBox_type.ImeMode = System.Windows.Forms.ImeMode.NoControl;
            this.comboBox_type.Items.AddRange(new object[] {
            "Command",
            "Script"});
            this.comboBox_type.Location = new System.Drawing.Point(21, 244);
            this.comboBox_type.Name = "comboBox_type";
            this.comboBox_type.Size = new System.Drawing.Size(85, 20);
            this.comboBox_type.TabIndex = 5;
            // 
            // ConsoleForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(729, 291);
            this.Controls.Add(this.comboBox_type);
            this.Controls.Add(this.textBox_input);
            this.Controls.Add(this.buttonConnect);
            this.Controls.Add(this.textBox_Host);
            this.Controls.Add(this.checkBox_watch);
            this.Controls.Add(this.richTextBox_log);
            this.Name = "ConsoleForm";
            this.Text = "Console";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.ConsoleForm_FormClosed);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.RichTextBox richTextBox_log;
        private System.Windows.Forms.CheckBox checkBox_watch;
        private System.Windows.Forms.TextBox textBox_Host;
        private System.Windows.Forms.Button buttonConnect;
        private System.Windows.Forms.TextBox textBox_input;
        private System.Windows.Forms.ComboBox comboBox_type;
    }
}