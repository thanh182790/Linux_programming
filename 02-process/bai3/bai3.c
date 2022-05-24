/*
dup()/dup2() dùng để tạo ra 1 bản copy của old fd truyền vào
giá trị trả về là new fd, Sau khi được tạo thành công thì có thể 
dùng nethế cho nhau vì chả hai đều trỏ đến 1 file. 
wfd và oldfd thay thế
sự khác biệt giữa dup và dup2 là thằng dup nó sẽ dùng 1 cái newfd có giá trị nhỏ nhát
trong hệ thống chưa sử dụng còn thằng dup2 là dùng cái newfd do ng dùng tự chọn
#include <unistd.h> 

int dup(int oldfd); 
int dup2(int oldfd, int newfd);  */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char* argv[]) 
{   
    int oldfd, newfd; 
    int num_byte; 
    oldfd = open("bai3.txt", O_CREAT|O_RDWR, 0777);
    if (oldfd == -1) {
        perror("Error open file: ");
    }
    num_byte = write(oldfd,"Chao ban Thanh Thanh1",strlen("Chao ban Thanh Thanh1"));
    if (num_byte == -1) {
        perror("Error write to file oldfd: ");
    }
    newfd = dup(oldfd);
    num_byte = write(newfd,"Chao ban Thanh Thanh2",strlen("Chao ban Thanh Thanh1"));
    if (num_byte == -1) {
        perror("Error write to file newfd: ");
    }
    close(oldfd);
    close(newfd);
    return 0 ;
}