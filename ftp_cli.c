#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include<string.h>

int main()
{
    FILE *fp;
    int sd, n, ser, s, cli, newsd;
    char name[100], rcvmsg[100], rcvg[100], new_name[100];
    struct sockaddr_in servaddr;
    
    
    sd = socket(AF_INET, SOCK_STREAM, 0);
    if (sd < 0)
    {
        printf("Error....\n");
        exit(0);
    }
    else
        printf("Socket is created\n");
        
        
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(3000);
    if (connect(sd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
        printf("Error in connection\n");
    else
        printf("connected\n");
        
        
    printf("Enter the existing file name\t");
    scanf("%s", name);
    send(sd, name, sizeof(name), 0);
    
    
    printf("Enter the new file name\t");
    scanf("%s", new_name);
    fp = fopen(new_name, "w");
    
    while (1)
    {
        s = recv(sd, rcvg, 100, 0);
        rcvg[s] = '\0';
        if (strcmp(rcvg, "error") == 0)
            printf("File is not available\n");
        if (strcmp(rcvg, "completed") == 0)
        {
            printf("File is transferred........\n");
            fclose(fp);
            close(sd);
            break;
        }
        else
            fputs(rcvg, stdout);
        fprintf(fp, "%s", rcvg);
        return 0;
    }
}
