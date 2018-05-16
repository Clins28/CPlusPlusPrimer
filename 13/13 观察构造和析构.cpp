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
struct X {
	X() { cout << "X()" << endl; }
	X(const X&) { cout << "X(const X&)" << endl; }
	X& operator=(X&) { cout << "X& operator=(X&)" << endl; }
	~X() { cout << "~X()" << endl; }
};

void Foo(X) {}
void Foo2(X&) {}

int main() {
	//������
	{
		cout << "��������Ϊ�����ò�������:" << endl;
		X x;
		Foo(x);
		cout << "��������Ϊ���ò�������:" << endl;
		X y;
		Foo2(y);
		cout << "�����Ƕ�̬����:" << endl;
		X *z = new X;
		delete z;
		cout << "�����Ǵ��������У�" << endl;
		vector<X> vx(5);
		cout << "��ѡ������" << endl;
		X c;
		X co(c);
		X coo = c;
		cout << "�뿪���÷�Χ��" << endl;
	}
	system("pause");
	return 0;
}