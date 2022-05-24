/* BT1. Viết một chương trình sử dụng hai pipe để cho phép giao tiếp hai chiều giữa hai tiến trình cha và con.
Parent process lặp lại việc đọc dữ  liệu văn bản từ bàn phím và sử dụng một trong các pipe để gửi văn bản đến child process,
child process chuyển nó thành chữ hoa và gửi lại cho parent process qua pipe còn lại.
Parent process đọc dữ liệu trả về từ child process và in ra màn hình trước khi lặp lại quá trình một lần nữa.
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <ctype.h> // cho thằng toupper
#define BUF_SIZ 100
#define handelerro(msg)     \
    do                      \
    {                       \
        perror(msg);        \
        exit(EXIT_FAILURE); \
    } while (0)
void signal_handelr(int signum) {
    printf("Child process terminated\n");
    wait(NULL);
    exit(EXIT_FAILURE);
}
int main(int argc, char *argv[])
{
    int fd_P_write_Ch_read[2]; // cha ghi, con đọc
    int fd_Ch_write_P_read[2]; // Con ghi, cha đọc
    char buff_w[BUF_SIZ];
    char buff_r[BUF_SIZ];
    int byte_r_par, byte_w_par;
    int byte_r_child, byte_w_child;
    pid_t child_id;

    /* tạo pipe  */
    if (pipe(fd_P_write_Ch_read) < 0)
        handelerro("Error creat pipe1: ");
    if (pipe(fd_Ch_write_P_read) < 0)
        handelerro("Error creat pipe2: ");

    child_id = fork();

    if ( child_id >= 0 ) {
        if( child_id == 0 ) {
            // process con
            printf("Im child Process, my ID is %d, my parent ID is %d\n", getpid(), getppid());
            while (1)
            {
                // thằng con đọc dữ liệu từ cha gửi sang 
                byte_r_child = read(fd_P_write_Ch_read[0], buff_r, BUF_SIZ);
                if (byte_r_child == -1)
                    handelerro("Child read error: ");
                printf("Data read from parent process: %s\n", buff_r);
                if (strncmp("exit", buff_r,4) == 0) { // nếu là exit thì thoát khỏi vong while 
                    printf("Exit\n");
                    break;
                }             
                for (size_t i = 0; i < strlen(buff_r); i++)
                    buff_r[i] = toupper((unsigned char) buff_r[i]);
                    // gửi dữ liệu qua cho cha 
                byte_w_child = write(fd_Ch_write_P_read[1], buff_r, BUF_SIZ);
                if (byte_w_child == -1)
                    handelerro("Child write error: "); 
            }
            
        } else {
        
            // process cha 
            signal(SIGCHLD, signal_handelr); // chống zoobie
            printf("Im parent Process, my ID is %d\n", getpid());
            // đóng đầu đọc của cha ở pipe 1 
            if (close(fd_P_write_Ch_read[0]) == -1) 
                handelerro("Error parent can't close read of pipe1");
            // đóng đầu ghi của cha ở pipe2
            if (close(fd_Ch_write_P_read[1]) == -1) 
                handelerro("Error parent can't close write of pipe2");
            sleep(1); // cho ngủ 1 s nếu ko thì ko hiển thị chỗ nhập chuỗi vào 
            while (1) {
                printf("Type data from keyboard: ");
                fgets(buff_w, BUF_SIZ, stdin);
                // ghi dữ liệu vào pipe1 để gửi cho con 
                byte_w_par = write(fd_P_write_Ch_read[1], buff_w, BUF_SIZ);
                if (byte_w_par == -1) 
                    handelerro("Parent write error: ");
                // đọc lại dữ liệu từ con gửi vào pipe2
                byte_r_par = read(fd_Ch_write_P_read[0], buff_w, BUF_SIZ);
                if (byte_r_par == -1) 
                    handelerro("Parent read error: ");
                printf("Data read from child: %s\n", buff_w);
                
            }
        }

    } else {
        handelerro("Create child process error: ");
        
    }

    return 0;
}