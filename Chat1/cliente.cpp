#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <thread>

using namespace std;

bool termino = false;

void leer(int _socketCli)
{
  int n;
  char buffer[1025];
  string _buffer;
  do
  {
    n = read(_socketCli,buffer,1024);
    buffer[n]='\0';
    cout<<"cliente : "<< buffer << endl;
    _buffer = buffer;
    if(_buffer.compare("END")==0)
    {
      termino = true;
    }
  } while(!termino);
}

void escribir(int _socketCli)
{
  int n;
  char buffer[1025];
  string _buffer;
  do
  {
    cout<<"MSG : ";
    getline(cin,_buffer);
    n = write(_socketCli,_buffer.c_str(),_buffer.size());
    if(_buffer.compare("END")==0)
    {
      termino = true;
    }
  } while(!termino);
}



int main()
{
  struct sockaddr_in stSockAddr;
  int SocketFD = socket(PF_INET,SOCK_STREAM,IPPROTO_TCP);
  int n;
  int Res;

  memset(&stSockAddr,0,sizeof(struct sockaddr_in));

  stSockAddr.sin_family = AF_INET;
  stSockAddr.sin_port = htons(45500);
  Res = inet_pton(AF_INET,"127.0.0.1",&stSockAddr.sin_addr);


  std::thread(leer,SocketFD).detach();
  std::thread(escribir,SocketFD).detach();

  while(!termino){};

  shutdown(SocketFD,SHUT_RDWR);
  close(SocketFD);
  return 0;












}
