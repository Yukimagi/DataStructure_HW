#ifndef SPARSEMT_DIM3_FAST_H
#define SPARSEMT_DIM3_FAST_H
#include"SparseMT.h"
#include<iostream>
using namespace std;
class SparseMT_DIM3_FAST :public SparseMT {
public:
    //�@�w�n�bpublic
    SparseMT_term* smArray;
    int terms;//�D�s��

	SparseMT_DIM3_FAST(int r, int c, int t) {
        this->cols = c;
        this->rows = r;
        this->terms = t;
        this->smArray = new SparseMT_term[terms];
    };
    void Transpose()override {
        SparseMT_term* bsmArray = new SparseMT_term[terms];
        if (terms > 0) {
            // �إ� rowSize �}�C�A�ΨӰO���C�@�� column ���X�Ӥ���
            int* rowSize = new int[cols];
            int* rowStart = new int[cols];

            // ��l�� rowSize
            for (int i = 0; i < cols; i++) { 
                rowSize[i] = 0; 
            }


            // �p��C�@�� column ���X�Ӥ���
            for (int i = 0; i < terms; i++) { 
                rowSize[smArray[i].col]++;
            }

            // �p��� x column ���Ĥ@�Ӥ����b b ������m
            rowStart[0] = 0;
            for (int i = 1; i < cols; i++) {
                rowStart[i] = rowStart[i - 1] + rowSize[i - 1];
            }

            // �N�쥻���x�}��m
            for (int i = 0; i < terms; i++) {
                int j = rowStart[smArray[i].col];
                bsmArray[j].row = smArray[i].col;
                bsmArray[j].col = smArray[i].row;
                bsmArray[j].value = smArray[i].value;
                rowStart[smArray[i].col]++;
            }

            // ����O����
            delete[] rowSize;
            delete[] rowStart;
        }
            int temp = rows;
            rows = cols;
            cols = temp;
            delete[] smArray;
            smArray = bsmArray;
    }
    void printMT() override {
        for (int i = 0; i < terms; i++) {
            cout << smArray[i].row << " " << smArray[i].col << " " << smArray[i].value << endl;
        }
    }
};
#endif
