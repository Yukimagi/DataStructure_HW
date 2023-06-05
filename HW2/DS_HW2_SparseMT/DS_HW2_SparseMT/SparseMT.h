/*由於課本有給題目是class因此先建.h*/
/*題目要求:
Given a sparse matrix A, transpose it by the following three methods:
Using traditional 2-dimensional array representation
Using the “Transpose” method in the textbook
Using the “FastTranspose” method in the textbook*/
#ifndef SPARSEMT_H
#define SPARSEMT_H
class SparseMT;			//最基本CLASS(用於多形展現)
class SparseMT_term;	//term

class SparseMT {//純定義用的定義class  

protected:
	int row;//int rows
	int column;//int cols
public:
	SparseMT();
	SparseMT(int, int);
	virtual void Transpose() = 0;//多形 純虛函式
	virtual void printMT() = 0;//多形 純虛函式
};

class SparseMT_term {//MatrixTerm
	friend class SparseMT_DIM3;//使用friend
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
