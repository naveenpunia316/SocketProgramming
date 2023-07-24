#include <iostream>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <cstdio>
using namespace std;

int main()
{
  // Creating socket
  int socketId;
  socketId = socket(AF_INET, SOCK_STREAM, 0);
  if (socketId < 0)
  {
    cout << "socket Not creted";
    return -1;
  }
  cout << "File Descriptor : " << socketId << endl;
  struct sockaddr_in address1;
  socklen_t addressLen = sizeof(address1);
  address1.sin_family = AF_INET;
  address1.sin_port = htons(8316);
  address1.sin_addr.s_addr = inet_addr("192.168.1.170");

  char message[200] = "Hello from server side";
  char reply[1000] = {0};

  // bind socket with particular port and address
  int Bind = bind(socketId, (struct sockaddr *)&address1, sizeof(address1));

  if (bind < 0)
  {
    cout << "Not Bind";
    return -1;
  }
  cout << "successFully Bind on port 8080 and ip 192.168.1.161" << endl;
  // Listen multiple requests and create a queue of req
  int retVal = listen(socketId, 4);
  if (retVal < 0)
  {
    cout << "Not listen";
    return -1;
  }
  cout << "Waiting to accept new connection" << endl;

  struct sockaddr_in clientaddr = {0};
  socklen_t clientAddrLen = 0;
  int newSocket = accept(socketId, (struct sockaddr *)&clientaddr, &clientAddrLen);
  if (newSocket < 0)
  {
    perror("accept");
    exit(EXIT_FAILURE);
    cout << "Client request not accepted" << endl;

    return -1;
  }
  //************************Checking port Number and ip address of client****************
  cout << "Client address" << endl
       << static_cast<int>(clientaddr.sin_port) << endl
       << static_cast<int>(clientaddr.sin_addr.s_addr) << endl;

  //***********************************************************************
  cout << "New Connection Accepted for FD  " << newSocket << endl;

  int size = read(newSocket, reply, 1000);
  cout << "message received to server of length : " << size << endl;
  cout << reply << endl;
  send(newSocket, message, strlen(message), 0);
  close(newSocket);
  return 0;
}
