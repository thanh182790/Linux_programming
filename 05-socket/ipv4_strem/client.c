#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h> // thư viện chứa cái đại chỉ của socket
#include <string.h>
#include <sys/socket.h>
#include <errno.h>
#include <arpa/inet.h>

#define BUFF_SIZE 256

int main(int argc, char *argv[])
{
    int sockfd, port, byte_read, byte_write;
    struct sockaddr_in ser_add;
    char recdata[BUFF_SIZE];
    char sendata[BUFF_SIZE];

    memset(&ser_add, 0, sizeof(ser_add));

    if (argc < 3)
    {
        printf("command : ./client <server address> <port number>\n");
        exit(EXIT_FAILURE);
    }

    port = atoi(argv[2]);
    /* khơi tạo địa chỉ của server */
    ser_add.sin_family = AF_INET;
    ser_add.sin_port = htons(port);
    ser_add.sin_addr.s_addr = inet_addr(argv[1]);

    /* Tạo socket */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("Error socket: ");
        exit(EXIT_FAILURE);
    }

    /* connect */
    if (connect(sockfd, (struct sockaddr *)&ser_add, sizeof(ser_add)) == -1)
    {
        perror("Error connection: ");
        exit(EXIT_FAILURE);
    }
    printf("Conection sucess\n");

    printf("Type data to server: ");
    fgets(sendata, BUFF_SIZE, stdin);
    byte_write = write(sockfd, sendata, BUFF_SIZE);
    if ( byte_write == -1) {
        perror("Error write data to server: ");
        exit(EXIT_FAILURE);
    }
    byte_read = read(sockfd, recdata, BUFF_SIZE);
    if (byte_read == -1)
    {
        perror("Error read data from server: ");
        exit(EXIT_FAILURE);
    } 
    
    printf("\nData recv from server: %s\n",recdata);
    close(sockfd);

    return 0;
}
