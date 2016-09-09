ROOT_PATH=$(shell pwd)
CLIENT=$(ROOT_PATH)/client
SERVER=$(ROOT_PATH)/server

ALL=$(SERVER) $(CLIENT)

.PHONY:output
output:
	@for i in "echo $(ALL)";\
	do\
		cd $$i;\
		make;\
		cd -;\
	done
	@mkdir output
	@cp $(SERVER)/udp_server output
	@cp $(CLIENT)/udp_client output

.PHONY:clean
clean:
	@rm -rf output
	@for i in 'echo $(ALL)';\
	do\
		cd $$i;\
		make clean;\
		cd -;\
	done

