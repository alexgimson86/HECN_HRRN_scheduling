#include"Success_array.h"
#include<iostream>
#include<fstream>
using namespace std;

Success_array::Success_array()
{
	size = 5;
	ptr = new Task [size];
	index = 0;
}
const Task & Success_array::get_task(int i)
{
	return ptr[i];
}
void Success_array::insert(const Task &t)
{
	if(index == size-1)
	{
		int new_size = size*1.5;
		Task *temp_ptr = new Task [new_size];
		for(int i = 0; i < size; i++)
			temp_ptr[i] = ptr[i];

		delete [] ptr;
		size =new_size;
		ptr = temp_ptr;
	}
	ptr[index]=t;
	index++;
}
Success_array::~Success_array()
{
	delete [] ptr;
}
void Success_array::write_to_file(ofstream &output_file)
{
	for(int i =0; i < index;i++)
	{
		output_file<<"value: "<<ptr[i].get_value()<<endl;
		output_file<<"io_value: "<<ptr[i].get_io_value()<<endl;
		output_file<<"io_length: "<<ptr[i].get_io_length()<<endl;
		output_file<<"execution_time: "<<ptr[i].get_execution_time()<<endl;
		output_file<<"total_wait_time: "<<ptr[i].get_wait_time()<<endl;
		output_file<<"Final hrrn number: "<<ptr[i].get_hrrn_number()<<endl;
		output_file<<"total_power_used: "<<ptr[i].get_total_power_used()<<endl<<endl;
	}
}
void Success_array::write_to_file_hecn(ofstream &output_file)
{
	for(int i =0; i < index;i++)
	{
		output_file<<"value: "<<ptr[i].get_value()<<endl;
		output_file<<"io_value: "<<ptr[i].get_io_value()<<endl;
		output_file<<"io_length: "<<ptr[i].get_io_length()<<endl;
		output_file<<"execution_time: "<<ptr[i].get_execution_time()<<endl;
		output_file<<"total_wait_time: "<<ptr[i].get_wait_time()<<endl;
		output_file<<"Final hecn number: "<<ptr[i].get_hecn_number()<<endl;
		output_file<<"total_power_used: "<<ptr[i].get_total_power_used()<<endl<<endl;
	}
}
void Success_array::print_to_screen()
{
	for(int i =0; i < index;i++)
	{
		cout<<"value: "<<ptr[i].get_value()<<endl;
		cout<<"io_value: "<<ptr[i].get_io_value()<<endl;
		cout<<"io_length: "<<ptr[i].get_io_length()<<endl;
		cout<<"execution_time: "<<ptr[i].get_execution_time()<<endl;
		cout<<"total_ticks: "<<ptr[i].get_total_ticks()<<endl;
		cout<<"total_power_used: "<<ptr[i].get_total_power_used()<<endl<<endl;
	}
}
const int Success_array::get_total_power_used()
{
	int total =0;
	for(int i =0; i < index;i++)
		total+=ptr[i].get_total_power_used();

	return total;
}
