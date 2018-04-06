#include <fstream>
#include <iostream>
#include <sstream>
#include <cassert>
#include <random>
#include <list>
#include <vector>
#include <math.h>
#include "boost/tuple/tuple.hpp"

using namespace std;
using boost::tuple;

typedef vector< tuple<int,double> > tuple_list;

double calcInertia(int num_actual_cluster, list<double> distances_to_centroid) {
  double inertia;
  double total_distance = 0;
  for (size_t i = 0; i < num_actual_cluster; i++) {
     double subtotal_distance = 0;
     for (auto n : distances_to_centroid) {
       subtotal_distance += n;
     }
     total_distance += subtotal_distance;
  }
  inertia = pow(total_distance, 2);
  return inertia;
}

void addInertiaTuple(tuple_list inertia_clusters, int num_actual_cluster, double actual_inertia_cluster) {
  inertia_clusters.push_back( tuple<int, double>(num_actual_cluster, actual_inertia_cluster));
}

int main() {
  tuple_list inertia_clusters;
  int num_cluster; //Number of the actual cluster
  double cluster_inertia; //Inertia of the actual cluster


  //To iterate on the tuple list -->
  //   for (tuple_list::const_iterator i = tl.begin(); i != tl.end(); ++i) {
  //       cout << "Age: " << i->get<0>() << endl;
  //       cout << "Name: " << i->get<1>() << endl;
  //   }
}
