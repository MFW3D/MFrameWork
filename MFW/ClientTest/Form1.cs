//using PCommon_Base;
using Google.Protobuf;
using PCommonBase;
using PLoginClient;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Net;
using System.Text;
using System.Windows.Forms;

namespace ClientTest
{
    public partial class Form1 : Form
    {
        //TCPClient tcpClient ;
        TCPHelper net = new TCPHelper();
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            //HttpHelper httpHelper = new HttpHelper();
            //HttpItem item = new HttpItem();
            //item.Method = "POST";
            //item.URL = "http://127.0.0.1:7777/dasdasd";
            ////item.URL = "http://www.sufeinet.com/";
            //item.Postdata = "sdadasd";
            //HttpResult result= httpHelper.GetHtml(item);
            //label1.Text = result.Html;
            //tcpClient = new TCPClient();
            //tcpClient.TCPserverIP = "127.0.0.1";
            //tcpClient.TCPserverPort = 7777;
            //tcpClient.SocketConnect();
            net.Connect("127.0.0.1", 8888);
            net.OnConnected += Net_OnConnected;
            net.OnReceived += Net_OnReceived;
        }

        private void Net_OnReceived(System.IO.Stream data)
        {

            int headl =data.ReadByte();
            byte[] head = new byte[headl];
            data.Read(head,0, headl);
            NetHead netHead = NetHead.Parser.ParseFrom(head);
            byte[] dataArea = new byte[netHead.DataLength];
            data.Read(dataArea, 0, netHead.DataLength);

            LC_Login lc_login = LC_Login.Parser.ParseFrom(dataArea);
            this.BeginInvoke(new LoginOk((LC_Login lgonInfo) => {
                m_data.Text = "登录成功";
                m_managerIp.Text = lgonInfo.ManagerIp;
                m_managerport.Text = lgonInfo.ManagerPort.ToString();
                m_Managerkey.Text = lgonInfo.Key;
            }
            ), lc_login);

        }
        delegate void InV(string data);
        delegate void LoginOk(LC_Login data);
        private void Net_OnConnected()
        {
            string data = "connected";
            this.BeginInvoke(new InV((string dd) => m_data.Text = dd), data);
        }

        private void m_login_Click(object sender, EventArgs e)
        {
            NetHead netHead = new NetHead();
            netHead.Cmd = (int)ELC_CMD.Login;
            netHead.Count = 1;
            netHead.Index = 1;
            CL_Login login = new CL_Login();
            login.Acc = m_user.Text;
            login.Pwd = m_passwd.Text;
            byte[] bytes = login.ToByteArray();
            netHead.DataLength = bytes.Length;
            byte[] headByts = netHead.ToByteArray();
            using (var memoryStream = new MemoryStream())
            {
                int headleng = headByts.Length;
                char headChar = (char)headleng;
                memoryStream.WriteByte((byte)headChar);
                memoryStream.Write(headByts, 0, headByts.Length);
                memoryStream.Write(bytes, 0, bytes.Length);
                net.Send(memoryStream.ToArray());
            }
        }
    }
}
