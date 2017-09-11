using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Text;
using System.Data;
using System.Collections;
using MySql.Data.MySqlClient;
using MySql.Data.Types;
using System.Configuration;
using System.IO;



public abstract class MySqlHelper
{
    public static string ConnectionStringManager
    {
        get { return connectionStringManager; }
    }
    public static string connectionStringManager ="";
    private static Hashtable parmCache = Hashtable.Synchronized(new Hashtable());

    /// <summary>
    /// Execute a SqlCommand command that does not return value, by appointed and specified connectionstring 
    /// The parameter list using parameters that in array forms
    /// </summary>
    /// <remarks>
    /// Usage example: 
    /// int result = ExecuteNonQuery(connString, CommandType.StoredProcedure,
    /// "PublishOrders", new MySqlParameter("@prodid", 24));
    /// </remarks>
    /// <param name="connectionString">a valid database connectionstring</param>
    /// <param name="cmdType">MySqlCommand command type (stored procedures, T-SQL statement, and so on.) </param>
    /// <param name="cmdText">stored procedure name or T-SQL statement</param>
    /// <param name="commandParameters">MySqlCommand to provide an array of parameters used in the list</param>
    /// <returns>Returns a value that means number of rows affected/returns>
    public static int ExecuteNonQuery(string connectionString, CommandType cmdType, string cmdText, params MySqlParameter[] commandParameters)
    {
        MySqlCommand cmd = new MySqlCommand();

        using (MySqlConnection conn = new MySqlConnection(connectionString))
        {
            PrepareCommand(cmd, conn, null, cmdType, cmdText, commandParameters);
            int val = cmd.ExecuteNonQuery();
            cmd.Parameters.Clear();
            return val;
        }
    }

    /// <summary>
    /// Execute a SqlCommand command that does not return value, by appointed and specified connectionstring 
    /// The parameter list using parameters that in array forms
    /// </summary>
    /// <remarks>
    /// Usage example: 
    /// int result = ExecuteNonQuery(connString, CommandType.StoredProcedure,
    /// "PublishOrders", new MySqlParameter("@prodid", 24));
    /// </remarks>
    /// <param name="cmdType">MySqlCommand command type (stored procedures, T-SQL statement, and so on.) </param>
    /// <param name="connectionString">a valid database connectionstring</param>
    /// <param name="cmdText">stored procedure name or T-SQL statement</param>
    /// <param name="commandParameters">MySqlCommand to provide an array of parameters used in the list</param>
    /// <returns>Returns true or false </returns>
    public static bool ExecuteNonQuery(CommandType cmdType, string connectionString, string cmdText, params MySqlParameter[] commandParameters)
    {
        MySqlCommand cmd = new MySqlCommand();

        using (MySqlConnection conn = new MySqlConnection(connectionString))
        {
            PrepareCommand(cmd, conn, null, cmdType, cmdText, commandParameters);
            try
            {
                int val = cmd.ExecuteNonQuery();
                return true;
            }
            catch
            {
                return false;
            }
            finally
            {
                cmd.Parameters.Clear();
            }
        }
    }
    /// <summary>
    /// Execute a SqlCommand command that does not return value, by appointed and specified connectionstring 
    /// Array of form parameters using the parameter list 
    /// </summary>
    /// <param name="conn">connection</param>
    /// <param name="cmdType">MySqlCommand command type (stored procedures, T-SQL statement, and so on.)</param>
    /// <param name="cmdText">stored procedure name or T-SQL statement</param>
    /// <param name="commandParameters">MySqlCommand to provide an array of parameters used in the list</param>
    /// <returns>Returns a value that means number of rows affected</returns>
    public static int ExecuteNonQuery(MySqlConnection conn, CommandType cmdType, string cmdText, params MySqlParameter[] commandParameters)
    {
        MySqlCommand cmd = new MySqlCommand();
        PrepareCommand(cmd, conn, null, cmdType, cmdText, commandParameters);
        int val = cmd.ExecuteNonQuery();
        cmd.Parameters.Clear();
        return val;
    }

