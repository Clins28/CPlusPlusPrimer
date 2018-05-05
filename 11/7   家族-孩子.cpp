#include <iostream>
using std::cout;
using std::cin;
using std::endl;
#include <vector>
using std::vector;
#include <string>
using std::string;
#include <map>
using std::map;
#include <set>
using std::set;
#include <iterator>
using std::istream_iterator;
using std::ostream_iterator;

int main() {
	map<string, vector<string>> families;
	string first_name;
	string last_name;
	char yon;
	ostream_iterator<string> output(cout," ");
	while (1) {
		cout << "�������ϣ�";
		cin >> last_name;
		cout << "�������֣�";
		cin >> first_name;
		families[last_name].push_back(first_name);
		cout << "�������룿(y/n)��";
		cin >> yon;
		if (yon == 'n' || yon == 'N') break;
	}
	for (auto vs : families) {
		cout << vs.first << "�ϼ�������Щ���ӣ�";
		std::copy(vs.second.cbegin(), vs.second.cend(), output);
		cout << endl;
	}
	system("pause");
	return 0;
}
