#ifndef STACK_H
#define STACK_H
#include <iostream>

template <class T>
class Stack
{ // objects: A finite ordered list with zero or more elements
public:
	Stack(int MaxStackSize = 100);
	// Create an empty stack whose maximum size is MaxStackSize
	bool IsFull();
	// if number of elements in the stack is equal to the maximum size
	// of the stack, return TRUE(1) else return FALSE(0)
	bool IsEmpty();
	// if number of elements in the stack is 0, return TRUE(1) else return FALSE(0)
	void Push(const T& item);
	// if IsFull(), then StackFull(); else insert item into the top of the stack.
	void Pop();
	// if IsEmpty(), then StackEmpty() and return;
	// else remove the top element of the stack.
	T Newest();
	int getTop() {
		return top;
	}
	T* getStack() {
		return stack;
	}
private:
	int top;
	T* stack;
	int MaxSize;
};

template<class T>
Stack<T>::Stack(int MaxStackSize) :MaxSize(MaxStackSize) {
	stack = new T[MaxSize];
	top = -1; //initialize this value for emptiness check
}

template<class T>
inline bool Stack<T>::IsFull() {
	if (top == MaxSize - 1) return true;
	else return false;
}

template<class T>
inline bool Stack<T>::IsEmpty() {
	if (top == -1) return true;
	else return false;
}

template <class T>
void Stack<T>::Push(const T& x)
{
	// add an item to the stack 
	if (IsFull())
		std::cout << "Full!!!" << std::endl;
	else
		stack[++top] = x;
}

template <class T>
void Stack<T>::Pop()
{
	// return the top element from the stack
	if (IsEmpty())
	{
		std::cout << "Empty!!!" << std::endl;
		return;
	}
	stack[top--] .~T(); //destructor for T;
}

template <class T>
T Stack<T>::Newest()
{
	// return the top element from the stack
	return stack[top];
}
#endif
