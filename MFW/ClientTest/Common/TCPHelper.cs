using System;
using System.IO;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
/// <summary>
/// 读取tcp接收数据的缓冲结构
/// </summary>
public class NetData
{
    // socket     
    public Socket workSocket = null;
    // 接收数据缓冲大小
    public const int BufferSize = 102400000;
    // 缓冲区     
    public byte[] buffer = new byte[BufferSize];
    // 接收数据     
    public StringBuilder sb = new StringBuilder();
}
/// <summary>
/// tcp客户端的连接类
/// </summary>
public class TCPHelper
{
    #region 回调事件
    //连接成功事件
    public delegate void Connected();
    public event Connected OnConnected;
    //断开事件
    public delegate void DisConnected();
    public event DisConnected OnDisConnected;
    //数据接收事件
    public delegate void Received(Stream data);
    public event Received OnReceived;
    //发送成功事件
    public delegate void Sended();
    public event Sended OnSended;
    #endregion
    #region 参数
    private Socket mServer;
    //已设置的ip和端口
    string mIpstr = "";
    int mPort = 0;
    #endregion
    public void Connect(string ipstr, int port)
    {
        try
        {
            mIpstr = ipstr;
            mPort = port;
            IPAddress ipAddress = IPAddress.Parse(ipstr);
            IPEndPoint remoteEP = new IPEndPoint(ipAddress, port);
            mServer = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            mServer.BeginConnect(remoteEP, new AsyncCallback(ConnectCallback), mServer);
        }
        catch (Exception e)
        {
        }
    }
    public void StopClient()
    {
        if (mServer != null)
        {
            mServer.Close();
        }
    }
    private void Receive(Socket client)
    {
        try
        {
            NetData state = new NetData();
            state.workSocket = client;
            client.BeginReceive(state.buffer, 0, NetData.BufferSize, 0,
                new AsyncCallback(ReceiveCallback), state);
        }
        catch (Exception e)
        {
        }
    }
    public void Send(byte[] data)
    {
        try
        {
            mServer.BeginSend(data, 0, data.Length, 0, new AsyncCallback(SendCallback), mServer);
        }
        catch (Exception e)
        {
        }
    }
    private void ConnectCallback(IAsyncResult ar)
    {
        try
        {
            Socket client = (Socket)ar.AsyncState;
            client.EndConnect(ar);
            if (OnConnected != null)
                OnConnected();
            //开始监听数据
            Receive(mServer);
        }
        catch (Exception e)
        {
        }
    }
    private void ReceiveCallback(IAsyncResult ar)
    {
        try
        {
            NetData state = (NetData)ar.AsyncState;
            Socket client = state.workSocket;
            int bytesRead = client.EndReceive(ar);
            if (bytesRead > 0)
            {
                using (Stream ms = new MemoryStream())
                {
                    ms.Position = 0;
                    ms.Write(state.buffer, 0, bytesRead);
                    ms.Position = 0;
                    if (OnReceived != null)
                        OnReceived(ms);
                }
            }
        }
        catch (Exception e)
        {

        }
    }
    private void SendCallback(IAsyncResult ar)
    {
        try
        {
            Socket client = (Socket)ar.AsyncState;
            int bytesSent = client.EndSend(ar);
            if (OnSended != null)
                OnSended();
        }
        catch (Exception e)
        {
        }
    }
}
