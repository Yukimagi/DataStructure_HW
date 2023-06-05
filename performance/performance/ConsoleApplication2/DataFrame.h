#include<iostream>
#include<iomanip>
#include<fstream>
#include<string>
#include<sstream>
#include<cfloat>
using namespace std;
//定義一個二元樹，使其能夠找出有哪些資料出現過。
struct Node {
    string data; // 元素值
    Node* left; // 指向左子節點的指針
    Node* right; // 指向右子節點的指針
};

// 定義一個insert函數，用於將元素插入到二元搜尋樹中
bool insert(Node*& root, const string& s) {
    // root是二元搜尋樹的根節點，s是要插入的元素值
    // 如果根節點為空，則創建一個新節點，存放元素值和空指針，並將根節點指向它
    if (root == nullptr) {
        root = new Node;
        root->data = s;
        root->left = nullptr;
        root->right = nullptr;
        return true; // 返回true表示插入成功
    }
    // 如果根節點不為空，則比較根節點與要插入的元素值的大小
    if (s < root->data) { // 如果要插入的元素值小於根節點的值
        return insert(root->left, s); // 遞迴地在左子樹中插入
    }
    else if (s > root->data) { // 如果要插入的元素值大於根節點的值
        return insert(root->right, s); // 遞迴地在右子樹中插入
    }
    else { // 如果要插入的元素值等於根節點的值
        return false; // 返回false表示插入失敗，因為該元素已經存在於二元搜尋樹中
    }
}