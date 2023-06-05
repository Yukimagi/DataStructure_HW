#ifndef SPARSEMT_DIM2_H
#define SPARSEMT_DIM2_H
#include "SparseMT.h"
#include<iostream>
using namespace std;
class SparseMT_DIM2 :public SparseMT {

	
public:
	//�@�w�n�bpublic
	int** array;//MT2D(�ʺA�G���}�C)

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

	//�]���Otranspose�ҥH�O����col�j�p�A��row
	void Transpose()override {
		int** swapMT = new int* [cols];//SPACE:����cols��swapMT
		for (int i = 0; i < cols; i++) {
			swapMT[i] = new int[rows];//SPACE:�o�̤S����cols����rows�ӪŶ�(cols*rows)
			fill(swapMT[i], swapMT[i] + rows, 0);
		}

		//��m
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				//TIME:row*column
				if (array[i][j] != 0) {//�N�D0�Ȧs�J
					swapMT[j][i] = array[i][j];
				}
			}
		}
		delete[]array;
		array = swapMT;

		//�Nrows�Bcols�ȥ洫
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
