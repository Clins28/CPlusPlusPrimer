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
#include <set>
using std::set;
#include <iterator>
using std::istream_iterator;
using std::ostream_iterator;

int main() {
	map<string, vector<pair<string,string>>> families;
	string first_name;
	string last_name;
	string birthday;
	char yon;
	while (1) {
		cout << "�������ϣ�";
		cin >> last_name;
		cout << "�������֣�";
		cin >> first_name;
		cout << "�������գ�";
		cin >> birthday;
		families[last_name].push_back({ first_name ,birthday });
		cout << "�������룿(y/n)��";
		cin >> yon;
		if (yon == 'n' || yon == 'N') break;
	}
	for (auto vs : families) {
		cout << vs.first << "�ϼ�������Щ���ӣ�"<<endl;
		for (auto p : vs.second) {
			cout << p.first << " " << p.second << endl;
		}
	}
	system("pause");
	return 0;
}
