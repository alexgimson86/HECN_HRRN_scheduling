#include"Task.h"
#include"Priority_queue.h"
#include "Success_array.h"
#include<iostream>
#include<time.h>
#include<cstdlib>
#include<fstream>

using namespace std;

double generate_number();
int generate_execution_time();
int generate_io_length();
int generate_power();
void print_output(Priority_queue &,Priority_queue &,Success_array &, ofstream &,int count);
void scheduling(int count);

int main()
{   
	int count =0;
	srand(time(NULL));
	//put the loops in a function to make
	//them easier to read
	scheduling(count);
	scheduling(count+1);

	//system("pause");
	return 0;
}
//generate number 0-1 for determining creation of a task or io value
double generate_number()
{
	return (double)rand()/RAND_MAX;
}
//execution time betweem 25-34
int generate_execution_time()
{
	return rand()%41 + 10;
}
//io_execution time between 20-49
int generate_io_length()
{
	return rand()%30 + 15;
}
int generate_power()
{
	return rand()%21 +10;
}
void print_output(Priority_queue &q,Priority_queue &io,Success_array &s, ofstream &outfile,int count)
{
	if(count ==0)
		cout<<"HRRN SCHEDULING INFO.\n";
	else
		cout<<"HECN SCHEDULING INFO.\n";
	cout<<"--------------------\n";
	cout<<"Throughput: "<<s.get_index()/1500.0<<endl;
	int total =0;
	for(int i = 0; i < s.get_index();i++)
	{
		Task temp = s.get_task(i);
		total+=temp.get_wait_time();
	}
	if(s.get_index()!=0)
		cout<<"Average Latency: "<<total/s.get_index()<<endl;

	int total_energy = 0;
	total+=s.get_total_power_used();
	total+=q.get_total_power_used();
	total+=io.get_total_power_used();

	cout<<"Total energy dissipated: "<<total<<endl;

	if(count ==0)
		s.write_to_file(outfile);
	else
		s.write_to_file_hecn(outfile);

	cout<<"successful tasks have printed to file."<<endl<<endl;
	outfile.close();
}
void scheduling(int count)
{
	Task *ptr;
	Priority_queue queue;
	Priority_queue io_queue;
	Success_array success;

	int value_status = 0;
	int finished_status = 0;
	int io_status = 0;
	int slice = 20;

	ofstream output_file;
	if(count ==0)
		output_file.open("hrrn_output.txt");
	else
		output_file.open("hecn_output.txt");

	//75 slices, 75*20 = 1500 ticks
	//***HRRN SCHEDULING***///
	for(int i = 0; i <75;i ++)
	{
		//slices, 20 ticks in a slice
		for(int j = 0; j<slice;j++)
		{
			double number = generate_number();
			//setting the io_value and length if number > .95 also will not generate if
			//remaining execution time is zero i.e. task is complete
			if(number > 0.97&& !queue.is_empty() && io_status !=1 && queue.get_remaining_exec()!=0)
			{
				queue.set_io_number(number);
				queue.set_io_len(generate_io_length());
				io_status = 1;
			}
			//decrement the execution time if io event hasnt occured
			if(io_status!=1)
			{
				if(!queue.is_empty() && queue.get_remaining_exec()>=1)
				{
					queue.decrement_execution_time();
					queue.increment_total_power_used();
				}
			}
			else
				queue.increment_wait_time(1);

			if(value_status ==0)
			{
				//generate new task object with execution time and value
				ptr = new Task(generate_number(),generate_execution_time(),generate_power());
				//if value > .9 set status and save this object
				if(ptr->get_value()>.97)
					value_status =1;
				//otherwise delete it and try again next iteration
				if(value_status == 0)
					delete ptr;
			}
			else
				ptr->set_wait_time(ptr->get_wait_time()+1);
		}
		//decrement io length of tasks in io
		io_queue.decrement_all(slice);
		io_queue.increment_wait_time(slice);
		if(count ==0)
		{	
			queue.set_hrrn_number(slice);
			io_queue.set_hrrn_number(slice);
		}
		else
		{
			queue.set_hecn_number(slice);
			io_queue.set_hecn_number(slice);
		}
		//remove task if execution time is 0
		//also set flag since theres no need to rotate
		if(!queue.is_empty() && queue.get_remaining_exec() == 0)
		{
			success.insert(queue.dequeue_task());
			finished_status = 1;
		}
		if(io_status ==1)
		{
			Task t =queue.dequeue_task();
			io_queue.enqueue_task(&t);
		}
		//check io queue for finished io tasks
		int size = io_queue.get_count();
		for(int i =0; i < size;i++)
		{
			//if len -0 then task done
			if(io_queue.get_io_len()==0)
			{
				Task t = io_queue.dequeue_task();
				queue.enqueue_task(&t);
			}
			//if first task len !=0 then rotate it to
			//the end and look at a different one
			else
				io_queue.rotate();
		}
		//if ptr has a value over .9 value_status is 1
		//will insert new task at the end of queue before
		//old value gets rotated
		if(value_status ==1)
		{
			if(count==0)
				ptr->set_hrrn_number();
			else
				ptr->set_hecn_number();

			queue.enqueue_task(ptr);
			value_status =0;
			delete ptr;
		}
		finished_status = 0;
		io_status=0;
		//sort them with hrrn numbers, highest first
		if(count == 0)
			queue.sort_hrrn();
		else
			queue.sort_hecn();
	}
	print_output(queue,io_queue,success,output_file,count);
}

