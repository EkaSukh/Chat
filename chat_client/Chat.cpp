//This is a Client version of the Chat
#include "Chat.h"


//работа с вектором пользователей

//добавляем пользователя в контенер пользователей
void Chat::addUser(Chat& cht, ClientTCP &client, const std::string& login, const std::string& name, const std::string& pass)
{
	//two positions is for operation descriptor
	// 11 is descriptor to findUser operation on server side
	client.clearBuffer();
	std::string descriptor = "11";
	int start = client.writeBuffer(0, descriptor);
	

	//copy login in buffer
	start = client.writeBuffer(start, login);
	
	//copy name in buffer
	start = client.writeBuffer(start, name);
	
	//copy name in buffer
	start = client.writeBuffer(start, pass);

	//client.showBuff();
	
	//connect and sedn data to the server
	client.clientConnect();
	client.writeOutput();  

	client.clientClose();

	
}

void Chat::insertUser(const User& usr)
{
	Users.insert({ usr.getLogin(), usr});
}

//выводим список пользователей чата по имени
void Chat::showUsers(ClientTCP &client)
{
	client.clearBuffer();
	std::string descriptor = "13";
	int start = client.writeBuffer(0, descriptor);
	
	client.clientConnect();
	client.writeOutput(); 

	client.clearBuffer();
	client.readInput();
	client.clientClose();

	std::string num_users_s;
	start = client.readBuffer(0, num_users_s);	
	std::cout <<"constructed nubmer of users by string: \"" << num_users_s << "\"\n";
	int n_users = client.transformInNumber(num_users_s);
	
	std::cout <<"constructed nubmer of users by int: \"" << n_users << "\"\n";
	

	for (int i = 0; i < n_users; i++)
	{
		std::string user_name;
		start = client.readBuffer(start, user_name);
		std::cout << user_name << "\n";
	}
	
}

//находит пользователя по логину и возвращает успешность
bool Chat::findUser(const std::string& login, ClientTCP &client)
{
	//two positions is for operation descriptor
	// 10 is descriptor to findUser operation on server side
	client.clearBuffer();
	std::string descriptor = "10";
	int start = client.writeBuffer(0, descriptor);
	     
	start = client.writeBuffer(start, login);
    
    client.clientConnect();
    client.writeOutput();

	//client.showBuff();
    
	client.clearBuffer();
	client.readInput();
	
	int result = client.atBuff(0) - '0';
	client.clientClose();
    
	//std::cout << "result is " << result << "\n";
	if (result == 0)
	{
		return false;
	}
	else
	{
		return true;
	}	
}

//находит пользователя по имени и возвращает успешность
bool Chat::findUserByName(const std::string& name, ClientTCP &client)
{
	//two positions is for operation descriptor
	// 10 is descriptor to findUser operation on server side
	client.clearBuffer();
	std::string descriptor = "12";
	int start = client.writeBuffer(0, descriptor);
	       

    start = client.writeBuffer(start, name);

	client.clientConnect();
    client.writeOutput();
    
	client.clearBuffer();
	client.readInput();
	
	int result = client.atBuff(0) - '0';
	client.clientClose();
    
	//std::cout << "result is " << result << "\n";
	if (result == 0)
	{
		return false;
	}
	else
	{
		return true;
	}	

}

//возвращает указатель на пользователя с данным логином
User* Chat::getUser(const std::string& login)
{
	std::map <std::string, User>::iterator usr = Users.find(login);
	
	if (usr != Users.end())
		return &(usr->second);
	else
		return nullptr;
}

//возвращает указатель на пользователя с данным имененм
User* Chat::getUserByName(const std::string& name)
{

	std::map <std::string, User>::iterator usr;
	for (usr = Users.begin();usr != Users.end();++usr)
	{
		std::string tmp = usr->second.getName();
		if (0 == tmp.compare(name))
			return &(usr->second);
	}	
	return nullptr;

}

//отображает количество сообщений в массивах общих и персоональных сообщений для конкретного пользователя
void Chat::chatState(Chat& cht, User* usr, ClientTCP &client)
{
	//construct a message to the server
	//descriptor for personal chat state information
	client.clearBuffer();

    std::string descriptor = "21";
	int start = client.writeBuffer(0, descriptor);

	start = client.writeBuffer(start, usr->getLogin());
	
	client.clientConnect();    
    client.writeOutput();

	client.clearBuffer();
	client.readInput();
	client.clientClose();

	std::string s_msg_all;
	start = client.readBuffer(0, s_msg_all);

	std::string s_msg_prs;
	client.readBuffer(start, s_msg_prs);
	
	std::cout << "Messages from all users: " << s_msg_all << std::endl;
	std::cout << "Personal mesages: " << s_msg_prs << std::endl;

}


