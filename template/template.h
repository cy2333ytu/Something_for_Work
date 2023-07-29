#pragma once
#ifndef TEMPLATE_H
#define TEMPLATE_H
#include <string>
#include <iostream>

namespace templatee{

using namespace std;

const int Size = 5;

template<class T>
class Array {
public:
	Array() {
		for (int i = 0; i < Size; i++) {
			a[i] = 0;
		}
	}
	T& operator[](int i);
	void sort();

private:
	T a[Size];
};

template<class T>
T& Array<T>::operator[](int i) {
	if (i<0 || i>Size - 1) {
		cout << "\n 数组不能越界" << '\n';
		exit(0);
	}
	return a[i];
}

template<class T>
void Array<T>::sort() {
	int p;
	for (int i = 0; i < Size - 1; i++) {
		p = i;
		for (int j = i; j < Size; j++) {
			if (a[p] < a[j])
				p = j;
		}
		T t = a[p];
		a[p] = a[i];
		a[i] = t;
	}
}

}

namespace stack 
{
using namespace std;
template<class T, int MAXSIZE>
class Stack {
private:
	T elem[MAXSIZE];
	int top;

public:
	// 使用列表初始化，不可行
	Stack() { top = 0; };            
	void push(T e);
	T pop();
	bool empty() {
		if (top <= -1)
			return 1;
		else
			return 0;
	}
	void setEmpty() { top = -1; }
	bool full() {
		if (top >= MAXSIZE - 1) {
			return 1;
		}
		else
			return 0;
	}
};

template <class T, int MAXSIZE>
void Stack<T, MAXSIZE>::push(T e) {
	if (full()) {
		cout << "栈已满，不能再添加元素了！";
		return;
	}
	elem[++top] = e;
}

template <class T, int MAXSIZE>
T Stack<T, MAXSIZE>::pop() {
	if (empty()) {
		cout << "栈已空，不能再弹出元素了！" << endl;
		return 0;
	}
	return elem[top--];
}

}





#endif // !TEMPLATE_H
