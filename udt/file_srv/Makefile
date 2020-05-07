all:_server _client
_server:server.o trans.o
	g++ -g -o _server server.o trans.o -ludt -lpthread
_client:client.o trans.o
	g++ -g -o _client client.o trans.o -ludt -lpthread
trans.o:trans.cc
	g++ -g -c trans.cc
server.o:server.cc trans.h
	g++ -g -c server.cc
client.o:client.cc trans.h
	g++ -g -c client.cc
clean:all
	rm _* *.o

