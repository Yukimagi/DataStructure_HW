#include <iostream>
#include<string>
#include "LinkedList.h"
#include <windows.h>
using namespace std;

int main()
{
    string first;
    string second;
    LARGE_INTEGER START1, END1;//�}�l�P�����ɶ�(�]�bmain�O���F�F��class�M�`��transpose�Y�i)
    QueryPerformanceCounter(&START1);
    while (getline(cin, first) && getline(cin, second))
    {
        // Create your objects and add two big numbers
        // <Your list class> obj1();
        // <Your list class> obj2();
        // <Your list class> sum = obj1 + obj2;
        LinkedList A(first);
        LinkedList B(second);
        cout << first << " + " << second << " = ";
        A.Add(B);
        A.Show();
        cout << endl;
    }
    QueryPerformanceCounter(&END1);
    cout << (double)(END1.QuadPart - START1.QuadPart) << " �L��\n";
    return 0;
}