#pragma once
//#ifndef PERSON_H
//#define PERSON_H
#include <string>
class Person
{
public:
	std::string name;
	std::string address;
	//��ȡname��address�ĳ�Ա����Ӧ����const�ģ���Ϊ��Щ��Ա���������޸Ķ��󡣣�����const�ĳ�Ա�����ܹ���const Person����ʹ�ø����ã�
	std::string get_name() const { return name; }
	std::string get_address() const { return address; }
private:
};

std::istream &read(std::istream &is, Person &p) {
	is >> p.name >> p.address;
	return is;
}
std::ostream &print(std::ostream &os, const Person &p) {
	os << p.get_name() << " " << p.get_address();
	return os;
}
//#endif