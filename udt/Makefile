all:_udt_client _udt_server
libudt:
	cd /home/rd/workspace/udt-git/udt4/src
_udt_client:udt_client.cc
	g++ -o _udt_client udt_client.cc  -ludt -lpthread

_udt_server:udt_server.cc
	g++ -o _udt_server udt_server.cc -ludt -lpthread
clean:
	rm -f _*
