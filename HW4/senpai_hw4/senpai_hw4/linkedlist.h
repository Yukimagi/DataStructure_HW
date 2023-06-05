#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_

#include "bcd.h"
#include <algorithm>
#include <iomanip>

class BCD64;
class LinkedList;

class Node {

    friend class LinkedList;

public:
    Node(BCD64 o) :obj(o), next(nullptr), prev(nullptr) {};
    Node(BCD64 o, Node* n, Node* p) :obj(o), next(n), prev(p) {};
    Node(string s) :obj(BCD64(s)), next(nullptr), prev(nullptr) {};
    Node(string s, Node* n, Node* p) :obj(BCD64(s)), next(n), prev(p) {};


private:
    BCD64 obj;
    Node* next;
    Node* prev;

};

class LinkedList {

public:
    LinkedList() :first(nullptr), last(nullptr) {};
    LinkedList(uint64_t b) :first(nullptr), last(nullptr) {

        last = first = new Node(BCD64(b), nullptr, nullptr);

    }

    LinkedList(string s) :first(nullptr), last(nullptr) {

        for (int i = s.size() - 1; i >= 0; i -= 16)
        {

            if (i - 15 < 0)
            {
                string sub = s.substr(0, i + 1);//從指定的位置起傳回字串中指定長度的字元。//https://help.salesforce.com/s/articleView?id=sf.bi_integrate_data_prep_recipe_formula_field_stringFunctions_substr.htm&type=5
                push_front(BCD64(sub));
            }
            else
            {
                string sub = s.substr(i - 15, 16);
                push_front(BCD64(sub));
            }


        }


    }

    ~LinkedList()
    {
        while (first != nullptr)
        {
            Node* tmp = first;
            first = first->next;


            delete tmp;

        }

    }




    void push_front(BCD64 b) {


        if (first == nullptr)
            last = first = new Node(b);
        else
        {
            first->prev = new Node(b, first, nullptr), first = first->prev;
        }

    }

    void print()
    {
        Node* cur = first;
        while (cur != nullptr)
        {
            if (cur != first)
                cout << setw(16) << setfill('0') << cur->obj;
            else
                cout << cur->obj;


            cur = cur->next;

        }

    }

    void add(LinkedList& x) {
        Node* a = x.last, * b = last;

        uint8_t carry = 0;
        BCD64 zero((uint64_t)0);
        BCD64 one((uint64_t)1);

        while (a != nullptr || b != nullptr)
        {

            if (a == nullptr)
                b->obj = b->obj.add(zero, &carry, carry), b = b->prev;
            else if (b == nullptr)
                push_front(a->obj.add(zero, &carry, carry)), a = a->prev;
            else
                b->obj = a->obj.add(b->obj, &carry, carry), a = a->prev, b = b->prev;


        }

        if (carry != 0)
            push_front(one);


    }

private:
    Node* first;
    Node* last;



};


#endif
