#include <iostream>
#include "HuffmanTree.h"
#include <sstream>
using namespace std;

int main()
{
    // Pair<HuffmanNode*,int> pp;
    string s;
    stringstream ss;
    int num=0;
    while (getline(cin, s))
    {
        if (s == "")
            break;
        ss << s << "\n";

        num++;
    }

    Pair<int, char>*char_freq = new Pair<int, char>[num];

    for (int i = 0; i < num; i++)
    {
        getline(ss, s, '\n');

        stringstream sss(s);
        char c;
        int freq;
        
        sss >> c;
        cout << c;
        sss >> freq;
        cout << freq<<" ";

        char_freq[i].first = freq;
        char_freq[i].second = c;



    }

   // for(int i=0;i<num;i++)
    // {
    //     cout<<char_freq[i].first<<" "<<char_freq[i].second<<endl;
    //}

    HuffmanTree tree(char_freq, num);
    //tree.traversal();
    tree.print_code();
    cin >> s;

    cout << "\n" << tree.encode(s) << endl;





    return 0;
}