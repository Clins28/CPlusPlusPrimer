#pragma once
#ifndef STRVEC_H
#define STRVEC_H
#include <utility>
#include <string>
using std::string;
#include <memory>
using std::uninitialized_copy;
using std::allocator;
#include <algorithm>

class StrVec {
public:
	StrVec() :elements(nullptr), first_free(nullptr), cap(nullptr) {}
	StrVec(std::initializer_list<string>);
	StrVec(const StrVec&);
	StrVec(StrVec&&) noexcept;
	StrVec &operator=(const StrVec&);
	StrVec &operator=(StrVec&&) noexcept;
	~StrVec() { free(); }
	void push_back(const string&);
	void reserve(size_t);
	void resize(size_t, const string& s = "");
	string& at(size_t n) { return *(elements + n); }
	size_t size() const { return first_free - elements; }
	size_t capacity() const { return cap - elements; }
	string *begin() const { return elements; }
	string *end() const { return first_free; }
private:
	static allocator<string> alloc;
	void chk_n_alloc() { if (size() == capacity()) reallocate(); }
	std::pair<string*, string*> alloc_n_copy(const string*, const string*);
	void free();
	void reallocate();
	void reallocate_n(size_t);
	string *elements;//��ָ��
	string *first_free;//ָ�����һ��ʵ��Ԫ��֮��
	string *cap;//ָ������ڴ�β��λ��
};

StrVec::StrVec(std::initializer_list<string>li) {
	auto newdata = alloc_n_copy(li.begin(), li.end());
	elements = newdata.first;
	first_free = cap = newdata.second;
}

StrVec::StrVec(const StrVec &sv) {
	auto newdata = alloc_n_copy(sv.begin(), sv.end());
	elements = newdata.first;
	first_free = cap = newdata.second;
}

StrVec::StrVec(StrVec &&sv) noexcept
	:elements(sv.elements), first_free(sv.first_free), cap(sv.cap) {
	sv.elements = sv.first_free = sv.cap = nullptr;
}

StrVec &StrVec::operator=(const StrVec &rhs) {
	auto newdata = alloc_n_copy(rhs.begin(), rhs.end());
	free();
	elements = newdata.first;
	first_free = cap = newdata.second;
	return *this;
}

StrVec& StrVec::operator=(StrVec &&rhs) noexcept {
	if (this != &rhs) {
		free();
		elements = std::move(rhs.elements);
		first_free = std::move(rhs.first_free);
		cap = std::move(rhs.cap);
		rhs.elements = rhs.first_free = rhs.cap = nullptr;
	}
	return *this;
}

void StrVec::push_back(const string &s) {
	chk_n_alloc();
	alloc.construct(first_free++, s);
}

void StrVec::reserve(size_t n) {
	if (n > capacity())
		reallocate_n(n);
}

void StrVec::resize(size_t n, const string& s) {
	while (n > size())
		push_back(s);
	while (n < size())
		alloc.destroy(--first_free);
}

std::pair<string*, string*> StrVec::alloc_n_copy(const string *b, const string *e) {
	auto data = alloc.allocate(e - b);
	return { data, std::uninitialized_copy(b, e, data) };
}

void StrVec::free() {
	if (elements) {
		std::for_each(elements, first_free, [](const string *p) {alloc.destroy(p);});
		alloc.deallocate(elements, cap - elements);
	}
}

void StrVec::reallocate() {
	auto newcapacity = size() ? size() * 2 : 1;
	reallocate_n(newcapacity);
}

void StrVec::reallocate_n(size_t n) {
	auto newdata = alloc.allocate(n);
	auto elem = elements;
	auto dest = newdata;
	for (size_t i = 0;i != size();i++)
		alloc.construct(dest++, std::move(*elem++));
	free();
	elements = newdata;
	first_free = dest;
	cap = elements + n;
}

allocator<string> StrVec::alloc{};//static��Աʹ����Ҫ����

#endif // !STRVEC_H
