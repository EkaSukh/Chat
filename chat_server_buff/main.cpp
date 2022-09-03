//This is a server version of the Chat
#include "Interface.h"
//#include "Chat.h"



int main()
{
	//создание объетов чата	
	Chat chat; //объект чата
	Interface interface(&chat);//объект интрефэйса
	std::cout << "Welcome to our chat!\n";

	//восстановление состояния чата из файлов
	//колекция общих сообщений
	chat.readFromFile();
	//состояния пользователей и их персональных коллеций сообщений
	chat.restoreUsersFromFile();

	//Establish server
	ServerTCP server;

//вход в тело чата
	while (interface.Enable(chat, server)) //вход в интерфэйс первого уровня
	{
		while (interface.startChat(chat, server))//вход в интерфэйс второго уровня
			continue;
	}
	std::cout << "Thank you for chatting.\n";

	return 0;
}
