#include<iostream>//Used for input output operations
#include<sys/socket.h>//Contains socket structures and functions , socket families are defined here
#include<string.h>
#include<arpa/inet.h>
#include<stdlib.h>//Used for memory allocations , conversions
#include<unistd.h>
using namespace std;

int main()
{
  // //Creating socket(socket connection)
  int socketId;//This var contains socket descriptor
  socketId = socket(AF_INET , SOCK_STREAM , 0);//This will return 0 or -1  which is file descriptor   
  if(socketId < 0)
  {
    cout << "Failed to open new file descriptor\n";//May be due to connectivity probelosm
    return 0;
  }

  //Create and initialize struct addr
  cout << "Successfuuly created socket descriptor" << endl;
  cout << "socket Descriptor : " << socketId << endl;
  struct sockaddr_in address = {0};//used to add structure address
  address.sin_family = AF_INET;//Initializing address family
  address.sin_port = htons(8316);//htons convert Ip port number into host byte order(liitle endian order to netwrok byte order(Big endian order)
  address.sin_addr.s_addr = inet_addr("192.168.1.170");//This funnction converts the string provided into ip address
  //Connect --> it will connect the socket with file descriptor socketId with to the address specified by addr

  char  message[200];
  cout << "Enter the message : ";
  cin >> message;
  char reply[1000] = {0};
  
  int retVal = connect(socketId , (struct sockaddr*)& address , sizeof(struct sockaddr_in));
  if(retVal < 0)
  {
    cout << "Failed to connect" << endl;
    return -1;
  }
  //Send call
  cout << strlen(message) << endl;
  send(socketId , message , 22 , 0);
  cout << "Message sent to server" << endl;
  //read call
  int size;
  size = read(socketId , reply , 1000);
  cout << "Reply : " <<  reply <<  endl ;
  cout << "Size of Reply : " << size << endl;
  close(socketId);
  return 0;

}
  

