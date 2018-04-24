#include<iostream>
using std::cout;
using std::cin;
using std::endl;
#include<fstream>
using std::ifstream;
using std::ofstream;
#include"Sales_data.h"

//��Ҫ������� argv[1] Ϊ�����ļ��� argv[2] Ϊ����ļ���
int main(int argc,char **argv) {
	ifstream input(argv[1]);
	ofstream output(argv[2], ofstream::app);
	Sales_data total;
	if (read(input, total)) {
		Sales_data trans;
		while (read(input, trans)) {
			if (total.isbn() == trans.isbn())
				total.combine(trans);
			else {
				print(output, total) << endl;
				total = trans;
			}
		}
		print(output, total) << endl;
	}
	else {
		std::cerr << "No data?!" << endl;
		system("pause");
		return -1;
	}
	system("pause");
	return 0;
}