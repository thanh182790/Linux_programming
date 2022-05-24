#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(int argc, char* argv[]) {
    int a = 3 , b = 2 ; 
    printf("My process ID bai2_2 : %d\n", getpid());
    printf("Mulitple of a * b = %d\n", a*b);
    return 0 ; 
}