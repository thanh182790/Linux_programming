all:
	gcc -o test bai4.c
debug:
	gdb test core 
core: # tạo file core 
	ulimit -c unlimited 
clean:
	rm -rf test core