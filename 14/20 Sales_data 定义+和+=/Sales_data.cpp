#include "Sales_data.h"


inline double Sales_data::avg_price() const {
	if (units_sold)
		return revenue / units_sold;
	else
		return 0;
}
Sales_data& Sales_data::combine(const Sales_data &rhs) {
	units_sold += rhs.units_sold;
	revenue += rhs.revenue;
	return *this;
}
Sales_data add(const Sales_data &lhs, const Sales_data &rhs) {
	Sales_data sum = lhs;
	return sum.combine(rhs);
}

//1 IO�����ڲ��ܱ����������ͣ�ֻ��ͨ���������������� 2 print�������У�ִ���������ĺ���Ӧ�þ������ٶ��ڸ�ʽ�Ŀ���
std::ostream &print(std::ostream &os, const Sales_data &item) {
	os << item.isbn() << " " << item.units_sold << " " << item.revenue << " " << item.avg_price();
	return os;
}

std::istream &read(std::istream &is, Sales_data &item) {
	double price = 0;
	is >> item.bookNo >> item.units_sold >> price;
	item.revenue = item.units_sold*price;
	return is;
}

std::ostream &operator<<(std::ostream &os, const Sales_data &item) {
	os << item.isbn() << " " << item.units_sold << " " << item.revenue << " " << item.avg_price();
	return os;
}

std::istream &operator>>(std::istream &is, Sales_data &item) {
	double price = 0;
	is >> item.bookNo >> item.units_sold >> price;
	if (is) //��������Ƿ�ɹ�
		item.revenue = item.units_sold*price;
	else //����ʧ����ִ��Ĭ�ϳ�ʼ��
		item = Sales_data();
	return is;
}

Sales_data operator+(const Sales_data &lhs, const Sales_data &rhs) {
	Sales_data sum = lhs;
	sum += rhs;
	return sum;
}

Sales_data& Sales_data::operator+=(const Sales_data &rhs) {
	combine(rhs);
	return *this;
}

bool operator==(const Sales_data &lhs, const Sales_data &rhs) {
	return lhs.isbn() == rhs.isbn()
		&& lhs.units_sold == rhs.units_sold
		&& lhs.revenue == rhs.revenue;
}

bool operator!=(const Sales_data &lhs, const Sales_data &rhs) {
	return lhs.isbn() != rhs.isbn()
		|| lhs.units_sold != rhs.units_sold
		|| lhs.revenue != rhs.revenue;
}
