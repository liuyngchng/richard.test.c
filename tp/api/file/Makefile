all:agent f_srv
libudt:
	cd /home/rd/workspace/udt-git/udt4/src
agent:agent.cc
	g++ -o _agent agent.cc  -ludt -lpthread
f_srv:f_srv.cc
	g++ -o _f_srv f_srv.cc -ludt -pthread

clean:
	rm -f _*
