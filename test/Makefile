CFLAGS += -I../sml/include/ -Wall
LIBSML = ../sml/lib/libsml.a

UNITY = \
	unity/unity.o \
	unity/unity_fixture.o

OBJS = \
	src/test_helper.o \
	src/sml_octet_string_test.o \
	src/sml_buffer_test.o \
	src/sml_number_test.o

test_run: libsml test
	@./test

test : $(UNITY) $(OBJS) $(LIBSML)
	$(CC) $(CFLAGS) $(LIBSML) $^ test_main.c -o test

.PHONY: code
libsml : 
	@$(MAKE) -C ../sml

%.o : %.c
	$(CC) $(CFLAGS) -c $^ -o $@

.PHONY: clean
clean :
	@rm -f unity/*.o
	@rm -f src/*.o






