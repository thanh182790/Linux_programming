#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <sys/un.h>
#define BUFF_SIZE 100
#define SER_PATH "./sersock"
#define LISTEN_BACKLOG 10
#define handel_error(msg)   \
    do                      \
    {                       \
        perror(msg);        \
        exit(EXIT_FAILURE); \
    } while (0)

int main(int argc, char *argv[])
{
    int fd_sr, newsock_fd;
    int byte_w, byte_r;
    socklen_t len_client_add;
    char sendata[BUFF_SIZE];
    char recvdata[BUFF_SIZE];
    struct sockaddr_un sr_add, cl_add;
    memset(&sr_add, 0, sizeof(sr_add));
    memset(&cl_add, 0, sizeof(cl_add));

    /* tao socket */
    fd_sr = socket(AF_UNIX, SOCK_STREAM, 0);
    if (fd_sr == -1)
        handel_error("Socket error: ");

    /* khoi tao dia chi*/
    sr_add.sun_family = AF_UNIX;
    strncpy(sr_add.sun_path, SER_PATH, sizeof(sr_add.sun_path) - 1);

    /* bind socket voi dai chi*/
    if (bind(fd_sr, (struct sockaddr *)&sr_add, sizeof(sr_add)) == -1)
        handel_error("Bind error: ");

    /* listen */
    if (listen(fd_sr, LISTEN_BACKLOG) == -1)
        handel_error("Listen error: ");
    len_client_add = sizeof(cl_add);
    newsock_fd = accept(fd_sr, (struct sockaddr *)&cl_add, &len_client_add);
    if (newsock_fd == -1)
        handel_error("Accept error: ");
    while (1)
    {

        /* bat dau noi chuyen */
        printf("Server is listening client-----\n");
        byte_r = read(newsock_fd, recvdata, BUFF_SIZE);
        if (byte_r == -1)
            handel_error("Error read data from client: ");
        printf("Data from client: %s\n", recvdata);
        if (strncmp("exit", recvdata, 4) == 0)
        {
            printf("Client exited\n");
            break;
        }
        printf("Type data to client: ");
        fgets(sendata, BUFF_SIZE, stdin);
        byte_w = write(newsock_fd, sendata, BUFF_SIZE);
        if (byte_w == -1)
            handel_error("Error send data to client: ");
        if (strncmp("exit", sendata, 4) == 0)
        {
           printf("Server exited\n");
           break;
        }
        system("clear");
    }
    remove(sr_add.sun_path);
    close(newsock_fd);
    close(fd_sr);
    return 0;
}