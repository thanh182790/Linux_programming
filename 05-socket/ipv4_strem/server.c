#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>// thư viện chứa cái đại chỉ của socket
#include <string.h>
#include <sys/socket.h>
#include <errno.h>
#include <arpa/inet.h>

#define LISTEN_BACKLOG 10
#define BUFF_SIZE 256

int main(int argc, char* argv[])
{
    int sockserver_fd, newsock_fd_to_communication;
    int port_number, lenadd_client;
    struct sockaddr_in ser_add, client_add; 
    int byte_read, bytew_write;
    char recvdata[BUFF_SIZE];
    char sendata[BUFF_SIZE];

    /* đọc cổng từ command line */
    if (argc < 2) {
        printf("Error syntax, no port number provied\n<command: ./file_excute portnumber>\n");
        exit(EXIT_FAILURE);
    } else 
        port_number = atoi(argv[1]); // chuyển địa chỉ cổng từ chuỗi sang số 
    
    memset(&ser_add,0,sizeof(ser_add));
    memset(&client_add,0,sizeof(client_add));

    /* tạo socket */
    sockserver_fd  = socket(AF_INET,SOCK_STREAM,0);
    if (sockserver_fd == -1) {
        perror("Error create socket: ");
        exit(EXIT_FAILURE);
    }

    /* khởi tạo địa chỉ server */
    ser_add.sin_family = AF_INET;
    ser_add.sin_port = htons(port_number);
    ser_add.sin_addr.s_addr = INADDR_ANY;// để khi server nó đổi địa chỉ thì thằng client nó vẫn chấp nhận

    /* gắn địa chỉ vào socket */
    if (bind(sockserver_fd, (struct sockaddr*)&ser_add, sizeof(ser_add)) == -1) {
        perror("Error bind address for socket: ");
        exit(EXIT_FAILURE);
    }

    /* lắng nghe tín hiệu từ bên client */
    if (listen(sockserver_fd, LISTEN_BACKLOG) == -1) {
        perror("Error listen request from client: ");
        exit(EXIT_FAILURE);
    }

    /* lấy độ dài của địa chỉ của client */
    lenadd_client = sizeof(client_add);

    /*chấp nhận yêu cầu*/
        printf("Server is listening from port %d\n", port_number);
        newsock_fd_to_communication = accept(sockserver_fd, (struct sockaddr*)&client_add, (socklen_t *)&lenadd_client);
        // giá trị trả về của hàm accept là 1 fd để giao tiếp giữa client và server 
        //chứ không phải giao tiếp qua fd của socket 
        if (newsock_fd_to_communication == -1) {
            perror("Error accept request from client: ");
            exit(EXIT_FAILURE);
        }
        system("clear");
        byte_read = read(newsock_fd_to_communication, recvdata, BUFF_SIZE);
        if (byte_read == -1) {
            perror("Error read data from client: ");
            exit(EXIT_FAILURE);
        } else {
            printf("\nData from client: %s\n", recvdata);
            printf("Type data to client: ");
            fgets(sendata, BUFF_SIZE, stdin);
            bytew_write = write(newsock_fd_to_communication, sendata, BUFF_SIZE);
            if (bytew_write == -1 ) {
                perror("Error write data to client: ");
                exit(EXIT_FAILURE); 
            }
            
        }
    close(newsock_fd_to_communication);
    close(sockserver_fd);
    return 0;
}

