#ifndef SPARSEMT_DIM2_H
#define SPARSEMT_DIM2_H
#include"SparseMT.h"
//傳統轉置二維矩陣
class SparseMT_DIM2 :public SparseMT {//繼承SparseMT(並展現多形)
private:
	int** MT2D;	//動態建立：動態建立的陣列本質是指向指標的指標。
public:
	SparseMT_DIM2(int, int, int**);
	void Transpose()override;//多形
	void printMT()override;//多形
};
#endif 

