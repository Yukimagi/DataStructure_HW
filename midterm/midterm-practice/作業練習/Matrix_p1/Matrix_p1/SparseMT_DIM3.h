#ifndef SPARSEMT_DIM3_H
#define SPARSEMT_DIM3_H
#include"SparseMT.h"
#include<iostream>
using namespace std;
class  SparseMT_DIM3 :public SparseMT {
public:
    //�@�w�n�bpublic
    SparseMT_term* smArray;//SparseMT_term* array;//�H��ꪺ�Φ���ܵ}���x�}�ϥΤT���ժ����X
    int terms;//#non-zero

    SparseMT_DIM3(int r, int c,  int t) {
        this->cols = c;
        this->rows = r;
        this->terms = t;
        this->smArray = new SparseMT_term[terms];//�e�q��terms

    };

    void Transpose()override {
        SparseMT_term* bsmArray = new SparseMT_term[terms];//space:O(terms)�e�q��terms(�s��m�᪺)
        if (terms > 0) {
            // currentB �ΨӰO�� b �����ĴX�Ӥ���
            int currentB = 0;


            // �N�쥻���x�}��m
            for (int c = 0; c < cols; c++) {
                for (int i = 0; i < terms; i++) {
                    if (smArray[i].col == c) {
                        bsmArray[currentB].row = c;
                        bsmArray[currentB].col = smArray[i].row;
                        bsmArray[currentB++].value = smArray[i].value;
                    }
                }
            }

        }
        int temp = rows;
        rows = cols;
        cols = temp;
        delete[] smArray;
        smArray = bsmArray;
    };

    void printMT() override {
        for (int i = 0; i < terms; i++) {
            cout << smArray[i].row << " " << smArray[i].col << " " << smArray[i].value << endl;
        }
    };
};
#endif
