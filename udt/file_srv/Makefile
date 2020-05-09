all:_server _client agent _appclient
_server:server.o trans.o
	g++ -g -o _server server.o trans.o -ludt -lpthread
_client:client.o agent trans.o
	g++ -g -o _client client.o libagent.a -lpthread 
_appclient:appclient.o trans.o
	g++ -g -o _appclient appclient.o trans.o -ludt -lpthread
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
clean:all
	rm _* *.o *.a

