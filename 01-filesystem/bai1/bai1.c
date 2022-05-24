/* BT1. Viết một chương trình mở một file bất kì và sử dụng cờ O_APPEND,
sau đó thực hiện seek về đầu file rồi ghi một vài dữ  liệu vào file đó.
 Dữ liệu sẽ xuất hiện ở vị trí nào của file và tại sao lại như vậy? */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#define SIZE_BUFF 256
int main(int argc, char *argv[])
{
    int fd, number_write;
    char buff[SIZE_BUFF];

    printf("Nhap chuoi vao buff: ");
    fgets(buff, SIZE_BUFF, stdin); // đoạn này là nhập chuỗi từ bàn phím để đưa vào buff
    printf("Length of buff = %ld, Sizeof buff = %ld\n", strlen(buff), sizeof(buff));
    // fd = open("bai1.txt", O_APPEND | O_TRUNC, 0777);
    // O_TRUNC nếu là một file thông thường đã tồn tại thì mở file và xóa nội dung đi
    // O_APPEND mở file và ghi thêm nội dung vào file
    fd = open("bai1.txt", O_CREAT|O_RDWR|O_APPEND, 0777); 
    /* Trong trường hợp mà dùng cwof O_APPEND thì ta không thể lseek được vì mặc định O_APPEND sẽ 
    đưa con trỏ file đến EOF để ghi tiếp vào file nên là nếu có dùng lseek để di chuyển đên đàu 
    file thì dữ liệu vẫn cứ ghi tiếp vào cuối file 
    . Nếu muốn dùng Lseek thì cần bỏ đi cờ O_APPEND */
    if (fd == -1) {
        printf("Error open file\n");
    }
    write(fd, "Truoc khi dich seek1 ", strlen("Truoc khi dich seek1 "));
    if (lseek(fd,0, SEEK_SET)==-1) {// di chuyển con trỏ file về đầu file rồi ghi bắt đầu từ vị trí offset = 0
        printf("Lseek error.");
    } 
    number_write = write(fd, buff, strlen(buff));
    if (number_write == -1) {
        perror("error write");
    }
    printf("Number byte is write in file : %d", number_write);
    close(fd);
    return 0;
}
