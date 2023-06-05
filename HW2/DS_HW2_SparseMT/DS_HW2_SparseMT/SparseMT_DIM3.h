#ifndef SPARSEMT_DIM3_H
#define SPARSEMT_DIM3_H
#include"SparseMT.h"
#include"SparseMT_DIM2.h"
#include"SparseMT_DIM3_FAST.h"
//三維的Transpose
class  SparseMT_DIM3 : public SparseMT {//由於要多形，因此將課本的拆成兩個class，呼叫同名異式的函式
private:
	SparseMT_term* array;//以緊湊的形式表示稀疏矩陣使用三元組的集合
	int terms;//非零數
public:
	SparseMT_DIM3(int, int, SparseMT_term* arr, int);
	void Transpose()override;//多形
	void printMT()override;//多形

};
#endif
