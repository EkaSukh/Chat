#pragma once

#include <map>
#include <filesystem>
#include "User.h"


//class User;

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
	//void writeUsersToFile();
	//void restoreUsersFromFile();

	//отражает колличество сообщений в общей и личной коллекции 
	//для чтения их вошедшим по паролю пользователем user
	void chatGetAllCollection(Chat& cht, User* usr, ClientTCP &client);
	void chatGetPersonalCollection(Chat& cht, User* usr, ClientTCP &client);

	//работа с массивом общих сообщений
	
	size_t countAllMessages() const;
	void readMsgAll(const size_t num_of_msg);
	void printToFile();
	void readFromFile();


private:
	//массив пользователей
	std::map <std::string, User> Users;
	
};