    /// <summary>
    /// Execute a SqlCommand command that does not return value, by appointed and specified connectionstring 
    /// Array of form parameters using the parameter list 
    /// </summary>
    /// <param name="conn">sql Connection that has transaction</param>
    /// <param name="cmdType">SqlCommand command type (stored procedures, T-SQL statement, and so on.)</param>
    /// <param name="cmdText">stored procedure name or T-SQL statement</param>
    /// <param name="commandParameters">MySqlCommand to provide an array of parameters used in the list</param>
    /// <returns>Returns a value that means number of rows affected </returns>
    public static int ExecuteNonQuery(MySqlTransaction trans, CommandType cmdType, string cmdText, params MySqlParameter[] commandParameters)
    {
        MySqlCommand cmd = new MySqlCommand();
        PrepareCommand(cmd, trans.Connection, trans, cmdType, cmdText, commandParameters);
        int val = cmd.ExecuteNonQuery();
        cmd.Parameters.Clear();
        return val;
    }

    /// <summary>
    /// Call method of sqldatareader to read data
    /// </summary>
    /// <param name="connectionString">connectionstring</param>
    /// <param name="cmdType">command type, such as using stored procedures: CommandType.StoredProcedure</param>
    /// <param name="cmdText">stored procedure name or T-SQL statement</param>
    /// <param name="commandParameters">parameters</param>
    /// <returns>SqlDataReader type of data collection</returns>
    public static MySqlDataReader ExecuteReader(string connectionString, CommandType cmdType, string cmdText, params MySqlParameter[] commandParameters)
    {
        MySqlCommand cmd = new MySqlCommand();
        MySqlConnection conn = new MySqlConnection(connectionString);

        // we use a try/catch here because if the method throws an exception we want to 
        // close the connection throw code, because no datareader will exist, hence the 
        // commandBehaviour.CloseConnection will not work
        try
        {
            PrepareCommand(cmd, conn, null, cmdType, cmdText, commandParameters);
            MySqlDataReader rdr = cmd.ExecuteReader(CommandBehavior.CloseConnection);
            cmd.Parameters.Clear();
            return rdr;
        }
        catch
        {
            conn.Close();
            throw;
        }
    }

    /// <summary>
    /// use the ExectueScalar to read a single result
    /// </summary>
    /// <param name="connectionString">connectionstring</param>
    /// <param name="cmdType">command type, such as using stored procedures: CommandType.StoredProcedure</param>
    /// <param name="cmdText">stored procedure name or T-SQL statement</param>
    /// <param name="commandParameters">parameters</param>
    /// <returns>a value in object type</returns>
    public static object ExecuteScalar(string connectionString, CommandType cmdType, string cmdText, params MySqlParameter[] commandParameters)
    {
        MySqlCommand cmd = new MySqlCommand();

        using (MySqlConnection connection = new MySqlConnection(connectionString))
        {
            PrepareCommand(cmd, connection, null, cmdType, cmdText, commandParameters);
            object val = cmd.ExecuteScalar();
            cmd.Parameters.Clear();
            return val;
        }
    }

    public static DataSet GetDataSet(string connectionString, string cmdText, params MySqlParameter[] commandParameters)
    {
        DataSet retSet = new DataSet();
        using (MySqlDataAdapter msda = new MySqlDataAdapter(cmdText, connectionString))
        {
            msda.Fill(retSet);
        }
        return retSet;
    }

    /// <summary>
    /// cache the parameters in the HashTable
    /// </summary>
    /// <param name="cacheKey">hashtable key name</param>
    /// <param name="commandParameters">the parameters that need to cached</param>
    public static void CacheParameters(string cacheKey, params MySqlParameter[] commandParameters)
    {
        parmCache[cacheKey] = commandParameters;
    }

    /// <summary>
    /// get parameters in hashtable by cacheKey
    /// </summary>
    /// <param name="cacheKey">hashtable key name</param>
    /// <returns>the parameters</returns>
    public static MySqlParameter[] GetCachedParameters(string cacheKey)
    {
        MySqlParameter[] cachedParms = (MySqlParameter[])parmCache[cacheKey];

        if (cachedParms == null)
            return null;

        MySqlParameter[] clonedParms = new MySqlParameter[cachedParms.Length];

        for (int i = 0, j = cachedParms.Length; i < j; i++)
            clonedParms[i] = (MySqlParameter)((ICloneable)cachedParms[i]).Clone();

        return clonedParms;
    }

