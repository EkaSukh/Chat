//This is a server version of the Chat
#include "Interface.h"
//#include "Chat.h"



int main()
{
	//создание объетов чата	
	
	//Establish server and connect to database
	ServerTCP server;
	DataBase data;
	data.connectToDataBase();
	DBUsers dbUsers(&data);
	DBMessAll dbMsgAll(&data);
	DBMessPrs dbMsgPrs(&data);

	Interface interface(&server, &dbUsers, &dbMsgAll, &dbMsgPrs);
//вход в тело чата
	while (interface.Enable()) //вход в интерфэйс первого уровня
	{}
	//std::cout << "Thank you for chatting.\n";

	return 0;
}
