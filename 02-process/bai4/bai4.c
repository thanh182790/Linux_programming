/*
segmenttation fault là lỗi gây ra do ta truy cập vào vùng nhớ không thuộc về mình. Nếu gặp lõi này 
thì có thể là đang truy cập vào 1 biến đã được giải phóng hoặc thưc giện ghi vào bộ nhớ chỉ đọc 
VD: int *p = NULL;
    *p = 1;
hoặc
    char *str = "Foo"; // Compiler marks the constant string as read-only
    *str = 'b'; // Which means this is illegal and results in a segfault
Dereferencing con trỏ NULL
Dereferencing con trỏ chưa được khởi tạo
Dereferencing con trỏ đã bị free hoặc delete
Ghi giá trị vượt quá giới hạn của mảng
Hàm đệ quy sử dụng hết vùng bộ dành cho stack – còn gọi là “stack overflow”
“Core dump” là gì ?
*/
/*
    Core dump là một file lưu lại trạng thái của chương trình tại thời điểm mà nó chết. 
     Nó cũng là bản sao lưu lại tất cả các vùng bộ nhớ ảo đã được truy cập bởi chương trình.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main()
{
    int a = 10 ; 
    int *p = &a ; 
    free(p);
    *p = 10 ; 
    printf("%d", *p);
    return 0;
}