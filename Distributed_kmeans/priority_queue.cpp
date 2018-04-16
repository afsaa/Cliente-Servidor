// constructing priority queues
#include <iostream>       // std::cout
#include <queue>          // std::priority_queue
#include <vector>         // std::vector
#include <functional>     // std::greater

// Para calcular la prioridad necesito la suma en el k que se está calculando, la suma del k anterior y la suma del k siguiente. Entre la suma anterior y la suma presente habría una pendiente (p1) y entre la suma presente y la suma siguiente habría una pendiente (p2). La prioridad se define por la diferencia entre p1 y p2.

using namespace std;

class mycomparison
{
  bool reverse;
public:
  mycomparison(const bool& revparam=false)
    {reverse=revparam;}
  bool operator() (const int& lhs, const int&rhs) const
  {
    if (reverse) return (lhs>rhs);
    else return (lhs<rhs);
  }
};

int main ()
{

  // using mycomparison:
  typedef std::priority_queue<int,std::vector<int>,mycomparison> mypq_type;

  mypq_type fourth;                       // less-than comparison
  mypq_type fifth (mycomparison(true));   // greater-than comparison

  //Push some numbers on fourth
  fourth.push(5);
  fourth.push(1);
  fourth.push(6);
  fourth.push(2);

  cout << "Fourth first number: " << fourth.top() <<'\n';
  return 0;
}
