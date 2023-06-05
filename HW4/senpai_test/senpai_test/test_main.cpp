#include <iostream>
#include <random>
#include <profileapi.h>
#include <fstream>
#include "Array.h"
#include "linkedlist.h"

using namespace std;

LARGE_INTEGER li;
double PCfreq = 0.0;
__int64 CounterStart = 0;
ofstream file;


void array_time(string& a, string& b);
void linkedlist_time(string& a, string& b);

int main()
{
    cin.tie(0);
    ios::sync_with_stdio(false);
    file.open("time.txt");
    QueryPerformanceFrequency(&li);
    PCfreq = double(li.QuadPart) / 1000;


    for (int i = 1; i <= 200001; i += 1000)
    {
        string a = "", b = "";
        a += rand() % 9 + 1 + '0';
        b += rand() % 9 + 1 + '0';
        // a+='9';
        // b+='1';

        for (int j = 2; j <= i; j++)
        {
            a += rand() % 10 + '0';
            b += rand() % 10 + '0';
            // a+='9';
            // b+='1';
        }

        //cout<<i<<" digits numbers : \n";
        file << i << " digits numbers : \n";

        array_time(a, b);
        linkedlist_time(a, b);

    }


    return 0;
}


void linkedlist_time(string& a, string& b)
{
    //cout<<"linkedlist_time ";
    file << "linkedlist_time ";
    QueryPerformanceCounter(&li);
    CounterStart = li.QuadPart;
    LinkedList x(a), y(b);
    QueryPerformanceCounter(&li);
    //cout<<"Creation of objects "<<double((li.QuadPart-CounterStart))/PCfreq<<" ms \t";
    file << "Creation of objects " << double((li.QuadPart - CounterStart)) / PCfreq << " ms \t";

    QueryPerformanceCounter(&li);
    CounterStart = li.QuadPart;
    x.Add(y);
    QueryPerformanceCounter(&li);
    //cout<<"addition of big numbers "<<double((li.QuadPart-CounterStart))/PCfreq<<" ms"<<endl;
    file << "addition of big numbers " << double((li.QuadPart - CounterStart)) / PCfreq << " ms" << "\t";

    QueryPerformanceCounter(&li);
    CounterStart = li.QuadPart;
    x.Show();
    QueryPerformanceCounter(&li);
    file << "print result " << double((li.QuadPart - CounterStart)) / PCfreq << " ms" << endl;



}


void array_time(string& a, string& b)
{
    file << "array_time ";
    QueryPerformanceCounter(&li);
    CounterStart = li.QuadPart;
    Array x(a), y(b);
    QueryPerformanceCounter(&li);
    //cout<<"Creation of objects "<<double((li.QuadPart-CounterStart))/PCfreq<<" ms \t";
    file << "Creation of objects " << double((li.QuadPart - CounterStart)) / PCfreq << " ms \t";


    QueryPerformanceCounter(&li);
    CounterStart = li.QuadPart;
    Array z = x.add(y);
    QueryPerformanceCounter(&li);
    //cout<<"addition of big numbers "<<double((li.QuadPart-CounterStart))/PCfreq<<" ms"<<endl;
    file << "addition of big numbers " << double((li.QuadPart - CounterStart)) / PCfreq << " ms" << "\t";

    QueryPerformanceCounter(&li);
    CounterStart = li.QuadPart;
    cout << z;
    QueryPerformanceCounter(&li);
    file << "print result " << double((li.QuadPart - CounterStart)) / PCfreq << " ms" << endl;

}