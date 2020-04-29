all:_server _client _file_io
_server:server.o trans.o
	g++ -g -o _server server.o trans.o
_client:client.o trans.o
	g++ -g -o _client client.o trans.o
_file_io:file_io.o trans.o
	g++ -g -o _file_io file_io.o trans.o
trans.o:trans.cc
	g++ -g -c trans.cc
server.o:server.cc trans.h
	g++ -g -c server.cc
client.o:client.cc trans.h
	g++ -g -c client.cc
file_io.o:file_io.cc trans.h
	g++ -g -c file_io.cc
clean:all
	rm _* *.o

