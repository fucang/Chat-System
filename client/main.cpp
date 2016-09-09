#include <iostream>
using namespace std;

#include <pthread.h>
#include <vector>
#include <string.h>
#include <signal.h>
#include <stdlib.h>
#include "cwindow.h"
#include "udp_data.h"
#include "udp_client.h"

cwindow win;

void* client_header(void* arg)
{
	win.create_header();
	win.myflush(win.get_header());
	string msg = "Welcon To Chat-System Of Fu-Cang";

	while(1)
	{
		win.put_str_to_win(win.get_header(), 2, 20, msg);
		win.myflush(win.get_header());

		sleep(1);
		win.clr_str_from_win(win.get_header(), 2, 1);
	}
}

void* client_output(void* arg)
{
	udp_client *client = (udp_client*)arg;
	udp_data data;

	string info;
	string nick_name, school, msg, cmd;	

	int total = 3; //输出信息的所在行

	win.create_output();
	win.myflush(win.get_output());

	while(1)
	{
		client->recv_data(info);//接收信息

		client->add_friend(info);//添加朋友

		data.to_value(info); //反序列化
		nick_name = data.get_name();
		school = data.get_school();
		msg = data.get_msg();
		cmd = data.get_cmd();

		if(msg == "QUIT" || msg == "quit" \
				||msg == "Q" || msg == "q")
		{
			client->del_friend(info); //退出了
		}

		//显示消息
		string show_msg = nick_name;
		show_msg += "-";
		show_msg += school;
		show_msg += ": ";
		show_msg += msg;
		
		win.put_str_to_win(win.get_output(), total++, 2, show_msg);
		win.myflush(win.get_output());
		total %= (LINES * 3 / 5 - 1);
		if(total == 0)
		{
			total = 3;
			win.clr_str_from_win(win.get_output(), 1, LINES * 3 / 5 - 1);
		    win.myflush(win.get_output());
		}

		usleep(100000);
	}

}

void* client_input(void* arg)
{
	udp_client* client = (udp_client*)arg;
	
	udp_data data;
	win.create_input();
	win.myflush(win.get_input());

	while(1)
	{
		win.put_str_to_win(win.get_input(), 1, 2, "Please Enter# ");
		string msg;
		win.get_str_from_win(win.get_input(), msg);
		data.set_name(client->get_nick_name());
		data.set_school(client->get_school());
		data.set_msg(msg);
		data.set_cmd("None");
		string client_msg;
		data.to_string(client_msg);
		client->send_data(client_msg);
		usleep(100000);
		win.clr_str_from_win(win.get_input(), 1, 1);
	}
}

void* client_list(void* arg)
{
	udp_client* client = (udp_client*)arg;
	win.create_flist();
	win.myflush(win.get_flist());
	while(1)
	{
		int i = 0;
		vector<string>& friends = client->get_friends_list();
		int size = friends.size();
		for(; i < size; ++i)
		{
			string& info = friends[i];
			udp_data data;
			data.to_value(info);
			string show_msg = data.get_name();
			show_msg += "-";
			show_msg += data.get_school();
			win.put_str_to_win(win.get_flist(), i+2, 2, show_msg);
		}
		win.myflush(win.get_flist());
		
		usleep(100000);
	}
}

int main(int argc, char *argv[])
{
	if(argc != 3)
	{
		cout << "./client [ip] [port]" << endl;
		return 2;
	}

	string nick_name = "fucang";
//	cout << "Please Enter Nick-Name# ";
//  cin >> nick_name;
//	
	string school = "bit";
//	cout << "Please Enter School# ";
//	cin >> school;

	udp_client client(nick_name, school);

	pthread_t header;
	pthread_t output;
	pthread_t input;
	pthread_t list;

	pthread_create(&header, NULL, client_header, (void*)&client);
	pthread_create(&output, NULL, client_output, (void*)&client);
	pthread_create(&input, NULL, client_input, (void*)&client);
	pthread_create(&list, NULL, client_list, (void*)&client);

	pthread_join(header, NULL);
	pthread_join(output, NULL);
	pthread_join(input, NULL);
	pthread_join(list, NULL);

	return 0;
}
