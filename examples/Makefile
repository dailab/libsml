UNAME := $(shell uname)
CFLAGS += -I../sml/include/ -g -Wall
OBJS = sml_server.o

ifeq ($(UNAME), Linux)
LIBS = -L../sml/lib/ ../sml/lib/libsml.o -luuid
endif
ifeq ($(UNAME), Darwin)
LIBS = -L../sml/lib/ ../sml/lib/libsml.o
endif


sml_server : $(OBJS)
	$(CC) $(CFLAGS) $(LIBS) -o sml_server $(OBJS)

.PHONY: clean
clean:
	@rm -f *.o
	@rm -f sml_server
