#include <zmqpp/zmqpp.hpp>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <time.h>

using namespace std;

// initialize the 0MQ context
zmqpp::context context;

void taskWorker() {
  //  Socket to receive messages on
  zmqpp::socket receiver(context, zmqpp::socket_type::pull);
  receiver.connect("tcp://localhost:5557");

  //  Socket to send messages to
  zmqpp::socket sender(context, zmqpp::socket_type::push);
  sender.connect("tcp://localhost:5558");

  // Tell me when the ventilator is ready to send tasks
  cout << "Press Enter when the ventilator is ready: " << endl;
  getchar ();
  cout << "Processing tasks from the ventilator…\n" << endl;

  //  Process tasks forever
  while (1) {

      zmqpp::message message;

      // Send a single message from server to client
      // zmqpp::message request;
      // request << "Hello";
      // sender.send(request);

      zmqpp::message response;
      receiver.receive(response);

      // assert("0" == response.get(0));
      cout << "Workers test OK" << endl;
      cout << "The message was: " << response.get(0);
      cout << endl;
      cout << endl;

  }
}

int main(int argc, char const *argv[]) {
  taskWorker();
  return 0;
}
