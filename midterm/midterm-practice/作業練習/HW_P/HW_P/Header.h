#ifndef HERDER_H
#define HEADER_H
#include<iostream>
using namespace std;
template <class T>
class ChainNode {
	friend class Chain<T>;
private:
	ChainNode* link;
	T data;
public:
	ChainNode();
	ChainNode(const T& data) {
		this->data = data;
	}
	ChainNode(const T& data, ChainNode* link) {
		this->data = data;
		this->link = link;
	}
};
template<class T>
class Chain {
private:
	ChainNode* first;
public:
	Chain() {
		first = NULL;
	}
	~Chain() {
		while (first != NULL) {
			ChainNode<T>* next= first->link;
			delete first;
			first = next;
		}
	}
	bool isEmpty() {
		return first == NULL;
	}
	void Delete(int index) {
		ChainNode<T>* deleteNode;
		if (isEmpty()||index<0) {
			throw"ERROE";
		}
		
		if(index==0) {
			deleteNode=first;
			first=first->link;
			delete deleteNode;
		}
		else {
			ChainNode<T>* p=first;
			for (int i = 0; i < index - 1; i++) {
				p=p->link;
			}
			deleteNode = p - link;
			p->link = p->link->link;
			
		}
		delete deleteNode;
	}
	void Insert(const T&d,int index) {
		if (index < 0) {
			throw"ERROR INDEX";
		}
		else if (index == 0) {
			first =new  ChainNode<T>(d, first);
		}
		else {
			ChainNode<T>* p = first;
			for (int i = 0; i < index - 1; i++) {
				p = p->link;
			}
			p->link = new ChainNode<T>(d, p->link);
		}
	}
};
#endif 

