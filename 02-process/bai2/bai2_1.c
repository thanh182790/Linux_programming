/* 
Điều gì xảy ra khi chúng ta sử dụng họ hàm execute (execl/exevp/exepv)? 
Giải thích và viết một chương trình để xác minh câu trả lời. 
Sau đó hãy cho biết bản chất khi lệnh system() hoạt động như thế nào.
 */
// khi thực hiện lệnh exec thì sẽ chạy 1 chương trình B từ chương trình A đang chạy hiện tại 
// process image của B sẽ thay thế process image của A (nghĩa là toàn bộ lệnh của thằng A sau exec sẽ ko được chạy)

/*  The system() library function uses fork(2) to create a child process that executes the shell command 
 specified in command using execl(3) as follows: execl("/bin/sh", "sh", "-c", command, (char *) NULL);
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(int argc, char* argv[]) {
    int a = 1 , b = 2 ; 
    printf("My process ID bai2_1: %d\n", getpid());
    // đối số đầu tiên là đường dẫn đến file thực thi , đối số thứ 2 là tên chương trình thực thi 
    execl("/home/thanh/working_space/Linux-Programming-N-System-main/Home-work/02-process/bai2/bai2_2","bai2_2", NULL);
    printf("Sum of a + b = %d\n", a+b);
    return 0 ; 
}