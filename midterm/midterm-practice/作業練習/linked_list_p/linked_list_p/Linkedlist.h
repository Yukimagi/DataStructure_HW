#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include<iostream>
#include <stdexcept>
using namespace std;

template<class T> class Chain;

template<class T>
class ChainNode 
{
private:
    T data;//T
    ChainNode<T>* link;

    friend class Chain<T>;
public:
    ChainNode() {}
    ChainNode(const T& data) {
        this->data = data;
    }
    ChainNode(const T& data, ChainNode<T> *link) {
        this->data = data;
        this->link = link;
    }
};

template<class T>
class Chain {//Chain
private:
    ChainNode<T>* first;
public:
    Chain() {//�غc�l�A�]first����
        first = NULL;
    }
    ~Chain()//�Ѻc�l//�R��������node//�o�̩���
    {
        while (first != NULL) {
            //delete first
            ChainNode<T>* next = first->link;
            delete first;
            first = next;
        }
    }
    bool IsEmpty()const {
        return first == NULL;//�n==
    }

    void Delete(int theIndex) {
        if (first == NULL) {
            throw "Cannot delete from empty chain";
        }
        ChainNode<T>* deleteNode;//<T>
        if (theIndex == 0) {
            //remove first node from chain
            deleteNode = first;
            first = first->link;
            delete deleteNode;
        }
        else {
            //use p as beforeNode
            ChainNode<T>* p = first;
            for (int i = 0; i < theIndex - 1; i++) {
                p = p->link;
            }
            deleteNode = p->link;
            p->link = p->link->link;
        }
        delete deleteNode;

    }

    void Insert(int theIndex, const T& theElement) {
        if (theIndex < 0) {
            throw "Bad insert index";
        }
        if (theIndex == 0) {
            //insert at front
            first = new ChainNode<T>(theElement, first);
        }
        else {
            //use p as beforeNode
            ChainNode<T>* p = first;
            for (int i = 0; i < theIndex - 1; i++) {
                p = p->link;
            }
            //insert after p
            p->link = new ChainNode<T>(theElement, p->link);
        }

    }

    void displayAll() {
        if (first == NULL) {
            cout << "linked list is empty" << endl;
            return;
        }
        cout << endl << "----link list items------" << endl;
        ChainNode<T>* temp = first;
        while (temp != NULL) {
            cout << temp->data << " | ";
            temp = temp->link;
        }
        cout << endl << "--------------------------" << endl;
    }

};
#endif 

