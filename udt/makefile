all:udt_client udt_server
udt_client:udt_client.cc /home/rd/so/libudt.so
	g++ -o _udt_client udt_client.cc  /home/rd/so/libudt.so -lpthread

udt_server:udt_server.cc /home/rd/so/libudt.so
	g++ -o _udt_server udt_server.cc /home/rd/so/libudt.so -lpthread
clean:
	rm -f _*
