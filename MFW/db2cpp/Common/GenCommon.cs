using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MFWTools.Common
{
    public static class GenCommon
    {
        public  static String Defualtauthor = "毛自豪";
        public static StringBuilder GenHeader(StringBuilder sb, string filename, string vesion, string description)
        {
//            sb.Append(@"/************************************************************
// * FileName: " + filename + @"
// * Author: " + Defualtauthor + @"
// * Version : " + vesion + @"
// * Date: " + DateTime.Now.ToString("yyyy年MM月dd日 HH:mm:ss") + @"
// * Description: 生成物：" + description + @"
// *
// ***********************************************************/
//");
            return sb;

        }

    }
}
