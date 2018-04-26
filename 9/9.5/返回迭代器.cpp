#include <list>
using std::list;
#include <deque>
using std::deque;
#include <vector>
using std::vector;
#include <iostream>
using std::cout;
using std::cin;
using std::endl;

vector<int>::iterator find(vector<int>::iterator ibegin, vector<int>::iterator iend, int n) {
	while (ibegin != iend) {
		if (*ibegin == n) return ibegin;
		ibegin++;
	}
	return iend;
}

int main() {
	list<deque<int>> lq;
	int n;
	cout << "���һ�����֣�1~20����";
	cin >> n;
	vector<int> nums = { 1,2,3,4,5,6,7,8,9,10,11,12,13 };
	if (find(nums.begin(), nums.end(), n) == nums.end()) cout << "δ�ҵ���" << endl;
	else cout <<n<<"�ڵ�"<< find(nums.begin(), nums.end(), n) - nums.begin() +1 <<"��λ��"<< endl;
	system("pause");
	return 0;
}