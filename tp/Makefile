all:_tp_client _tp_server
libtp:
	cd /home/rd/workspace/tp-git/tp4/src
_tp_client:tp_client.cc
	g++ -o _tp_client tp_client.cc  -ltp -lpthread

_tp_server:tp_server.cc
	g++ -o _tp_server tp_server.cc -ltp -lpthread
clean:
	rm -f _*