    /// <summary>
    ///Prepare parameters for the implementation of the command
    /// </summary>
    /// <param name="cmd">mySqlCommand command</param>
    /// <param name="conn">database connection that is existing</param>
    /// <param name="trans">database transaction processing </param>
    /// <param name="cmdType">SqlCommand command type (stored procedures, T-SQL statement, and so on.) </param>
    /// <param name="cmdText">Command text, T-SQL statements such as Select * from Products</param>
    /// <param name="cmdParms">return the command that has parameters</param>
    private static void PrepareCommand(MySqlCommand cmd, MySqlConnection conn, MySqlTransaction trans, CommandType cmdType, string cmdText, MySqlParameter[] cmdParms)
    {
        if (conn.State != ConnectionState.Open)
            conn.Open();

        cmd.Connection = conn;
        cmd.CommandText = cmdText;

        if (trans != null)
            cmd.Transaction = trans;

        cmd.CommandType = cmdType;

        if (cmdParms != null)
            foreach (MySqlParameter parm in cmdParms)
                cmd.Parameters.Add(parm);
    }
    #region parameters
    /// <summary>
    /// Set parameters
    /// </summary>
    /// <param name="ParamName">parameter name</param>
    /// <param name="DbType">data type</param>
    /// <param name="Size">type size</param>
    /// <param name="Direction">input or output</param>
    /// <param name="Value">set the value</param>
    /// <returns>Return parameters that has been assigned</returns>
    public static MySqlParameter CreateParam(string ParamName, MySqlDbType DbType, Int32 Size, ParameterDirection Direction, object Value)
    {
        MySqlParameter param;


        if (Size > 0)
        {
            param = new MySqlParameter(ParamName, DbType, Size);
        }
        else
        {

            param = new MySqlParameter(ParamName, DbType);
        }


        param.Direction = Direction;
        if (!(Direction == ParameterDirection.Output && Value == null))
        {
            param.Value = Value;
        }


        return param;
    }

    /// <summary>
    /// set Input parameters
    /// </summary>
    /// <param name="ParamName">parameter names, such as:@ id </param>
    /// <param name="DbType">parameter types, such as: MySqlDbType.Int</param>
    /// <param name="Size">size parameters, such as: the length of character type for the 100</param>
    /// <param name="Value">parameter value to be assigned</param>
    /// <returns>Parameters</returns>
    public static MySqlParameter CreateInParam(string ParamName, MySqlDbType DbType, int Size, object Value)
    {
        return CreateParam(ParamName, DbType, Size, ParameterDirection.Input, Value);
    }

    /// <summary>
    /// Output parameters 
    /// </summary>
    /// <param name="ParamName">parameter names, such as:@ id</param>
    /// <param name="DbType">parameter types, such as: MySqlDbType.Int</param>
    /// <param name="Size">size parameters, such as: the length of character type for the 100</param>
    /// <param name="Value">parameter value to be assigned</param>
    /// <returns>Parameters</returns>
    public static MySqlParameter CreateOutParam(string ParamName, MySqlDbType DbType, int Size)
    {
        return CreateParam(ParamName, DbType, Size, ParameterDirection.Output, null);
    }

    /// <summary>
    /// Set return parameter value 
    /// </summary>
    /// <param name="ParamName">parameter names, such as:@ id</param>
    /// <param name="DbType">parameter types, such as: MySqlDbType.Int</param>
    /// <param name="Size">size parameters, such as: the length of character type for the 100</param>
    /// <param name="Value">parameter value to be assigned<</param>
    /// <returns>Parameters</returns>
    public static MySqlParameter CreateReturnParam(string ParamName, MySqlDbType DbType, int Size)
    {
        return CreateParam(ParamName, DbType, Size, ParameterDirection.ReturnValue, null);
    }

