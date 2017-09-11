using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;
using System.IO;


public class IniFile
{
    //文件INI名称 
    public string Path;

    /**/
    ////声明读写INI文件的API函数 
    [DllImport("kernel32")]

    private static extern long WritePrivateProfileString(string section, string key, string val, string filePath);
    [DllImport("kernel32")]

    private static extern int GetPrivateProfileString(string section, string key, string def, StringBuilder retVal, int size, string filePath);

    //类的构造函数，传递INI文件名 
    public IniFile(string inipath)
    {
        // 
        // TODO: Add constructor logic here 
        // 
        Path = inipath;
    }

    //写INI文件 
    public void IniWriteValue(string Section, string Key, string Value)
    {
        WritePrivateProfileString(Section, Key, Value, this.Path);

    }

    //读取INI文件指定 
    public string IniReadValue(string Section, string Key)
    {
        try
        {
            if (this.Path.Split('.')[this.Path.Split('.').Length - 1] != "ini")
            {
                return "";
            }
            StringBuilder temp = new StringBuilder(1000);
            int i = GetPrivateProfileString(Section, Key, "", temp, 1000, this.Path);
            return temp.ToString();
        }
        catch
        {
            return "";
        }
    }
    /**/
    /// <summary>
    /// 验证文件是否存在
    /// </summary>
    /// <returns>布尔值</returns>
    public bool ExistINIFile()
    {
        return File.Exists(this.Path);
    }

}
