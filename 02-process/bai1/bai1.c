/* Giả sử rằng một parent process đã thiết lập một handler cho SIGCHLD
và cũng block tín hiệu này. Sau đó, một trong các child process của
nó thoát ravà parent process sau đó thực hiện wait() để thu thập
trạng thái của child process. Điều gì xảy ra khi parent process
bỏ chặn SIGCHLD? Viết một chương trình để xác minh câu trả lời. */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/types.h>

void SIGCHILD_handler(int signum)
{
    
    printf("Im in SIGCHILD_handler()\n");
    wait(NULL);// chỗ này sẽ ko bị block do là khi có SIGCHILD thì tức là có thằng process con kết thúc rồi 
    // nên nó mới nhảy vào đây xử lý => ko block
}

int main(int argc , char* argv[]) {
    pid_t child_id ; 
    child_id = fork(); 
    int status;
    if (child_id>=0) {
        if (child_id ==0) {
            // child process
            printf("Im child process, my id is %d\n", getpid());
            printf("Child process will termination after 2 seconds\n");
            sleep(10);
        } else {
            // process parent
            sleep(2);
            sigset_t newset, oldset; // tạo một cái sigset để lưu lại sigmask
            sigemptyset(&newset);
            sigemptyset(&oldset);
            printf("Im parent process, my id is %d\n", getpid());
            // nếu dùng wait() thì phải sau 10s thằng child process chết thì mới in được thằng "Process Child was release"
            //wait(&status); 
            //printf("Process Child was release\n");
            // block SIGCHILD
            sigaddset(&newset,SIGCHLD);
            if (sigprocmask(SIG_BLOCK,&newset,&oldset) == -1) {
                perror("Error set sigmask for process: ");
            }
            //unblock SIGCHILD
            if (sigprocmask(SIG_UNBLOCK,&newset,&oldset) == -1) {
                perror("Error set sigmask for process: ");
            }
            //register signal
            if (signal(SIGCHLD, SIGCHILD_handler) == SIG_ERR) {
                perror("Error SIGCHILD: ");
                exit(EXIT_FAILURE);
            }
            while (1);

        }
    } else {
        printf("creat child process error\n");
    }
    return 0 ; 
}