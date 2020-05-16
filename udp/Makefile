all:_client _server
_client:client.o
	gcc -o _client client.o
_server:server.o
	gcc -o _server server.o
client.o:client.c
	gcc -c client.c
server.o:server.c
	gcc -c server.c
clean:
	rm -f *.o _*
