#pragma once
#include <iostream>
#include <mysql.h>

#include "net.h"

//This class adjusts connection and connects to an existing database
class DataBase
{
    public:
    DataBase();
    ~DataBase();

    MYSQL* getDescriptorMYSQL();

    void setAllParam();
    bool connectToDataBase();
    void createDataBase();  


    private:

    void setHost(const std::string& input);
    void setUser(const std::string& input);
    void setPasswd(const std::string& input);
    void setDBname(const std::string& input);
    void setSocket(const std::string& input);
    void setPort(const unsigned int input);
    void setFlag(const unsigned int input);

    void createTheUsersTable();
    void createTheAllMessagesTable();
    void createThePerosonalMessagesTable();
    
    MYSQL* mysql;
    const char* host = "localhost";
    const char* user = "root";
    const char* passwd = "root";
    const char* dbname = "Chat_data_base";
    const char* socket = NULL;
    unsigned int port = 0;
    unsigned int flag = 0;
    
};
