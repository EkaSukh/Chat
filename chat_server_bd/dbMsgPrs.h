#pragma once

#include "dataBase.h"

class DBMessPrs
{
    public:
    DBMessPrs(DataBase* db): dataBase(db) {std::cout << "Create a DBMsgPrs object.\n";}
    ~DBMessPrs(){}

    //this functions only form SQL querry
    void addMessage(const std::string& from_login,const std::string& to_login, const std::string& text);
    //this functions return values found with querry
    std::string packPrsMsgCollectionInBuffer(const std::string& to_login);
    std::string packMsgInBuffer(const int n);

    private:
    //this functions only form SQL querry    
    void composePrsMsgCOllection(const std::string& to_login);
    void getMessage(const int n);

    DataBase* dataBase;
    MYSQL* mysql = dataBase->getDescriptorMYSQL();

    MYSQL_RES* res;
    MYSQL_ROW row;

    ServerTCP* server;
};