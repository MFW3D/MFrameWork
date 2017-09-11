using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MFWTools.Common
{
    public static class OutPut
    {
        public static void Out(String filepath,String data)
        {
            System.IO.StreamWriter sw = new System.IO.StreamWriter(filepath);
            sw.Write(data);
            sw.Close();
        }
    }
}
