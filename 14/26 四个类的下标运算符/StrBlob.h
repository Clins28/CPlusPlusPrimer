#pragma once
#ifndef STRBLOB_H
#define STRBLOB_H
#include <vector>
using std::vector;
#include <string>
using std::string;
#include <memory>
using std::shared_ptr;
using std::weak_ptr;

class StrBlobPtr;
//StrBlob��
class StrBlob {
	friend class StrBlobPtr;
	friend bool operator==(const StrBlob&, const StrBlob&);
	friend bool operator!=(const StrBlob&, const StrBlob&);
	friend bool operator<(const StrBlob&, const StrBlob&);
	friend bool operator<=(const StrBlob&, const StrBlob&);
	friend bool operator>(const StrBlob&, const StrBlob&);
	friend bool operator>=(const StrBlob&, const StrBlob&);
public:
	typedef vector<string>::size_type size_type;
	StrBlob();
	StrBlob(std::initializer_list<string> li);
	//���������
	string& operator[](const int n) { return (*data)[n]; }
	const string& operator[](const int n) const { return (*data)[n]; }
	size_type size() const { return data->size(); }
	bool empty() const { return data->empty(); }
	//��Ӻ�ɾ��Ԫ��
	void push_back(const string &t) { data->push_back(t); }
	void push_back(string &&s) { data->push_back(std::move(s)); }
	void pop_back();
	//����Ԫ��
	string& front();
	string& back();
	const string& front() const;//�����������Խ��ܳ�������ͷǳ�������ĵ��ã����Ƕ��󲻿ɸĶ���
	const string& back() const;
	//������
	StrBlobPtr begin() const;
	StrBlobPtr end() const;
private:
	shared_ptr<vector<string>> data;
	void check(size_type i, const string &msg) const;
};

//StrBlobPtr����ָ����
class StrBlobPtr {
	friend bool operator==(const StrBlobPtr&, const StrBlobPtr&);
	friend bool operator!=(const StrBlobPtr&, const StrBlobPtr&);
	friend bool operator<(const StrBlobPtr&, const StrBlobPtr&);
	friend bool operator<=(const StrBlobPtr&, const StrBlobPtr&);
	friend bool operator>(const StrBlobPtr&, const StrBlobPtr&);
	friend bool operator>=(const StrBlobPtr&, const StrBlobPtr&);
public:
	StrBlobPtr() :curr(0) {}
	StrBlobPtr(const StrBlob &sb, size_t sz = 0) :wptr(sb.data), curr(sz) {}
	//���������
	string& operator[](const int n) { return (*wptr.lock())[n]; }
	const string& operator[](const int n) const { return (*wptr.lock())[n]; }
	string& deref() const;
	StrBlobPtr& incr();
	bool compare(const StrBlobPtr &anotherStrBlobPtr) { return wptr.lock() == anotherStrBlobPtr.wptr.lock() && curr == anotherStrBlobPtr.curr; }
private:
	shared_ptr<vector<string>> check(size_t, const string) const;
	weak_ptr<vector<string>> wptr;
	size_t curr;
};

#endif // !STRBLOB_H