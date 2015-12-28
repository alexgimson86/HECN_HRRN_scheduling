#include"Priority_queue.h"

void Priority_queue::enqueue_task(Task *t)
{
	Task p(*t);
	q.push_back(p);
	count++;
}
const Task &Priority_queue::dequeue_task()
{
	method_task = q.front();
	q.pop_front();
	count--;
	return method_task;
}
void Priority_queue::print_first_element()
{
	if(!q.empty())
	{
		method_task = q.front();
		cout<<"value: "<<method_task.get_value()<<endl;
		cout<<"io_value: "<<method_task.get_io_value()<<endl;
		cout<<"io_length: "<<method_task.get_io_length()<<endl;
		cout<<"execution_time: "<<method_task.get_execution_time()<<endl<<endl;
	}
	else
		cout<<"it's empty!\n";
}
bool Priority_queue::is_empty()
{
	return q.empty();
}
void Priority_queue::decrement_execution_time()
{
	if(q[0].get_execution_time()>=1)
		q[0].set_execution_time(q[0].get_execution_time()-1);
}
void Priority_queue::rotate()
{
	if(q.size()>1)
	{
		method_task = q.front();
		q.pop_front();
		q.push_back(method_task);
	}
}
const int Priority_queue::get_remaining_exec()
{
	return q[0].get_execution_time();
}
const int Priority_queue::get_count()
{
	return count;
}
void Priority_queue::decrement_all(int slice)
{
	for(int i = 0; i < q.size();i++)
	{	
		if(q[i].get_io_length() !=0)
		{
			q[i].set_io_length(q[i].get_io_length()-slice);
			if(q[i].get_io_length()<0)
				q[i].set_io_length(0);
		}
	}
}
void Priority_queue::set_io_number(double num)
{
	q[0].set_io_value(num);
}
void Priority_queue::set_io_len(int len)
{
	q[0].set_io_length(len);
}
int Priority_queue::get_io_number()
{
	return q[0].get_io_value();
}
int Priority_queue::get_io_len()
{
	return q[0].get_io_length();
}
void Priority_queue::increment_ticks(int slice)
{
	for(int i =0; i < q.size();i++)
		q[i].set_total_ticks(q[i].get_total_ticks()+slice);
}
void Priority_queue::set_hrrn_number(int slice)
{
	//increment wait time by the slice number
	//this gets called at end of the slice
	//once wait time is incremented, we 
	//set the new hrrn number
	//first task that was executing doesn't get wait
	//time incremented.
	if(!is_empty())
		q[0].set_hrrn_number();

	for(int i =1; i < q.size();i++)
	{
		q[i].set_wait_time(q[i].get_wait_time()+slice);
		q[i].set_hrrn_number();
	}
}
void Priority_queue::set_hecn_number(int slice)
{
	//increment wait time by the slice number
	//this gets called at end of the slice
	//once wait time is incremented, we 
	//set the new hecn number
	//first task that was executing doesn't get wait
	//time incremented.
	if(!is_empty())
		q[0].set_hecn_number();

	for(int i =1; i < q.size();i++)
	{
		q[i].set_wait_time(q[i].get_wait_time()+slice);
		q[i].set_hecn_number();
	}
}
void Priority_queue::sort_hrrn()
{
	int j;
	Task temp;
	//insertion sort, efficient for arrays that
	//are almost completely sorted already
	for(int i = 1; i <q.size();i++)
	{
		j =i;
		while(j>0 && q[j].get_hrrn_number() > q[j-1].get_hrrn_number())
		{
			temp = q[j-1];
			q[j-1] = q[j];
			q[j] = temp;
			j--;
		}
	}
}
void Priority_queue::sort_hecn()
{
	int j;
	Task temp;
	//insertion sort, efficient for arrays that
	//are almost completely sorted already
	for(int i = 1; i <q.size();i++)
	{
		j =i;
		while(j>0 && q[j].get_hecn_number() > q[j-1].get_hecn_number())
		{
			temp = q[j-1];
			q[j-1] = q[j];
			q[j] = temp;
			j--;
		}
	}

}
void Priority_queue::increment_total_power_used()
{
	q[0].set_total_power_used(q[0].get_power());
}
const int Priority_queue::get_total_power_used()
{
	int total =0;
	for(int i =0; i < q.size();i++)
		total+=q[i].get_total_power_used();

	return total;
}
void Priority_queue::increment_wait_time(int n)
{
	if(!q.empty())
		q[0].set_wait_time(q[0].get_wait_time()+n);
}