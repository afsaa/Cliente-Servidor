// constructing priority queues
#include <iostream>       // std::cout
#include <queue>          // std::priority_queue
#include <vector>         // std::vector
#include <functional>     // std::greater

// Para calcular la prioridad necesito la suma en el k que se está calculando, la suma del k anterior y la suma del k siguiente. Entre la suma anterior y la suma presente habría una pendiente (p1) y entre la suma presente y la suma siguiente habría una pendiente (p2). La prioridad se define por la diferencia entre p1 y p2 dependiendo del cambio de pendiente entre las 2.
// Cada prioridad va acompañado  de su k correspondiente.

using namespace std;

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


int main ()
{

  SSD SSD1(2, 200); //(prioridad, numero de k)
	SSD SSD2(1, 30);
	SSD SSD3(5, 150);
	SSD SSD4(1, 10);
	SSD SSD5(3, 1);

	//priority_queue<SSD> queue;
	priority_queue<SSD, vector<SSD>, SSDCompare> queue;

	queue.push(SSD1);
	queue.push(SSD2);
	queue.push(SSD3);
	queue.push(SSD4);
	queue.push(SSD5);

	while (!queue.empty())
	{
		SSD t = queue.top();
		cout << "priority " << t.priority << " k_number " << t.k_number << endl;
		queue.pop();
	}

	return 0;
}
