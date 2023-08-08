#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>

void main()
{
    int c_sd, k;
    char buff[100];
    struct sockaddr_in client;
    c_sd = socket(AF_INET, SOCK_STREAM, 0);

    client.sin_family = AF_INET;
    client.sin_port = 3000;
    client.sin_addr.s_addr = INADDR_ANY;

    k = connect(c_sd, (struct sockaddr *)&client, sizeof(client));

    printf("Enter the data to send : ");
    fgets(buff, 100, stdin);

    send(c_sd, buff, 100, 0);

    recv(c_sd, buff, 100, 0);
    printf("%s\n", buff);
}