all:_server _client
_server:server.o
	g++ -o _server server.o
_client:client.o
	g++ -o _client client.o
server.o:server.cc common.h
	g++ -c server.cc
client.o:client.cc common.h
	g++ -c client.cc
clean:all
	rm _* *.o

