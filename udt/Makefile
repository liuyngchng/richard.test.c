all:udt_client udt_server
libudt:
	cd /home/rd/workspace/udt-git/udt4/src
udt_client:udt_client.cc
	g++ -o _udt_client udt_client.cc  -ludt -lpthread

udt_server:udt_server.cc
	g++ -o _udt_server udt_server.cc -ludt -lpthread
clean:
	rm -f _*
