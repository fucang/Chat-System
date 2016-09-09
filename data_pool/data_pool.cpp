/*************************************************************************
	> File Name: data_pool.cpp
	> Author: fucang_zxx
	> Mail: fucang_zxx@163.com 
	> Created Time: Mon 22 Aug 2016 08:29:23 PM CST
 ************************************************************************/

#include <iostream>
using namespace std;

#include "data_pool.h"


data_pool::data_pool(int size)
	:pool(size), cap(size), space_step(0), data_step(0)
//	 ,space_sem(size),data_sem(0)
{
	sem_init(&space_sem, 0, cap);
	sem_init(&data_sem, 0, 0);
}

data_pool::~data_pool()
{

}

void data_pool::get_data(string &out)
{
	sem_wait(&data_sem); //P data_sem - 1

	out = pool[data_step++];
	data_step %= cap;

	sem_post(&space_sem);//V space_sem + 1
}

void data_pool::put_data(const string &in)
{
	sem_wait(&space_sem);

	pool[space_step++] = in;
	space_step %= cap;

	sem_post(&data_sem);
}

