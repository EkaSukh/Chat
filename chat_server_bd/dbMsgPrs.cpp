#include "dbMsgPrs.h"

//this functions only form SQL querry
    void DBMessPrs::addMessage(const std::string& from_login,const std::string& to_login, const std::string& text)
    {
        //form a query line
        std::string query = "INSERT INTO messages_to_person_table (sender, recepient, text) values (\'";
        query += from_login;
        query += "\', \'";
        query += to_login;
        query += "\', \'";
        query += text;
        query += "\')";

        //check the final query line
        std::cout << "Query: \"" << query << "\"\n";

        //do a query
        mysql_query(mysql, query.c_str());
    }
    void DBMessPrs::composePrsMsgCOllection(const std::string& to_login)
    {
        //form a query line
        std::string query = "SELECT id, sender, time FROM messages_to_person_table WHERE recepient = \'";
        query +=to_login;
        query += "\'";   

        //check the final query line
        std::cout << "Query: \"" << query << "\"\n";

        //do a query
        mysql_query(mysql, query.c_str());

    }

    void DBMessPrs::getMessage(const int n)
    {
        //form a query line
        std::string query = "SELECT text FROM messages_to_person_table WHERE id = ";
        query += std::to_string(n);    

        //check the final query line
        std::cout << "Query: \"" << query << "\"\n";

        //do a query
        mysql_query(mysql, query.c_str());

    }

//this functions return values found with querry
    std::string DBMessPrs::packPrsMsgCollectionInBuffer(const std::string& to_login)
    {
        //do query with the function
        composePrsMsgCOllection(to_login);
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

    
    std::string DBMessPrs::packMsgInBuffer(const int n)
    {
        //do query with the function
        getMessage(n);
        res = mysql_store_result(mysql);
        //if result of a query has not been constructed
        if(res == NULL)
        {
            std::cout << "No infromation got on \"getMessage\" query.\n";
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