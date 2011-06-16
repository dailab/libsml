CFLAGS+=-I./include/ -fPIC -g -Wall

LIB_DIR=./lib
OBJ_LIB=$(LIB_DIR)/libsml.o
DYN_LIB=$(LIB_DIR)/libsml.so
ST_LIB=$(LIB_DIR)/libsml.a

OBJS = \
	src/sml.o \
	src/sml_attention_response.o \
	src/sml_transport.o \
	src/sml_octet_string.o \
	src/sml_shared.o \
	src/sml_number.o \
	src/sml_message.o \
	src/sml_time.o \
	src/sml_list.o \
	src/sml_status.o \
	src/sml_value.o \
	src/sml_tree.o \
	src/sml_boolean.o \
	src/sml_crc16.o \
	src/sml_open_request.o \
	src/sml_open_response.o \
	src/sml_get_list_request.o \
	src/sml_get_list_response.o \
	src/sml_close_request.o \
	src/sml_close_response.o \
	src/sml_set_proc_parameter_request.o \
	src/sml_get_proc_parameter_request.o \
	src/sml_get_profile_pack_request.o \
	src/sml_get_profile_pack_response.o \


libsml: $(DYN_LIB) $(ST_LIB) $(OBJ_LIB)

$(DYN_LIB): $(OBJS)
	$(LD) -shared -o $@ $^

$(OBJ_LIB): $(OBJS)
	$(LD) -r -o $@ $^

$(ST_LIB): $(OBJS)
	$(AR) -rs $@ $^

.PHONY: clean
clean:
	@rm -f src/*.o
	@rm -f $(LIB_DIR)/*.so $(LIB_DIR)/*.a $(LIB_DIR)/*.o

