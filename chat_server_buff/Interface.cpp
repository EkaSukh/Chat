#include "Interface.h"

/*
The porgram logic uses decriptors to define action requested from a client

10 "findUser"
11 "addUser"
12 "findUserByName"
13 "showUsers"

20 "logIn"
21 "reconstruction chat state for the user"
22 "send message to all oter users"
*/



//первый уровень интерфэйса
bool Interface::Enable(Chat& chat, ServerTCP &server)
{
	
		
	std::cout << "Waiting for message from a client...\n";

	//read a descriptor from a client's message	
	int input = server.readInput();
	
	//move through the menu
		switch (input)
		{
			//This is an action for finding user operation
			case 10:
			{
				
				std::cout << "Doing \"findUser\" operation\n";							
				
				//Read a user's login that is in the buffer
				std::string login;
				server.readBuffer(0, login);
        		
				//check if a user exists
				std::cout <<"login is \"" << login << "\"\n";
				bool find = chat.findUser(login);
				std::cout << "result of finding is " << find << "\n";
				
				//compose an answer
				server.clearBuffer();
				if(find)
					{
						std::string result = "1";
						server.writeBuffer(0, result);
					}
				else
					{
						std::string result = "0";
						server.writeBuffer(0, result);						
					}
				
				server.writeOutput();	

				return enable;
			
			}
			//This is an action to put new user in the chat
			case 11:
			{
				
				std::cout << "Doing \"addUser\" operation\n";							
				
				//Read a user's login that is in the buffer
				std::string login;
				int n = server.readBuffer(0, login);								
				std::cout <<"login reconstruction: \"" << login << "\"\n";
				
				//Read a user's name that is in the buffer
				std::string name;
				n = server.readBuffer(n, name);
				std::cout <<"name reconstruction: \"" << name << "\"\n";
				
				//Read a user's pass that is in the buffer
				std::string pass;
				server.readBuffer(n, pass);
				std::cout <<"pass reconstruction: \"" << pass << "\"\n";
				
				//construct an object  and put a user in the list of users
				User user(login, pass, name);
				
				chat.addUser(user);
				std::cout << "Your user account successfully created.\n";	

				//save new state of the chat
				chat.writeUsersToFile();			

				return enable;			
			}

			case 12:
			{
				std::cout << "Doing \"findUserByName\" operation\n";							
				
				//Read a user's login that is in the buffer				
				std::string name;
				server.readBuffer(0, name);				
				std::cout <<"name is \"" << name << "\"\n";

				//check if a user exists
				bool find = p_chat->findUserByName(name);
				std::cout << "result of finding is " << find << "\n";
				
				//compose an answer
				if(find)
					{
						std::string result = "1";
						int start = server.writeBuffer(0, result);
					}
				else
					{
						std::string result = "0";
						int start = server.writeBuffer(0, result);
					}

				server.writeOutput();
				
				return enable;

			}

			//return a list of the avalible users to write to...
			case 13:
			{
				std::cout << "\nList current users...\n";
				p_chat->showUsers(server);		

				server.writeOutput();
				return enable;
			}

			
			case 20:
			{
				std::cout << "Doing \"logIn\" operation\n";							
				
				//Read a user's login that is in the buffer
				std::string login;
				int n = server.readBuffer(0, login);
				std::cout <<"login reconstruction: \"" << login << "\"\n";
				
				//Read a user's pass that is in the buffer
				std::string pass;
				server.readBuffer(n, pass);
				std::cout <<"pass reconstruction: \"" << pass << "\"\n";

				//compose an answer
				int result = logIn(chat, login, pass);				

				//compose operation descriptor

				server.clearBuffer();
				
				if(result == 1)
					{
						std::string result = "1";
						int start = server.writeBuffer(0, result);
						//compose a name of an active user

						std::string u_name = active_user->getName();
						server.writeBuffer(start, u_name);
						
					}
				else
					{
						std::string result = "0";
						int start = server.writeBuffer(0, result);
					}
							

				server.writeOutput();

				//set active user to nullptr for server should not keep the state of a client
				nullActiveUser();

				return enable;
			}
			case 21:
			{
				std::string login;
				int n = server.readBuffer(0, login);
				std::cout <<"login reconstruction: \"" << login << "\"\n";

				setActiveUser(login);

				//enter personalized interface
				LoggedIn = true;

				//define option in personal interface
				//chat state recostruction
				setInputPersonal(10);

				return enable;
			}

			case 22:
			{
				std::string login;
				int n = server.readBuffer(0, login);
				std::cout <<"login reconstruction: \"" << login << "\"\n";

				setActiveUser(login);

				//define option in personal interface
				//write a message to "for all" collection
				setInputPersonal(11);

				//enter personalized interface
				LoggedIn = true;

				return enable;
			}

			case 23:
			{
				std::string login;
				int n = server.readBuffer(0, login);
				std::cout <<"login reconstruction: \"" << login << "\"\n";

				setActiveUser(login);

				//define option in personal interface
				//write a message to a personal collection
				setInputPersonal(12);

				//включение ентерфэйса второго уровня
				LoggedIn = true;

				return enable;
			}

			case 24:
			{
				std::string login;
				int n = server.readBuffer(0, login);
				std::cout <<"login reconstruction: \"" << login << "\"\n";

				setActiveUser(login);

				//define option in personal interface
				//read a message from "for all" collection
				setInputPersonal(13);

				//включение ентерфэйса второго уровня
				LoggedIn = true;

				return enable;
			}

			case 25:
			{
				std::string login;
				int n = server.readBuffer(0, login);
				std::cout <<"login reconstruction: \"" << login << "\"\n";

				setActiveUser(login);

				//define option in personal interface
				//read a message from a personal collection
				setInputPersonal(14);

				//включение ентерфэйса второго уровня
				LoggedIn = true;

				return enable;
			}
			
			case 26:
			{
				std::string login;
				int n = server.readBuffer(0, login);
				std::cout <<"login reconstruction: \"" << login << "\"\n";

				setActiveUser(login);

				//define option in personal interface
				//read a message from a personal collection
				setInputPersonal(15);

				//включение ентерфэйса второго уровня
				LoggedIn = true;

				return enable;
			}

			default: return enable;//если введено не 1, 2, 3, то выходим из чата
	
		}	
	
}

