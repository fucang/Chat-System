#ifndef __UDP_CLIENT_H__
#define __UDP_CLIENT_H__

#include <iostream>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>
#include <vector>
#include "cwindow.h"
#include "udp_data.h"

using namespace std;

class udp_client
{
	public:
		udp_client(const string& _nick_name = "", const string& _school = "",\
				const string &_ip = "0", const int _port = 8080);
		~udp_client();
		int init();
		int recv_data(string &out);
		int send_data(string &data);

		void set_server_ip(const string &_ip);
		void set_server_port(int _port);

		void add_friend(string& _key);
		void del_friend(string& _key);

		string& get_nick_name();
		string& get_school();
		vector<string>& get_friends_list();
		
	private:
		bool is_friend_exist(string& _key);

	private:
		string nick_name;
		string school;
		string dst_ip;
		int dst_port;
		int sock;
		vector<string> friends_list;
};

#endif //__UDP_CLIENT_H__
