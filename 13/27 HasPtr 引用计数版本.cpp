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
#include <memory>
using std::shared_ptr;
using std::unique_ptr;
using std::make_shared;
using std::allocator;
#include <new>

class HasPtr {
public:
	HasPtr(const string &s = string()) :ps(new string(s)), i(0), use(new std::size_t(1)) {}
	HasPtr(const HasPtr &hp) :ps(hp.ps), i(hp.i), use(hp.use) { ++*use; }
	HasPtr& operator=(const HasPtr &hp);
	~HasPtr();
	void print() { cout << *ps << " " << i << endl; }
private:
	string *ps;
	int i;
	std::size_t *use;
};
HasPtr::~HasPtr() {
	if (--*use == 0) {
		delete ps;
		delete use;
	}
}
HasPtr& HasPtr::operator=(const HasPtr& hp) {
	++*hp.use;//��Ϊconst HasPtr &hp�ĳ�Աuse��һ��ָ�룬��ָ���ڴ˴�����ʹ�ò�û�б��ı����Բ�Υ��const����ָ��ָ��Ķ��󲢲�����hp
	if (--*use == 0) {
		delete ps;
		delete use;
	}
	ps = hp.ps;
	i = hp.i;
	use = hp.use;
	return *this;
}

int main() {
	HasPtr hp("aaaaa");
	HasPtr hp2(hp);
	HasPtr hp3 = hp2;
	hp2 = HasPtr("bbbb");
	hp2.print();
	hp.print();
	hp3.print();
	system("pause");
	return 0;
}