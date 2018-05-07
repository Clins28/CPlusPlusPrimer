#include <sstream>
#include <utility>
using std::pair;
using std::make_pair;
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
using std::multimap;
#include <set>
using std::set;
#include <iterator>
using std::istream_iterator;
using std::ostream_iterator;

int main() {
	multimap<string, string> families_m;
	map<string, vector<string>> families;
	string first_name;
	string last_name;
	char yon;
	ostream_iterator<string> output(cout, " ");
	while (1) {
		cout << "�������ϣ�";
		cin >> last_name;
		cout << "�������֣�";
		cin >> first_name;
		families_m.insert({ last_name,first_name });
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
	for (auto f : families_m) {
		cout << f.first << f.second << " ";
	}

	cout << endl;
	system("pause");
	return 0;
}

