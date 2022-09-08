#include "dbUsers.h"

void DBUsers::insertUserInTable(const std::string& login, const std::string& name, const std::string& passwd)
{
    //form a query line
    std::string query = "INSERT INTO users_table (login, name, pass) values (\'";
    query += login;
    query += "\', \'";
    query += name;
    query += "\', \'";
    query += passwd;
    query += "\')";

    //check the final query line
    std::cout << "Query: \"" << query << "\"\n";

    //do a query
    mysql_query(mysql, query.c_str());
}
void DBUsers::findUserLoginInTable(const std::string& login)
{
    std::string query = "SELECT id FROM users_table WHERE login = \'";
    query += login;
    query += "\'";

    //check the final query line
    std::cout << "Query: \"" << query << "\"\n";

    //do a query
    mysql_query(mysql, query.c_str());
}
void DBUsers::findUserNameInTable(const std::string& name)
{
    std::string query = "SELECT id FROM users_table WHERE name = \'";
    query += name;
    query += "\'";

    //check the final query line
    std::cout << "Query: \"" << query << "\"\n";

    //do a query
    mysql_query(mysql, query.c_str());
}

void DBUsers::getUserNameFromTable(const std::string& login)
{
    std::string query = "SELECT name FROM users_table WHERE login = \'";
    query += login;
    query += "\'";

    //check the final query line
    std::cout << "Query: \"" << query << "\"\n";

    //do a query
    mysql_query(mysql, query.c_str());
}

void DBUsers::findUserPassInTable(const std::string& login, const std::string& passwd)
{
    std::string query = "SELECT pass FROM users_table WHERE login = \'";
    query += login;
    query += "\'";

    //check the final query line
    std::cout << "Query: \"" << query << "\"\n";

    //do a query
    mysql_query(mysql, query.c_str());
}

void DBUsers::changePass(const std::string& login, const std::string& new_passwd)
{
    std::string query = "UPDATE users_table SET pass = \'";
    query += new_passwd;
    query += "\' ";
    query += "WHERE login = \'";
    query += login;
    query += "\'";

    //check the final query line
    std::cout << "Query: \"" << query << "\"\n";

    //do a query
    mysql_query(mysql, query.c_str());

}

void DBUsers::changeName(const std::string& login, const std::string& new_name)
{
    std::string query = "UPDATE users_table SET name = \'";
    query += new_name;
    query += "\' ";
    query += "WHERE login = \'";
    query += login;
    query += "\'";

    //check the final query line
    std::cout << "Query: \"" << query << "\"\n";

    //do a query
    mysql_query(mysql, query.c_str());
}

void DBUsers::listUsersName()
{
    std::string query = "SELECT name FROM users_table";

    //do a query
    mysql_query(mysql, query.c_str());
}

//process the final result of the query
bool DBUsers::findUserByLogin(const std::string& login)
{
    //do query with the function
    findUserLoginInTable(login);
    res = mysql_store_result(mysql);
    //if result of a query has not been constructed
    if(res == NULL)
    {
        std::cout << "No infromation got on \"Find user by login\" query.\n";
        return false;
    }

    //validate constructed result
    row = mysql_fetch_row(res);
    if(row == NULL)
    {
        std::cout << "There is no such user.\n";
        return false;
    }
    std::cout << "Result of \"FindUserByLogin\" is \'" << row[0] << "\'\n";

    return true;
}

//process the final result of the query
bool DBUsers::fingUserByName(const std::string& name)
{
    //do query with the function
    findUserNameInTable(name);
    res = mysql_store_result(mysql);
    //if result of a query has not been constructed
    if(res == NULL)
    {
        std::cout << "No infromation got on \"Find user by name\" query.\n";
        return false;
    }

    //validate constructed result
    row = mysql_fetch_row(res);
    if(row == NULL)
    {
        std::cout << "There is no such user.\n";
        return false;
    }
    std::cout << "Result of \"FindUserByName\" is \'" << row[0] << "\'\n";

    return true;
}

//process the final result of the query
bool DBUsers::checkPass(const std::string& login, const std::string& passwd)
{
    //do query with the function
    findUserPassInTable(login, passwd);
    res = mysql_store_result(mysql);
    //if result of a query has not been constructed
    if(res == NULL)
    {
        std::cout << "No infromation got on \"Find user's pass\" query.\n";
        return false;
    }

    //validate constructed result
    row = mysql_fetch_row(res);
    if(row == NULL)
    {
        std::cout << "There is no such user.\n";
        return false;
    }
    std::cout << "Result of \"FindUser's Pass\" is \'" << row[0] << "\'\n";
    std::string pass(row[0]);
    if(pass.compare(passwd)==0)
    {
        std::cout << "The passwords are identical.\n";
        return true;
    }
    else
    {
        std::cout << "The passwords are not identical.\n";
        return false;
    }    
}

//process the final result of the query
std::string DBUsers::packUserListInBuffer()
{
    //do query with the function
    listUsersName();
    res = mysql_store_result(mysql);
    //if result of a query has not been constructed
    if(res == NULL)
    {
        std::cout << "No infromation got on \"Find user's pass\" query.\n";
        return "\0";
    }
    std::string list;
    //validate constructed result
    while(row = mysql_fetch_row(res))
    { 
        //print the list
        if(row == NULL)
        {
            std::cout << "There is no user.\n";
            return "\0";
        }
        for(int i = 0; i < mysql_num_fields(res); i++)
        {
            //write result in string
            std::string output(row[i]);
            list += output;
            list += "\n";
            //server->writeBuffer(start, output);
            //std::cout << row[i] << " ";
        }
        
    } 
    list += "#";
    
    return list; 
}

std::string  DBUsers::packUserNameInBuffer(const std::string& login)
{
    //do query with the function
    getUserNameFromTable(login);
    res = mysql_store_result(mysql);
    //if result of a query has not been constructed
    if(res == NULL)
    {
        std::cout << "No infromation got on \"get user's name\" query.\n";
        return "\0";
    }
    //validate constructed result
    row = mysql_fetch_row(res);
    
    //print the list
    if(row == NULL)
    {
        std::cout << "There is no user.\n"; 
        return "\0";          
    }
        
    //write result in buffer
    std::string output(row[0]);
    std::cout << "User's name is " << row[0] << "\n";
    //server->writeBuffer(start, output);
    return  output;     
}