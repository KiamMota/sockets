#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>


int main()
{
  struct sockaddr_in addr;
  int clisock = socket(AF_INET, SOCK_STREAM, 0);
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  addr.sin_port = htons(7192);

  if(connect(clisock, (const struct sockaddr*)&addr, sizeof(addr)) == 0)
  {
    printf("connected into server");
  }
  

}
