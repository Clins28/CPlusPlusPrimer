#include<iostream>
using std::cout;
using std::cin;
using std::endl;
#include<fstream>
using std::ifstream;
#include<string>
using std::string;
#include<sstream>
using std::istringstream;
#include<vector>
using std::vector;
#include<map>
using std::map;
#include<set>
using std::set;
#include<memory>
using std::shared_ptr;
using std::weak_ptr;

class StrBlobPtr;
//StrBlob��
class StrBlob {
	friend class StrBlobPtr;
public:
	typedef vector<string>::size_type size_type;
	StrBlob();
	StrBlob(std::initializer_list<string> li);
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

//TextQuery��
class QueryResult;
class TextQuery {
public:
	using line_no = vector<string>::size_type;
	TextQuery(std::istream &);
	QueryResult query(const string&) const;
private:
	shared_ptr<StrBlob> file;
	map<string, shared_ptr<set<line_no>>> wm;
};


TextQuery::TextQuery(std::istream &is) :file(new StrBlob) {
	string text;
	while (std::getline(is, text)) {
		file->push_back(text);
		int n = file->size() - 1;
		string word;
		istringstream line(text);
		while (line >> word) {
			if (!wm[word]) wm[word].reset(new set<line_no>);
			wm[word]->insert(n);
		}
	}
}

class QueryResult {
	using line_no = vector<string>::size_type;
	friend std::ostream& print(std::ostream&, const QueryResult&);
public:
	QueryResult(string s, shared_ptr<set<line_no>> p,shared_ptr<StrBlob> f):sought(s),lines(p),file(f) {};
private:
	string sought;
	shared_ptr<set<line_no>> lines;
	shared_ptr<StrBlob> file;
};

QueryResult TextQuery::query(const string &sought) const {
	static shared_ptr<set<line_no>> nodata(new set<line_no>);
	auto loc = wm.find(sought);
	if ( loc == wm.end()) {
		return QueryResult(sought, nodata, file);
	}
	else return QueryResult(sought, loc->second, file);
}

std::ostream& print(std::ostream& os, const QueryResult &qr) {
	auto linesBegin = qr.lines->begin();
	os << "һ����������" << qr.lines->size() << "���С�" << endl;
	while (linesBegin != qr.lines->end()) {
		StrBlobPtr sbp(*qr.file, *linesBegin);
		os << "(line " << *linesBegin << ") " << sbp.deref() <<endl;
		linesBegin++;
	}
	return os;
}

void runQueries(ifstream &infile) {
	TextQuery tq(infile);
	while (true) {
		cout << "������Ҫ��ѯ�ĵ��ʣ�������q�˳���";
		string s;
		if (!(cin >> s) || s == "q") break;
		print(cout, tq.query(s)) << endl;

	}
}

int main() {
	ifstream infile("what faith can do");
	runQueries(infile);
	system("pause");
	return 0;
}