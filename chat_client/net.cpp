#include "net.h"

ClientTCP::ClientTCP()
{    
    // adjust structure for the server    
    serveraddress.sin_addr.s_addr = inet_addr("127.0.0.1");
    serveraddress.sin_port = htons(PORT);
    serveraddress.sin_family = AF_INET;

    buff_shift = 0;
}

ClientTCP::ClientTCP(std::string &ip)
{     
    // adjust structure for the server
    const char *addr = ip.c_str();
    serveraddress.sin_addr.s_addr = inet_addr(addr);
    serveraddress.sin_port = htons(PORT);
    serveraddress.sin_family = AF_INET;

    buff_shift = 0;    
}

void ClientTCP::clientConnect()
{
    // create a socket and check the success
    sockd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockd < 0)
    {
        std::cout << "Socket creation failed\n";
        exit(1);
    }

    connection = connect(sockd, (struct sockaddr *)&serveraddress, sizeof(serveraddress));
    if (connection < 0)
    {
        std::cout << "Failed connect to the server\n";
        exit(1);
    }

}

void ClientTCP::readInput()
{
    //put server to listen and accept a message from a client
    int bytes_read = read(sockd, buff, BUF_SIZE);
    //std::cout << "received " << bytes_read << " bytes.\n";
}

int ClientTCP::readBuffer(int start,  std::string &outcome, char s)
{
    while(buff[start+buff_shift] != s)
    {		
        outcome += buff[start+buff_shift];
        ++start;
    }
    
    return ++start;
}

char ClientTCP::atBuff(int n)
{
    return buff[n];
}

int ClientTCP::writeBuffer(int start, const std::string &outcome, char s)
{
    std::copy(outcome.begin(),outcome.end(),buff + start);
	start += outcome.size();
	buff[start] = s;
	++start;

    return start;
}

void ClientTCP::clearBuffer()
{
    bzero(buff, BUF_SIZE);

}

void ClientTCP::writeOutput()
{
    int sent_bytes = send(sockd, buff, BUF_SIZE, 0);
    //std::cout << "Sent " << sent_bytes << " bytes.\n";
}

int ClientTCP::transformInNumber(std::string& str_num)
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

void ClientTCP::showBuff(const int n)
{
    for(int k = 0; k < n; ++k)
    {
        std::cout << "symbol " << k << " is " << buff[k] << "\n";
    }
}