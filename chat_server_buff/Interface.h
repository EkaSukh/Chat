#pragma once
//#include "User.h"
#include "Chat.h"

//#include <unistd.h>
//#include <string.h>
//#include <sys/socket.h>
//#include <netinet/in.h>
//include <arpa/inet.h>


#define BUF_SIZE 1024
#define PORT 7777

//предварительное объявление классов
//используемых при определении класса Interface
class User;
class Chat;

//класс реализует общение между пользователем и внутренними классами программы
class Interface
{
public:
	//конструкторы и деструкторы
	Interface(Chat* ptr_chat): p_chat(ptr_chat)
	{}
	~Interface() {}

	//for server 
	
	
	//первый уровень интерфэйса общения
	bool Enable(Chat& chat, ServerTCP &server);//булева функция используется во внешнем цикле запуска

	
	//функции работают в первом уровне интерфэйса и вызываютс¤ из Enable()
	//static void registration(Chat& cht, ServerTCP &server);
	int logIn(Chat& cht, const std::string &login, const std::string &passw);
	void setActiveUser(const std::string &login);
	void nullActiveUser();
	void setInputPersonal(int n);
	//void quit(Chat& cht);

	//второй уровень интерфэйса
	bool startChat(Chat& chat, ServerTCP &server);

	//читает ввод пользователя для формирования текста сообщения
	static void readTheInput(std::string& str);
	

private:
	//переменные контролируют подключение уровня интерфэйса
	bool enable = true;//подключает 1-ый уровень интерфэйса
	bool LoggedIn = false;//подключает 1-ый уровень интерфэйса

	//указатель на юзера, который вошел через процедуру ввода пароля во 2-ой уровень интерфэйса
	User* active_user = nullptr;
	Chat* p_chat = nullptr;
	int input_personal = 0;
};