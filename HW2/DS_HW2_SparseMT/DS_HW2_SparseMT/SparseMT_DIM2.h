#ifndef SPARSEMT_DIM2_H
#define SPARSEMT_DIM2_H
#include"SparseMT.h"
//�ǲ���m�G���x�}
class SparseMT_DIM2 :public SparseMT {//�~��SparseMT(�îi�{�h��)
private:
	int** MT2D;	//�ʺA�إߡG�ʺA�إߪ��}�C����O���V���Ъ����СC
public:
	SparseMT_DIM2(int, int, int**);
	void Transpose()override;//�h��
	void printMT()override;//�h��
};
#endif 

