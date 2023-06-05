#ifndef HEADER_H
#define HEADER_H
#include<iostream>
using namespace std;
template <class T>
class Stack {
private:
	int top;
	int max;
	T* stack;
public:
	Stack(int MAX=12) {
		max = MAX;
		top = -1;
		stack = new T[max];
	}
	void MAX(int n) {
		max = n;
	}
	T stack_top() {
		return stack[top];
	}
	bool isEmpty() {
		if (top == -1) {
			return true;
		}
		else {
			return false;
		}
	}
	bool isFull() {
		if (top == max-1) {
			return true;
		}
		else {
			return false;
		}
	}
	void Pop();
	void Push(const T& x) {
		if (isFull()) {
			cout << "is Full" << endl;
		}
		else {
			stack[top] = x;
		}
	}
};
template <class T>
void Stack<T>::Pop() {
	if (isEmpty()) {
		cout << "is Empty" << endl;
		return;
	}
	else {
		stack[top--].~T();
	}
}
#endif // !HEADER_H

