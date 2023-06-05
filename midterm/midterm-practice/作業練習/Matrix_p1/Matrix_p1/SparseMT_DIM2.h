#ifndef SPARSEMT_DIM2_H
#define SPARSEMT_DIM2_H
#include "SparseMT.h"
#include<iostream>
using namespace std;
class SparseMT_DIM2 :public SparseMT {

	
public:
	//一定要在public
	int** array;//MT2D(動態二維陣列)

	SparseMT_DIM2(int r, int c) {
		this->cols = c;
		this->rows = r;
		this->array = new int* [r];
		for (int i = 0; i < r; i++) {
			array[i] = new int[cols];
		}
		for (int i = 0; i < r; i++) {
			for (int j = 0; j < c; j++) {
				array[i][j] = 0;
			}
		}
	}

	//因為是transpose所以是先有col大小再有row
	void Transpose()override {
		int** swapMT = new int* [cols];//SPACE:產生cols個swapMT
		for (int i = 0; i < cols; i++) {
			swapMT[i] = new int[rows];//SPACE:這裡又對應cols產生rows個空間(cols*rows)
			fill(swapMT[i], swapMT[i] + rows, 0);
		}

		//轉置
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				//TIME:row*column
				if (array[i][j] != 0) {//將非0值存入
					swapMT[j][i] = array[i][j];
				}
			}
		}
		delete[]array;
		array = swapMT;

		//將rows、cols值交換
		int temp = rows;
		rows = cols;
		cols = temp;
	}
	void printMT()override {
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				cout << array[i][j] << " ";// cout << *(*(MT2D + i) + j) << "\t";
			}
			cout << endl;
		}
	}
};
#endif 
