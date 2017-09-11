using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace MFWTools
{
    public partial class CodeGeneratorForm : Form
    {
        public CodeGeneratorForm()
        {
            InitializeComponent();

        }

        //读取配置
        private void m_startBt_Click(object sender, EventArgs e)
        {

            try
            {
                GlobalData.ServerIni.IniWriteValue("db", "ip", m_dbIpTB.Text);
                GlobalData.ServerIni.IniWriteValue("db", "port", m_dbPortTB.Text);
                GlobalData.ServerIni.IniWriteValue("db", "user", m_dbNameTB.Text);
                GlobalData.ServerIni.IniWriteValue("db", "name", m_dbUserTB.Text);
                GlobalData.ServerIni.IniWriteValue("db", "pwd", m_dbpwdTB.Text);
                GlobalData.ServerIni.IniWriteValue("db", "lang", m_LangSelectCB.Text);
                GlobalData.ServerIni.IniWriteValue("db", "path", m_OutPathTB.Text);
                GlobalData.ServerIni.IniWriteValue("proto", "path", m_prototb.Text);
                GlobalData.SavePath = m_OutPathTB.Text;
                GlobalData.ProtoPath = m_prototb.Text;
            }
            catch
            {

            }


            try
            {
                MySqlHelper.connectionStringManager = "server=" + m_dbIpTB.Text + ";database=" + m_dbNameTB.Text + ";uid=" + m_dbUserTB.Text + ";pwd=" + m_dbpwdTB.Text;

                //初始化所有的数据库结构
                DownDatas.ClearData();
                DownDatas.download();
                //生成数据库数据结构
                Gencpp.GenStructs();
                Gencpp.GenDBDatas();
                Gencpp.GenIds();
                Gencpp.GenDBHandler();
                Gencpp.GenDBReader();
                Gencpp.GenRedisHandler();
                Gencpp.GenRedisReader();

                //生成协议相关
                Gencpp.GenDBGameProto();
                Gencpp.GenDBStructProto();

                //生成特定的消息处理类
                // Gencpp.GenDBGameTask();

                MessageBox.Show("OK");
            }
            catch
            {
                MessageBox.Show("生成代码过程中发生错误");
            }
        }

        private void m_liulanBT_Click(object sender, EventArgs e)
        {
            string path = string.Empty;
            System.Windows.Forms.FolderBrowserDialog fbd = new System.Windows.Forms.FolderBrowserDialog();
            if (fbd.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                path = fbd.SelectedPath;
                m_OutPathTB.Text = path;
                GlobalData.SavePath = path;
            }
        }

        private void CodeGeneratorForm_Load(object sender, EventArgs e)
        {
            m_dbIpTB.Text = GlobalData.ServerIni.IniReadValue("db", "ip");
            m_dbPortTB.Text = GlobalData.ServerIni.IniReadValue("db", "port");
            m_dbNameTB.Text = GlobalData.ServerIni.IniReadValue("db", "user");
            m_dbUserTB.Text = GlobalData.ServerIni.IniReadValue("db", "name");
            m_dbpwdTB.Text = GlobalData.ServerIni.IniReadValue("db", "pwd");
            m_LangSelectCB.Text = GlobalData.ServerIni.IniReadValue("db", "lang");
            m_OutPathTB.Text = GlobalData.ServerIni.IniReadValue("db", "path");
            m_prototb.Text = GlobalData.ServerIni.IniReadValue("proto", "path");
        }

        private void m_protopathdt_Click(object sender, EventArgs e)
        {
            string path = string.Empty;
            System.Windows.Forms.FolderBrowserDialog fbd = new System.Windows.Forms.FolderBrowserDialog();
            if (fbd.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                path = fbd.SelectedPath;
                m_prototb.Text = path;
                GlobalData.ProtoPath = path;
            }
        }
    }
}
