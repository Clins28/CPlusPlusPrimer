#include<vector>
using std::vector;
#include<string>
using std::string;
#include<memory>
using std::shared_ptr;
#include<iostream>
using std::cout;
using std::cin;
using std::endl;
class strBlob {
public:
	typedef vector<string>::size_type size_type;
	strBlob();
	strBlob(std::initializer_list<string> li);
	size_type size() const { return data->size(); }
	bool empty() const { return data->empty(); }
	//��Ӻ�ɾ��Ԫ��
	void push_back(const string &t) { data->push_back(t); }
	void pop_back();
	//����Ԫ��
	string& front();
	string& back();
	const string& front() const;//�����������Խ��ܳ�������ͷǳ�������ĵ��ã����Ƕ��󲻿ɸĶ���
	const string& back() const;

private:
	shared_ptr<vector<string>> data;
	void check(size_type i, const string &msg) const;
};
//���캯��
strBlob::strBlob() :data(std::make_shared<vector<string>>()) {}
strBlob::strBlob(std::initializer_list<string> li) : data(std::make_shared<vector<string>>(li)) {}
//Ԫ�ط��ʳ�Ա����
void strBlob::check(size_type i, const string &msg) const {
	if (i >= data->size()) {
		throw std::out_of_range(msg);
	}
}
void strBlob::pop_back() {
	check(0, "pop_back on empty strBlob!");
	data->pop_back();
}

string& strBlob::front() {
	check(0, "front on empty strBlob!");
	return data->front();
}

string& strBlob::back() {
	check(0, "back on empty strBlob!");
	return data->back();
}

const string& strBlob::front() const {
	check(0, "front on empty strBlob!");
	return data->front();
}

const string& strBlob::back() const {
	check(0, "back on empty strBlob!");
	return data->back();
}
int main() {
	const strBlob sb{"aaa","bbb"};
	cout << sb.front() << endl;
	system("pause");
	return 0;
}