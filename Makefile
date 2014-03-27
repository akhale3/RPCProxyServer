GEN_SRC := server.cpp webserver_constants.cpp webserver_types.cpp lrucache.cpp fifocache.cpp random.cpp
GEN_OBJ := $(patsubst %.cpp,%.o, $(GEN_SRC))
CURL_SRC := webcurl.c
CURL_OBJ := $(patsubst %.c,%.o, $(CURL_SRC))

THRIFT_DIR := /usr/local/include/thrift
BOOST_DIR := /usr/local/include

INC := -I$(THRIFT_DIR) -I$(BOOST_DIR)
CC := gcc

.PHONY: all clean

all: webserver webclient

%.o: %.c
	$(CC) -Wall -DHAVE_INTTYPES_H -DHAVE_NETINET_IN_H $(INC) -c $< -o $@ -lpthread -lresolv -lnsl -lcurl

%.o: %.cpp
	$(CXX) -Wall -DHAVE_INTTYPES_H -DHAVE_NETINET_IN_H $(INC) -c $< -o $@

webserver: webserver.o $(GEN_OBJ) webcurl.o
	$(CXX) $^ -o $@ -L/usr/local/lib -lcurl -lthrift

webclient: client.o $(GEN_OBJ)
	$(CXX) $^ -o $@ -L/usr/local/lib -lthrift

clean:
	$(RM) *.o webserver webclient
