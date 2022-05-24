/* chương trình thực hiện cho client gửi data đên server và server gửi lại thông điệp in hoa cho client */
#include <sys/un.h>
#include <sys/socket.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#define BUF_SIZE 100 
#define SOCK_PATH "./sock_ser" //đường dẫn để mà gán cho socket

int main(int argc, char *argv[])
{
    struct sockaddr_un svaddr, claddr;
    int sock_fd, j;
    ssize_t numBytes;
    socklen_t len;
    char buf[BUF_SIZE];

    sock_fd = socket(AF_UNIX, SOCK_DGRAM, 0); /* Create server socket */
    if (sock_fd == -1)
        perror("socket: ");
    
    /* Tạo địa chỉ cho socket */
    memset(&svaddr, 0, sizeof(struct sockaddr_un));
    svaddr.sun_family = AF_UNIX;
    // copy cái đường dãn SOCK_PATH vào sunpath của sockaddr_un
    strncpy(svaddr.sun_path, SOCK_PATH, sizeof(svaddr.sun_path) - 1);

    /* gán địa chỉ cho socket */
    if (bind(sock_fd, (struct sockaddr *)&svaddr, sizeof(struct sockaddr_un)) == -1)
        perror("bind: ");
    
    for (;;)
    {
        len = sizeof(struct sockaddr_un); // lấy ra độ dài của địa chỉ 
        /* nhận dữ liệu từ client */
        numBytes = recvfrom(sock_fd, buf, BUF_SIZE, 0, (struct sockaddr *)&claddr, &len);
        if (numBytes == -1)
            perror("recvfrom: ");

        printf("Server received %ld bytes from %s\n", (long)numBytes, claddr.sun_path);
        printf("Data from client is: %s\n",buf);
        /*  so sánh nếu thấy client gửi lệnh exit thì thoát luôn chương trình */
        if(strncmp("exit", buf, 4) == 0) {
            printf("Client exited.\n");
            break;
        }
        /*  đoạn này đổi data từ client thành chữ hoa rồi chuyển đi  */
        for (j = 0; j < numBytes; j++)
            buf[j] = toupper((unsigned char)buf[j]);
        if (sendto(sock_fd, buf, numBytes, 0, (struct sockaddr *)&claddr, len) != numBytes)
            printf("sento error\n");
    }
    remove(svaddr.sun_path);
    return 0; 
}