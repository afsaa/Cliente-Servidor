#include <zmqpp/zmqpp.hpp>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <time.h>
#include <sys/time.h>

using namespace std;

// initialize the 0MQ context
zmqpp::context context;

void taskSink() {

  //  Prepare our socket
  zmqpp::socket receiver(context, zmqpp::socket_type::pull);
  receiver.bind("tcp://*:5558");

  //  Wait for start of batch
  zmqpp::message message;
  receiver.receive(message);
  cout << "The message was: " << message.get(0);
  cout << endl;

  //  Start our clock now
  struct timeval tstart;
  gettimeofday (&tstart, NULL);

  //  Process 100 confirmations
  int task_nbr;
  int total_msec = 0;     //  Total calculated cost in msecs
  for (task_nbr = 0; task_nbr < 100; task_nbr++) {

      receiver.receive(message);
      if (message.get(0) == "0")
          cout << ":" << flush;
      else
          cout << "." << flush;
  }

  //  Calculate and report duration of batch
  struct timeval tend, tdiff;
  gettimeofday (&tend, NULL);

  if (tend.tv_usec < tstart.tv_usec) {
      tdiff.tv_sec = tend.tv_sec - tstart.tv_sec - 1;
      tdiff.tv_usec = 1000000 + tend.tv_usec - tstart.tv_usec;
  }
  else {
      tdiff.tv_sec = tend.tv_sec - tstart.tv_sec;
      tdiff.tv_usec = tend.tv_usec - tstart.tv_usec;
  }
  total_msec = tdiff.tv_sec * 1000 + tdiff.tv_usec / 1000;
  cout << "\nTotal elapsed time: " << total_msec << " msec\n" << endl;

}

int main(int argc, char const *argv[]) {
  taskSink();
  return 0;
}
