Hướng dẫn debug với gdb 
- Để có thể debug được 1 chương trình C thì cần cài gdb trước => "sudo apt-get install gdb -y"
- Thêm option -g là mode debug với gdb trong khi complier : VD gcc -o test bai4.c -g
- Trước tiên là dùng lệnh này để tạo ra file core khi chạy file thực thi chương trình bị crash => "ulimit -c unlimited"
- sau đó chạy debug cả file core và file thực thi => gdb test core
-  dùng thêm lệnh "backtrace" để tìm lỗi segmantation ở đoạn nào 