#include "dbMsgAll.h"

void DBMessAll::addMessage(const std::string& login, const std::string& text)
{
    //form a query line
    std::string query = "INSERT INTO messages_to_all_table (sender, text) values (\'";
    query += login;
    query += "\', \'";
    query += text;
    query += "\')";

    //check the final query line
    std::cout << "Query: \"" << query << "\"\n";

    //do a query
    mysql_query(mysql, query.c_str());

}
void DBMessAll::getMessage(const int n)
{
    //form a query line
    std::string query = "SELECT text FROM messages_to_all_table WHERE id = ";
    query += std::to_string(n);    

    //check the final query line
    std::cout << "Query: \"" << query << "\"\n";

    //do a query
    mysql_query(mysql, query.c_str());

}

void DBMessAll::composeAllMsgCOllection()
{
    //form a query line
    std::string query = "SELECT id, sender, time FROM messages_to_all_table";
        
    //check the final query line
    std::cout << "Query: \"" << query << "\"\n";

    //do a query
    mysql_query(mysql, query.c_str());
}

std::string DBMessAll::packMsgInBuffer(int n)
{
    //do query with the function
    getMessage(n);
    res = mysql_store_result(mysql);
    //if result of a query has not been constructed
    if(res == NULL)
    {
        std::cout << "No infromation got on \"Find user's pass\" query.\n";
        return "\0";
    }
    //validate constructed result
    std::string list;
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
            //write result in buffer
            std::string output(row[i]);
            list += output;
            list += " ";
            //server->writeBuffer(start, output);

            //std::cout << row[i] << " ";
        }
        
    }
    list += "#";

    std::cout << "The list: " << list << "\n";
    return list;
}

std::string DBMessAll::packAllMsgCOllectionInBuffer()
{
    //do query with the function
    composeAllMsgCOllection();
    res = mysql_store_result(mysql);
    //if result of a query has not been constructed
    if(res == NULL)
    {
        std::cout << "No infromation got on \"composePrsMsgCOllection\" query.\n";
        return "\0";
    }
    //validate constructed result
    std::string list;
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
            //write result in buffer
            std::string output(row[i]);
            list += output;
            list += " ";
            //server->writeBuffer(start, output);

            //std::cout << row[i] << " ";
        }
        list += "\n";
    }

    list += "#";

    return list;
}