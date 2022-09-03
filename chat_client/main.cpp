//this is a Client version of the chat
#include "Interface.h"
//#include "Chat.h"

int main()
{
	//create a client object
	/*
	std::cout << "Enter server Ip-adress: ";
	std::string ip_server;
	std::cin >> ip_server;
	ClientTCP client(ip_server);*/
	ClientTCP client;


//создание объетов чата
	Interface interface;//объект интрефэйса
	Chat chat; //объект чата
	std::cout << "Welcome to our chat!\n";

//вход в тело чата
	while (interface.Enable(chat, client)) //вход в интерфэйс первого уровня
	{
		while (interface.startChat(chat, client))//вход в интерфэйс второго уровня
			continue;
	}
	std::cout << "Thank you for chatting.\n";

	return 0;
}
