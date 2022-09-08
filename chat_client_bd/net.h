#pragma once
#include <iostream>
#include <unistd.h>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cmath>

class ClientTCP
{
    public:

        ClientTCP();
        ClientTCP(std::string &ip);
        ~ClientTCP() {}
        
        void clientConnect();
        void clientClose() {close(sockd);}

        void readInput();
        int readBuffer(int start, std::string &outcome, char s = '\0');
        char atBuff(int n);
        int writeBuffer(int start, const std::string &outcome, char s = '\0');
        void clearBuffer();
        void writeOutput();

        int transformInNumber(std::string& str_num);
        void showBuff(const int n);

    private:
        const static int BUF_SIZE = 1024;
        const static int PORT = 7777;
        
        int sockd, connection;
        int buff_shift;
        struct sockaddr_in serveraddress, client;
        char buff[BUF_SIZE];
        socklen_t length;
        
};



