#include <zmqpp/zmqpp.hpp>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <time.h>

using namespace std;

const string endpoint = "tcp://localhost:4242";

// initialize the 0MQ context
zmqpp::context context;

// generate a push socket
zmqpp::socket_type type = zmqpp::socket_type::push;
zmqpp::socket socket (context, type);

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
  message << "0" << 1;
  sink.send(message);

  //  Initialize random number generator
  srandom ((unsigned) time (NULL));

  //  Send 100 tasks
  int task_nbr;
  int total_msec = 0;     //  Total expected cost in msecs
  for (task_nbr = 0; task_nbr < 100; task_nbr++) {
      int workload;
      //  Random workload from 1 to 100msecs
      workload = rand() % 100 + 1;
      total_msec += workload;

      //message.rebuild(10);
      message << '\0' << 10;
      cout << "Workload: " << workload;
      sender.send(message);
  }
  cout << "Total expected cost: " << total_msec << " msec" << endl;
  sleep (1);              //  Give 0MQ time to deliver
}

int main(int argc, char const *argv[]) {
  taskVentilator();
  return 0;
}
