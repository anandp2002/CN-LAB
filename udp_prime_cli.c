#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netdb.h>

int main()
{
    struct sockaddr_in server;

    int sock_desc = socket(AF_INET, SOCK_DGRAM, 0);

    if (sock_desc == -1)
        printf("Error in socket();");

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = 3000;

    char buffer[100];
    printf("Enter a number to check prime : ");
    fgets(buffer, 100, stdin);

    int k = sendto(sock_desc, buffer, sizeof(buffer), 0, (struct sockaddr *)&server, sizeof(server));

    if (k == -1)
        printf("Error in sendto");

    return 0;
}