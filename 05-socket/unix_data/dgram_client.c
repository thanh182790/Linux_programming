#include <sys/un.h>
#include <sys/socket.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#define BUF_SIZE 100 /* Maximum size of messages exchanged \
between client to server */
#define SOCK_PATH "./sock_ser"

int main(int argc, char *argv[])
{
    struct sockaddr_un svaddr, claddr;
    int sock_fd, j;
    size_t msgLen;
    ssize_t bytes_read, bytes_write;
    char sendata[BUF_SIZE];
    char recvdata[BUF_SIZE];
   
    /* Trong 1 số hệ thống unix, thì ở unix domain datagram socket nta vẫn bind client để việc trao đổi dữ 
    liệu giữa server và client chắc là dễ hơn chăng :v  */
    sock_fd = socket(AF_UNIX, SOCK_DGRAM, 0); //tạo client socket
    if (sock_fd == -1)
        perror("socket: ");
    // gán địa chỉ 
    memset(&claddr, 0, sizeof(struct sockaddr_un));
    claddr.sun_family = AF_UNIX;
    // ghi cái string đường dãn có id vào sun_path
    snprintf(claddr.sun_path, sizeof(claddr.sun_path),"./sock_client.%ld", (long)getpid());

    if (bind(sock_fd, (struct sockaddr *)&claddr, sizeof(struct sockaddr_un)) == -1)
        perror("bind");
    /* Khơi tạo địa chỉ cho server */
    memset(&svaddr, 0, sizeof(struct sockaddr_un));
    svaddr.sun_family = AF_UNIX;
    strncpy(svaddr.sun_path, SOCK_PATH, sizeof(svaddr.sun_path) - 1);

    while (1)
    {
        // 
        printf("\nType data want send to server: ");
        fgets(sendata,BUF_SIZE,stdin);
        
        bytes_write = sendto(sock_fd,sendata,strlen(sendata),0,(struct sockaddr *)&svaddr,sizeof(struct sockaddr_un));
        if (bytes_write == - 1) {
            perror("sendto: ");
        } 
        if (strncmp("exit",sendata,4) == 0) {
            printf("Client exited.\n");
            break;
        }
        bytes_read = recvfrom(sock_fd,recvdata,BUF_SIZE,0,NULL,NULL);
        if (bytes_read == - 1) 
            perror("recvfromL: ");
        printf("Data recvied from server is %s\n",recvdata);
        sleep(3);
        system("clear");
    }
    remove(claddr.sun_path);
    return 0;
    
}