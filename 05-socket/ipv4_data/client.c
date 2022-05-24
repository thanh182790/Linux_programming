#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h> // thư viện của inet_addr
#define BUFF_SIZE 100

int main(int argc, char* argv[])
{
    int cl_fd, port_no;
    socklen_t len_add_sr;           
    struct sockaddr_in sr_add;
    ssize_t bytes_write, bytes_read;
    char recdata[BUFF_SIZE];
    char sendata[BUFF_SIZE];

    if(argc < 3 ) {
        printf("command : ./client <server address> <port number>\n");
        exit(EXIT_FAILURE);
    }
    port_no = atoi(argv[2]);
    
    /* khởi tạo địa chỉ socket cho server*/

    memset(&sr_add, 0, sizeof(sr_add));
    sr_add.sin_family = AF_INET;
    sr_add.sin_port = htons(port_no);
    sr_add.sin_addr.s_addr = inet_addr(argv[1]);

    /* tạo socket */
    cl_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (cl_fd == -1) {
        perror("Error socket: ");
        exit(EXIT_FAILURE);
    }

    /* giao tiếp */
    len_add_sr = sizeof(sr_add);
    while (1)
    {
        // 
        printf("\nType data want send to server: ");
        fgets(sendata,BUFF_SIZE,stdin);
        
        bytes_write = sendto(cl_fd,sendata,strlen(sendata),0,(struct sockaddr *)&sr_add,len_add_sr);
        if (bytes_write == - 1) {
            perror("sendto: ");
        } 
        if (strncmp("exit",sendata,4) == 0) {
            printf("Client exited.\n");
            break;
        }
        bytes_read = recvfrom(cl_fd,recdata,BUFF_SIZE,0,NULL,NULL);
        if (bytes_read == - 1) 
            perror("recvfrom: ");
        printf("Data recvied from server is %s\n",recdata);
        sleep(3);
        system("clear");
    }
    close(cl_fd);
    return 0;
}