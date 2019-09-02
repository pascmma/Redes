#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <thread>
#include <string>

using namespace std;

bool termino = false;

void read_thread(int _socketCliente, string _buffer)
{
  int n;
  char buffer[1025];
  strcpy(buffer,_buffer.c_str());
  string str;
  do
  {
    n=read(_socketCliente,buffer,1024);
    buffer[n]='\0';
    cout<<"cliente : "<<buffer<<endl;
    str = buffer;
    if(str.compare("END")==0)
    {
      termino = true;
    }
 }while(!termino);
}
int main()
{
  struct sockaddr_in stSockAddr;
  int SocketFD = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
  char buffer[1025];
  int n;
///////////////////////////////////////
  memset(&stSockAddr, 0, sizeof(struct sockaddr_in));

  stSockAddr.sin_family = AF_INET;
  stSockAddr.sin_port = htons(45500);
  stSockAddr.sin_addr.s_addr = INADDR_ANY;

  for (;;)
  {
    int ConnectClient = accept(SocketFD,NULL,NULL);
  //  read(ConnectClient,buffer,1);//socket,mensaje,cuanto leer del mensaje
  /*  if(buffer[0]==1)
    {
      n=read(ConnectClient,buffer,2);
      buffer[n]='\0';
      int tamano = atoi(buffer);
*/
      n = read(ConnectClient,buffer,1024);
      buffer[n] = '\0';
      std::thread(read_thread,ConnectClient,buffer).detach();
      shutdown(ConnectClient,SHUT_RDWR);
      close(ConnectClient);


  }


}
