#pragma once
#ifndef NOTEPAD_H
#define NOTEPAD_H
#include <string>
#include <vector>
class Screen
{
public:
	typedef std::string::size_type pos;
	//Ҳ����ʹ�����ͱ����ȼ۵�����һ����������
	//using pos=std::string::size_type;

	Screen() = default;
	Screen(pos ht, pos wd) :height(ht), width(wd), contents(ht * wd, ' ') {}
	Screen(pos ht, pos wd, char c) :height(ht), width(wd), contents(ht * wd, c) {}
	char get() const { return contents[cursor]; } //��ʽ����
	char get(pos, pos) const;
	Screen& move(pos, pos);

private:
	pos cursor = 0;//���λ��
	pos height = 0, width = 0;//��Ļ�߿�
	std::string contents;
};

inline char Screen::get(pos r, pos c) const {
	pos row = r * width;
	return contents[row + c];
}

//����ֵ��*this �Ƕ�����ֵ���ã�������ΪScreen&
inline Screen& Screen::move(pos r, pos c) {
	pos row = r * width;
	cursor = row + c;
	return *this;
}

class Window_mgr 
{
public:

private:
	//���Window_mgr׷�ٵ�Screen
	//Ĭ������£�һ��Window_mgr����һ����׼�ߴ�Ŀհ�Screen
	std::vector<Screen> screens{ Screen(24, 80, ' ') };
};
#endif