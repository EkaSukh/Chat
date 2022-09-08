#pragma once

#include <vector>
#include <exception>
#include <iostream>
#include <fstream>
#include "net.h"


//класс для формирования исключений в функции чтения сообщений из вектора персональных сообщений
class bad_range :public std::exception
{
public:
	virtual const char* what() const noexcept override
	{
		return "EXCEPTION: index is out of range\n";
	}

};

//класс описывает пользователя чата
class User
{
public:
	//конструкторы 
	User() {}
	User(const std::string& login, const std::string& passw, const std::string& name) :
		_login(login), _password(passw), _name(name) {}

	//деструкторы
	~User() {}

	//геттеры приватных данных
	std::string getName() const;
	std::string getLogin() const;

	//сэттеры приватных данных
	void setName(const std::string& name);
	void setPass(const std::string& pass);

	//проверка пароля
	bool checkPass(const std::string& psw);

	//работа с коллекцией персоональных сообщений
	//void addMessageToMyCollection(const Message<std::string>& msg);
	size_t countReceivedMsg() const;
	void readPersonalMsg(const size_t n);

	//запись и восстановление пользователя из файла
	friend std::ofstream& operator <<(std::ofstream& os, User& user);
	
private:
	const std::string _login; //константная переменная для однозначного определения юзера в списке
	std::string _password;
	std::string _name;

	// коллекция персоональных сообщений для данного юзера
	//std::vector<Message<std::string> > receivedMessg;

};
