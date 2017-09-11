using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace MFWTools
{
    class GlobalData
    {
        public static string SavePath = Application.StartupPath;
        public static string ProtoPath = Application.StartupPath;
        public static IniFile ServerIni = new IniFile(Application.StartupPath+"/appini.ini");
    }
}
