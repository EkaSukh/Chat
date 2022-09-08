#pragma once
#include <iostream>
#include <fstream>
#include "dbUsers.h"
#include "dbMsgAll.h"
#include "dbMsgPrs.h"


#define BUF_SIZE 1024
#define PORT 7777


//класс реализует общение между пользователем и внутренними классами программы
class Interface
{
public:
	//конструкторы и деструкторы
	Interface(ServerTCP* ptr_server, DBUsers* ptr_usrs, DBMessAll* ptr_msAll, DBMessPrs* ptr_msPrs): server(ptr_server),
	 baseUsers(ptr_usrs), baseMsgAll(ptr_msAll), baseMsgPrs(ptr_msPrs)
	{}
	~Interface() {}

	//for server 
	
	
	//первый уровень интерфэйса общения
	bool Enable();//булева функция используется во внешнем цикле запуска	
	

private:
	//переменные контролируют подключение уровня интерфэйса
	bool enable = true;//подключает 1-ый уровень интерфэйса
	ServerTCP* server;
	DBUsers* baseUsers;
	DBMessAll* baseMsgAll;
	DBMessPrs* baseMsgPrs;
	
};