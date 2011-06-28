CFLAGS += -I../sml/include/ -Wall
LIBSML = ../sml/lib/libsml.a

UNITY = \
	unity/unity.o \
	unity/unity_fixture.o

OBJS = \
	src/test_sml_octet_string.o

test_run: libsml test
	@./test

test : $(UNITY) $(OBJS)
	$(CC) $(CFLAGS) $(LIBSML) $^ test_main.c -o test

.PHONY: code
libsml : 
	@$(MAKE) -C ../sml

%.o : %.c
	$(CC) $(CFLAGS) -c $^ -o $@

.PHONY: clean
clean :
	@rm -f unity/*.o
	@rm -f src/*.tst






