#include <iostream>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <cstdio>
using namespace std;

#define PORT 8316
#define IP "192.168.1.170"
int main()
{
    int sockFd, portNo, lisId;
    char buffer[1000];

    sockFd = socket(AF_INET, SOCK_STREAM, 0);
    // first argument is for address family(AF_INET FOR IPV4)
    // second argument is for type of socket (SOCK_STREAM FOR THE TCP SOCKET)
    // third argument is for the type of protocol (0 for the default protocol for the given AF and TYPE of socket)

    if (sockFd < 0)
    {
        cout << "ERROR OPENING SOCKET";
        return 1;
    }

    struct sockaddr_in address1;
    socklen_t addressLen = sizeof(address1);
    address1.sin_family = AF_INET;
    address1.sin_port = htons(PORT);
    address1.sin_addr.s_addr = inet_addr(IP);

    char message[200] = "Hello from server side";
    char reply[1000] = {0};

    // bind socket with particular port and address
    int Bind = bind(sockFd, (struct sockaddr *)&address1, sizeof(address1));
    if (bind < 0)
    {
        cout << "BIND ERR \n aborting....";
        return 1;
    }
    cout << "successFully Bind on port " << PORT << " and " << IP << endl;

    lisId = listen(sockFd, 1000);

    if (lisId < 0)
    {
        cout << "LISTEN ERR";
        return 1;
    }

    struct sockaddr_in clientaddr = {0};
    socklen_t clientAddrLen = 0;
    int clientFd = accept(sockFd, (struct sockaddr *)&clientaddr, &clientAddrLen);
    /*
    all read-write operations will be done on this descriptor to communicate with the client.
    The returned descriptor is assumed to be a client socket descriptor and
    */

    if (clientFd < 0)
    {
        cout << "Client's request not accepted" << endl;
        return -1;
    }

    cout << "Connected to client : "
         << static_cast<int>(clientaddr.sin_port) << ":"
         << static_cast<int>(clientaddr.sin_addr.s_addr) << endl;

    int requestLength = read(clientFd, buffer, 1000);
    if(requestLength < 0) {
        cout << "ERR RECV\n";
        return -1;
    }
    cout << "Message Recieved : " << buffer << "(" << requestLength << ")\n";
    char response[1000];
    cout << "Enter the response for the client : ";
    cin >> response;

    send(clientFd, response, strlen(response), 0);
    shutdown(clientFd, 2);
    /*
        0 − indicates that receiving is not allowed,
        1 − indicates that sending is not allowed, and
        2 − indicates that both sending and receiving are not allowed. When how is set to 2, it's the same thing as close().
    */
    return 0;
}