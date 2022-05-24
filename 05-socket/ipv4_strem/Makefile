.PHONY: server client
alll:
	gcc -o client client.c
	gcc -o server server.c
clean:
	rm -rf client server
server:
	./server 2000
client:
	./client 192.168.213.128 2000
