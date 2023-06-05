#include"SparseMT.h"
#include"SparseMT_DIM2.h"
#include"SparseMT_DIM3.h"
#include"SparseMT_DIM3.h"
#include"SparseMT_DIM3_FAST.h"

#include<iostream>
#include <windows.h>
using namespace std;
int main() {
	int rows, cols, terms = 0;
	cin >> rows >> cols;
	SparseMT_DIM2 DIM2(rows, cols);
	int row, col, val;
	while (cin >> row >> col >> val) {
		if (row == -1 && col == -1) {
			break;
		}
		DIM2.array[row][col] = val;
		terms++;
	}
	SparseMT_DIM3 DIM3t(rows, cols, terms);
	SparseMT_DIM3_FAST DIM_fast(rows, cols, terms);
	int t = 0;
	for (int i = 0; i < rows; i++) {
		for (int j = -0; j < cols; j++) {
			if (DIM2.array[i][j] != 0) {
				DIM3t.smArray[t].row = i;
				DIM3t.smArray[t].col = j;
				DIM3t.smArray[t].value = DIM2.array[i][j];

				DIM_fast.smArray[t].row = i;
				DIM_fast.smArray[t].col = j;
				DIM_fast.smArray[t].value = DIM2.array[i][j];
				t++;
			}
		}
	}
	
	for (int i = 0; i < terms; i++) {
		cout << "(" << DIM3t.smArray[i].row << ", " << DIM3t.smArray[i].col << ", " << DIM3t.smArray[i].value << ") becomes (" << DIM3t.smArray[i].col << ", " << DIM3t.smArray[i].row << ", " << DIM3t.smArray[i].value << ") in the transpose" << endl;
	}

	//�ѩ󥻨Өϥνҥ���time.h�|�o�{���@�ǥX�Ӫ�����ɶ���0�A�]���ڨϥΧ�p��쪺���ɶ���k(�L��)
	LARGE_INTEGER START1, END1;//�}�l�P�����ɶ�(�]�bmain�O���F�F��class�M�`��transpose�Y�i)
	QueryPerformanceCounter(&START1);
	DIM2.Transpose();
	QueryPerformanceCounter(&END1);
	cout << (double)(END1.QuadPart - START1.QuadPart) << " �L��\n";

	LARGE_INTEGER START2, END2;//�}�l�P�����ɶ�(�]�bmain�O���F�F��class�M�`��transpose�Y�i)
	QueryPerformanceCounter(&START2);
	DIM3t.Transpose();
	QueryPerformanceCounter(&END2);
	cout << (double)(END2.QuadPart - START2.QuadPart) << " �L��\n";

	LARGE_INTEGER START3, END3;//�}�l�P�����ɶ�(�]�bmain�O���F�F��class�M�`��transpose�Y�i)
	QueryPerformanceCounter(&START3);
	

	QueryPerformanceCounter(&END3);
	cout << (double)(END3.QuadPart - START3.QuadPart) << " �L��\n";

}