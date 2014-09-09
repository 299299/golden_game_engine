namespace ToolCenter
{
    partial class HashForm
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
            this.textBox_String = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label_result = new System.Windows.Forms.Label();
            this.buttonShow = new System.Windows.Forms.Button();
            this.textBox_hash = new System.Windows.Forms.TextBox();
            this.lable_result2 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // textBox_String
            // 
            this.textBox_String.Location = new System.Drawing.Point(24, 36);
            this.textBox_String.Name = "textBox_String";
            this.textBox_String.Size = new System.Drawing.Size(297, 21);
            this.textBox_String.TabIndex = 0;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(22, 9);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(101, 12);
            this.label1.TabIndex = 1;
            this.label1.Text = "type the string:";
            // 
            // label_result
            // 
            this.label_result.AutoSize = true;
            this.label_result.Location = new System.Drawing.Point(26, 81);
            this.label_result.Name = "label_result";
            this.label_result.Size = new System.Drawing.Size(143, 12);
            this.label_result.TabIndex = 2;
            this.label_result.Text = "I am the hash result :)";
            // 
            // buttonShow
            // 
            this.buttonShow.Location = new System.Drawing.Point(24, 219);
            this.buttonShow.Name = "buttonShow";
            this.buttonShow.Size = new System.Drawing.Size(297, 33);
            this.buttonShow.TabIndex = 3;
            this.buttonShow.Text = "Show";
            this.buttonShow.UseVisualStyleBackColor = true;
            this.buttonShow.Click += new System.EventHandler(this.buttonShow_Click);
            // 
            // textBox_hash
            // 
            this.textBox_hash.Location = new System.Drawing.Point(24, 120);
            this.textBox_hash.Name = "textBox_hash";
            this.textBox_hash.Size = new System.Drawing.Size(297, 21);
            this.textBox_hash.TabIndex = 4;
            // 
            // lable_result2
            // 
            this.lable_result2.AutoSize = true;
            this.lable_result2.Location = new System.Drawing.Point(26, 175);
            this.lable_result2.Name = "lable_result2";
            this.lable_result2.Size = new System.Drawing.Size(155, 12);
            this.lable_result2.TabIndex = 5;
            this.lable_result2.Text = "I am the string result :)";
            // 
            // HashForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoSize = true;
            this.ClientSize = new System.Drawing.Size(352, 285);
            this.Controls.Add(this.lable_result2);
            this.Controls.Add(this.textBox_hash);
            this.Controls.Add(this.buttonShow);
            this.Controls.Add(this.label_result);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.textBox_String);
            this.Name = "HashForm";
            this.Text = "HashFrom";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox textBox_String;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label_result;
        private System.Windows.Forms.Button buttonShow;
        private System.Windows.Forms.TextBox textBox_hash;
        private System.Windows.Forms.Label lable_result2;
    }
}