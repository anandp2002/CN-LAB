// goback-client.c
#include <stdio.h>
#include <netinet/in.h>

struct frame
{
    int packet[40];
};
struct ack
{
    int acknowledge[40];
};
int main()
{
    int clientsocket;
    struct sockaddr_in serveraddr;
    socklen_t len;

    struct frame f1;
    int windowsize, totalpackets, totalframes, i = 0, j = 0, framesrecieved = 0, k, l, buffer;
    struct ack acknowledgement;
    char req[50];
    clientsocket = socket(AF_INET, SOCK_DGRAM, 0);

    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = 3000;
    serveraddr.sin_addr.s_addr = INADDR_ANY;

    // reading and sending window size
    printf("\nEnter the window size \n");
    scanf("%d", &windowsize);
    printf("\nSending window size\n");
    sendto(clientsocket, (char *)&windowsize, sizeof(windowsize), 0, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    printf("\nWaiting for the server response\n");

    // recieving total number of packets
    recvfrom(clientsocket, (char *)&totalpackets, sizeof(totalpackets), 0, (struct sockaddr *)&serveraddr, &len);
    printf("\ntotal number of frames or windows are :\t%d\n", totalpackets);

    printf("\nStarting the process of recieving\n");
    while (i < totalpackets)
    {
        printf("\nthe expected frame is %d with packets:", framesrecieved);
        j = 0;
        buffer = i;
        while (j < windowsize && i < totalpackets)
        {
            printf("%d", i);
            i++;
            j++;
        }
        // receivning frames
        printf("\nwaiting for the frame\n");
        recvfrom(clientsocket, (char *)&f1, sizeof(f1), 0, (struct sockaddr *)&serveraddr, &len);

        // acknowlegement processing
        printf("\nRecieved frame %d\n\nenter -1 to send negative acknowledgement for the packets\n", framesrecieved);
        j = 0;
        l = buffer; // buffer value contain staring value of each frame
        k = 0;
        while (j < windowsize && l < totalpackets)
        {
            printf("\npacket:%d\n", f1.packet[j]);
            scanf("%d", &acknowledgement.acknowledge[j]);
            if (acknowledgement.acknowledge[j] == -1)
            {
                if (k == 0)
                {
                    i = f1.packet[j];
                    k = 1;
                }
            }
            j++;
            l++;
        }
        framesrecieved++;
        sendto(clientsocket, (char *)&acknowledgement, sizeof(acknowledgement), 0, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    }
    printf("\nAll frames recieved successfully \nclosing connection with the server \n");
    close(clientsocket);
}
