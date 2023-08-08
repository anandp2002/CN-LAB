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

    int k = bind(sock_desc, (struct sockaddr *)&server, sizeof(server));
    if (k == -1)
        printf("\nError in bind");

    char buffer[100];
    socklen_t server_len = sizeof(server);

    printf("Server waiting....\n");

    k = recvfrom(sock_desc, buffer, 100, 0, (struct sockaddr *)&server, &server_len);
    if (k == -1)
        printf("Error in recvfrom()!");

    // check prime
    char *n = buffer;
    int m = atoi(n);
    int i, flag = 0;

    if (m == 0 || m == 1)
        printf("\nNeither prime nor composite\n");
    if (m == 2)
        printf("\nPrime\n");
    else if (m > 2)
    {
        for (i = 2; i < m / 2; i++)
        {
            if ((m % i) == 0)
            {
                flag = 1;
                printf("\nNot Prime\n");
                break;
            }
        }
        if (!flag)
            printf("\nPrime\n");
    }
    return 0;
}