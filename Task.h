#ifndef TASK_H
#define TASK_H

class Task
{
private:
	double value;
	int io_length;
	double io_value;
	int execution_time;
	int total_ticks;
	double hrrn_number;
	double hecn_number;
	int wait_time;
	int power;
	int total_power_used;
public:
	Task();
	Task(double v,int exec,int p);
	void set_io_length(int l);
	void set_io_value(double v);
	void set_value(double v);
	const double get_io_value();
	const int get_io_length();
	const double get_value();
	const int get_execution_time();
	void set_execution_time(int exec_time);
	void set_total_ticks(int t);
	const int get_total_ticks();
	const double get_hrrn_number();
	void set_hrrn_number();
	const double get_hecn_number();
	void set_hecn_number();
	void set_wait_time(int);
	const int get_wait_time();
	const int get_power();
	const int get_total_power_used();
	void set_power(int);
	void set_total_power_used(int);
};
#endif