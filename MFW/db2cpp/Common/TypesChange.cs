using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MFWTools.Common
{
    public static class TypesChange
    {
        public static String dbtocpp(String oldType)
        {
            String newType = "";
            switch (oldType)
            {
                case "bigint":
                    newType = "long long";
                    break;
                case "timestamp":
                case "year":
                case "tinyint":
                case "smallint":
                case "mediumint":
                    newType = "short";
                    break;
                case "varchar":
                case "tinytext":
                case "mediumtext":
                case "longtext":
                case "text":
                case "datetime":
                case "time":
                case "date":
                case "blob":
                case "char":
                    newType = "std::string";
                    break;
                case "decimal":
                    newType = "double";
                    break;
                default:
                    newType = oldType;
                    break;
            }
            return newType;
        }
        public static String dbtocs(String oldType)
        {
            String newType = "";
            switch (oldType)
            {
                case "bigint":
                    newType = "Int64";
                    break;
                case "timestamp":
                case "year":
                case "tinyint":
                case "smallint":
                case "mediumint":
                    newType = "char";
                    break;
                case "varchar":
                case "tinytext":
                case "mediumtext":
                case "longtext":
                case "text":
                case "datetime":
                case "time":
                case "date":
                case "blob":
                    newType = "string";
                    break;
                case "bit":
                    newType="bool";
                    break;

                default:
                    newType = oldType;
                    break;
            }
            return newType;
        }
        public static String dbtoProto(String oldType)
        {
            String newType = "";
            switch (oldType)
            {
                case "bigint":
                    newType = "uint64";
                    break;
                case "int":
                    newType = "uint32";
                    break;
                case "timestamp":
                case "year":
                case "tinyint":
                case "smallint":
                case "mediumint":
                    newType = "short";
                    break;
                case "varchar":
                case "tinytext":
                case "mediumtext":
                case "longtext":
                case "text":
                case "datetime":
                case "time":
                case "date":
                case "char":
                    newType = "string";
                    break;
                case "blob":
                    newType = "bytes";
                    break;
                default:
                    newType = oldType;
                    break;
            }
            return newType;

        }
        public static String dbtoProtohead(String oldType)
        {
            String newType = "";
            switch (oldType)
            {
                case "bigint":
                    newType = "ul";
                    break;
                case "int":
                    newType = "ui";
                    break;
                case "float":
                    newType = "f";
                    break;
                case "timestamp":
                case "year":
                case "tinyint":
                case "smallint":
                case "mediumint":
                    newType = "us";
                    break;
                case "varchar":
                case "tinytext":
                case "mediumtext":
                case "longtext":
                case "text":
                case "datetime":
                case "time":
                case "date":
                case "blob":

                    newType = "s";
                    break;
                default:
                    newType = oldType;
                    break;
            }
            return newType;

        }
    }
}
