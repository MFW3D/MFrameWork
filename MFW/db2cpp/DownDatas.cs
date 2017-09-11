using System;
using System.Collections.Generic;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MFWTools
{
    public struct DBField
    {
        public String name;
        public String type;
    }
    public static class DownDatas
    {
        private static List<String> tablenames = new List<string>();
        public static Dictionary<String, List<DBField>> tables = new Dictionary<string, List<DBField>>();
        public static void ClearData()
        {
            tablenames.Clear();
            tables.Clear();
        }
        public static bool download()
        {
            DataSet ds = MySqlHelper.GetDataSet(MySqlHelper.ConnectionStringManager, "show TABLES;", null);
            DataTable dt = ds.Tables.Count > 0 ? ds.Tables[0] : null;
            if (dt == null)
            {
                return false;
            }
            for (int i = 0; i < dt.Rows.Count; i++)
            {
                tablenames.Add(dt.Rows[i][0].ToString());
            }
            //查询所有的表结构
            for (int i = 0; i < tablenames.Count; i++)
            {
                ds = MySqlHelper.GetDataSet(MySqlHelper.ConnectionStringManager, "desc "+tablenames[i]+";", null);
                dt = ds.Tables.Count > 0 ? ds.Tables[0] : null;
                if (dt == null)
                {
                    return false;
                }
                List<DBField> fields = new List<DBField>();
                for(int j=0;j<dt.Rows.Count;j++)
                {
                    DBField field = new DBField();
                    field.name = dt.Rows[j][0].ToString();
                    field.type = dt.Rows[j][1].ToString().Split('(')[0];
                    fields.Add(field);
                }
                tables.Add(tablenames[i], fields);
            }

            return true;

        }

    }
}
