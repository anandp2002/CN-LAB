#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

int main()
{
  char buff[100];
  int k;
  struct sockaddr_in client;
  socklen_t len;
  
  int sock_desc = socket(AF_INET,SOCK_STREAM,0); 
  if(sock_desc==-1)
    printf("Error in socket creation");
	
  client.sin_family=AF_INET;
  client.sin_addr.s_addr=INADDR_ANY;
  client.sin_port=3003;
	
  k=connect(sock_desc,(struct sockaddr*)&client,sizeof(client));
  if(k==-1)
    printf("Error in connecting");
	
  printf("Enter the data to be send : ");
  fgets(buff,100,stdin);
  k=send(sock_desc,buff,100,0);
  if(k==-1)
    printf("Error in sending");
	
  k=recv(sock_desc,buff,100,0);
  if(k==-1)
    printf("Error in receiving");
    
  printf("Message got from server is : %s",buff);
  return 0;
}

