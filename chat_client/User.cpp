#include "User.h"


//геттеры
std::string User::getName() const { return _name; }
std::string User::getLogin() const { return _login; }

//сеттеры
void User::setName(const std::string& name) { _name = name; }
void User::setPass(const std::string& pass) { _password = pass; }
//проверка пароля
bool User::checkPass(const std::string& psw) { return (0 == psw.compare(_password)); }

//добавление сообщения в коллекцию персоональных сообщений
void User::addMessageToMyCollection(const Message<std::string>& msg)
{
	receivedMessg.push_back(msg);
}

//подсчет персоональных сообщени в коллекции
size_t User::countReceivedMsg() const
{
	return receivedMessg.size();
}

//чтение выбранного сообщения из коллекции по персональному номеру сообщения
void User::readPersonalMsg(const size_t n)
{
	if (receivedMessg.empty())//нет сообщений
	{
		std::cout << "There is no messages yet\n";
	}
	else//есть сообщения
	{

		if ((n <= receivedMessg.size()))
		{

			receivedMessg[n - 1].showMessage();
		}
		else
			throw bad_range();

	}
}

//определение процедуры записи пользователя в файл
std::ofstream& operator <<(std::ofstream& os, User& user)
{
	os << user._login;
	os << ' ';
	os << user._password;
	os << ' ';
	os << user._name;
	os << ' ';
	//записываем количество сообщений в коллекции
	os << user.countReceivedMsg();
	os << ' ';
	//записываем всю коллекцию сообщений
	for(auto itr = user.receivedMessg.begin(); itr != user.receivedMessg.end(); ++itr)
	os << *itr;

	return os;
}
