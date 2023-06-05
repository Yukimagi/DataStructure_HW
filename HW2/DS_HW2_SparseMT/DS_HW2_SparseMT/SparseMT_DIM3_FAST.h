/*由於課本有給題目是class因此先建.h*/
/*題目要求:
Given a sparse matrix A, transpose it by the following three methods:
Using traditional 2-dimensional array representation
Using the “Transpose” method in the textbook
Using the “FastTranspose” method in the textbook*/
#ifndef SPARSEMT_DIM3_FAST_H
#define SPARSEMT_DIM3_FAST_H
#include"SparseMT.h"
#include"SparseMT_DIM2.h"
#include"SparseMT_DIM3.h"
//三維的Fast Transpose
class SparseMT_DIM3_FAST :public SparseMT {//fastTranspose
private:
	SparseMT_term* array;//以緊湊的形式表示稀疏矩陣使用三元組的集合
	int terms;//非零數
public:
	SparseMT_DIM3_FAST(int, int, SparseMT_term* a, int);
	void Transpose()override;//多形
	void printMT()override;//多形
};
#endif