    /// <summary>
    /// Generate paging storedProcedure parameters
    /// </summary>
    /// <param name="CurrentIndex">CurrentPageIndex</param>
    /// <param name="PageSize">pageSize</param>
    /// <param name="WhereSql">query Condition</param>
    /// <param name="TableName">tableName</param>
    /// <param name="Columns">columns to query</param>
    /// <param name="Sort">sort</param>
    /// <returns>MySqlParameter collection</returns>
    public static MySqlParameter[] GetPageParm(int CurrentIndex, int PageSize, string WhereSql, string TableName, string Columns, Hashtable Sort)
    {
        MySqlParameter[] parm = { 
                                   MySqlHelper.CreateInParam("@CurrentIndex",  MySqlDbType.Int32,      4,      CurrentIndex    ),
                                   MySqlHelper.CreateInParam("@PageSize",      MySqlDbType.Int32,      4,      PageSize        ),
                                   MySqlHelper.CreateInParam("@WhereSql",      MySqlDbType.VarChar,  2500,    WhereSql        ),
                                   MySqlHelper.CreateInParam("@TableName",     MySqlDbType.VarChar,  20,     TableName       ),
                                   MySqlHelper.CreateInParam("@Column",        MySqlDbType.VarChar,  2500,    Columns         ),
                                   MySqlHelper.CreateInParam("@Sort",          MySqlDbType.VarChar,  50,     GetSort(Sort)   ),
                                   MySqlHelper.CreateOutParam("@RecordCount",  MySqlDbType.Int32,      4                       )
                                   };
        return parm;
    }
    /// <summary>
    /// Statistics data that in table
    /// </summary>
    /// <param name="TableName">table name</param>
    /// <param name="Columns">Statistics column</param>
    /// <param name="WhereSql">conditions</param>
    /// <returns>Set of parameters</returns>
    public static MySqlParameter[] GetCountParm(string TableName, string Columns, string WhereSql)
    {
        MySqlParameter[] parm = { 
                                   MySqlHelper.CreateInParam("@TableName",     MySqlDbType.VarChar,  20,     TableName       ),
                                   MySqlHelper.CreateInParam("@CountColumn",  MySqlDbType.VarChar,  20,     Columns         ),
                                   MySqlHelper.CreateInParam("@WhereSql",      MySqlDbType.VarChar,  250,    WhereSql        ),
                                   MySqlHelper.CreateOutParam("@RecordCount",  MySqlDbType.Int32,      4                       )
                                   };
        return parm;
    }
    /// <summary>
    /// Get the sql that is Sorted 
    /// </summary>
    /// <param name="sort"> sort column and values</param>
    /// <returns>SQL sort string</returns>
    private static string GetSort(Hashtable sort)
    {
        string str = "";
        int i = 0;
        if (sort != null && sort.Count > 0)
        {
            foreach (DictionaryEntry de in sort)
            {
                i++;
                str += de.Key + " " + de.Value;
                if (i != sort.Count)
                {
                    str += ",";
                }
            }
        }
        return str;
    }

    /// <summary>
    /// execute a trascation include one or more sql sentence(author:donne yin)
    /// </summary>
    /// <param name="connectionString"></param>
    /// <param name="cmdType"></param>
    /// <param name="cmdTexts"></param>
    /// <param name="commandParameters"></param>
    /// <returns>execute trascation result(success: true | fail: false)</returns>
    public static bool ExecuteTransaction(string connectionString, CommandType cmdType, string[] cmdTexts, params MySqlParameter[][] commandParameters)
    {
        MySqlConnection myConnection = new MySqlConnection(connectionString);       //get the connection object
        myConnection.Open();                                                        //open the connection
        MySqlTransaction myTrans = myConnection.BeginTransaction();                 //begin a trascation
        MySqlCommand cmd = new MySqlCommand();
        cmd.Connection = myConnection;
        cmd.Transaction = myTrans;

        try
        {
            for (int i = 0; i < cmdTexts.Length; i++)
            {
                PrepareCommand(cmd, myConnection, null, cmdType, cmdTexts[i], commandParameters[i]);
                cmd.ExecuteNonQuery();
                cmd.Parameters.Clear();
            }
            myTrans.Commit();
        }
        catch
        {
            myTrans.Rollback();
            return false;
        }
        finally
        {
            myConnection.Close();
        }
        return true;
    }
    #endregion
}

