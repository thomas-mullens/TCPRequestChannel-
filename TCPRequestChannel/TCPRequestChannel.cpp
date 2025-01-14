#include "TCPRequestChannel.h"
#include <iostream>
#include <string>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <sys/uio.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <fstream>

using namespace std;


TCPRequestChannel::TCPRequestChannel (const std::string _ip_address, const std::string _port_no) {
    if (_ip_address == "") { // for the server
        // set up variables
        struct sockaddr_in server;
        int server_sock, bind_stat, listen_stat;

        // socket - make socket - socket (int domain, int type, int protocal)
        // AF_INET = IPv4
        // SOCK_STREAM = TCP
        // Normally only a single protocol exists to support a paticular socket type
        // within a given protocol family, in which case protocal can be specified as
        // 0.
        this->sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if(this->sockfd < 0) {
            perror("Failed to make socket");
            exit(1);
        }

        // protocal necessary machine info for sockaddr_in
        // address family, IPv4
        // IPv4 address, use current IPv4 address (INADDR_ANY)
        // connection port
        // convert short from host byte order to network byte order
        server.sin_family = AF_INET;
        server.sin_addr.s_addr = INADDR_ANY;
        server.sin_port = htons(stoi(_port_no));

        // bind -assisgn address to socket - bind(int sockfd, const struck sockaddr *addr, socklen_t addrlen)
        bind_stat = bind(this->sockfd, (sockaddr *)&server, sizeof(server));

        // listen - listen for client - listen(int sockfd, int backlog)
        listen_stat = listen(this->sockfd, 5);

        // accept - accept connection
        // written in a seperate method

    } else { // for the client
        // set up variable
        struct sockaddr_in server_info;
        int client_sock, connect_stat;

        // socket - make socket - socket (int domain, int type, )
        this->sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if(this->sockfd < 0) {
            perror("Failed to make socket");
            exit(1);
        }
        // generate server's info based on parameters
        // address family, IPv4
        // connection port 
        // convert short from host byte order to network byte
        // convert ip address c-string to binary respentation for sin_addr
        server_info.sin_family = AF_INET;
        server_info.sin_port = htons(stoi(_port_no));

        inet_pton(AF_INET, _ip_address.c_str(), &server_info.sin_addr);

        // connect - connect to listening socket - connect(int sockfd, struck sockaddr *addr, socklen_t addrlen)
        connect_stat = connect(this->sockfd, (sockaddr *)&server_info, sizeof(server_info));
    }
}

TCPRequestChannel::TCPRequestChannel (int _sockfd) {

    // assign an existing socket to object; socket file descriptor
    this->sockfd = _sockfd;
}

TCPRequestChannel::~TCPRequestChannel () {

    // close socket - close(this->sockfd)
    close(this->sockfd);
}

int TCPRequestChannel::accept_conn () {

    // accept - accept connection
    // socket file descriptor for accepted connection
    sockaddr_in newSockAddr;
    socklen_t newSockAddrSize = sizeof(newSockAddr);
    // accept connection - accept(int sockfd, struck sockaddr *addr, socklen_t *addrlen)
    int acceptedSocket = accept(this->sockfd, (sockaddr *)&newSockAddr, &newSockAddrSize);
    if(acceptedSocket < 0){
        perror("Failed to accept");
        return -1;
    }
    cout << "Connection Accepted" << endl;
    // reutrn socket file descriptor
    return acceptedSocket;
}

int TCPRequestChannel::cread (void* msgbuf, int msgsize) {

    ssize_t no_bytes = read(this->sockfd, msgbuf, msgsize); // number of bytes to read
    // read from socket - read(int fd, void *buf, size_t count)
    if(no_bytes < 0){
        perror("Failed to read");
        return -1;
    }
    // return number of bytes read
    return no_bytes;
}

int TCPRequestChannel::cwrite (void* msgbuf, int msgsize) {

    ssize_t no_bytes = write(this->sockfd, msgbuf, msgsize); // number of bytes to write
    // write to socket - write(int fd, const void *buf, size_t count)
    if(no_bytes < 0){
        perror("Failed to write");
        return -1;
    }
    // return number of bytes written
    return no_bytes;
}
