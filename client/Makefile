
ROOT_PATH=$(shell pwd)
CC=g++
CLIENT=udp_client
COMMON=$(ROOT_PATH)/../common
LIB=$(ROOT_PATH)/../lib
WINDOW=$(ROOT_PATH)/../window

INCLUDE=-I$(COMMON) -I$(LIB)/include -I$(WINDOW)
LIB_PATH=-L$(LIB)/lib

LDFLAGS=-ljsoncpp -lpthread -lncurses

SRC=$(shell ls *.cpp)
SRC+=$(shell cd $(COMMON);ls *.cpp)
SRC+=$(shell cd $(WINDOW);ls *.cpp)

OBJ=$(SRC:.cpp=.o)

$(CLIENT):$(OBJ)
	$(CC) -o $@ $^ $(LIB_PATH) $(LDFLAGS)
%.o:%.cpp
	$(CC) -c $< $(INCLUDE)
%.o:$(COMMON)/%.cpp
	$(CC) -c $< $(INCLUDE)
%.o:$(WINDOW)/%.cpp
	$(CC) -c $< $(INCLUDE)

.PHONY:clean
clean:
	rm -f $(CLIENT) *.o

.PHONY:debug
debug:
	@echo $(ROOT_PATH)
	@echo $(SRC)
	@echo $(OBJ)

