#include"Task.h"
#include<time.h>
#include<stdlib.h>

Task::Task()
{
	value = 0;
	io_length=0;
	io_value=0;
	execution_time=0;
	total_ticks=0;
	hrrn_number= 1.0;
	hecn_number = 1.0;
	wait_time=0;
	total_power_used=0;
	power=0;

}
Task::Task(double v,int exec,int p)
{
	execution_time = exec;
	value = v;
	power=p;
	io_length=0;
	io_value = 0;
	total_ticks=0;
	hrrn_number = 1.0;
	hecn_number =1.0;
	wait_time = 0;
	total_power_used=0;
}
const double Task::get_value()
{
	return value;
}
const int Task::get_io_length()
{
	return io_length;
}
const double Task::get_io_value()
{
	return io_value;
}
void Task::set_io_length(int l)
{
	io_length = l;
}
void Task::set_io_value(double v)
{
	io_value = v;
}
void Task::set_value(double v)
{
	value = v;
}
void Task::set_execution_time(int exec_time)
{
	execution_time = exec_time;
}
const int Task::get_execution_time()
{
	return execution_time;
}
void Task::set_total_ticks(int t)
{
	total_ticks=t;
}
const int Task::get_total_ticks()
{
	return total_ticks;
}
const double Task::get_hecn_number()
{
	return hecn_number;
}
void Task::set_hecn_number()
{
	if(execution_time!=0)
		hecn_number = (wait_time+execution_time*power)/static_cast<double>(execution_time*power);
}
void Task::set_hrrn_number()
{
	//execution time is remaining execution time
	//change to a double because we want hrrn number to be a double
	//check for division by zero
	if(execution_time!=0)
		hrrn_number = (wait_time+execution_time)/static_cast<double>(execution_time);
}
const double Task::get_hrrn_number()
{
	return hrrn_number;
}
void Task::set_wait_time(int t)
{
	wait_time = t;
}
const int Task::get_wait_time()
{
	return wait_time;
}
void Task::set_power(int p)
{
	power=p;
}
void Task::set_total_power_used(int t)
{
	total_power_used += t;
}
const int Task::get_power()
{
	return power;
}
const int Task::get_total_power_used()
{
	return total_power_used;
}