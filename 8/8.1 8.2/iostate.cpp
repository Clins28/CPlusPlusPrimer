#include <iostream>
#include <string>
#include <fstream>

std::istream& func(std::istream& input) {
	std::string str;
	while (input >> str) {
		std::cout << str << std::endl;
	}
	input.clear();
	return input;
}
int main() {
	std::ifstream inputF("sstream");
	std::cout << "ʹ���ļ����룺" << std::endl;
	std::cout << func(inputF).good() << std::endl;
	std::cout << "ʹ��cin���룺" << std::endl;//Ctrl+ZΪ������
	std::cout<<func(std::cin).good()<<std::endl;
	system("pause");
	return 0;
}