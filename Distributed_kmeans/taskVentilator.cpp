#include <zmqpp/zmqpp.hpp>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <time.h>
#include <queue>
#include <vector>
#include <functional>
#include <utility>
#include <list>
#include <iterator>

using namespace std;

// Initialize the 0MQ context
zmqpp::context context;

// Generate a push socket
zmqpp::socket_type type = zmqpp::socket_type::push;
zmqpp::socket socket (context, type);

class SSD
{
public:
	int priority;
	int k_number;

	SSD(int priority, int k_number)
		: priority(priority), k_number(k_number)
	{

	}
};

struct SSDCompare
{
	bool operator()(const SSD &t1, const SSD &t2) const
	{
		int t1value = t1.priority * 1000 + t1.k_number;
		int t2value = t2.priority * 1000 + t2.k_number;
		return t1value < t2value;
	}
};

// Get a k_ssd
int getSSD(int k) {
	list<int> ssd_list {30, 23, 20, 18, 15};
	auto ssd_list_front = ssd_list.begin();
	advance(ssd_list_front, k);
	// cout << *ssd_list_front << '\n';
	return *ssd_list_front;
}

// Get three (3) values of k and throw the best k with its priority.
pair<int,int> getBestK(int prev_k, int actual_k, int next_k) {
	double slope1 = 0; // Pendiente 1
	double slope2 = 0; // Pendiente 2
	double slope_change = 0; //(cambio de pendiente)
	int prev_kssd = getSSD(prev_k);
	int actual_kssd = getSSD(actual_k);
	int next_kssd = getSSD(next_k);

	//slope = (y2-y1)/(x2-x1)
	slope1 = (prev_kssd - actual_kssd)/(prev_k - actual_k);
	slope2 = (next_kssd - actual_kssd)/(next_k - actual_k);
	slope_change = slope1 - slope2;

	// // Condition to set the best k with its priority.
	// if (/* condition */) {
	// 	/* code */
	// }
	// else{
	//
	// }

	pair <int,int> best_k;
	best_k.first = 5; //priority
	best_k.second = prev_k; //Value of k
	int priority = best_k.first;
	int k_value = best_k.second;
	cout << "Priority: "<< priority << " Value of k: "<< k_value;
	cout << endl;
	return {priority, k_value};
}

void taskVentilator() {

  //  Socket to send messages on
  zmqpp::socket sender(context, type);
  sender.bind("tcp://*:5557");

  cout << "Press Enter when the workers are ready: " << endl;
  getchar ();
  cout << "Sending tasks to workers…\n" << endl;

  //  The first message is "0" and signals start of batch
  zmqpp::socket sink(context, type);
  sink.connect("tcp://localhost:5558");
  zmqpp::message message;
  //The next 2 lines shows the way to send a message.
  message << "0";
  sink.send(message);

  //  Initialize random number generator
  srandom ((unsigned) time (NULL));

  // Send 100 tasks
  int task_nbr;
  int total_msec = 0;     //  Total expected cost in msecs
  for (task_nbr = 0; task_nbr < 100; task_nbr++) {
      int workload;
      //  Random workload from 1 to 100msecs
      workload = rand() % 100 + 1;
      total_msec += workload;
      char string [10];
      sprintf (string, "%d", workload);
      cout << "Workload: " << string <<endl;
      sender.send(string);

  // Send the next k to the workers
  // zmqpp::message k;
  // k << "10";
  // sender.send(k);

  }
  cout << "Total expected cost: " << total_msec << " msec" << endl;
  sleep (1);              //  Give 0MQ time to deliver
}

int main(int argc, char const *argv[]) {
  taskVentilator();
  getBestK(1,2,3);
  return 0;
}
