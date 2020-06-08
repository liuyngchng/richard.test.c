all:_server _client agent _appclient _md5test
_server:server.o trans.o
	g++ -g -o _server server.o trans.o -ludt -lpthread
_client:client.o agent trans.o
	g++ -g -o _client client.o libagent.a -lpthread 
_appclient:appclient.o trans.o
	g++ -g -o _appclient appclient.o trans.o -ludt -lpthread
_md5test:md5test.o md5.o
	g++ -o _md5test md5test.o md5.o
agent:agent.o
	ar crv libagent.a agent.o trans.o udt_o/*.o 
trans.o:trans.cc
	g++ -g -c trans.cc
server.o:server.cc trans.h
	g++ -g -c server.cc
client.o:client.cc agent.h
	g++ -g -c client.cc
agent.o:agent.cc trans.h
	g++ -g -c -fPIC agent.cc
appclient.o:appclient.cc trans.h
	g++ -g -c appclient.cc
md5.o:md5.cc md5.h
	g++ -g -c md5.cc
md5test.o:md5test.cc md5.h
	g++ -g -c md5test.cc
clean:all
	rm _* *.o *.a

