#include "udp_client.h"

static void print_log(const char *msg, const char *fun, const int line)
{
	std::cerr << "[ " << msg << " ] " << "[ " << fun << " ] " << "[ " << line << " ]"<<endl;
}

udp_client::udp_client(const string& _nick_name, const string& _school, const string &_ip, const int _port)
	:nick_name(_nick_name),school(_school),
	dst_ip(_ip),dst_port(_port),sock(-1)
{
	sock = init();
	udp_data data;
	data.set_name(nick_name);
	data.set_school(school);

	string self;
	data.to_string(self);
	this->friends_list.push_back(self);
}

udp_client::~udp_client()
{
	if(sock > 0)
	{
		close(sock);
		sock = -1;
	}
} 

int udp_client::init()
{
	int lsk = socket(AF_INET, SOCK_DGRAM, 0);
	if(lsk < 0)
	{
		print_log("CREATE_SOCKET ARREA", __FUNCTION__, __LINE__);
		exit(1);
	}
	//客户端不需要绑定
	return lsk;
}

int udp_client::recv_data(string &out)
{
	//接收数据，将接收到的数据保存到out
	struct sockaddr_in remote;//输出型参数
	socklen_t len = sizeof(remote);
	char buf[1024];
	ssize_t _s = recvfrom(sock, buf, sizeof(buf) - 1, 0, (struct sockaddr*)&remote, &len);
	if(_s > 0)
	{
		buf[_s - 1] = '\0';
		out = buf;
	}
	else if(_s == 0)
	{
		print_log("server is close", __FUNCTION__, __LINE__);
	}
	else
	{
		print_log("recv_data err", __FUNCTION__, __LINE__);
	}
	return _s;	   
}

int udp_client::send_data(string &data)
{
	struct sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr(dst_ip.c_str());
	server.sin_port = htons(dst_port);
	socklen_t len = sizeof(server);
	ssize_t _s = sendto(sock, data.c_str(), data.size(), 0, \
			(struct sockaddr*)&server, len);
	if(_s < 0)
	{
		print_log("client send_data err", __FUNCTION__, __LINE__);
	}
	return _s;
}


void udp_client::set_server_ip(const string &_ip)
{
	this->dst_ip = _ip;
}

void udp_client::set_server_port(int _port)
{
	this->dst_port = _port;
}

void udp_client::add_friend(string& _key)
{
	//先判断是否存在
	if(!is_friend_exist(_key))
	{
		this->friends_list.push_back(_key);
	}
}
void udp_client::del_friend(string& _key)
{
	vector<string>::iterator it = this->friends_list.begin();
	while(*it != _key)
	{
		++it;
	}
	if(it != this->friends_list.end())
	{
		this->friends_list.erase(it);
	}
}

vector<string>& udp_client::get_friends_list()
{
	return this->friends_list;
}

bool udp_client::is_friend_exist(string& _key)
{
	int i = 0;
	int size = this->friends_list.size();
	for(; i < size; ++i)
	{
		if(_key == this->friends_list[i])
		{
			return true;
		}
	}

	return true;
}

string& udp_client::get_nick_name()
{
	return this->nick_name;
}

string& udp_client::get_school()
{
	return this->school;
}

