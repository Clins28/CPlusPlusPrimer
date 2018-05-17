#include<vector>
using std::vector;
#include<string>
using std::string;
#include<memory>
using std::shared_ptr;
using std::unique_ptr;
using std::weak_ptr;
#include<fstream>
using std::ifstream;
#include<iostream>
using std::cout;
using std::cin;
using std::endl;
class StrBlobPtr;
//StrBlob��
class StrBlob {
	friend class StrBlobPtr;
public:
	typedef vector<string>::size_type size_type;
	StrBlob();
	StrBlob(std::initializer_list<string> li);
	StrBlob(const StrBlob& sb) :data(std::make_shared<vector<string>>(*sb.data)) {}
	StrBlob& operator=(const StrBlob &);
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
	//������
	StrBlobPtr begin() const;
	StrBlobPtr end() const;
private:
	shared_ptr<vector<string>> data;
	void check(size_type i, const string &msg) const;
};
//���캯��
StrBlob::StrBlob() :data(std::make_shared<vector<string>>()) {}
StrBlob::StrBlob(std::initializer_list<string> li) : data(std::make_shared<vector<string>>(li)) {}
StrBlob& StrBlob::operator=(const StrBlob &sb) {
	data=std::make_shared<vector<string>>(*sb.data);
	return *this;
}
//Ԫ�ط��ʳ�Ա����
void StrBlob::check(size_type i, const string &msg) const {
	if (i >= data->size()) {
		throw std::out_of_range(msg);
	}
}
void StrBlob::pop_back() {
	check(0, "pop_back on empty StrBlob!");
	data->pop_back();
}

string& StrBlob::front() {
	check(0, "front on empty StrBlob!");
	return data->front();
}

string& StrBlob::back() {
	check(0, "back on empty StrBlob!");
	return data->back();
}

const string& StrBlob::front() const {
	check(0, "front on empty StrBlob!");
	return data->front();
}

const string& StrBlob::back() const {
	check(0, "back on empty StrBlob!");
	return data->back();
}

//StrBlobPtr����ָ����
class StrBlobPtr {
public:
	StrBlobPtr() :curr(0) {}
	StrBlobPtr(const StrBlob &sb, size_t sz = 0) :wptr(sb.data), curr(sz) {}
	string& deref() const;
	StrBlobPtr& incr();
	bool compare(const StrBlobPtr &anotherStrBlobPtr) { return wptr.lock() == anotherStrBlobPtr.wptr.lock() && curr == anotherStrBlobPtr.curr; }
private:
	shared_ptr<vector<string>> check(size_t, const string) const;
	weak_ptr<vector<string>> wptr;
	size_t curr;
};

shared_ptr<vector<string>> StrBlobPtr::check(size_t i, const string msg) const {
	auto ret = wptr.lock();
	if (!ret) {
		throw std::runtime_error("unbound StrBlobPtr");
	}
	if (i >= ret->size()) {
		throw std::out_of_range(msg);
	}
	return ret;
}

string& StrBlobPtr::deref() const {
	return check(curr, "dereference past end")->at(curr);
}

StrBlobPtr& StrBlobPtr::incr() {
	//���curr�Ѿ�ָ��������β��λ�ã��Ͳ��ܵ�����
	auto ret = check(curr, "increment past end of StrBlobPtr");
	++curr;
	return *this;
}

//��ȻStrBlobPtr������д����StrBlob�ඨ��ǰ�棬����StrBlobPtr����������֮ǰ�������޷�ʹ��StrBlobPtr�Ĺ��캯������StrBlob���begin��end��Ҫд��StrBlobPtr��������֮��
StrBlobPtr StrBlob::begin() const { return StrBlobPtr(*this); }
StrBlobPtr StrBlob::end() const { return StrBlobPtr(*this, data->size()); }

int main() {
	const StrBlob strbb{ "aaa","bbb","ccc" };
	StrBlob strcc = strbb;
	for (StrBlobPtr strbb_b = strbb.begin();!strbb_b.compare(strbb.end());strbb_b.incr()) {
		auto a = strbb_b.compare(strbb.end());
		cout << strbb_b.deref() << endl;
	}
	strbb.begin().deref() = "mmm";
	for (StrBlobPtr strcc_b = strcc.begin();!strcc_b.compare(strcc.end());strcc_b.incr()) {
		auto a = strcc_b.compare(strcc.end());
		cout << strcc_b.deref() << endl;
	}
	system("pause");
	return 0;
}