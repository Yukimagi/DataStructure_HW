#include <iostream>
//#include "bcd.h"
//#include "bcd_modify.h"
// #include "bcd_sub.h"
//#include "bcd_array.h"
// #include "linkedlist_mod.h"
#include "linkedlist.h"
#include<string>


using namespace std;

int main()
{

    //cout<<hex<<(0xFLL << (5 << 2)&0x1111111111111111);
    string a, b;

    while (getline(cin, a))
    {
        getline(cin, b);

        LinkedList x(a), y(b);


        // cout<<x<<endl;
        // cout<<y<<endl;

        //BCD64 v(a),vv(b);
        // cout<<(v<vv)<<endl;
        // cout<<(vv<v)<<endl;
        // uint8_t c=0;
        // BCD64 p=v.sub(vv,c);
        // cout<<p<<endl;

        // x.print();
        // cout<<endl;
        // y.print();
        // cout<<endl;

        //cout<<a+" - "+b+" = ";
        cout << a + " + " + b + " = ";

        x.add(y);
        //cout<<x.add(y)<<endl;


        x.print();
        cout << endl;

    }




    return 0;
}