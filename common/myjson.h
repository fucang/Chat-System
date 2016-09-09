
#ifndef __MYJSON_H__
#define __MYJSON_H__

#include <iostream>
using namespace std;

#include <string>
#include "json/json.h"

class myjson
{
	public:
		myjson();
		~myjson();
		//序列化
		static void serialize(Json::Value &val, string &out);
		//反序列化
		static void unserialize(string &in, Json::Value &val);
};

#endif
