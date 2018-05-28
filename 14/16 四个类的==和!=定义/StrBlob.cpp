#include "StrBlob.h"

//���캯��
StrBlob::StrBlob() :data(std::make_shared<vector<string>>()) {}
StrBlob::StrBlob(std::initializer_list<string> li) : data(std::make_shared<vector<string>>(li)) {}
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

bool operator==(const StrBlob &lhs, const StrBlob &rhs) {
	return *lhs.data == *rhs.data;
}

bool operator!=(const StrBlob &lhs, const StrBlob &rhs) {
	return *lhs.data != *rhs.data;
}


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

bool operator==(const StrBlobPtr &lhs, const StrBlobPtr &rhs) {
	return lhs.curr == rhs.curr
		&& lhs.wptr.lock()==rhs.wptr.lock();
}

bool operator!=(const StrBlobPtr &lhs, const StrBlobPtr &rhs) {
	return !(lhs==rhs);
}

//��ȻStrBlobPtr������д����StrBlob�ඨ��ǰ�棬����StrBlobPtr����������֮ǰ�������޷�ʹ��StrBlobPtr�Ĺ��캯������StrBlob���begin��end��Ҫд��StrBlobPtr��������֮��
StrBlobPtr StrBlob::begin() const { return StrBlobPtr(*this); }
StrBlobPtr StrBlob::end() const { return StrBlobPtr(*this, data->size()); }
