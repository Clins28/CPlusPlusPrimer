#include <iostream>
using std::istream;
using std::cin;
using std::cout;
using std::endl;
#include <string>
using std::string;
#include <vector>
using std::vector;
#include <fstream>
using std::ifstream;
#include <sstream>
using std::istringstream;

std::istream& func(std::istream& input) {
	std::string str;
	while (std::getline(input,str)) {
		std::cout << str << std::endl;
	}
	input.clear();
	return input;
}
int main() {
	string str("ABCDEF AAAA CCC 222");
	istringstream record(str);
	std::ifstream inputF("sstream");
	std::cout << "ʹ���ļ����룺" << std::endl;
	std::cout << func(inputF).good() << std::endl;
	std::cout << "ʹ��istringstream���룺" << std::endl;
	std::cout << func(record).good() << std::endl;
	//std::cout << "ʹ��cin���룺" << std::endl;//Ctrl+ZΪ������
	//std::cout << func(std::cin).good() << std::endl;
	system("pause");
	return 0;
}
