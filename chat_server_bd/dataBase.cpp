#include "dataBase.h"

//initializing the descriptor mysql on object creation
DataBase::DataBase()
{
    mysql = mysql_init(NULL);
    if(mysql == NULL)
    {
        std::cout << "Can't create mysql descriptor.\n";
    }
}

//release the descriptor on object destruction
DataBase::~DataBase()
{
    mysql_close(mysql);
}    

MYSQL* DataBase::getDescriptorMYSQL()
{
    return mysql;
}  
    
// seting pirvate variable
void DataBase::setHost(const std::string& input)
{
    host = input.c_str();
    std::cout << "HOst is: " << host << "\n";
}
void DataBase::setUser(const std::string& input)
{
    user = input.c_str();
    std::cout << "User is: " << user << "\n";
}
void DataBase::setPasswd(const std::string& input)
{
    passwd = input.c_str();
    std::cout << "Pass is: " << passwd << "\n";
}
void DataBase::setDBname(const std::string& input)
{
    dbname = input.c_str();
    std::cout << "Data base name is: " << dbname << "\n";
}
void DataBase::setSocket(const std::string& input)
{
    socket = input.c_str();
}
void DataBase::setPort(const unsigned int input)
{
    port = input;
}
void DataBase::setFlag(const unsigned int input)
{
    flag = input;
}

//setting all variable via user interaction
void DataBase::setAllParam()
{/**/
    //if default parameters are not right then adjust
    std::cout << "Enter a hostame for database (defaul is \'localhost\'): ";
    std::string host_input;
    std::cin >> host_input;
    if(host_input.empty())
    {
        host_input = "localhost";
    }
    setHost(host_input);

    std::cout << "Enter a user's name for database: ";
    std::string name_input;
    std::cin >> name_input;
    if(name_input.empty())
    {
        name_input = "root";
    }
    setUser(name_input);
    
    std::cout << "Enter a user's password for database: ";
    std::string pass_input;
    std::cin >> pass_input;
    if(pass_input.empty())
    {
        pass_input = "root";
    }
    setPasswd(pass_input);
 /**/
    std::cout << "Enter a database name: ";
    std::string db_input;
    std::cin >> db_input;
    if(db_input.empty())
    {
        db_input = "Chat_data_base";
    }
    setDBname(db_input);

    //additional adjustment
    std::cout << "Do you need to adjust \"soket\", \"port\" and \"flag\" parameters: y/n? ";
    char ch;
    while (!(std::cin >> ch))
	{
		std::cin.clear();
		while (std::cin.get() != '\n')
			continue;
		std::cout << "Input shood be a letter \"y\" or \"n\".\n";
	}
    if(ch == 'y' || ch == 'Y')
    {
        std::cout << "Enter a socket name: ";
        std::string socket_input;
        std::cin >> socket_input;        
        setSocket(socket_input);

        std::cout << "Enter a port number: ";
        unsigned int num_input = 0;
        std::cin >> num_input;
        setPort(num_input);

        std::cout << "Enter a client flag: ";
        std::cin >> num_input;
        setFlag(num_input);
    }
        
}

//connection to a defined database
bool DataBase::connectToDataBase()
{
    if(!mysql_real_connect(mysql, host, user, passwd, dbname, port, socket, flag))
    {
        std::cout << "Can not connect to database: " << mysql_error(mysql) << std::endl;
        return false;
    }
    else
    {
        std::cout << "Successfully connected to the database." << std::endl;
        mysql_set_character_set(mysql, "utf8mb4");
        return true;
    }
}

//create a table for users if there is not one
void DataBase::createTheUsersTable()
{
    const std::string createTheUsers =
     "CREATE TABLE IF NOT EXISTS users_table(id INT AUTO_INCREMENT NOT NULL,\
                                            login VARCHAR(20) UNIQUE,\
                                            name VARCHAR(20),\
                                            pass VARCHAR(20),\
                                            PRIMARY KEY (id))";

    mysql_query(mysql, createTheUsers.c_str());
}

//create a table for messages collection "for all users" if there is not one
void DataBase::createTheAllMessagesTable()
{
    const std::string createAllMessages =
     "CREATE TABLE IF NOT EXISTS messages_to_all_table(id INT AUTO_INCREMENT NOT NULL,\
                                            sender VARCHAR(20),\
                                            time DATETIME DEFAULT now(),\
                                            text VARCHAR(110),\
                                            PRIMARY KEY (id))";

    mysql_query(mysql, createAllMessages.c_str());
}

//create a table for messages collection "for a defined user" if there is not one
void DataBase::createThePerosonalMessagesTable()
{
    const std::string createThePersonalMessages = 
    "CREATE TABLE IF NOT EXISTS messages_to_person_table(id INT AUTO_INCREMENT NOT NULL,\
                                            sender VARCHAR(20),\
                                            recepient VARCHAR(20),\
                                            time DATETIME DEFAULT now(),\
                                            text VARCHAR(110),\
                                            PRIMARY KEY (id))";
    mysql_query(mysql, createThePersonalMessages.c_str());
}

//Create tables if there are not any table yet
void DataBase::createDataBase()
{
    createTheUsersTable();
    createTheAllMessagesTable();
    createThePerosonalMessagesTable();
}