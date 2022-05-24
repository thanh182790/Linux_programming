/*
BT1. Viết một chương trình để chứng minh rằng các thread khác nhau trong cùng một process 
có thể có các tập hợp signal đang chờ xử lý (set of pending signal) khác nhau,được trả về bằng sigpending(). 
Bạn có thể làm điều này bằng cách sử dụng pthread_kill() để gửi các tín hiệu khác nhau đến hai thread khác 
nhau đã bị block các tín hiệu này, và sau với mỗi thread gọi sigpending() hãy hiển thị thông tin về các tín hiệu đang chờ xử lý. 
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>

static void* handel_thread1(void* arg) 
{

}

static void* handel_thread2(void* arg) 
{
    
}
pthread_t threadID1, threadID2;
int ret1, ret2;
int main(int argc, char* argv[])
{   
    int s; 
    sigset_t newset;
    sigemptyset(&newset);

    sigaddset(&newset,SIGALRM);
    sigaddset(&newset,SIGQUIT);

    s = pthread_sigmask(SIG_BLOCK, &newset, NULL);
    if (s != 0) {
        perror("Error sigmask: ");
        exit(EXIT_FAILURE);
    }
    if (ret1 = pthread_create(&threadID1, NULL, &handel_thread1, &newset)) {
        perror("Error create thread1");
        exit(EXIT_FAILURE);
    }

    if (ret2 = pthread_create(&threadID2, NULL, &handel_thread2, &newset)) {
        perror("Error create thread2");
        exit(EXIT_FAILURE);
    }

    
    
}
