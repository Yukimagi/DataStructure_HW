#ifndef SPARSEMT_H
#define SPARSEMT_H

//�ݭn�@��term�s�D�s�x�}
class SparseMT_term {
	//�|�Mtranspose�Bfast��friend
	friend class SparseMT_DIM3;
	friend class SparseMT_DIM3_FAST;

public:
	//�@�w�n��public
	int row;//int row_term
	int col;//int col_term
	int value;//int val
};

class SparseMT {
protected://�]���|�Q�h�ΩҥH��protected
	int rows;//int row
	int cols;//int column
public:
	virtual void Transpose() = 0;//�h�� �µ�禡
	virtual void printMT() = 0;//�h�� �µ�禡
};
#endif
