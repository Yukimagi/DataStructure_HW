#ifndef SPARSEMT_DIM3_FAST_H
#define SPARSEMT_DIM3_FAST_H
#include"SparseMT.h"
#include<iostream>
using namespace std;
class SparseMT_DIM3_FAST :public SparseMT {
public:
    //一定要在public
    SparseMT_term* smArray;
    int terms;//非零數

	SparseMT_DIM3_FAST(int r, int c, int t) {
        this->cols = c;
        this->rows = r;
        this->terms = t;
        this->smArray = new SparseMT_term[terms];
    };
    void Transpose()override {
        SparseMT_term* bsmArray = new SparseMT_term[terms];
        if (terms > 0) {
            // 建立 rowSize 陣列，用來記錄每一個 column 有幾個元素
            int* rowSize = new int[cols];
            int* rowStart = new int[cols];

            // 初始化 rowSize
            for (int i = 0; i < cols; i++) { 
                rowSize[i] = 0; 
            }


            // 計算每一個 column 有幾個元素
            for (int i = 0; i < terms; i++) { 
                rowSize[smArray[i].col]++;
            }

            // 計算第 x column 的第一個元素在 b 中的位置
            rowStart[0] = 0;
            for (int i = 1; i < cols; i++) {
                rowStart[i] = rowStart[i - 1] + rowSize[i - 1];
            }

            // 將原本的矩陣轉置
            for (int i = 0; i < terms; i++) {
                int j = rowStart[smArray[i].col];
                bsmArray[j].row = smArray[i].col;
                bsmArray[j].col = smArray[i].row;
                bsmArray[j].value = smArray[i].value;
                rowStart[smArray[i].col]++;
            }

            // 釋放記憶體
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