void Interface::nullActiveUser()
{
	std::cout << "active User set to null...\n";
	active_user = nullptr;	
}

void Interface::setActiveUser(const std::string &login)
{
	std::cout << "active User set to \"" << login << "\"...\n";
	active_user = p_chat->getUser(login);	
}

//вход в чат зарегистрированного пользователя по логину и паролю
int Interface::logIn(Chat& cht, const std::string &login, const std::string &passw)
{
	setActiveUser(login);//установка указателя на пользователя

	if (active_user->checkPass(passw))
	{
		std::cout << "You have successfully signed in.\n\n";		
		return 1;
	}
	else
	{	
		std::cout << "The password is incorrect.\n";
		return 0;
	}
		
}

//save the chat state when quit
/*
void Interface::quit(Chat& cht)
{
	enable = false;//отключение первого уровня интерфэйса
	cht.printToFile();//выводим массив общих сообщений в файл
	cht.writeUsersToFile();//выводим пользователей в файл
}
*/


//compose text for a message
void Interface::readTheInput(std::string& str)
{
	char ch[100];
	std::cin.get(ch, 100, '#');
	str += ch;
}

void Interface::setInputPersonal(int n)
{
	input_personal = n;
	std::cout << "input personal is " << n <<"\n";

}

//интерфэйс второго уровня
bool Interface::startChat(Chat& cht, ServerTCP &server)
{
	if (!LoggedIn)
	{
		return false;
	}
		
	std::cout << "Personal user's mode is working.\n";
	//show user's chatState in a server console
	cht.chatState(active_user);		

	//int input = server.readInput();	

	switch (input_personal)
	{
		/*
		10 -- recostruct state for user
		11 -- write a message for all users
		12 -- write personal message to a user
		13 -- read a message from "for all" collection
		14 -- read a personal message
		15 -- enter personal interface
		16 -- exit from startChat()
		
		*/

		//this is for reconstruction of a user's state of the chat
		case 10:
		{
			std::cout << "Reconstructing chat's state for the user\n";
			
			//receive nubmers for messages collection
			int msg_all = cht.countAllMessages();
			int msg_prs = active_user->countReceivedMsg();

			//change int in string constants
			std::string s_msg_all = std::to_string(msg_all);
			std::string s_msg_prs = std::to_string(msg_prs);
			std::cout << "Reconstruction: from all " << s_msg_all << " personal " << s_msg_prs << "\n";

			//send responce to the client
			server.clearBuffer();
			int start = server.writeBuffer(0, s_msg_all);
			server.writeBuffer(start, s_msg_prs);

			server.writeOutput();

			//leave the personal user's interface
			std::cout << "Exit personal user's mode\n";	
			LoggedIn = false;
			return false;						
		}

		//write a message for all users
		case 11: 
		{
			std::cout << "Have a message to all other users\n";
			std::string to = "all";

			//read the message text
			std::string inp_text;

			//geting a right position to read from a buffer
			std::string login = active_user->getLogin();
			int start = 1 + login.size();			

			//read a text of the message
			start = server.readBuffer(start, inp_text, '#');
			std::cout <<"text reconstruction: \"" << inp_text << "\"\n";
				
			//Read a name of a sender
			std::string from;
			server.readBuffer(start, from);
			std::cout <<"Sended by reconstruction: \"" << from << "\"\n";

			Message<std::string> fresh(to, from, inp_text);//создание сообщения

			//add new message and save a state of the chat
			cht.addMessageToAll(fresh);

			cht.printToFile();

			//leave the personal user's interface
			std::cout << "Exit personal user's mode\n";	
			LoggedIn = false;
			return false;			
		}
						

		  //write a message to a named user
		case 12: 
		{			
			//enter a recepients name
			std::cout << "Have a message to a particular users\n";			

			std::string from = (active_user->getName());
			
			std::string inp_text;

			//geting a right position to read from a buffer
			std::string login = active_user->getLogin();
			int start = 1 + login.size();

			//read a text of the message
			start = server.readBuffer(start, inp_text, '#');
			std::cout <<"Text reconstruction: \"" << inp_text << "\"\n";
				
			//Read a name of a sender
			std::string to;	
			server.readBuffer(start, to);
			std::cout <<"Recepient by reconstruction: \"" << to << "\"\n";			

			Message<std::string> fresh(to, from, inp_text);
		
		
			//find a sertain user and add a message to his personal collection
			User* recipient_user = cht.getUserByName(to);//pointer to a receiver of the message
			if (recipient_user)
			{
				recipient_user->addMessageToMyCollection(fresh);
				std::cout << "Added\n";
			}
			else
			{
				std::cout << "Something went wrong.\n";
			}
				
			//save new chat's state
			cht.writeUsersToFile();			

			//leave the personal user's interface
			std::cout << "Exit personal user's mode\n";	
			LoggedIn = false;
			return false;
		}

		  //read a message from a collection to all users
		case 13:
		{
			std::cout << "Reading a massage from collection to all\n";
			std::string mess_num;

			//geting a right position to read from a buffer
			std::string login = active_user->getLogin();
			int start = 1 + login.size();
			std::cout << "buff start " << start <<"\n";

			//read from a buffer
			server.readBuffer(start, mess_num);
			std::cout <<"constructed nubmer of a message by string: \"" << mess_num << "\"\n";

			int n_mess_num = server.transformInNumber(mess_num);
			
			server.clearBuffer();
			//processed an exeption if a number of the message exeeds the range
			try {
				cht.readMsgAll(n_mess_num, server);
			}
			catch (std::exception& e)
			{
				std::cout << e.what();
			}			

			server.writeOutput();
			
			//leave the personal user's interface
			std::cout << "Exit personal user's mode\n";	
			LoggedIn = false;
			return false;			
		}

		//read a message from a personal collection
		case 14:
		{
			std::cout << "Reading a massage from personal collection\n";
			std::string mess_num;

			//geting a right position to read from a buffer
			std::string login = active_user->getLogin();
			int start = 1 + login.size();
			std::cout << "buff start " << start <<"\n";

			//read from a buffer
			server.readBuffer(start, mess_num);
			std::cout <<"constructed nubmer of a message by string: \"" << mess_num << "\"\n";

			int n_mess_num = server.transformInNumber(mess_num);
			
			server.clearBuffer();

			//processed an exeption if a number of the message exeeds the range
			try 
			{
				active_user->readPersonalMsg(n_mess_num, server);
			}

			catch (std::exception& e)
			{
				std::cout << e.what();
			}

			server.writeOutput();
		
			//leave the personal user's interface
			std::cout << "Exit personal user's mode\n";	
			LoggedIn = false;
			return false;
		}

	//personal interface to change name of password
	case 15:
	{
		std::cout << "Enter personal menu for pass and name changing...\n";
		bool in_personal = true;//validate to stay in personal changing menu
		while (in_personal)
		{	
			//geting a right position to read from a buffer
			std::string login = active_user->getLogin();
			int start = 4 + login.size();

			int input = server.atBuff(start) - '0';
			std::cout << "Have an input " << input << "\n";

			switch (input)
			{
				case 1://change users name
				{		
					std::cout << "Changing user's name...\n";
					std::string new_name;
					start -= 1;
					server.readBuffer(start, new_name);

					active_user->setName(new_name);
					std::cout << "Your new name is \"" << active_user->getName() << "\".\n";
					cht.writeUsersToFile();
					in_personal = false;
					break;

				
				}

				case 2://change users password
				{
					std::cout << "Changing user's password...\n";
					std::string new_pass;					
					start -= 1;
					server.readBuffer(start, new_pass);

					active_user->setPass(new_pass);
					std::cout << "Your password is changed\n";
					cht.writeUsersToFile();
					in_personal = false;	
					break;		

				}

				case 3://quit personal changing mode
				{
					std::cout << "Exiting personal changing mode...\n";
					in_personal = false;
					break;
				}

				default://if input is not 1, 2, 3, quit personal changing mode
				{
					in_personal = false;
					break;
				}

			}
		}


		//leave the personal user's interface
		std::cout << "Exit personal user's mode\n";	
		LoggedIn = false;
		return false;
	}
	
	default: //если введено целое не от 1 до 6, то тоже выход в первый уровень интерфэйса
		return false;
	}

}


