/* Viết một chương trình có só lượng command-line arguments là 3, Có dạng như sau:
$ ./example_program filename num-bytes [r/w] "Hello"
Trong đó:
	1.  example_grogram: Tên file thực thi
	2. filename: Tên file
	3. num-bytes: Số byte muốn read/write
	4. [r/w]: r -> Thực hiện đọc từ  filename và in ra màn hình
		    w -> Thực hiện ghi vào filename
	5. "Hello": Nội dung bất kì muốn read/write vào filename
 */

#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#define SIZE_BUFF 256

int main(int argc , char* argv[]) {

    int fd, numb_bytes_want; // number bytes want to read or write from commamd line
    int num_read, num_write; // number bytes read or write from file actually
    char buff[SIZE_BUFF];

    if (argc<5) { // if number arguments <5 => fail format 
        printf("command line error - Syntax: ./example_program filename num-bytes [r/w] \"Hello\" \n");
        exit(1);
    }
    numb_bytes_want = atoi(argv[2]); // convert string to integer
    /* open file */
    fd = open(argv[1],O_CREAT|O_RDWR,0777);
    if (fd == -1 )
        perror("open file error: ");
    /* start read/write file */
    if (strcmp(argv[3],"r")==0) {// read, compare argv from command line to specific read or write 
        num_read = read(fd, buff, numb_bytes_want);
        if (num_read == -1 ) {
            perror("Error read file: ");
        } else {
            printf("Number bytes is read from file(actually): %d\n", num_read);
            printf("Data in buff(actually) : %s\n", buff);
        }
    } else if (strcmp(argv[3],"w")==0) {//compare argv from command line to specific read or write 
        strncpy(buff, argv[4], strlen(argv[4]));
        num_write = write(fd, buff, numb_bytes_want);
        if (num_write == -1) {
            perror("Error write file: ");
        } else {
            printf("Number bytes is written to file(actually): %d\n", num_write);
        }
    } else {
        printf("Ban nhap sai dinh dang cua argv[3] roi. \n");
        return -1 ; 
    }
    close(fd);

    return 0; 
}