//#include<vector>
//using std::vector;
//#include<string>
//using std::string;
//#include<memory>
//using std::shared_ptr;
//using std::unique_ptr;
//using std::weak_ptr;
//#include<fstream>
//using std::ifstream;
//#include<iostream>
//using std::cout;
//using std::cin;
//using std::endl;
//
//class longAs {
//public:
//	bool operator()(const string &s, int n) {
//		return s.size() == n;
//	}
//};
//class longerThan {
//public:
//	bool operator()(const string &s, int n) {
//		return s.size() >= n;
//	}
//};
//int main() {
//	ifstream infile("what faith can do");
//	string s;
//	longAs la;
//	longerThan lt;
//	vector<int> num(11,0);
//	while (infile >> s) {
//		for (int i = 1;i <= 9;i++) {
//			if (la(s, i)) num[i]++;
//		}
//		if (lt(s, 9)) num[10]++;
//	}
//	for (int i : num) {
//		cout << i << endl;
//	}
//	system("pause");
//	return 0;
//}

#include <algorithm>
#include <numeric>
#include <iterator>
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

class ShorterThan {
public:
	bool operator()(const string &s1, const string &s2) const {
		return s1.size() < s2.size();
	}

};
class LongerThan {
public:
	LongerThan(const size_t n) :sz(n) {}
	bool operator()(const string &s) {
		return s.size() > sz;
	}
private:
	size_t sz;
};
void elimDups(vector<string> &words) {
	sort(words.begin(), words.end());
	for (string i : words) {
		cout << i << " ";
	}
	cout << endl;
	auto end_unique = std::unique(words.begin(), words.end());
	//�˴�words��sizeû�䵫��ֻ�ܴ�ӡ��4�Ҳ����˵�ظ�����ֻ�е�һ����������ӡ  ������Ϊʲô��
	for (string i : words) {
		cout << i << " ";
	}
	cout << endl;
	words.erase(end_unique, words.end());
}
string make_plural(int count, const string &s1, const string &s2) {
	return (count > 1) ? s1 + s2 : s1;
}

void biggies(vector<string> &vs, string::size_type sz) {
	elimDups(vs);//���ֵ������е��ʣ���ɾȥ�ظ���
	std::stable_sort(vs.begin(), vs.end(), ShorterThan());//����������������ȵ�Ԫ�ر����ֵ���
	auto first_find = std::find_if(vs.begin(), vs.end(), LongerThan(sz));//�ҳ���һ�����ȴ��ڵ���sz�ĵ���
	int count = vs.end() - first_find;//�����ж���Ԫ����������
	cout << count << make_plural(count, " word", "s") << " of length " << sz << " or longer" << endl;
	std::for_each(first_find, vs.end(), [](const string &s) { cout << s << " "; });//�������������Ԫ��
}
int main() {
	vector<string> vs = { "aaa","aaa","bbb","aaa","bbb","ccc","777777","457435847365438976548793","21321321321" };
	biggies(vs, 5);
	cout << endl;
	system("pause");
	return 0;
}