#include <iostream>
#include <sstream>//�M������Ū���r��åB�B�z�A�ܦh�ɭԮ��Ӱ��r�ꪺ���ΡA�Ϊ̬Oint��string���O�������ഫ�C
#include "HuffmanTree.h"
using namespace std;

int main()
{
    string s1;//��J�r��
    stringstream s2;//�Ω������Φr��
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
        getline(s2, s1, '\n');//sstream+getline(�r�����)
        stringstream s3(s1);//�N������type�ǤJ
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

    tree.show();//�L�X�U�ۤ�coding�᪺���G
    
    cin >> s1;

    cout << "\n" << tree.encoding(s1) << endl;//�ন�@��binary bits
    return 0;
}