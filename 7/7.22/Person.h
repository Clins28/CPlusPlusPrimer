#pragma once
//#ifndef PERSON_H
//#define PERSON_H
#include <string>
class Person
{
	friend std::ostream &print(std::ostream &os, const Person &p);
	friend std::istream &read(std::istream &is, Person &p);
public:
	//���캯��
	Person() = default;
	Person(std::string &n, std::string &a) :name(n), address(a) {}
	Person(std::istream &is) { read(is, *this); }
	Person(std::string &n) :name(n) {}

	//��ȡname��address�ĳ�Ա����Ӧ����const�ģ���Ϊ��Щ��Ա���������޸Ķ��󡣣�����const�ĳ�Ա�����ܹ���const Person����ʹ�ø����ã�
	std::string get_name() const { return name; }
	std::string get_address() const { return address; }
private:
	std::string name;
	std::string address;
};
std::ostream &print(std::ostream &os, const Person &p);
std::istream &read(std::istream &is, Person &p);

std::istream &read(std::istream &is, Person &p) {
	is >> p.name >> p.address;
	return is;
}
std::ostream &print(std::ostream &os, const Person &p) {
	os << p.get_name() << " " << p.get_address();
	return os;
}

//#endif