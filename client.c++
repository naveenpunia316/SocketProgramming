#include <iostream>     //Used for input output operations
#include <sys/socket.h> //Contains socket structures and functions , socket families are defined here
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h> //Used for memory allocations , conversions
#include <unistd.h>
using namespace std;

#define PORT 8316
#define HOST_ADDR "192.168.1.170"

int main()
{
    // to create a socket use socket and bind function
    int sockFd = socket(AF_INET, SOCK_STREAM, 0);
    /*
        socket file descriptot is used to refer the socket

        arguments :
            first argument specifies the address family
                AF_INET for Ipv4
                AF_INET6 for Ipv6
                AF_UNIX for local communication

            second argument is specified by type of socket :
                stream socket (TCP)
                datagram socket (UDP)

            third argument specifies the protocol :

    */

    if (sockFd < 0)
    {
        cout << "CREATE SOCK FAILED";
        return -1;
    }

    cout << "SERVER CONNECTED\n";
    struct sockaddr_in address = {0};               // used to add structure address
    address.sin_family = AF_INET;                   // Initializing address family
    address.sin_port = htons(PORT);                 // htons convert Ip port number into host byte order(liitle endian order to netwrok byte order(Big endian order)
    address.sin_addr.s_addr = inet_addr(HOST_ADDR); // This funnction converts the string provided into ip address
                                                    // Connect --> it will connect the socket with file descriptor socketId with to the address specified by addr

    int connectionFlag = connect(sockFd, (struct sockaddr *)&address, sizeof(struct sockaddr_in));
    if (connectionFlag < 0)
    {
        cout << "CONNECITONERR";
        return -1;
    }
    char message[1000];
    cout << "Enter the message to be sent to the " << HOST_ADDR << ":" << PORT << " : ";
    cin >> message;
    int sentBytes = send(sockFd, message, strlen(message), 0);
    if (sentBytes < 0)
    {
        cout << "MESSAGE NOT SENT";
        return -1;
    }
    cout << "\n MESSAGE"
         << "(" << sentBytes << ")"
         << " SENT TO " << HOST_ADDR << " : " << PORT << "\n ";

    char response[1000];

    int recvBytes = read(sockFd, response, 1000);
    if (recvBytes < 0)
    {
        cout << "\n ERR REPLY ";
        return -1;
    }
    cout << "\nServer response : " << response << "\n";
    shutdown(sockFd, 2);
    return 0;
};