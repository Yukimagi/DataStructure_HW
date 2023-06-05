#include <iostream>
#include <sstream>//專門拿來讀取字串並且處理，很多時候拿來做字串的切割，或者是int跟string類別之間的轉換。
#include "HuffmanTree.h"
using namespace std;

int main()
{
    string s1;//輸入字串
    stringstream s2;//用於後續分割字串
    int num = 0;
    while (getline(cin, s1))
    {
        if (s1 == "") {
            break;
        }
        s2 << s1 << "\n";
        num++;
    }

    Pair<int, char>* huffmanCoding = new Pair<int, char>[num];

    for (int i = 0; i < num; i++)
    {
        getline(s2, s1, '\n');//sstream+getline(字串分割)
        stringstream s3(s1);//將對應的type傳入
        char c;
        int t;
        //s1[0] = c;
        //s1[1] = freq;
        s3 >> c;
        s3 >> t;

        huffmanCoding[i].y = c;
        huffmanCoding[i].x = t;
    }

    HuffmanTree tree(huffmanCoding, num);

    tree.show();//印出各自元coding後的結果
    
    cin >> s1;

    cout << "\n" << tree.encoding(s1) << endl;//轉成一串binary bits
    return 0;
}