namespace MFWTools
{
    partial class CodeGeneratorForm
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
            this.m_startBt = new System.Windows.Forms.Button();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.m_dbpwdTB = new System.Windows.Forms.TextBox();
            this.m_dbUserTB = new System.Windows.Forms.TextBox();
            this.m_dbNameTB = new System.Windows.Forms.TextBox();
            this.m_dbPortTB = new System.Windows.Forms.TextBox();
            this.m_dbIpTB = new System.Windows.Forms.TextBox();
            this.label5 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.m_liulanBT = new System.Windows.Forms.Button();
            this.m_LangSelectCB = new System.Windows.Forms.ComboBox();
            this.label9 = new System.Windows.Forms.Label();
            this.label10 = new System.Windows.Forms.Label();
            this.m_OutPathTB = new System.Windows.Forms.TextBox();
            this.m_prototb = new System.Windows.Forms.TextBox();
            this.label6 = new System.Windows.Forms.Label();
            this.m_protopathdt = new System.Windows.Forms.Button();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.SuspendLayout();
            // 
            // m_startBt
            // 
            this.m_startBt.Location = new System.Drawing.Point(257, 343);
            this.m_startBt.Name = "m_startBt";
            this.m_startBt.Size = new System.Drawing.Size(75, 23);
            this.m_startBt.TabIndex = 0;
            this.m_startBt.Text = "转换";
            this.m_startBt.UseVisualStyleBackColor = true;
            this.m_startBt.Click += new System.EventHandler(this.m_startBt_Click);
            // 
            // groupBox1
            // 
            this.groupBox1.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.groupBox1.Controls.Add(this.m_dbpwdTB);
            this.groupBox1.Controls.Add(this.m_dbUserTB);
            this.groupBox1.Controls.Add(this.m_dbNameTB);
            this.groupBox1.Controls.Add(this.m_dbPortTB);
            this.groupBox1.Controls.Add(this.m_dbIpTB);
            this.groupBox1.Controls.Add(this.label5);
            this.groupBox1.Controls.Add(this.label4);
            this.groupBox1.Controls.Add(this.label3);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Location = new System.Drawing.Point(12, 12);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(320, 189);
            this.groupBox1.TabIndex = 2;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = " maom";
            // 
            // m_dbpwdTB
            // 
            this.m_dbpwdTB.Location = new System.Drawing.Point(62, 129);
            this.m_dbpwdTB.Name = "m_dbpwdTB";
            this.m_dbpwdTB.Size = new System.Drawing.Size(252, 21);
            this.m_dbpwdTB.TabIndex = 1;
            // 
            // m_dbUserTB
            // 
            this.m_dbUserTB.Location = new System.Drawing.Point(62, 102);
            this.m_dbUserTB.Name = "m_dbUserTB";
            this.m_dbUserTB.Size = new System.Drawing.Size(252, 21);
            this.m_dbUserTB.TabIndex = 1;
            // 
            // m_dbNameTB
            // 
            this.m_dbNameTB.Location = new System.Drawing.Point(62, 74);
            this.m_dbNameTB.Name = "m_dbNameTB";
            this.m_dbNameTB.Size = new System.Drawing.Size(252, 21);
            this.m_dbNameTB.TabIndex = 1;
            // 
            // m_dbPortTB
            // 
            this.m_dbPortTB.Enabled = false;
            this.m_dbPortTB.Location = new System.Drawing.Point(62, 47);
            this.m_dbPortTB.Name = "m_dbPortTB";
            this.m_dbPortTB.Size = new System.Drawing.Size(252, 21);
            this.m_dbPortTB.TabIndex = 1;
            // 
            // m_dbIpTB
            // 
            this.m_dbIpTB.Location = new System.Drawing.Point(62, 20);
            this.m_dbIpTB.Name = "m_dbIpTB";
            this.m_dbIpTB.Size = new System.Drawing.Size(252, 21);
            this.m_dbIpTB.TabIndex = 1;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(15, 135);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(41, 12);
            this.label5.TabIndex = 0;
            this.label5.Text = "密码：";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(3, 107);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(53, 12);
            this.label4.TabIndex = 0;
            this.label4.Text = "用户名：";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(15, 79);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(41, 12);
            this.label3.TabIndex = 0;
            this.label3.Text = "库名：";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(15, 51);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(41, 12);
            this.label2.TabIndex = 0;
            this.label2.Text = "端口：";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(15, 23);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(41, 12);
            this.label1.TabIndex = 0;
            this.label1.Text = "地址：";
            // 
            // groupBox2
            // 
            this.groupBox2.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.groupBox2.Controls.Add(this.m_protopathdt);
            this.groupBox2.Controls.Add(this.m_liulanBT);
            this.groupBox2.Controls.Add(this.label6);
            this.groupBox2.Controls.Add(this.m_LangSelectCB);
            this.groupBox2.Controls.Add(this.label9);
            this.groupBox2.Controls.Add(this.m_prototb);
            this.groupBox2.Controls.Add(this.label10);
            this.groupBox2.Controls.Add(this.m_OutPathTB);
            this.groupBox2.Location = new System.Drawing.Point(12, 207);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(320, 130);
            this.groupBox2.TabIndex = 2;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "代码";
            // 
            // m_liulanBT
            // 
            this.m_liulanBT.Location = new System.Drawing.Point(277, 57);
            this.m_liulanBT.Name = "m_liulanBT";
            this.m_liulanBT.Size = new System.Drawing.Size(43, 23);
            this.m_liulanBT.TabIndex = 3;
            this.m_liulanBT.Text = "...";
            this.m_liulanBT.UseVisualStyleBackColor = true;
            this.m_liulanBT.Click += new System.EventHandler(this.m_liulanBT_Click);
            // 
            // m_LangSelectCB
            // 
            this.m_LangSelectCB.FormattingEnabled = true;
            this.m_LangSelectCB.Location = new System.Drawing.Point(62, 32);
            this.m_LangSelectCB.Name = "m_LangSelectCB";
            this.m_LangSelectCB.Size = new System.Drawing.Size(252, 20);
            this.m_LangSelectCB.TabIndex = 2;
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(15, 62);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(41, 12);
            this.label9.TabIndex = 0;
            this.label9.Text = "输出：";
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(15, 35);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(41, 12);
            this.label10.TabIndex = 0;
            this.label10.Text = "语言：";
            // 
            // m_OutPathTB
            // 
            this.m_OutPathTB.Location = new System.Drawing.Point(62, 59);
            this.m_OutPathTB.Name = "m_OutPathTB";
            this.m_OutPathTB.Size = new System.Drawing.Size(209, 21);
            this.m_OutPathTB.TabIndex = 1;
            // 
            // m_prototb
            // 
            this.m_prototb.Location = new System.Drawing.Point(62, 88);
            this.m_prototb.Name = "m_prototb";
            this.m_prototb.Size = new System.Drawing.Size(209, 21);
            this.m_prototb.TabIndex = 1;
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(15, 91);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(41, 12);
            this.label6.TabIndex = 0;
            this.label6.Text = "协议：";
            // 
            // m_protopathdt
            // 
            this.m_protopathdt.Location = new System.Drawing.Point(277, 86);
            this.m_protopathdt.Name = "m_protopathdt";
            this.m_protopathdt.Size = new System.Drawing.Size(43, 23);
            this.m_protopathdt.TabIndex = 3;
            this.m_protopathdt.Text = "...";
            this.m_protopathdt.UseVisualStyleBackColor = true;
            this.m_protopathdt.Click += new System.EventHandler(this.m_protopathdt_Click);
            // 
            // CodeGeneratorForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(344, 424);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.m_startBt);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            this.MaximizeBox = false;
            this.MaximumSize = new System.Drawing.Size(360, 460);
            this.MinimizeBox = false;
            this.MinimumSize = new System.Drawing.Size(360, 460);
            this.Name = "CodeGeneratorForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "数据库代码生成器";
            this.Load += new System.EventHandler(this.CodeGeneratorForm_Load);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button m_startBt;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.TextBox m_dbpwdTB;
        private System.Windows.Forms.TextBox m_dbUserTB;
        private System.Windows.Forms.TextBox m_dbNameTB;
        private System.Windows.Forms.TextBox m_dbPortTB;
        private System.Windows.Forms.TextBox m_dbIpTB;
        private System.Windows.Forms.TextBox m_OutPathTB;
        private System.Windows.Forms.ComboBox m_LangSelectCB;
        private System.Windows.Forms.Button m_liulanBT;
        private System.Windows.Forms.Button m_protopathdt;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.TextBox m_prototb;
    }
}

