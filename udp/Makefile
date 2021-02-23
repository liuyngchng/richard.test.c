all:_client _server
_client:client.o lt_function.o -lm
	gcc -g -o $@ $^
_server:server.o lt_function.o -lm
	gcc -g -o $@ $^
%.o:%.c
	gcc -g -o $@ -c $<
clean:
	rm -f *.o _*
