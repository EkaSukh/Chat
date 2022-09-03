#pragma once

//#include <vector>
#include <map>
#include <filesystem>
#include "User.h"
//#include <unistd.h>
//#include <cstring>
//#include <sys/socket.h>
//#include <netinet/in.h>
//#include <arpa/inet.h>


#define BUF_SIZE 1024
#define PORT 7777

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

	//for net_client working
	//int client_connect(struct sockaddr_in &serveraddress);

	//работа с массивом пользователей
	void addUser(Chat& cht, ClientTCP &client, const std::string& login, const std::string& name, const std::string& pass);
	void insertUser(const User& usr);
	void showUsers(ClientTCP &client);
	bool findUser(const std::string& login, ClientTCP &client);
	bool findUserByName(const std::string& name, ClientTCP &client);
	User* getUser(const std::string& login);
	User* getUserByName(const std::string& name);
	void writeUsersToFile();
	void restoreUsersFromFile();

	//отражает колличество сообщений в общей и личной коллекции 
	//для чтения их вошедшим по паролю пользователем user
	void chatState(Chat& cht, User* usr, ClientTCP &client);

	//работа с массивом общих сообщений
	void addMessageToAll(const Message<std::string>& msg_all);
	size_t countAllMessages() const;
	void readMsgAll(const size_t num_of_msg);
	void printToFile();
	void readFromFile();


private:
	//массив пользователей
	std::map <std::string, User> Users;

	//массив сообщение, доступный всем пользователям
	std::vector <Message<std::string> > all_messages;
};
