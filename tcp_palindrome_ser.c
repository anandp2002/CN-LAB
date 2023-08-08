#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>

void main()
{
    int sd, new_sd, k;
    char buff[100];
    struct sockaddr_in server, client;
    sd = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = 3000;
    server.sin_addr.s_addr = INADDR_ANY;

    k = bind(sd, (struct sockaddr *)&server, sizeof(server));
    if (k == -1)
        printf("Error in binding !");

    listen(sd, 5);

    socklen_t len = sizeof(client);
    new_sd = accept(sd, (struct sockaddr *)&client, &len);

    recv(new_sd, buff, 100, 0);
    printf("Data recieved from client is : %s", buff);

    int l = strlen(buff) - 1;

    int i;
    char *pal = "Palindrome";
    for (i = 0; i < l / 2; i++)
    {
        if (buff[i] != buff[l - i - 1])
            pal = "Not palindrome";
    }

    send(new_sd, pal, 100, 0);
}