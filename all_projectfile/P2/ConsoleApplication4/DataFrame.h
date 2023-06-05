#include<iostream>
#include<iomanip>
#include<fstream>
#include<string>
#include<sstream>
#include<cfloat>
using namespace std;
//�w�q�@�ӤG����A�Ϩ�����X�����Ǹ�ƥX�{�L�C
struct Node {
    string data; // ������
    Node* left; // ���V���l�`�I�����w
    Node* right; // ���V�k�l�`�I�����w
};

// �w�q�@��insert��ơA�Ω�N�������J��G���j�M��
bool insert(Node*& root, const string& s) {
    // root�O�G���j�M�𪺮ڸ`�I�As�O�n���J��������
    // �p�G�ڸ`�I���šA�h�Ыؤ@�ӷs�`�I�A�s�񤸯��ȩM�ū��w�A�ñN�ڸ`�I���V��
    if (root == nullptr) {
        root = new Node;
        root->data = s;
        root->left = nullptr;
        root->right = nullptr;
        return true; // ��^true��ܴ��J���\
    }
    // �p�G�ڸ`�I�����šA�h����ڸ`�I�P�n���J�������Ȫ��j�p
    if (s < root->data) { // �p�G�n���J�������Ȥp��ڸ`�I����
        return insert(root->left, s); // ���j�a�b���l�𤤴��J
    }
    else if (s > root->data) { // �p�G�n���J�������Ȥj��ڸ`�I����
        return insert(root->right, s); // ���j�a�b�k�l�𤤴��J
    }
    else { // �p�G�n���J�������ȵ���ڸ`�I����
        return false; // ��^false��ܴ��J���ѡA�]���Ӥ����w�g�s�b��G���j�M��
    }
}