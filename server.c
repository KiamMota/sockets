#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>


void tratarCliente(int clientfd)
{
  printf("cliente conectado!\n");

}
int main()
{
  // inicia um endereço usando a estrutura padrão de C;
  struct sockaddr_in sock_address;
  struct sockaddr_in client_addr;
  // define a porta 7192;
  const int port = 7192;
  bzero(&sock_address, sizeof(sock_address));
  // insere a família do socket, no caso é a IPv4
  sock_address.sin_family = AF_INET;
  // explicita o endereço na qual aceita conexões, na qual: todos;
  sock_address.sin_addr.s_addr = htonl(INADDR_ANY);
  // diz a porta na qual ouvir
  sock_address.sin_port = htons(port);
  // abre o descritor de arquivo do socket;
  int sock = socket(AF_INET, SOCK_STREAM, 0);
  // vincula o endereço ao descritor de arquiv do socket;
  if(bind(sock, (const struct sockaddr*)&sock_address, sizeof(sock_address)) != 0)
  {
    printf("bind falhou!\n");
    exit(0);
  }
  printf("fazendo bind...\n");

  // isso aqui é necessario porque o tamanho do cliente não pode ser unsigned int, como retornado pelo sizeof
  socklen_t client_size = sizeof(client_addr);
  // cria uma variável pra guardar o valor do descritor do cliente;
  int clientfd;
  // começa a ouvir o socket;
  if(listen(sock, 5) != 0)
  {
    printf("listen failed...\n");
    exit(0);
  }
  printf("ouvindo...\n");

  printf("ouvindo em %d\n", ntohs(sock_address.sin_port));
  printf("no endereço: %s\n", inet_ntoa(sock_address.sin_addr));

  fflush(stdout);

  // aceita conexão do cliente, e adiciona as informações do cliente no descritor;
  clientfd = accept(sock, (struct sockaddr*)&client_addr, &client_size); 
  printf("connection accepted!");
  fflush(stdout); 
  ssize_t valread;
  char buffer[1024];
  while ((valread = read(clientfd, buffer, 1024))) {
    printf("client: %s", buffer);
    memset(buffer, 0, sizeof(buffer));
  
  }


  close(clientfd);
  // fecha o fd do servidor;
  close(sock);
}
