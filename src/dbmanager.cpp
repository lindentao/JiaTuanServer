﻿/*****************************************
> File Name : dbmanager.cpp
> Description : dbmanager.cpp  file
> Author : linden
> Date : 2015-09-14
*******************************************/

#include "dbmanager.h"

CDBManager::CDBManager()  
{  
    connection = mysql_init(NULL); // 初始化数据库连接变量  
    if(connection == NULL)  
    {  
        cout << "Error:" << mysql_error(connection);  
        exit(1);
    }  
}  
  
CDBManager::~CDBManager()  
{  
    if(connection != NULL)  // 关闭数据库连接  
    {  
        mysql_close(connection);  
    }  
}  
  
bool CDBManager::initDB(string host, string user, string pwd, string db_name)  
{  
    // 函数mysql_real_connect建立一个数据库连接  
    // 成功返回MYSQL*连接句柄，失败返回NULL  
    connection = mysql_real_connect(connection, host.c_str(),  
            user.c_str(), pwd.c_str(), db_name.c_str(), 0, NULL, 0);  
    if(connection == NULL)  
    {  
        cout << "Error:" << mysql_error(connection);  
        exit(1);  
    }  
    return true;  
}  
  
bool CDBManager::executeSQL(string sql)  
{  
    // mysql_query()执行成功返回0，失败返回非0值。与PHP中不一样  
    if(mysql_query(connection, sql.c_str()))
    {  
        cout << "Query Error:" << mysql_error(connection);  
        exit(1);  
    }  
    else  
    {  
        result = mysql_use_result(connection); // 获取结果集  
        // mysql_field_count()返回connection查询的列数  
        for(int i=0; i < mysql_field_count(connection); ++i)  
        {  
            // 获取下一行  
            row = mysql_fetch_row(result);  
            if(row <= 0)  
            {  
                break;  
            }  
            // mysql_num_fields()返回结果集中的字段数  
            for(int j=0; j < mysql_num_fields(result); ++j)  
            {  
                cout << row[j] << " ";  
            }  
            cout << endl;  
        }  
        // 释放结果集的内存  
        mysql_free_result(result);  
    }  
    return true;  
}

/************************************************
Function : user_register_func
Description : 用户注册
Input : string user_login
		string user_pass
Output :
Return : true/false
Others :
*************************************************/
bool CDBManager::user_register_func(string user_login, string user_pass)
{	
	//string user_register_sql = "insert into jt_users (user_login,user_pass,user_registered) values ("testname","testpwd",now());";
	string sql = "insert into jt_users (user_login,user_pass,user_registered) values (" + user_login + "," + user_pass + ",now())";
    // mysql_query()执行成功返回0，失败返回非0值
	if (mysql_query(connection, sql.c_str()))
    {  
        cout << "Query Error:" << mysql_error(connection);
        return false;  
    }
    return true;
}

/************************************************
Function : user_login_func
Description : 用户登陆
Input : string user_login
	string user_pass
Output :
Return : true/false
Others :
*************************************************/
bool CDBManager::user_login_func(string user_login, string user_pass)
{
	//string user_register_sql = "select * from jt_users where user_login = "13814381438" and user_pass = "123456";";
	string sql = "select * from jt_users where user_login = " + user_login + " and user_pass = " + user_pass;
	// mysql_query()执行成功返回0，失败返回非0值
	if (mysql_query(connection, sql.c_str()))
	{
		fprintf(stderr, "Sql: %s\n", sql.c_str());
		cout << "Query Error:" << mysql_error(connection);
		return false;
	}
	else
	{
		// mysql_field_count()返回connection查询的列数  
		if (!mysql_field_count(connection))
		{
			// query does not return data
			return false;
		}
	}
	return true;
}
