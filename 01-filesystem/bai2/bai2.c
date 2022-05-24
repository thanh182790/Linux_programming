/* fd1 = open(file, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
fd2 = dup(fd1);
fd3 = open(file, O_RDWR);
write(fd1, "Hello,", 6);
write(fd2, "world", 6);
lseek(fd2, 0, SEEK_SET);
write(fd1, "HELLO,", 6);
write(fd3, "Gidday",6);
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#define SIZE_BUFF 256
int main(int argc, char *argv[])
{
    int fd1, fd2, fd3;
    // mở một file với các cờ đọc ghi , cờ tạo , cờ xóa nội dung , mode 0600
    fd1 = open("bai2.txt", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    printf("fd1 = %d\n", fd1);
    fd2 = dup(fd1); // copy fd1 sang fd2 sau đó 2 cái fd này có thể dùng thay thế lẫn nhau 
    printf("fd2 = %d\n", fd2);
    fd3 = open("bai2.txt", O_RDWR);
    printf("fd3 = %d\n", fd3);
    write(fd1, "Hello,", 6); //Hello,
    write(fd2, "world", 6); //Hello,world\0
    lseek(fd2, 0, SEEK_SET);//di chuyen den dau file
    write(fd1, "HELLO,", 6);//HELLO,world
    // cái đoạn này nó mở lại file nên con trỏ file lại nhảy về đầu file để ghi 
    write(fd3, "Gidday", 6);//Giddayworld\0 
    return 0;
}
