#pragma once
//#include "User.h"
#include "Chat.h"


//предварительное объявление классов
//используемых при определении класса Interface
class User;
class Chat;

//класс реализует общение между пользователем и внутренними классами программы
class Interface
{
public:
	//конструкторы и деструкторы
	Interface()
	{}
	~Interface() {}

	//первый уровень интерфэйса общения
	bool Enable(Chat& chat, ClientTCP &client);//булева функция используется во внешнем цикле запуска

	//функции работают в первом уровне интерфэйса и вызываютс¤ из Enable()
	static void registration(Chat& cht, ClientTCP &client);
	void logIn(Chat& cht,  ClientTCP &client);
	void quit(Chat& cht);

	//второй уровень интерфэйса
	bool startChat(Chat& cht, ClientTCP &client);

	//читает ввод пользователя для формирования текста сообщения
	static void readTheInput(std::string& str);
	
private:
	//переменные контролируют подключение уровня интерфэйса
	bool enable = true;//подключает 1-ый уровень интерфэйса
	bool LoggedIn = false;//подключает 1-ый уровень интерфэйса

	//указатель на юзера, который вошел через процедуру ввода пароля во 2-ой уровень интерфэйса
	User* active_user = nullptr;
};

