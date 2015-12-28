#include"Task.h"
#include<iostream>
#include<fstream>
using namespace std;

#ifndef SUCCESS_ARRAY_H
#define SUCCESS_ARRAY_H

class Success_array
{
private:
	Task *ptr;
	int index;
	int size;
public:
	Success_array();
	const Task & get_task(int index);
	void insert(const Task &t);
	int get_index(){return index;}
	void write_to_file(ofstream &output_file);
	void write_to_file_hecn(ofstream &output_file);
	void print_to_screen();
	const int get_total_power_used();
	~Success_array();
};
#endif