//работа с вектором общих сообщений

//добавляет сообщение в конец вектора общих сообщений
void Chat::addMessageToAll(const Message<std::string>& msg_all)
{
	all_messages.push_back(msg_all);
}

//подсчитывает количество сообщений в массиве общих сообщений
size_t Chat::countAllMessages() const
{
	return all_messages.size();
}

//вывод текста сообщения по его порядковому номеру в массиве общих сообщений
void Chat::readMsgAll(const size_t num_of_msg)
{
	//когда нет сообщений
	if (all_messages.empty())
	{
		std::cout << "There is no messages yet.\n";
	}
	else//есть сообщения
	{
		if ((num_of_msg <= all_messages.size()))
		{
			all_messages[num_of_msg - 1].showMessage();
		}
		else
			throw bad_range();

	}
}

//запись коллекции общих сообщений в файл
void Chat::printToFile()
{
	std::ofstream messages_file("messages_to_all.txt");
	//фиксируем количество сообщений в хранилище
	messages_file << countAllMessages();

	//записываем сообщения в хранилище
	for(auto itr = all_messages.begin(); itr != all_messages.end(); ++itr)
		messages_file << *itr;

	//определяем права доступа к файлу только для владельца
	std::filesystem::permissions("messages_to_all.txt", std::filesystem::perms::group_all | std::filesystem::perms::others_all, std::filesystem::perm_options::remove);
}

//чтение коллекции общих сообщений из файла
void Chat::readFromFile()
{
	std::ifstream messages_file("messages_to_all.txt");
	//если такого файла нет
	if(!messages_file)
	return;

	messages_file.seekg(0, std::ios_base::beg);
	//получаем количество сообщени в коллекции
	size_t number_of_messages;
	messages_file >> number_of_messages;

	//входим в цикл по количеству сообщиний
	while(number_of_messages != 0)
	{
		//считываем сообщиение во временный объект и кладем его в коллекцию
		Message<std::string> msg_tmp;
		messages_file >> msg_tmp;
		all_messages.push_back(msg_tmp);

		//после считывания символ '#' остался в потоке и нужно его пропустить
		int position = messages_file.tellg();
		messages_file.seekg(position + 1, std::ios_base::beg);

		--number_of_messages;
	}
}

//запись пользователей в файл
void Chat::writeUsersToFile()
{
	std::ofstream users_file("users_file.txt");
	//фиксируем количество в хранилище
	users_file << Users.size();

	//записываем сообщения в хранилище
	for(auto itr = Users.begin(); itr != Users.end(); ++itr)
		users_file << itr->second;

	//определяем права доступа к файлу только для владельца
	std::filesystem::permissions("users_file.txt", std::filesystem::perms::group_all | std::filesystem::perms::others_all, std::filesystem::perm_options::remove);

}

/*
//восстановление пользователей из файла
void Chat::restoreUsersFromFile()
{
	
	std::ifstream users_file("users_file.txt");
	//если нет такого файла
	if(!users_file)
		return;

	//получаем сколько пользователей записано в файл
	int num_users;
	users_file >> num_users;
	
	//каждого пользователя создаем по очереди пока не восстановим всех
	while(num_users != 0)
	{
		--num_users;
		//создаем временный объект 
		std::string tmp_login;
		users_file >> tmp_login;
		std::string tmp_pass;
		users_file >> tmp_pass;
		std::string tmp_name;
		users_file >> tmp_name;

		User user_tmp(tmp_login, tmp_pass, tmp_name);
		
		//получаем количество его персональных сообщений
		size_t num_msg;
		users_file >> num_msg;
		
		//восстанавливаем все сообщения из колекции по очереди
		while(num_msg != 0)
		{
			--num_msg;

			//создаем временный объект и кладем его в коллекцию
			Message<std::string> msg_tmp;
			users_file >> msg_tmp;
			user_tmp.addMessageToMyCollection(msg_tmp);
			
			//после считывания символ '#' остался в потоке и нужно его пропустить
			int position = users_file.tellg();
			users_file.seekg(position + 1, std::ios_base::beg);
		}
		//
		addUser(user_tmp);
		
	}
}
*/