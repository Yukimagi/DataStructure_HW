#ifndef HEADER_H
#define HEADER_H
template<class T>
class ChainNode {
	friend class Doubly_Linked_List<T>;
private:
	ChainNode<T>* link;
	T data;
public:
	ChainNode();
	ChainNode(const T& x) {
		data = x;
	}
	ChainNode(const T& x, ChainNode<T>* link) {
		data = x;
		this->link = link;
	}
};
template <class T>
class Doubly_Linked_List {
private:
	ChainNode<T>* first;
	int index;
public:
	Doubly_Linked_List() {
		first = NULL;
		index = 0;
	}
	bool isEmpty(){
		return first == NULL;
	}
	void Delete() {
		if (isEmpty()) {
			throw"is empty";
		}
		ChainNode<T>* n;
		if (index == 0) {
			n = first;
			first = first->link;
			delete n;
		}
		else {
			ChainNode<T>* p;
			for (int i = 0; i < index - 1; i++) {
				p = p->link;
			}
			n = p->link;
			p->link = p->link->link;
			delete n;
		}


	}
	void getIndex(int a) {
		index = a;
	}
	void forward(int a) {
		int i = index;
		int c = index;
		ChainNode<T>* p=;
		for (i; i > c - a; i++) {
			p = p->link;
		}
		p = p->link;
		cout >> p->data;
	}
	void back(int a) {
		int i = index;
		int c = index;
		ChainNode<T>* p = ;
		for (i; i > c - a; i++) {
			p = p->link;
		}
		p = p->link;
		cout >> p->data;
	}
	void Insert(const T&data) {
		if (index<0) {
			cout<<"Here is already first page"<<endl;
		}
		ChainNode<T>* n;
		if (index == 0) {
			first = new ChainNode<T>(data, first);
		}
		else {
			ChainNode<T>* p;
			for (int i = 0; i < index - 1; i++) {
				p = p->link;
			}
			p->link= new ChainNode<T>(data, p->link);
		}


	}
};
#endif // !HEADER_H

