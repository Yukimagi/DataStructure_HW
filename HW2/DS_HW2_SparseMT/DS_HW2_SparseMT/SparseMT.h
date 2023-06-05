/*�ѩ�ҥ������D�جOclass�]������.h*/
/*�D�حn�D:
Given a sparse matrix A, transpose it by the following three methods:
Using traditional 2-dimensional array representation
Using the ��Transpose�� method in the textbook
Using the ��FastTranspose�� method in the textbook*/
#ifndef SPARSEMT_H
#define SPARSEMT_H
class SparseMT;			//�̰�CLASS(�Ω�h�ήi�{)
class SparseMT_term;	//term

class SparseMT {//�©w�q�Ϊ��w�qclass  

protected:
	int row;//int rows
	int column;//int cols
public:
	SparseMT();
	SparseMT(int, int);
	virtual void Transpose() = 0;//�h�� �µ�禡
	virtual void printMT() = 0;//�h�� �µ�禡
};

class SparseMT_term {//MatrixTerm
	friend class SparseMT_DIM3;//�ϥ�friend
	friend class SparseMT_DIM3_FAST;
private:
	int row_term;//int row
	int col_term;//int col
	int val;//int value

public:
	SparseMT_term();
	SparseMT_term(int, int, int);
};





#endif
