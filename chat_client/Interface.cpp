#include "Interface.h"


//first interface level
bool Interface::Enable(Chat& chat, ClientTCP &client)
{
	//show menu and read user's input
	std::cout << "Please, choose an option:\n"
		<< "1 Registration of a new user.\n"
		<< "2 Sign in as an existing user\n"
		<< "3 Quit the Chat" << std::endl;
	int input;
	while (!(std::cin >> input))//запрос ввода
	{
		std::cin.clear();
		while (std::cin.get() != '\n')
			continue;
		std::cout << "Input shood be an integer from 1 to 3. Please, try again.\n";
	}

	//движение по меню
	switch (input)
	{
	case 3:
	{
		quit(chat);
		return enable;
	}
	case 2:
	{
		logIn(chat, client);
		return enable;
	}

	case 1:
	{
		registration(chat, client);
		return enable;
	}

	default: return false;//если введено не 1, 2, 3, то выходим из чата
	}
}

//регистрация в чате нового пользователя
void Interface::registration(Chat& cht, ClientTCP &client)
{
	std::string name;
	std::string login;
	std::string pass;
	std::cout << "Enter your login up to 9 characters (it can not be changed in future):\n";
	std::cin >> login;

	//проверка логина, вдруг такой уже есть
	while (cht.findUser(login, client))
	{
		std::cout << "This login is engaged, choose another one:\n";
		std::cin >> login;
	}

	std::cout << "Enter your name (you may change it in future):\n";
	std::cin >> name;
	std::cout << "Enter your password:\n";
	std::cin >> pass;

	//User user(login, pass, name);//создание объекта пользователя, который будет скопирован в массив

	//положить пользователя в лист юзеров
	cht.addUser(cht, client, login, name, pass);
	std::cout << "Your user account successfully created.\n";

}


//enter the chat as a registrated user with login and pass
void Interface::logIn(Chat& cht, ClientTCP &client)
{
	std::cout << "Enter your loggin:\n";
	std::string lg_inp;
	std::cin >> lg_inp;
	//chech if the login exists
	if (!cht.findUser(lg_inp, client))
	{
		std::cout << "There is no user with this login.\n";
		return;
	}


	std::cout << "Enter your password:\n";
	std::string pass_inp;
	std::cin >> pass_inp;

	//construct a message to the server
	//descriptor for logIn on the server
	client.clearBuffer();
	std::string descriptor = "20";

	//the variable is a positin in buffer after the writeBuffer
	//and next writeBuffer operation will start writing in buffer from this position
	int start = client.writeBuffer(0, descriptor);
    

	//login
	start = client.writeBuffer(start, lg_inp);
	

	//password
	start = client.writeBuffer(start, pass_inp);

	
	//connect and send data to the server
	client.clientConnect();  

    client.writeOutput();	

	client.readInput();

	//client.showBuff(30);
	
	int result = client.atBuff(0) - '0';
	client.clientClose();
    
	std::cout << "result is " << result << "\n";
	if (result == 0)
	{
		std::cout << "The password is incorrect.\n";
	}
	else
	{
		std::cout << "You have successfully signed in.\n\n";
		//Read a user's name that is in the buffer
		std::string name;
		client.readBuffer(2, name);

		std::cout <<"name reconstruction: \"" << name << "\"\n";

		User actual_user(lg_inp, pass_inp, name);
		cht.insertUser(actual_user);
		//set pointer on active user
		active_user = cht.getUser(lg_inp);

		LoggedIn = true;//enable second level interface, that is a personal interface
	}	
	
}

//выход из чата
void Interface::quit(Chat& cht)
{
	enable = false;//отключение первого уровня интерфэйса
	cht.printToFile();//выводим массив общих сообщений в файл
	cht.writeUsersToFile();//выводим пользователей в файл
}

//формирует текст сообщения из пользовательского ввода
void Interface::readTheInput(std::string& str)
{
	char ch[100];
	std::cin.get(ch, 100, '#');
	str += ch;
}


