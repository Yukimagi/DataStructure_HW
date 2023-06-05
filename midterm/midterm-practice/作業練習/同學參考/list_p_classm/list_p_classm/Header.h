#include<iostream>
using namespace std;

struct Term {
	long long int coef;//常數
	long long int exp;//指數
	Term Set(long long int c, long long int e) {
		coef = c;
		exp = e;
		return *this;
	};
};

template<class T>class Chain;
class Polynomial;

template<class T>
class ChainNode {
	friend class Chain<T>;
public:
	ChainNode(const T& data, ChainNode<T>* link = NULL) {
		this->data = T(data);
		this->link = link;
	}
private:
	T data;
	ChainNode<T>* link;
};

template<class T>
class Chain {
	friend class Polynomial;
public:
	Chain() {
		first = NULL;
		last = NULL;
	};
	/*
	~Chain() {
		ChainNode<T>* next_node = NULL;
		while (first != NULL)
		{
			next_node = first->link;
			delete first;
			first = next_node;
		}
	};
	*/
	void Delete(int theIndex) {
		if (first == NULL) {
			throw "Cannot delete from empty chain\n";
		}
		ChainNode<T>* deleteNode;
		if (theIndex == 0) {
			deleteNode = first;
			first = first->link;
			delete deleteNode;
		}
		else {
			ChainNode<T>* p = first;
			for (int i = 0; i < theIndex - 1; i++) {
				p = p->link;
			}
			deleteNode = p->link;
			p->link = p->link->link;
		}
		delete deleteNode;
	}

	void Insert(int theIndex, T& e) {
		if (theIndex < 0) {
			throw "Bad insert index\n";
		}
		if (theIndex == 0) {
			first = new ChainNode<T>(e, first);
		}
		else {
			ChainNode<T>* p = first;
			for (int i = 0; i < theIndex - 1; i++) {
				p = p->link;
			}
			p->link = new ChainNode<T>(e, p->link);
		}
	}
	void InsertBack(const T& e) {
		if (first != NULL) {
			last->link = new ChainNode<T>(e);
			last = last->link;
		}
		else first = last = new ChainNode<T>(e);
	}
	/*
	void Concatenate(Chain<T>& b) {
		if (first) {
			last->link = b.first;
			last = b.last;
		}
		else {
			first = b.first;
			last = b.last;
		}
		b.first = b.last = NULL;
	}
	*/
	void Reverse() {
		ChainNode<T>
			* current = first,
			* previous = NULL;
		while (current) {
			ChainNode<T>
				* r = previous;
			previous = current;
			current = current->link;
			previous->link = r;
		}
		first = previous;
	}

	void show() {
		ChainNode<T>
			* current = first;
		while (current != NULL) {
			if (current->link != NULL) {
				if (current->data.exp == 0) {
					cout << current->data.coef << " + ";
				}
				else {
					cout << current->data.coef << "x^" << current->data.exp << " + ";
				}
			}
			else {
				if (current->data.exp == 0) {
					cout << current->data.coef << endl;
					break;
				}
				cout << current->data.coef << "x^" << current->data.exp << endl;
				break;
			}
			current = current->link;
		}
	}
	class ChainIterator {//Iterator: an object permits you to traverse all the elements of a container class (such as list class).

	public:
		ChainIterator(ChainNode<T>* startNode) {
			current = startNode;
		};
		T& operator*() const {
			return current->data;
		}
		T* operator->() const {
			return &current->data;
		}
		ChainIterator& operator++() {
			current = current->link;
			return *this;
		}
		ChainIterator operator++(int) {
			ChainIterator old = *this;
			current = current->link;
			return old;
		}
		bool operator!=(ChainIterator right) {
			return current != right.current;
		}
		bool operator==(ChainIterator right) {
			return current == right.current;
		}
	private:
		ChainNode<T>* current;
	};
	ChainIterator begin() const {
		return ChainIterator(first);
	}
	ChainIterator end() const {
		return ChainIterator(NULL);
	}
private:
	ChainNode<T>* first;
	ChainNode<T>* last;
};

class Polynomial {
public:
	Polynomial operator+(const Polynomial& b) const {
		Term temp;
		Chain<Term>::ChainIterator
			ai = poly.begin(),
			bi = b.poly.begin();
		Polynomial c;
		while (ai != NULL && bi != NULL) {
			if (ai->exp == bi->exp) {
				int sum = ai->coef + bi->coef;
				if (sum) {
					c.poly.InsertBack(temp.Set(sum, ai->exp));
					ai++;
					bi++;
				}
			}
			else if (ai->exp < bi->exp) {
				c.poly.InsertBack(temp.Set(bi->coef, bi->exp));
				bi++;
			}
			else {
				c.poly.InsertBack(temp.Set(ai->coef, ai->exp));
				ai++;
			}
		}
		while (ai != poly.end()) {
			c.poly.InsertBack(temp.Set(ai->coef, ai->exp));
			ai++;
		}
		while (bi != poly.end()) {
			c.poly.InsertBack(temp.Set(bi->coef, bi->exp));
			bi++;
		}
		return c;
	}

	Chain<Term> poly;
};
