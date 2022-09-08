#pragma once

#include "dataBase.h"

class DBMessAll
{
    public:
    DBMessAll(DataBase* db): dataBase(db) {std::cout << "Create a DBMsgAll object.\n";}
    ~DBMessAll(){} 
       
    //this functions only form SQL querry
    void addMessage(const std::string& login, const std::string& text);
    //this functions return values found with querry
    std::string packMsgInBuffer(int n);
    std::string packAllMsgCOllectionInBuffer();

    private:
    //this functions only form SQL querry    
    void getMessage(const int n);
    void composeAllMsgCOllection();

    DataBase* dataBase;
    MYSQL* mysql = dataBase->getDescriptorMYSQL();

    MYSQL_RES* res;
    MYSQL_ROW row;

    ServerTCP* server;
};