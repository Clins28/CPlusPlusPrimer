#include <string>
using std::string;
#include <list>
using std::list;
#include <forward_list>
using std::forward_list;
#include <deque>
using std::deque;
#include <vector>
using std::vector;
#include <iostream>
using std::cout;
using std::cin;
using std::endl;

int main() {
	list<int> vi = { 0,1,2,3,4,5,6,7,8,9 };
	auto vb = vi.begin();
	while (vb != vi.end()) {
		if (*vb % 2) {
			vb = vi.insert(vb, *vb);
			vb++;
			vb++;//list����forward_list�ĵ������޷�һ�μ�2
		}
		else vb = vi.erase(vb);
	}
	for (int i : vi) {
		cout << i << " ";
	}
	cout << endl;
	system("pause");
	return 0;
}