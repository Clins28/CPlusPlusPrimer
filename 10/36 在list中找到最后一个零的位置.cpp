#include<iostream>
#include<iterator>
using std::istream_iterator;
using std::ostream_iterator;
#include<vector>
using std::vector;
#include<list>
using std::list;
#include<algorithm>
#include<numeric>
#include<fstream>
#include<string>
using std::string;
#include"Sales_item.h"
using std::cout;
using std::cin;
using std::endl;


int main() {
	list<int> li{ 1,2,3,0,4,5,6,7,8,0,98,7,0,322,5,6,7,7 };
	auto last_zero = std::find(li.crbegin(), li.crend(), 0);
	//auto pos = li.end() - last_zero.base();//�����ã���Ϊlist�����������洢����������֧����������
	int pos = 0;
	auto lib = li.cbegin();
	while (lib != last_zero.base()) {
		pos++;
		lib++;
	}
	cout << "���һ��������ڵ�" << pos << "λ";
	cout << endl;
	system("pause");
	return 0;
}