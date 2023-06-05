#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_

#include "bcd2.h"
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
    //1.计﹚竡篶﹚竡node
    Node(BCD64 o, Node* n, Node* p) :obj(o), next(n), prev(p) {};
    //2.计﹚竡篶
    Node(BCD64 o) :obj(o), next(nullptr), prev(nullptr) {};
    //3.秨﹍ъstring块﹚竡┮Τ篶
    Node(string s) :obj(BCD64(s)), next(nullptr), prev(nullptr) {};
    //4.秨﹍ъstring块﹚竡┮Τ篶﹚竡node
    Node(string s, Node* n, Node* p) :obj(BCD64(s)), next(n), prev(p) {};
};

class LinkedList {
private:
    Node* head;//繷
    Node* last;//Ю
public:
    LinkedList(){

        head = nullptr;//﹍てnull
        last = nullptr;//﹍てnull
    };
    LinkedList(uint64_t b) :head(nullptr), last(nullptr) {

        last = head = new Node(BCD64(b), nullptr, nullptr);//块﹚竡 玡夹ミnull
    }

    LinkedList(string s) :head(nullptr), last(nullptr) {
        //bcd.hい璶―璶ぃ16じノよ猭盢だ澄Θぃ16じ﹃
        for (int a = s.size() - 1; a >= 0; a -= 16){

            if (a - 15 < 0){
                //眖﹚竚癬肚﹃い﹚じ
                //https://help.salesforce.com/s/articleView?id=sf.bi_integrate_data_prep_recipe_formula_field_stringFunctions_substr.htm&type=5
                string SUB = s.substr(0, a + 1);
                //cout << s.substr(0, a + 1) << endl;
                PushHead(BCD64(SUB));
            }
            else{
                string SUB = s.substr(a - 15, 16);
                PushHead(BCD64(SUB));
            }
        }
    }
    ~LinkedList(){
        //讽繷ぃ单null玥ぃ耞┕nodedelete
        while (head != nullptr){

            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void PushHead(BCD64 b) {//и琌パ┕玡тstring穦琌push front
        //ミ竊翴
        if (head == nullptr) {  //繷玥繷Юミnode
            last = head = new Node(b);
        }
        else{                   //玥盢
            head->prev = new Node(b, head, nullptr);//﹚竡瞷繷玡穝竊翴
            head = head->prev;//τ繷玥ㄓhead玡
        }
    }

    void Add(LinkedList& x) {
        Node* first = x.last;//砆计程
        Node* second = last;//计程

        uint8_t carry = 0;/* You may need to prepare a carry variable to 
                            * get the carryout produced by add() method!
                            * 
                            * And, initialize it to 0!
                            * */

        BCD64 zero((uint64_t)0);//﹚竡0
        BCD64 one((uint64_t)1);////﹚竡1

        while (first != nullptr || second != nullptr){

            if (first == nullptr) {//first=null
               /* BCD64 obj5 = obj2.add(obj3, &carry);//Add obj2 and obj3 to obj5.
                                                        You may use the third parameter
                                                        when using linked list!
                */
                second->obj = second->obj.add(zero, &carry);//num carry_in carry_out
                second = second->prev;//传
            }
            else if (second == nullptr) {//second = null

                PushHead(first->obj.add(zero, &carry));//num carry_in carry_out
                first = first->prev;//传
            }
            else {
                //讽常ぃ琌nullㄢ
                second->obj = first->obj.add(second->obj, &carry);
                first = first->prev;
                second = second->prev;
            }
        }

        if (carry != 0) {
            PushHead(one);//程carry狦ぃ单0玥秈1
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

