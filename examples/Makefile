CFLAGS += -I../sml/include/ -g -Wall
OBJS = sml_server.o
LIBS = -L../sml/lib/ ../sml/lib/libsml.o -luuid

sml_server : $(OBJS)
	$(CC) $(CFLAGS) $(LIBS) -o sml_server $(OBJS)

.PHONY: clean
clean:
	@rm -f *.o
	@rm -f sml_server
