#include <iostream>
#include <algorithm>
using namespace std;
class HuffmanTree;
class Node;

template<class T1, class T2>
class Pair {//�s��ӹ�����char�M�W�vtimes

public:
    Pair() {};
    Pair(T1 a, T2 b){ 
        x = a;
        y = b;
    };
    T1 x;
    T2 y;
    // �ۭq������(�Ω�sort)
    bool operator>(const Pair& b) const//�h���j��
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

class Node {//�إ߸`�I
    friend class HuffmanTree;
private:
    char ch;
    int times;
    Node* left;//��
    Node* right;//�k
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
    string ANS_TABLE[256] = { "" };//�i�̷Ӧr���s�������table[i]
    Node* root;//�ڸ`�I

public:
    HuffmanTree(Pair<int, char>ch_times[], int num) :root(nullptr) {//num=ch�ƶq

        // �Ƨ� ch_times �}�C�A�ݫ��w�ƧǪ��_�l�P�����d��
        sort(ch_times, ch_times + num, greater<Pair<int, char> >());//�᭱�O�ۭq������

        Node* tree_now[256];//�̦h�i��ʬ�256��
        //�إ�node
        for (int i = 0; i < num; i++) {
            tree_now[i] = new Node(ch_times[i].y, ch_times[i].x);
        }

        while (num != 1)
        {
            Node* Node_connect = new Node(tree_now[num - 1]->times + tree_now[num - 2]->times);//�N��l�`�I�ۥ[

            Node_connect->left = tree_now[num - 1];//�N������쥪�`�I
            Node_connect->right = tree_now[num - 2];//�N�������k�`�I
            num--;

            int n_place = min(tree_now, Node_connect->times, num);//�ۥ[���X�̤p���~��

            for (int i = num - 1; i >= n_place; i--) {
                tree_now[i] = tree_now[i - 1];//�N�U�`�I���쪺��m�j������
            }

            tree_now[n_place] = Node_connect;//�ñN�ۥ[�᪺�`�I���n_place
        }
        root = tree_now[0];//��0�Ӭ�root

        Coding(root, "");//�N���ഫ��0��1
    }

    int min(Node* tree_now[], int times, int num){//�ۥ[���X�̤p���~��
        int first = 0;
        int last = num - 1;
        int mid;

        while (first <= last)//�ϥ�binary search
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
        if (now->ch == char(0))//�N���]��0�A�k��1
        {
            Coding(now->left, code_now + "0");
            Coding(now->right, code_now + "1");
        }
        else
        {
            ANS_TABLE[now->ch - 0] = code_now;//�̷Ӧr�������Ʀr�s
        }
    }

    void show()//��������table�æL�X��~
    {
        for (int i = 0; i < 256; i++)
        {
            if (ANS_TABLE[i] != "")
            {
                cout << char(i) << " " << ANS_TABLE[i] << endl;
            }
        }
    }


    string encoding(string s)//��������table�æL�X��~
    {
        string ans = "";
        for (int i = 0; i < s.size(); i++)
        {
            ans += ANS_TABLE[s[i] - 0];
        }
        return ans;
    }
};
