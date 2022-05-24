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

int main(int argc, char* argv[])
{
    struct sockaddr_un cl_add, sr_add;  
    int cl_fd, byte_w, byte_r; 
    char recv[BUFF_SIZE];
    char sen[BUFF_SIZE];
    memset(&cl_add, 0, sizeof(cl_add));
    memset(&sr_add, 0, sizeof(sr_add));

    /* tao socket */
    cl_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (cl_fd == -1)
        handel_error("Error socket: ");
    /* khoi tao dia chi cho client */
    // cl_add.sun_family = AF_UNIX;
    // strncpy(cl_add.sun_path, CLIENT_PATH, sizeof(cl_add.sun_path) - 1);

    // if (bind(cl_fd, (struct sockaddr *)&cl_add, sizeof(cl_add)) == -1)
    //     handel_error("Bind error: ");
    /* khoi tao dia chi cho server */
    sr_add.sun_family = AF_UNIX;
    strncpy(sr_add.sun_path, SER_PATH, sizeof(sr_add.sun_path)-1);

    /* connect to server */
    if (connect(cl_fd, (struct sockaddr*)&sr_add, sizeof(sr_add)) == -1)
        handel_error("Error connect: ");
    printf("Conection sucess\n");
    while (1)
    {
        /* bat dau tro chuyen */
        printf("Type data send to server: ");
        fgets(sen, BUFF_SIZE, stdin);
        byte_w = write(cl_fd, sen, BUFF_SIZE);
        if (byte_w == -1)
            handel_error("Error write: ");
        if ( strncmp("exit", sen,4) == 0) {
            printf("Client exited.\n");
            sleep(1);
            break;
        }
        byte_r = read(cl_fd, recv, BUFF_SIZE);
        if (byte_r == -1)
            handel_error("Error read: ");
        printf("Data from server is %s", recv);
        if (strncmp("exit", recv, 4) == 0)
        {
           printf("Server exited\n");
           break;
        }
        
        sleep(2);
        system("clear");
    }
    close(cl_fd);
    return 0;
}