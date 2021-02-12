#include <stdio.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

#define PORT_NUMBER 8090

int main(int argc, char *argv[])
{
  int s, aux;
  char bufferC[60], bufferS[1500];
  struct sockaddr_in server;
  
  if((s = socket(AF_INET, SOCK_STREAM, 0)) == -1)
  {
     perror("\nError al abrir el socket");
     exit(-1);
  } 
 
  printf("Socket asignado = %d\n", s);

  server.sin_family=AF_INET;
  server.sin_port=htons(PORT_NUMBER);
  server.sin_addr.s_addr = INADDR_ANY;//inet_addr("8.25.100.170");

  if((connect(s,(struct sockaddr*)&server,sizeof(struct sockaddr))) == -1)
  {
    perror("Error en la conexion\n");
    exit(-1);
  }

  fgets(bufferC, sizeof(bufferC), stdin);
  
  if((aux=send(s,bufferC,strlen(bufferC)+1,0)) == -1)
    printf("Error al enviar\n");
  else
  {
    printf("Se enviaran %d bytes\n", aux);
    if(recv(s,bufferS,sizeof(bufferS),0) == -1)
      printf("Error al recivir\n");
    else
      printf("El servidor dice: %s \n\n",bufferS);
  }

  close(s);
}