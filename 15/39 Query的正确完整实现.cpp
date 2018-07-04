#include <vector>
using std::vector;
#include <string>
using std::string;
#include <memory>
using std::shared_ptr;
using std::make_shared;
#include <map>
using std::map;
#include <set>
using std::set;
#include <sstream>
using std::istringstream;
#include <iostream>
using std::cout;
using std::cin;
using std::endl;
#include <fstream>
using std::ifstream;
#include <algorithm>
#include <iterator>

class QueryResult;
class TextQuery {
public:
	using line_no = vector<string>::size_type;
	TextQuery(std::istream&);
	QueryResult query(const string&) const;
private:
	shared_ptr<vector<string>> file;
	map<string, shared_ptr<set<line_no>>> wm;
};


TextQuery::TextQuery(std::istream &is) :file(new vector<string>) {
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
	QueryResult(string s, shared_ptr<set<line_no>> p, shared_ptr<vector<string>> f) :sought(s), lines(p), file(f) {};
	set<line_no>::iterator begin() const { return lines->begin(); }
	set<line_no>::iterator end() const { return lines->end(); }
	shared_ptr<vector<string>> get_file() const { return file; }
private:
	string sought;
	shared_ptr<set<line_no>> lines;
	shared_ptr<vector<string>> file;
};

QueryResult TextQuery::query(const string &sought) const {
	static shared_ptr<set<line_no>> nodata(new set<line_no>);
	auto loc = wm.find(sought);
	if (loc == wm.end()) {
		return QueryResult(sought, nodata, file);
	}
	else return QueryResult(sought, loc->second, file);
}

std::ostream& print(std::ostream& os, const QueryResult &qr) {
	auto linesBegin = qr.lines->begin();
	os << "һ����������" << qr.lines->size() << "���С�" << endl;
	while (linesBegin != qr.lines->end()) {
		os << "(line " << *linesBegin << ") " << qr.file->at(*linesBegin) << endl;
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

class Query_base {
	friend class Query;
protected:
	using line_no = TextQuery::line_no;
	virtual ~Query_base() = default;
private:
	virtual QueryResult eval(const TextQuery&) const = 0;
	virtual string rep() const = 0;
};

class Query {
	friend Query operator~(const Query&);
	friend Query operator&(const Query&, const Query&);
	friend Query operator|(const Query&, const Query&);
public:
	Query(const string&);
	QueryResult eval(const TextQuery &t) const { return q->eval(t); }
	string rep() const { 
		cout << "Query rep" << endl;
		return q->rep(); 
	}
private:
	Query(shared_ptr<Query_base> query) :q(query) { cout << "Query constructor" << endl; }
	shared_ptr<Query_base> q;
};

class WordQuery :public Query_base {
	friend class Query;
	WordQuery(const string &s):query_word(s) { cout << "WordQuery constructor" << endl; }
	QueryResult eval(const TextQuery &t) const {
		return t.query(query_word);
	}
	string rep() const { 
		cout << "WordQuery rep" << endl;
		return query_word; 
	}
	string query_word;
};

inline
Query::Query(const string &s):q(new WordQuery(s)) {
	cout << "Query constructor" << endl; 
}

class NotQuery :public Query_base {
	friend Query operator~(const Query&);
	NotQuery(const Query &q) :query(q) { cout << "NotQuery constructor" << endl; }
	string rep() const { 
		cout << "NotQuery rep" << endl;
		return "~(" + query.rep() + ")"; 
	}
	QueryResult eval(const TextQuery&) const;
	Query query;
};

QueryResult NotQuery::eval(const TextQuery &text) const {
	cout << "NotQuery eval" << endl;
	auto result = query.eval(text);
	auto ret_lines = make_shared<set<line_no>>();
	auto beg = result.begin(), end = result.end();
	auto sz = result.get_file()->size();
	for (size_t n = 0;n != sz;n++) {
		if (beg == end || *beg != n)
			ret_lines->insert(n);
		else if (beg != end)
			++beg;
	}
	return QueryResult(rep(), ret_lines, result.get_file());
}

inline Query operator~(const Query &operand) {
	return shared_ptr<Query_base>(new NotQuery(operand));
}

class BinaryQuery :public Query_base {
protected:
	BinaryQuery(const Query &l, const Query &r, const string &s) :lhs(l), rhs(r), opSym(s) { cout << "BinaryQuery constructor" << endl; }
	string rep() const { 
		cout << "BinaryQuery rep" << endl;
		return "(" + lhs.rep() + " " + opSym + " " + rhs.rep() + ")"; 
	}
	//BinaryQuery������eval�����Ǽ̳���Query_base�Ĵ��麯�������BinaryQueryҲ��һ��������࣬���ǲ��ܴ���BinaryQuery���͵Ķ���
	Query lhs, rhs;
	string opSym;
};

class AndQuery :public BinaryQuery {
	friend Query operator&(const Query&, const Query&);
	AndQuery(const Query &left, const Query &right) :BinaryQuery(left, right, "&") { cout << "AndQuery constructor" << endl; }
	QueryResult eval(const TextQuery& q) const;
};

QueryResult AndQuery::eval(const TextQuery& text) const {
	cout << "AndQuery eval" << endl;
	QueryResult right = rhs.eval(text), left = lhs.eval(text);
	shared_ptr<set<line_no>> ret_lines = make_shared<set<line_no>>();
	std::set_intersection(left.begin(), left.end(), right.begin(), right.end(), std::inserter(*ret_lines, ret_lines->begin()));
	return QueryResult(rep(), ret_lines, left.get_file());
}

inline Query operator&(const Query &lhs, const Query &rhs) {
	return shared_ptr<Query_base>(new AndQuery(lhs, rhs));
}

class OrQuery :public BinaryQuery {
	friend Query operator|(const Query&, const Query&);
	OrQuery(const Query &left, const Query &right) :BinaryQuery(left, right, "|") { cout << "OrQuery constructor" << endl; }
	QueryResult eval(const TextQuery&) const;
};

QueryResult OrQuery::eval(const TextQuery& text) const {
	cout << "OrQuery eval" << endl;
	QueryResult right = rhs.eval(text), left = lhs.eval(text);
	shared_ptr<set<line_no>> ret_lines = make_shared<set<line_no>>(left.begin(), left.end());
	ret_lines->insert(right.begin(), right.end());
	return QueryResult(rep(), ret_lines, left.get_file());
}

inline Query operator|(const Query &lhs, const Query &rhs) {
	return shared_ptr<Query_base>(new OrQuery(lhs, rhs));
}

std::ostream& operator<<(std::ostream &os, const Query &query) {
	return os << query.rep();
}

 int main() {
	ifstream infile("Alice");
	//runQueries(infile);
	Query q = Query("fiery") & Query("bird") | Query("wind");
	cout << q << endl;
	print(cout,q.eval(infile));
	system("pause");
	return 0;
}