#include <algorithm>
#include <string>
using std::string;
#include <vector>
using std::vector;
#include <list>
using std::list;
#include <iostream>
using std::cout;
using std::cin;
using std::endl;

int main() {
	list<string> ls;
	string s;
	while (cin >> s) {
		ls.push_back(s);
	}
	cout << "cbg������" << std::count(ls.begin(), ls.end(), "cbg") << "��" << endl;
	system("pause");
	return 0;
}