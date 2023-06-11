#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netdb.h>
int main()
{
  struct sockaddr_in server,client;
    
  int sock_desc = socket(AF_INET,SOCK_DGRAM,0);
  
  if(sock_desc == -1)
    printf("Error in socket();"); 
    
  server.sin_family=AF_INET;
  server.sin_addr.s_addr=INADDR_ANY;
  server.sin_port=3000;
	
  int k = bind(sock_desc,(struct sockaddr*)&server,sizeof(server));
  if (k==-1)
    printf("\nError in bind");
	
  char buffer[100];
  socklen_t server_len=sizeof(server);
  
  printf("Server waiting....\n");
  
  k = recvfrom(sock_desc,buffer,100,0,(struct sockaddr*)&server,&server_len);
  if(k == -1)
    printf("Error in recvfrom()!");
  printf("Datagram got from server is %s",buffer);
  
  return 0;
}

