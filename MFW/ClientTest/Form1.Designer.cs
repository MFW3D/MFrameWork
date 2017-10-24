namespace ClientTest
{
    partial class Form1
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
            this.m_connectServer = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.m_data = new System.Windows.Forms.Label();
            this.m_login = new System.Windows.Forms.Button();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.m_user = new System.Windows.Forms.TextBox();
            this.m_passwd = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.m_managerIp = new System.Windows.Forms.Label();
            this.m_managerport = new System.Windows.Forms.Label();
            this.m_Managerkey = new System.Windows.Forms.Label();
            this.m_managerServer = new System.Windows.Forms.Button();
            this.m_managerLogion = new System.Windows.Forms.Button();
            this.label8 = new System.Windows.Forms.Label();
            this.m_uidlabal = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // m_connectServer
            // 
            this.m_connectServer.Location = new System.Drawing.Point(26, 77);
            this.m_connectServer.Name = "m_connectServer";
            this.m_connectServer.Size = new System.Drawing.Size(75, 23);
            this.m_connectServer.TabIndex = 0;
            this.m_connectServer.Text = "连接服务器";
            this.m_connectServer.UseVisualStyleBackColor = true;
            this.m_connectServer.Click += new System.EventHandler(this.button1_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(26, 42);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(41, 12);
            this.label1.TabIndex = 1;
            this.label1.Text = "状态：";
            // 
            // m_data
            // 
            this.m_data.AutoSize = true;
            this.m_data.Location = new System.Drawing.Point(73, 42);
            this.m_data.Name = "m_data";
            this.m_data.Size = new System.Drawing.Size(0, 12);
            this.m_data.TabIndex = 1;
            // 
            // m_login
            // 
            this.m_login.Location = new System.Drawing.Point(26, 162);
            this.m_login.Name = "m_login";
            this.m_login.Size = new System.Drawing.Size(99, 23);
            this.m_login.TabIndex = 0;
            this.m_login.Text = "发送登录消息";
            this.m_login.UseVisualStyleBackColor = true;
            this.m_login.Click += new System.EventHandler(this.m_login_Click);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(26, 109);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(41, 12);
            this.label2.TabIndex = 1;
            this.label2.Text = "用户：";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(26, 136);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(41, 12);
            this.label3.TabIndex = 1;
            this.label3.Text = "密码：";
            // 
            // m_user
            // 
            this.m_user.Location = new System.Drawing.Point(73, 106);
            this.m_user.Name = "m_user";
            this.m_user.Size = new System.Drawing.Size(172, 21);
            this.m_user.TabIndex = 2;
            // 
            // m_passwd
            // 
            this.m_passwd.Location = new System.Drawing.Point(73, 133);
            this.m_passwd.Name = "m_passwd";
            this.m_passwd.Size = new System.Drawing.Size(172, 21);
            this.m_passwd.TabIndex = 2;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(26, 207);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(77, 12);
            this.label4.TabIndex = 1;
            this.label4.Text = "管理服务器：";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(38, 233);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(29, 12);
            this.label5.TabIndex = 1;
            this.label5.Text = "ip：";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(26, 255);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(41, 12);
            this.label6.TabIndex = 1;
            this.label6.Text = "端口：";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(26, 279);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(41, 12);
            this.label7.TabIndex = 1;
            this.label7.Text = "令牌：";
            // 
            // m_managerIp
            // 
            this.m_managerIp.AutoSize = true;
            this.m_managerIp.Location = new System.Drawing.Point(84, 233);
            this.m_managerIp.Name = "m_managerIp";
            this.m_managerIp.Size = new System.Drawing.Size(0, 12);
            this.m_managerIp.TabIndex = 1;
            // 
            // m_managerport
            // 
            this.m_managerport.AutoSize = true;
            this.m_managerport.Location = new System.Drawing.Point(84, 255);
            this.m_managerport.Name = "m_managerport";
            this.m_managerport.Size = new System.Drawing.Size(0, 12);
            this.m_managerport.TabIndex = 1;
            // 
            // m_Managerkey
            // 
            this.m_Managerkey.AutoSize = true;
            this.m_Managerkey.Location = new System.Drawing.Point(84, 279);
            this.m_Managerkey.Name = "m_Managerkey";
            this.m_Managerkey.Size = new System.Drawing.Size(0, 12);
            this.m_Managerkey.TabIndex = 1;
            // 
            // m_managerServer
            // 
            this.m_managerServer.Location = new System.Drawing.Point(306, 12);
            this.m_managerServer.Name = "m_managerServer";
            this.m_managerServer.Size = new System.Drawing.Size(99, 23);
            this.m_managerServer.TabIndex = 0;
            this.m_managerServer.Text = "连接管理服务器";
            this.m_managerServer.UseVisualStyleBackColor = true;
            this.m_managerServer.Click += new System.EventHandler(this.m_managerServer_Click);
            // 
            // m_managerLogion
            // 
            this.m_managerLogion.Location = new System.Drawing.Point(306, 51);
            this.m_managerLogion.Name = "m_managerLogion";
            this.m_managerLogion.Size = new System.Drawing.Size(99, 23);
            this.m_managerLogion.TabIndex = 0;
            this.m_managerLogion.Text = "发送登录消息";
            this.m_managerLogion.UseVisualStyleBackColor = true;
            this.m_managerLogion.Click += new System.EventHandler(this.m_managerLogion_Click);
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(26, 301);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(29, 12);
            this.label8.TabIndex = 1;
            this.label8.Text = "UID:";
            // 
            // m_uidlabal
            // 
            this.m_uidlabal.AutoSize = true;
            this.m_uidlabal.Location = new System.Drawing.Point(84, 301);
            this.m_uidlabal.Name = "m_uidlabal";
            this.m_uidlabal.Size = new System.Drawing.Size(0, 12);
            this.m_uidlabal.TabIndex = 1;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(916, 365);
            this.Controls.Add(this.m_passwd);
            this.Controls.Add(this.m_user);
            this.Controls.Add(this.m_data);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.m_uidlabal);
            this.Controls.Add(this.m_Managerkey);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.m_managerport);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.m_managerIp);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.m_managerLogion);
            this.Controls.Add(this.m_managerServer);
            this.Controls.Add(this.m_login);
            this.Controls.Add(this.m_connectServer);
            this.Name = "Form1";
            this.Text = "Form1";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button m_connectServer;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label m_data;
        private System.Windows.Forms.Button m_login;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox m_user;
        private System.Windows.Forms.TextBox m_passwd;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label m_managerIp;
        private System.Windows.Forms.Label m_managerport;
        private System.Windows.Forms.Label m_Managerkey;
        private System.Windows.Forms.Button m_managerServer;
        private System.Windows.Forms.Button m_managerLogion;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label m_uidlabal;
    }
}

