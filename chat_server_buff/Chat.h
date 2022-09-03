#pragma once

//#include <vector>
#include <map>
#include <filesystem>
#include "User.h"




//предварительное объявление явной специализации шаблонного класса Message
//который входит в объявление класса Chat
template<> class Message <std::string>;


//предварительное объявления класса
//используемого при определении класса Chat
class User;

//класс Chat
//хранит массив пользователей
//хранит массив общих сообщений
//осуществляет работу с этими массивами
class Chat
{
public:
	//конструктор и деструктор класса
	Chat() {}
	~Chat() {}

	//работа с массивом пользователей
	void addUser(const User& usr);
	void showUsers(ServerTCP &server);
	bool findUser(const std::string& login);
	bool findUserByName(const std::string& name);
	User* getUser(const std::string& login);
	User* getUserByName(const std::string& name);
	void writeUsersToFile();
	void restoreUsersFromFile();

	//отражает колличество сообщений в общей и личной коллекции 
	//для чтения их вошедшим по паролю пользователем user
	void chatState(User* usr);

	//работа с массивом общих сообщений
	void addMessageToAll(const Message<std::string>& msg_all);
	size_t countAllMessages() const;
	void readMsgAll(const size_t num_of_msg, ServerTCP &server);
	void printToFile();
	void readFromFile();


private:
	//массив пользователей
	std::map <std::string, User> Users;

	//массив сообщение, доступный всем пользователям
	std::vector <Message<std::string> > all_messages;
};
