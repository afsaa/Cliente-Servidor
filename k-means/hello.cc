#include <iostream>
#include <omp.h>

using namespace std;

int main(int argc, char const *argv[]) {
  #pragma omp parallel
  {
    int ID = omp_get_thread_num();
    cout << "hello(" << ID <<")" <<endl;
    cout << "world(" << ID <<")" <<endl;
  }
  return 0;
}
