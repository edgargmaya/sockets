#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

#define PORT_NUMBER 8090

int main(int argc, char *argv[])
{
  int s,s2, aux,tc;
  unsigned char buffer[60], buffer2[1500];
  struct sockaddr_in cliente, servidor;

  if((s = socket(AF_INET, SOCK_STREAM, 0)) == -1)
  {
     perror("\nError al abrir el socket");
     exit(-1);
  }
  
  printf("Socket asignado = %d\n", s);
  
  servidor.sin_family=AF_INET;
  servidor.sin_port=htons(PORT_NUMBER);
  servidor.sin_addr.s_addr =  INADDR_ANY;//inet_addr("8.25.100.170");
  bzero(&(servidor.sin_zero),8); 
  
  if(bind(s,(struct sockaddr *)&servidor, sizeof(servidor)) == -1)
  {
    printf("Error de bind\n");
    exit(-1);
  }
  
   if(listen(s,10) == -1)
   { 
      printf("error en listen\n");
      exit(-1);
   }
   
  printf("Escuchando: \n\n");

  tc=sizeof(cliente);
  if ((s2 = accept(s,(struct sockaddr *)&cliente,&tc))==-1)
  {
    printf("error en accept()\n");
    exit(-1);
  }

  recv(s2,buffer2,sizeof(buffer2),0);

  printf("El cliente Dijo: %s \n",buffer2);

  fgets(buffer, sizeof(buffer), stdin);
      
  send(s2,buffer,sizeof(buffer),0);

  close(s2);
}