ROOT_PATH=$(shell pwd)

test_data:myjson.cpp udp_data.cpp
	g++ -o $@ $^ -L$(ROOT_PATH)/../lib/lib -I$(ROOT_PATH)/../lib/include -ljsoncpp

.PHONY:clean
clean:
	rm -f test_data


