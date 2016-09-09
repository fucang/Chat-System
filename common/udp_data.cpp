/*************************************************************************
	> File Name: udp_data.cpp
	> Author: fucang_zxx
	> Mail: fucang_zxx@163.com 
	> Created Time: 2016年08月23日 星期二 19时49分30秒
 ************************************************************************/

#include <iostream>
using namespace std;

#include "udp_data.h"

udp_data::udp_data(const string& _nick_name, const string& _school,\
		const string& _msg, const string& _cmd)
:nick_name(_nick_name),school(_school),msg(_msg),cmd(_cmd)
{

}

udp_data::~udp_data()
{

}

string& udp_data::get_name()
{
	return this->nick_name;
}

string& udp_data::get_school()
{
	return this->school;
}

string& udp_data::get_msg()
{
	return this->msg;
}

string& udp_data::get_cmd()
{
	return this->cmd;
}

void udp_data::set_name(const string &_nick_name)
{
	this->nick_name = _nick_name;
}

void udp_data::set_school(const string &_school)
{
	this->school = _school;
}

void udp_data::set_msg(const string &_msg)
{
	this->msg = _msg;
}

void udp_data::set_cmd(const string &_cmd)
{
	this->cmd = _cmd;
}

//向服务器端发送，将昵称学校等合并
void udp_data::to_string(string &out)
{
	Json::Value val;
	val["nick_name"] = this->nick_name;
	val["school"] = this->school;
	val["msg"] = this->msg;
	val["cmd"] = this->cmd;
	myjson::serialize(val, out);
}

//拆解
void udp_data::to_value(string &in)
{
	Json::Value val;
    myjson::unserialize(in, val);
	//asString()  asInt()  asFront()
	this->nick_name = val["nick_name"].asString();
	this->school = val["school"].asString();
	this->msg = val["msg"].asString();
	this->cmd = val["cmd"].asString();

}

//测试
//int main()
//{
//	udp_data ud("fucang", "SUST", "nihao", "None");
//	string str;
//	ud.to_string(str);
//	cout<<str<<endl;
//	
//	return 0;
//}
