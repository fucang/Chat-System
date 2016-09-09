/*************************************************************************
	> File Name: data_pool.h
	> Author: fucang_zxx
	> Mail: fucang_zxx@163.com 
	> Created Time: 2016年08月22日 星期一 20时10分50秒
 ************************************************************************/

#ifndef __DATA_POOL_H__
#define __DATA_POOL_H__

#include <iostream>
using namespace std;

#include <vector>
#include <string>
#include <semaphore.h>

#define _CAP_ 1024

//数据池
class data_pool
{
	public:
		data_pool(int size = _CAP_);
		~data_pool();
		void get_data(string &out);
		void put_data(const string &in);

	private:
		vector<string> pool; //数据池：环形队列
		int cap;//容量
		int space_step;
		int data_step;
		sem_t space_sem;
		sem_t data_sem;
};

#endif
