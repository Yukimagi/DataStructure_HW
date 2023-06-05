#include"Linkedlist.h"
#include<iostream>
using namespace std;

int main() {
    Chain <int> list;
    int ch, item, index;
    bool quit = false;
    do {
        cout << "====================================" << endl;
        cout << "select option :" << endl;
        cout << "1: insert at index" << endl;
        cout << "2: delete at index" << endl;
        cout << "3: delete all" << endl;
        cout << "4: display items" << endl;
        cout << "5: exit" << endl;
        cin >> ch;
        cout << "====================================" << endl;
        switch (ch)
        {
        case 1:
            cout << "enter item to insert:" << endl;
            cin >> item;
            cout << "enter index:" << endl;
            cin >> index;
            list.Insert(index, item);
            break;
        case 2:
            cout << "enter index:" << endl;
            cin >> index;
            list.Delete(index);
            break;
        case 3:
            list.~Chain();
            cout << "Chain ¤w¥ş§R!" << endl;
            break;
        case 4:
            list.displayAll();
            break;

        case 5:
            quit = true;
            break;
        default:
            cout << "invalid selection" << endl;
            break;
        }
    } while (!quit);
    return 0;
}