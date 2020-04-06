all:tcp_server tcp_client mytime
mytime:mytime.cc
	g++ -o ./libmytime.so -fPIC -shared mytime.cc
tcp_server:tcp_server.cc mytime
	g++ -o _tcp_server tcp_server.cc ./libmytime.so -lpthread
tcp_client:tcp_client.cc mytime
	g++ -o _tcp_client tcp_client.cc ./libmytime.so
clean:
	rm -f _* *.o *.so
	
