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
	std::stable_sort(vs.begin(), vs.end(), [](const string &s1, const string &s2) {return s1.size() < s2.size();});//����������������ȵ�Ԫ�ر����ֵ���
	auto end_partition = std::stable_partition(vs.begin(), vs.end(), [sz](const string &s) {return s.size() >= sz;});//�ҳ���һ�����ȴ��ڵ���sz�ĵ���
	int count = std::count_if(vs.begin(), vs.end(), [sz](const string &s) {return s.size() >= sz;});
	cout << count << make_plural(count, " word", "s") << " of length " << sz << " or longer" << endl;
	std::for_each(vs.begin(),end_partition, [](const string &s) { cout << s << " "; });//�������������Ԫ��
}
int main() {
	vector<string> vs = { "aaa","aaa","bbb","aaa","bbb","ccc","777777","457435847365438976548793","21321321321" };
	biggies(vs, 6);
	cout << endl;
	system("pause");
	return 0;
}