#ifndef SPARSEMT_H
#define SPARSEMT_H

//需要一個term存非零矩陣
class SparseMT_term {
	//會和transpose、fast為friend
	friend class SparseMT_DIM3;
	friend class SparseMT_DIM3_FAST;

public:
	//一定要放public
	int row;//int row_term
	int col;//int col_term
	int value;//int val
};

class SparseMT {
protected://因為會被多形所以用protected
	int rows;//int row
	int cols;//int column
public:
	virtual void Transpose() = 0;//多形 純虛函式
	virtual void printMT() = 0;//多形 純虛函式
};
#endif
