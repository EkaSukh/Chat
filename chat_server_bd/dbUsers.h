#pragma once

#include "dataBase.h"

class DBUsers
{
    public:
    DBUsers(DataBase* db): dataBase(db) {std::cout << "Create a DBUser object.\n";}
    ~DBUsers() {}  

    //this function only form SQL querry  
    void insertUserInTable(const std::string& login, const std::string& name, const std::string& passwd);
    void changePass(const std::string& login, const std::string& new_passwd);
    void changeName(const std::string& login, const std::string& new_name);

    //this functions return values found with querry    
    bool findUserByLogin(const std::string& login);
    bool fingUserByName(const std::string& name);
    bool checkPass(const std::string& login, const std::string& passwd);
    
    std::string packUserListInBuffer();
    std::string packUserNameInBuffer(const std::string& login);

    private:
    //these functions only form SQL querry    
    void findUserLoginInTable(const std::string& login);
    void findUserNameInTable(const std::string& name);
    void findUserPassInTable(const std::string& login, const std::string& passwd);
    void getUserNameFromTable(const std::string& login);
    
    void listUsersName();

    DataBase* dataBase;
    MYSQL* mysql = dataBase->getDescriptorMYSQL();

    MYSQL_RES* res;
    MYSQL_ROW row;

    ServerTCP* server;
};