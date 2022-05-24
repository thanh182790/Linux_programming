#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#define BUFF_SIZE 100

int main(int argc, char* argv[])
{
    int sr_fd, port_no;
    socklen_t len_add_client;
    struct sockaddr_in sr_add, cl_add;
    ssize_t byte_w, byte_r;
    char recdata[BUFF_SIZE];
    char sendata[BUFF_SIZE];
    if (argc < 2) {
        printf("Error syntax, no port number provied\n<command: ./file_excute portnumber>\n");
        exit(EXIT_FAILURE);
    } else 
        port_no = atoi(argv[1]); // chuyển địa chỉ cổng từ chuỗi sang số 

    /* tạo socket */
    sr_fd = socket(AF_INET,SOCK_DGRAM,0);
    if (sr_fd == -1) {
        perror("Error socket: ");
        exit(EXIT_FAILURE);
    }
    /* đằng kí địa chỉ */
    memset(&sr_add, 0, sizeof(sr_add));
    memset(&cl_add, 0, sizeof(cl_add));

    sr_add.sin_family = AF_INET;
    sr_add.sin_port = htons(port_no);
    sr_add.sin_addr.s_addr = INADDR_ANY;

    /* bind address vào socket */

    if (bind(sr_fd, (struct sockaddr*)&sr_add, sizeof(sr_add)) == -1) {
        perror("Error bind: ");
        exit(EXIT_FAILURE);
    }

    /* bắt dầu trò chuyện  */
    printf("Server is comminication to port %d\n", port_no);
    for (;;)
    {
        len_add_client = (socklen_t)sizeof(cl_add);
        /* nhận dữ liệu từ client */
        byte_r = recvfrom(sr_fd, recdata, BUFF_SIZE, 0, (struct sockaddr*)&cl_add, &len_add_client);
        if (byte_r == -1) {
            perror("recvfrom: ");
            exit(EXIT_FAILURE);
        }
        printf("Data from client is: %s\n",recdata);
        /*  so sánh nếu thấy client gửi lệnh exit thì thoát luôn chương trình */
        if(strncmp("exit", recdata, 4) == 0) {
            printf("Client exited.\n");
            break;
        }
        /* gửi dữ liệu cho client */
        printf("Respone for client: ");
        fgets(sendata,BUFF_SIZE,stdin);

        byte_w  = sendto(sr_fd, sendata, BUFF_SIZE, 0, (struct sockaddr *)&cl_add, len_add_client);
        if (byte_r == -1) {
            perror("recvfrom: ");
            exit(EXIT_FAILURE);
        }
    }
    close(sr_fd);

    return 0;
}