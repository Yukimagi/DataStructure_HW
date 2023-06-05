#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_

#include "bcd.h"
#include <algorithm>
#include <iomanip>

class BCD64;
class LinkedList;

class Node { //ListNode
    friend class LinkedList;

private:
    BCD64 obj;// create a number - 0
    /*
    BCD64 obj1;             // create a number - 0
    BCD64 obj2(0x6414589);    // create a number - 0x6414589
    BCD64 obj3("185456214562186")//create a number 0x185456214562186
                                   the length of string should be less than 16.
    BCD64 obj4("1854562145621864821562189") // Exception will occur!
    */
    Node* next;
    Node* prev;

public:
    Node(BCD64 o) :obj(o), next(nullptr), prev(nullptr) {};
    Node(BCD64 o, Node* n, Node* p) :obj(o), next(n), prev(p) {};
    Node(string s) :obj(BCD64(s)), next(nullptr), prev(nullptr) {};
    Node(string s, Node* n, Node* p) :obj(BCD64(s)), next(n), prev(p) {};
};

class LinkedList {
private:
    Node* head;//頭
    Node* last;//尾
public:
    LinkedList() {

        head = nullptr;
        last = nullptr;
    };
    LinkedList(uint64_t b) :head(nullptr), last(nullptr) {

        last = head = new Node(BCD64(b), nullptr, nullptr);
    }

    LinkedList(string s) :head(nullptr), last(nullptr) {

        for (int a = s.size() - 1; a >= 0; a -= 16) {

            if (a - 15 < 0) {
                //從指定的位置起傳回字串中指定長度的字元。
                //https://help.salesforce.com/s/articleView?id=sf.bi_integrate_data_prep_recipe_formula_field_stringFunctions_substr.htm&type=5
                string SUB = s.substr(0, a + 1);
                PushHead(BCD64(SUB));
            }
            else {
                string SUB = s.substr(a - 15, 16);
                PushHead(BCD64(SUB));
            }
        }
    }
    ~LinkedList() {

        while (head != nullptr) {

            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void PushHead(BCD64 b) {

        if (head == nullptr) {
            last = head = new Node(b);
        }
        else {
            head->prev = new Node(b, head, nullptr);
            head = head->prev;
        }
    }

    void Add(LinkedList& x) {
        Node* first = x.last;
        Node* second = last;

        uint8_t carry = 0;/* You may need to prepare a carry variable to
                            * get the carryout produced by add() method!
                            *
                            * And, initialize it to 0!
                            * */

        BCD64 zero((uint64_t)0);
        BCD64 one((uint64_t)1);

        while (first != nullptr || second != nullptr) {

            if (first == nullptr) {
                /* BCD64 obj5 = obj2.add(obj3, &carry);//Add obj2 and obj3 to obj5.
                                                         You may use the third parameter
                                                         when using linked list!
                 */
                second->obj = second->obj.add(zero, &carry, carry);
                second = second->prev;
            }
            else if (second == nullptr) {

                PushHead(first->obj.add(zero, &carry, carry));
                first = first->prev;
            }
            else {

                second->obj = first->obj.add(second->obj, &carry, carry);
                first = first->prev;
                second = second->prev;
            }
        }

        if (carry != 0) {
            PushHead(one);
        }
    }

    void Show() {
        Node* now = head;

        while (now != nullptr) {

            if (now != head) {
                // It can be printed by cout directly!
                cout << setw(16) << setfill('0') << now->obj;// the length of the number should be <= 16
            }
            else {

                cout << now->obj;
            }

            now = now->next;
        }

    }
};


#endif