/*�ѩ�ҥ������D�جOclass�]������.h*/
/*�D�حn�D:
Given a sparse matrix A, transpose it by the following three methods:
Using traditional 2-dimensional array representation
Using the ��Transpose�� method in the textbook
Using the ��FastTranspose�� method in the textbook*/
#ifndef SPARSEMT_DIM3_FAST_H
#define SPARSEMT_DIM3_FAST_H
#include"SparseMT.h"
#include"SparseMT_DIM2.h"
#include"SparseMT_DIM3.h"
//�T����Fast Transpose
class SparseMT_DIM3_FAST :public SparseMT {//fastTranspose
private:
	SparseMT_term* array;//�H��ꪺ�Φ���ܵ}���x�}�ϥΤT���ժ����X
	int terms;//�D�s��
public:
	SparseMT_DIM3_FAST(int, int, SparseMT_term* a, int);
	void Transpose()override;//�h��
	void printMT()override;//�h��
};
#endif
