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
    //1.�j�Ʃw�q���غc�l�A�t�w�qnode
    Node(BCD64 o, Node* n, Node* p) :obj(o), next(n), prev(p) {};
    //2.�j�Ʃw�q���غc�l
    Node(BCD64 o) :obj(o), next(nullptr), prev(nullptr) {};
    //3.�@�}�l���string��J����w�q�Ҧ����غc�l
    Node(string s) :obj(BCD64(s)), next(nullptr), prev(nullptr) {};
    //4.�@�}�l���string��J����w�q�Ҧ����غc�l�A�t�w�qnode
    Node(string s, Node* n, Node* p) :obj(BCD64(s)), next(n), prev(p) {};
};

class LinkedList {
private:
    Node* head;//�Y
    Node* last;//��
public:
    LinkedList(){

        head = nullptr;//��l�Ƭ�null
        last = nullptr;//��l�Ƭ�null
    };
    LinkedList(uint64_t b) :head(nullptr), last(nullptr) {

        last = head = new Node(BCD64(b), nullptr, nullptr);//��J�w�q �e����Х��إ߬�null
    }

    LinkedList(string s) :head(nullptr), last(nullptr) {
        //�]���bbcd.h���n�D�n����j��16�줸�A�]���ΥH�U��k�N�L�̤��Φ����j��16�줸���r��
        for (int a = s.size() - 1; a >= 0; a -= 16){

            if (a - 15 < 0){
                //�q���w����m�_�Ǧ^�r�ꤤ���w���ת��r���C
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
        //���Y������null�h���_�a����@��node��delete
        while (head != nullptr){

            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void PushHead(BCD64 b) {//�]���ڭ̬O�ѫ᩹�e��string�]���|�Opush front
        //�إ߸`�I
        if (head == nullptr) {  //�Y���ūh�Y�B���إ߬ۦPnode
            last = head = new Node(b);
        }
        else{                   //�_�h�N
            head->prev = new Node(b, head, nullptr);//�w�q�{�b���Y���e�@�Ӭ��s�`�I
            head = head->prev;//���Y�h����Ӫ�head���e�@��
        }
    }

    void Add(LinkedList& x) {
        Node* first = x.last;//�Q�[�ƪ��̫�@�ӭ�
        Node* second = last;//�[�ƪ��̫�@�ӭ�

        uint8_t carry = 0;/* You may need to prepare a carry variable to 
                            * get the carryout produced by add() method!
                            * 
                            * And, initialize it to 0!
                            * */

        BCD64 zero((uint64_t)0);//�w�q0
        BCD64 one((uint64_t)1);////�w�q1

        while (first != nullptr || second != nullptr){

            if (first == nullptr) {//first=null
               /* BCD64 obj5 = obj2.add(obj3, &carry);//Add obj2 and obj3 to obj5.
                                                        You may use the third parameter
                                                        when using linked list!
                */
                second->obj = second->obj.add(zero, &carry);//num carry_in carry_out
                second = second->prev;//����U�@��
            }
            else if (second == nullptr) {//second = null

                PushHead(first->obj.add(zero, &carry));//num carry_in carry_out
                first = first->prev;//����U�@��
            }
            else {
                //�����Onull�ɨ�̬ۥ[
                second->obj = first->obj.add(second->obj, &carry);
                first = first->prev;
                second = second->prev;
            }
        }

        if (carry != 0) {
            PushHead(one);//�̫᪺carry�p�G������0�h�i��1
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

