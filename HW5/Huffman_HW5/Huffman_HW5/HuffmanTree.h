#include <iostream>
#include <algorithm>
using namespace std;
class HuffmanTree;
class Node;

template<class T1, class T2>
class Pair {//存兩個對應的char和頻率times

public:
    Pair() {};
    Pair(T1 a, T2 b){ 
        x = a;
        y = b;
    };
    T1 x;
    T2 y;
    // 自訂比較函數(用於sort)
    bool operator>(const Pair& b) const//多載大於
    {
        if (x > b.x) {
            return true;
        }
        else if (x == b.x && y > b.y) {
            return true;
        }
        else {
            return false;
        }

    }

};

class Node {//建立節點
    friend class HuffmanTree;
private:
    char ch;
    int times;
    Node* left;//左
    Node* right;//右
public:
    //HuffmanNode() {};
    Node(int n) { 
        ch = char(0);
        times = n;
        left = nullptr;
        right = nullptr;
    };
    Node(char c, int n) {
        ch = c;
        times = n;
        left = nullptr;
        right = nullptr;
    };
};


class HuffmanTree {
private:
    string ANS_TABLE[256] = { "" };//可依照字元存到對應的table[i]
    Node* root;//根節點

public:
    HuffmanTree(Pair<int, char>ch_times[], int num) :root(nullptr) {//num=ch數量

        // 排序 ch_times 陣列，需指定排序的起始與結束範圍
        sort(ch_times, ch_times + num, greater<Pair<int, char> >());//後面是自訂比較函數

        Node* tree_now[256];//最多可能性為256個
        //建立node
        for (int i = 0; i < num; i++) {
            tree_now[i] = new Node(ch_times[i].y, ch_times[i].x);
        }

        while (num != 1)
        {
            Node* Node_connect = new Node(tree_now[num - 1]->times + tree_now[num - 2]->times);//將兩子節點相加

            Node_connect->left = tree_now[num - 1];//將其對應到左節點
            Node_connect->right = tree_now[num - 2];//將其對應到右節點
            num--;

            int n_place = min(tree_now, Node_connect->times, num);//相加後找出最小值繼續做

            for (int i = num - 1; i >= n_place; i--) {
                tree_now[i] = tree_now[i - 1];//將各節點比找到的位置大的往後
            }

            tree_now[n_place] = Node_connect;//並將相加後的節點放到n_place
        }
        root = tree_now[0];//第0個為root

        Coding(root, "");//將樹轉換成0或1
    }

    int min(Node* tree_now[], int times, int num){//相加後找出最小值繼續做
        int first = 0;
        int last = num - 1;
        int mid;

        while (first <= last)//使用binary search
        {
            mid = (first+last) / 2;
            if ((tree_now[mid]->times) > times) {
                first = mid + 1;
                mid++;
            }
            else {
                last = mid - 1;
            }
        }
        return mid;
    }

    void  Coding(Node* now, string code_now)
    {
        if (now->ch == char(0))//將左設為0，右為1
        {
            Coding(now->left, code_now + "0");
            Coding(now->right, code_now + "1");
        }
        else
        {
            ANS_TABLE[now->ch - 0] = code_now;//依照字對應的數字存
        }
    }

    void show()//找到對應的table並印出來~
    {
        for (int i = 0; i < 256; i++)
        {
            if (ANS_TABLE[i] != "")
            {
                cout << char(i) << " " << ANS_TABLE[i] << endl;
            }
        }
    }


    string encoding(string s)//找到對應的table並印出來~
    {
        string ans = "";
        for (int i = 0; i < s.size(); i++)
        {
            ans += ANS_TABLE[s[i] - 0];
        }
        return ans;
    }
};