//интерфэйс второго уровня
bool Interface::startChat(Chat& cht, ClientTCP &client)
{
	if (!LoggedIn)
		return false;

	cht.chatState(cht, active_user, client);

	std::cout << "You may choose an option:\n";
	std::cout << "1 Send a message to all other users\n";
	std::cout << "2 Send a message to a selected user\n";
	std::cout << "3 Read a messages from all users\n";
	std::cout << "4 Read a personal message\n";
	std::cout << "5 Personal: change name or password\n";
	std::cout << "6 Go to main menu\n\n";


	int input;
	while (!(std::cin >> input))//проверка ввода
	{
		std::cin.clear();
		while (std::cin.get() != '\n')
			continue;
		std::cout << "Input shood be an integer from 1 to 6. Please, try again.\n";
	}

	switch (input)
	{
		//write a message to "for all" collection
	case 1: {
		std::cout << "Enter the message up to 100 symbols (enter # to finish the message):\n";
		std::string inp_text;
		readTheInput(inp_text);

		std::string from = (active_user->getName());
		//std::string to = "all";

		//write descrptor of an action for the server
		client.clearBuffer();
		std::string descriptor = "22";
		int start = client.writeBuffer(0, descriptor);

		//write login of an active user for the server
		std::string login = active_user->getName();
   		start = client.writeBuffer(start, login);

		//text
		start = client.writeBuffer(start, inp_text, '#');
		
		//from
		start = client.writeBuffer(start, from);

		client.showBuff(30);
		
		client.clientConnect();   
		client.writeOutput();
    	client.clientClose();	
		
		
		return true;
	}

		  //write a message to a selected user
	case 2: {

		{//show  list of users
			std::cout << "\nList of current users:\n";
			cht.showUsers(client);
		}
		//enter a recepient
		std::cout << "Enter recipient's name:\n";
		std::string to;
		std::cin >> to;

		//check the recepeient exists
		if (!cht.findUserByName(to, client))
		{
			std::cout << "Can Not Find the user.\n";
			return true;
		}

		std::string from = (active_user->getName());
		std::cout << "Enter the message up to 100 symbols (enter # to finish the message):\n";
		std::string inp_text;		
		readTheInput(inp_text);

		
		client.clearBuffer();
		std::string descriptor = "23";
		int start = client.writeBuffer(0, descriptor);

		//write login of an active user for the server
		std::string login = active_user->getName();
   		start = client.writeBuffer(start, login);
		
		//text
		start = client.writeBuffer(start, inp_text, '#');		

		//to
		start = client.writeBuffer(start, to);
				
		//connect and send data
		client.clientConnect();
		
    	client.writeOutput();
    	client.clientClose();
		
		return true;

	}

		  //read a message from "for all" collection
	case 3:
	{
		std::cout << "Enter a serial number of a message you want to read:\n";
		size_t sn;
		while (!(std::cin >> sn))//проверка ввода
		{
			std::cin.clear();
			while (std::cin.get() != '\n')
				continue;
			std::cout << "Input shood be a posotive integer. Please, try again.\n";
		};

		client.clearBuffer();
		std::string descriptor = "24";
		int start = client.writeBuffer(0, descriptor);

		start = client.writeBuffer(start, active_user->getLogin());
		
		std::string num = std::to_string(sn);
		start = client.writeBuffer(start, num);

		client.showBuff(15);
		
		
		//connect and send data
		client.clientConnect();
		client.writeOutput();  
    	

		client.clearBuffer();
		client.readInput();
		client.clientClose();
				
		//read information from the server
		std::string inp_text;	
		start = client.readBuffer(0,inp_text, '#');	
		
		std::string from;
		start = client.readBuffer(start,from);
		
		std::string to;
		start = client.readBuffer(start,to);
		
		Message<std::string> received(to, from, inp_text);
		received.showMessage();
		
		return true;
	}

	//read a message from a personal collection
	case 4:
	{
		std::cout << "Enter a serial number of a message you want to read:\n";
		size_t sn;
		while (!(std::cin >> sn))//проверка ввода
		{
			std::cin.clear();
			while (std::cin.get() != '\n')
				continue;
			std::cout << "Input shood be a positive integer. Please, try again.\n";
		}

		client.clearBuffer();
		std::string descriptor = "25";
		int start = client.writeBuffer(0, descriptor);	

		start = client.writeBuffer(start, active_user->getLogin());	

		std::string num = std::to_string(sn);
		start = client.writeBuffer(start, num);
				
		//connect and send data
		client.clientConnect();
		client.writeOutput();  
    	

		client.clearBuffer();
		client.readInput();
		client.clientClose();
				
		
		//read information from the server
		std::string inp_text;	
		start = client.readBuffer(0,inp_text, '#');			

		std::string from;
		start = client.readBuffer(start,from);
		
		std::string to;
		start = client.readBuffer(start,to);
		
		Message<std::string> received(to, from, inp_text);
		received.showMessage();
		
		return true;
	}

	//персональный интерфэйс для смены пароля и имени пользователя	
	case 5:
	{
		bool in_personal = true;//валидатор нахождения внутри персонального интерфэйса
		while (in_personal)
		{
			std::cout << "You may change your user's name and password:\n";
			std::cout << "1 Change user's name.\n";
			std::cout << "2 Change user's password.\n";
			std::cout << "3 Go upward menu.\n";
			int input;
			while (!(std::cin >> input))//проверка ввода
			{
				std::cin.clear();
				while (std::cin.get() != '\n')
					continue;
				std::cout << "Input shood be an integer 1, 2  or 3. Please, try again.\n";
			}

			client.clearBuffer();
			std::string descriptor = "26";
			int start = client.writeBuffer(0, descriptor);
			start = client.writeBuffer(start, active_user->getLogin());
			

			switch (input)
			{
			case 1://смена имени пользователя
			{
				
				descriptor = "1";
				start = client.writeBuffer(start, descriptor);				

				std::cout << "Your current user's name is " << active_user->getName() << std::endl;
				std::cout << "Would you like to change it? (y/n)\n";
				char ch;
				std::cin >> ch;
				if ((ch == 'y') || (ch == 'Y'))
				{
					std::cout << "Enter new name:\n";
					std::string new_name;
					std::cin >> new_name;

					active_user->setName(new_name);
					std::cout << "Your new name is \"" << active_user->getName() << "\".\n";

					start = client.writeBuffer(start, new_name);
					
		
					//connect and send data
					client.clientConnect();
					client.writeOutput();  

					client.clientClose();

					break;

				}
				else
				{
					break;
				}
					
			}
			case 2://смена пароля пользователя
			{
				descriptor = "2";
				start = client.writeBuffer(start, descriptor);	
				
				std::cout << "Would you like to change your password? (y/n)\n";
				char ch;
				std::cin >> ch;
				if ((ch == 'y') || (ch == 'Y'))
				{
					std::cout << "Enter new password:\n";
					std::string new_pass;
					std::cin >> new_pass;

					//active_user->setPass(new_pass);
					std::cout << "Your password is changed\n";
					
					start = client.writeBuffer(start, new_pass);
							
					//connect and send data
					client.clientConnect();
					client.writeOutput();  

					client.clientClose();

					break;

				}
				else
				{
					break;
				}


			}
			case 3://выход из персонального меню во второй уровень интерфэйса
			{
				
				descriptor = "3";
				start = client.writeBuffer(start, descriptor);
				client.clientConnect();
				client.writeOutput();  

				client.clientClose();

				in_personal = false;
				break;
			}
			default://если введено не 1, 2, 3, то тоже выход во второй уровень интерфэйса
			{
				in_personal = false;
				break;
			}

			}
		}


		return true;
	}


	case 6: //выход в первый уровень интерфэйса
	{
		
		client.clearBuffer();
		std::string descriptor = "16";
		int start = client.writeBuffer(0, descriptor);

		//connect and send data
		client.clientConnect();
		client.writeOutput();  

		client.clientClose();

		LoggedIn = false;
		return false;
	}


	default: //если введено целое не от 1 до 6, то тоже выход в первый уровень интерфэйса
		return false;
	}


}
