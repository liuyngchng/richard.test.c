all:_server _client mytime
mytime:mytime.cc
	g++ -o ./libmytime.so -fPIC -shared mytime.cc
_server:server.cc mytime
	g++ -o _server server.cc ./libmytime.so -lpthread
_client:client.cc mytime
	g++ -o _client client.cc ./libmytime.so
clean:
	rm -f _* *.o *.so
	
