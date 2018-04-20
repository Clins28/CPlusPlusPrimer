#pragma once
#ifndef NOTEPAD_H
#define NOTEPAD_H
#include <string>
#include <vector>
class Screen
{
	friend class Window_mgr;
public:
	typedef std::string::size_type pos;
	//Ҳ����ʹ�����ͱ����ȼ۵�����һ����������
	//using pos=std::string::size_type;

	Screen() = default;
	Screen(pos ht, pos wd) :height(ht), width(wd), contents(ht * wd, ' ') {}
	Screen(pos ht, pos wd, char c) :height(ht), width(wd), contents(ht * wd, c) {}
	pos size() const { return height * width; }
	char get() const { return contents[cursor]; } //��ʽ����
	char get(pos, pos) const;
	Screen& move(pos, pos);
	Screen& set(char);
	Screen& set(pos, pos, char);
	Screen& display(std::ostream &os) { do_display(os);return *this; }
	const Screen& display(std::ostream &os) const { do_display(os);return *this; }
private:
	pos cursor = 0;//���λ��
	pos height = 0, width = 0;//��Ļ�߿�
	std::string contents;
	void do_display(std::ostream &os) const { os << contents; }
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

inline Screen& Screen::set(char c) {
	contents[cursor] = c;
	return *this;
}

inline Screen& Screen::set(pos r, pos c, char ch) {
	contents[r*width + c] = ch;
	return *this;
}

class Window_mgr 
{
public:
	using ScreenIndex = std::vector<Screen>::size_type;
	ScreenIndex addScreen(const Screen&);
	void clear(ScreenIndex);
private:
	//���Window_mgr׷�ٵ�Screen
	//Ĭ������£�һ��Window_mgr����һ����׼�ߴ�Ŀհ�Screen
	std::vector<Screen> screens{ Screen(24, 80, ' ') };
};

Window_mgr::ScreenIndex Window_mgr::addScreen(const Screen &s) {
	screens.push_back(s);
	return screens.size() - 1;
}

void Window_mgr::clear(ScreenIndex i) {
	Screen &s = screens[i];
	s.contents = std::string(s.height * s.width, ' ');
}

#endif