/* BT1. Viết chương trình block tín hiệu SIGINT và 
sau đó in ra signal mask của process hiện tại. */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <syscall.h>
// void SIGINT_HANDLER() {
//     printf("\nIm in SIGINT_HANDLER()\n");
// }
int main(int argc, char* argv[])
{
    printf("Xin chao my id is %d\n", getpid());
    sigset_t newset, oldset; 
    sigemptyset(&newset);
    sigemptyset(&oldset);
    
    // if (signal(SIGINT, SIGINT_HANDLER) == SIG_ERR) {
	// 	fprintf(stderr, "Cannot handle SIGINT\n");
	// 	exit(EXIT_FAILURE);
	// }
    sigaddset(&newset, SIGINT);// block tín hiệu SIGINT

    if (sigprocmask(SIG_BLOCK, &newset, &oldset) == -1) { // set signalmask for process
        perror("Set sigmask error: ");
    } else {
        sigprocmask(SIG_BLOCK,NULL,&oldset);
        printf("Signal mask of process %x\n",oldset);
    }
    while (1) {
        printf("hello\n");
		sleep(1);
    }
    
    
    return 0; 
}