/*************************************************************************
	> File Name: myjson.cpp
	> Author: fucang_zxx
	> Mail: fucang_zxx@163.com 
	> Created Time: 2016年08月23日 星期二 19时27分29秒
 ************************************************************************/

#include <iostream>
using namespace std;

#include "myjson.h"

myjson::myjson()
{

}

myjson::~myjson()
{

}

void myjson::serialize(Json::Value &val, string &out)
{
#ifdef __DEBUG__
	Json::FastWriter writer;//快速序列化
	out = writer.write(val);
#else
	Json::StyledWriter writer;
	out = writer.write(val);
#endif

}

void myjson::unserialize(string &in, Json::Value &val)
{
	Json::Reader reader;
	reader.parse(in, val, false);
}


