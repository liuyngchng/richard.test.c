all:tcp_server tcp_client mytime
mytime:mytime.cc
	g++ -fPIC -shared mytime.cc -o /home/rd/so/libmytime.so
tcp_server:tcp_server.cc mytime
	g++ -o _tcp_server tcp_server.cc /home/rd/so/libmytime.so
tcp_client:tcp_client.cc mytime
	g++ -o _tcp_client tcp_client.cc /home/rd/so/libmytime.so
clean:
	rm -f _* *.o
	
