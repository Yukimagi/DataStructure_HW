#ifndef SPARSEMT_DIM3_H
#define SPARSEMT_DIM3_H
#include"SparseMT.h"
#include"SparseMT_DIM2.h"
#include"SparseMT_DIM3_FAST.h"
//�T����Transpose
class  SparseMT_DIM3 : public SparseMT {//�ѩ�n�h�ΡA�]���N�ҥ�������class�A�I�s�P�W�������禡
private:
	SparseMT_term* array;//�H��ꪺ�Φ���ܵ}���x�}�ϥΤT���ժ����X
	int terms;//�D�s��
public:
	SparseMT_DIM3(int, int, SparseMT_term* arr, int);
	void Transpose()override;//�h��
	void printMT()override;//�h��

};
#endif
