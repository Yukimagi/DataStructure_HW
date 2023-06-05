#ifndef SPARSEMT_DIM3_H
#define SPARSEMT_DIM3_H
#include"SparseMT.h"
#include<iostream>
using namespace std;
class  SparseMT_DIM3 :public SparseMT {
public:
    //一定要在public
    SparseMT_term* smArray;//SparseMT_term* array;//以緊湊的形式表示稀疏矩陣使用三元組的集合
    int terms;//#non-zero

    SparseMT_DIM3(int r, int c,  int t) {
        this->cols = c;
        this->rows = r;
        this->terms = t;
        this->smArray = new SparseMT_term[terms];//容量為terms

    };

    void Transpose()override {
        SparseMT_term* bsmArray = new SparseMT_term[terms];//space:O(terms)容量為terms(存轉置後的)
        if (terms > 0) {
            // currentB 用來記錄 b 中的第幾個元素
            int currentB = 0;


            // 將原本的矩陣轉置
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
