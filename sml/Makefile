UNAME := $(shell uname)
CFLAGS += -I./include/ -fPIC -g -Wall

# Available Flags:
# _NO_UUID_LIB - compile without uuid lib

ifeq ($(UNAME), Linux)
LIBS = -luuid
endif

LIB_DIR=./lib
OBJ_LIB=$(LIB_DIR)/libsml.o
DYN_LIB=$(LIB_DIR)/libsml.so
ST_LIB=$(LIB_DIR)/libsml.a

OBJS = \
	src/sml_file.o \
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
	src/sml_get_proc_parameter_response.o \
	src/sml_get_profile_pack_request.o \
	src/sml_get_profile_pack_response.o \
	src/sml_get_profile_list_request.o 

ifeq ($(UNAME), Linux)
libsml: $(DYN_LIB) $(ST_LIB) $(OBJ_LIB)
endif
ifeq ($(UNAME), Darwin)
libsml: $(ST_LIB) $(OBJ_LIB)
endif

$(DYN_LIB): $(OBJS)
	$(LD) $(LIBS) -shared -o $@ $^

$(OBJ_LIB): $(OBJS)
	$(LD) -r -o $@ $^

$(ST_LIB): $(OBJS)
	$(AR) -rs $@ $^

.PHONY: clean
clean:
	@rm -f src/*.o
	@rm -f $(LIB_DIR)/*.so $(LIB_DIR)/*.a $(LIB_DIR)/*.o

