#ifndef HEADER_H
#define HEADER_H
#include<iostream>
using namespace std;
template <class T>
class Stack {
public:
	Stack(int MaxStackSize = 100);
	bool IsEmpty();
	bool IsFull();
	void Push(const T& item);
	void Pop();
	int getTop() {
		return top;
	}
	T* getStack() {
		return stack;
	}
	T Stack_top(){//沒有全部->不用星星
		return stack[top];
	}
private:
	T* stack;//only T
	int top;
	int MaxSize;
};

template <class T>
Stack<T>::Stack(int MaxStackSize) :MaxSize(MaxStackSize) {
	stack = new T[MaxSize];//易忘記
	top = -1;
}

template <class T>
bool Stack<T>::IsEmpty() {
	if (top == -1) {
		return true;
	}
	else {
		return false;
	}
}

template <class T>
bool Stack<T>::IsFull() {
	if (top == MaxSize-1) {
		return true;
	}
	else {
		return false;
	}
}

template <class T>
void Stack<T>::Push(const T& x) {
	if (IsFull()) {
		cout << "IsFull!" << endl;
	}
	else {
		stack[++top] = x;
	}
}
template <class T>//一定要在外面
void Stack<T>::Pop() {
	if (IsEmpty()) {
		cout << "IsEmpty!" << endl;
		return;
	}
	else {
		stack[top--].~T();//要記得()要加
	}
}
#endif // !HEADER_H

