#include "net.h"

// constructor for the server
ServerTCP::ServerTCP()
{
    //create a socket and check the success
    sockd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockd < 0)
    {
        std::cout << "Socket creation failed\n";
        exit(1);
    }

    // adjust structure for the server
    serveraddress.sin_addr.s_addr = htonl(INADDR_ANY);
    serveraddress.sin_port = htons(PORT);
    serveraddress.sin_family = AF_INET;

    //bind the socket
    bind_status = bind(sockd, (struct sockaddr *)&serveraddress, sizeof(serveraddress));
    if(bind_status < 0)
    {
        std::cout << "socket binding failed\n";
        exit(1);
    }

    //buff_shift is equal for the action descriptor lenght and plus '\0' symbol
    buff_shift = 3;
    
}

void ServerTCP::serverConnect()
{
	connection_status = listen(sockd, 10);

    if(connection_status < 0)
    {
        std::cout << "Unable to listen to a new connection.\n";
        exit(1);
    }
    else
    {
        std::cout << "Server is listening for a client connection...\n";
    }

	length = sizeof(client);
	connection = accept(sockd, (struct sockaddr *)&client, &length);

	//return connection;
}

int ServerTCP::readInput()
{
    //put server to listen and accept a message from a client
    serverConnect();

    //read a message
    bzero(buff, BUF_SIZE);
	int read_bytes = read(connection, buff, BUF_SIZE);
	std::cout << "reseived " << read_bytes <<" bytes \n";		

    //extract descriptor for a server operation
	int input = (buff[0]-'0')*10 + (buff[1] - '0');
	std::cout << "Have intput " << input << std::endl; 

    //return descriptor
    return input;
}

int ServerTCP::readBuffer(int start,  std::string &outcome, char s)
{
    while(buff[start+buff_shift] != s)
    {		
        outcome += buff[start+buff_shift];
        ++start;
    }
    
    return ++start;
}

char ServerTCP::atBuff(int n)
{
    return buff[n];
}

int ServerTCP::writeBuffer(int start, std::string &outcome, char s)
{
    std::copy(outcome.begin(),outcome.end(),buff + start);
	start += outcome.size();
	buff[start] = s;
	++start;

    return start;
}

void ServerTCP::clearBuffer()
{
    bzero(buff, BUF_SIZE);

}

void ServerTCP::writeOutput()
{
    int sent_bytes = write(connection, buff, sizeof(buff));
    std::cout << "Sent " << sent_bytes << " bytes.\n";
}

int ServerTCP::transformInNumber(std::string& str_num)
{
	int mess_num_letters = str_num.size();
	int n_mess_num = 0;
	int k = 0;
	while (k < mess_num_letters)
	{
		n_mess_num += (str_num[k]-'0')*pow(10, --mess_num_letters);
	}
	std::cout <<"constructed nubmer of a message by int: \"" << n_mess_num << "\"\n";

	return n_mess_num;
}

void ServerTCP::showBuff(const int n)
{
    for(int k = 0; k < n; ++k)
    {
        std::cout << "symbol " << k << " is " << buff[k] << "\n";
    }
}
