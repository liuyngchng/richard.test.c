all:_server _client _file_io
_server:server.o trans.o
	g++ -g -o $@ $^ 
_client:client.o trans.o 
	g++ -g -o $@ $^
_file_io:file_io.o trans.o
	g++ -g -o $@ $^
trans.o:trans.cc
	g++ -g -c $<
server.o:server.cc 
	g++ -g -c $<
client.o:client.cc 
	g++ -g -c $<
file_io.o:file_io.cc 
	g++ -g -c $<
clean:all
	rm _* *.o

