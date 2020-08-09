all:_client _server
_client:client.o lt_function.o
	gcc -o $@ $^
_server:server.o lt_function.o
	gcc -o $@ $^
%.o:%.c
	gcc -o $@ -c $<
clean:
	rm -f *.o _*
