/*由於課本有給題目是class因此先建.h*/
/*題目要求:
Given a sparse matrix A, transpose it by the following three methods:
Using traditional 2-dimensional array representation
Using the “Transpose” method in the textbook
Using the “FastTranspose” method in the textbook*/
#ifndef SPARSEMT_H
#define SPARSEMT_H
class SparseMT;			//最基本CLASS(用於多形展現)
class SparseMT_DIM2;	//轉換二維
class SparseMT_tri;		//三維的被繼承CLASS
class SparseMT_DIM3;	//三維的Transpose
class SparseMT_DIM3_FAST;//三維的fast Transpose

class SparseMT {
protected:
	int row;
	int column;
public:
	SparseMT();
	SparseMT(int, int);
	virtual void Transpose() = 0;//多形 純虛函式
	virtual void printMT() = 0;//多形 純虛函式
};

class SparseMT_DIM2 :public SparseMT {
private:
	int** MT2D;	//動態建立：動態建立的陣列本質是指向指標的指標。
public:
	SparseMT_DIM2(int, int, int**);
	void Transpose();
	void printMT();
};

class SparseMT_tri {
	friend class SparseMT_DIM3;//使用friend
	friend class SparseMT_DIM3_FAST;
private:
	int row_tri;
	int col_tri;
	int val;

public:
	SparseMT_tri();
	SparseMT_tri(int, int, int);
};

class  SparseMT_DIM3 : public SparseMT {//由於要多形，因此將課本的拆成兩個class，呼叫同名異式的函式
private:
	SparseMT_tri* array;	
	int terms;				
public:
	SparseMT_DIM3(int, int, SparseMT_tri *arr, int);
	void Transpose();
	void printMT();

};

class SparseMT_DIM3_FAST :public SparseMT {//fastTranspose
private:
	SparseMT_tri* array;
	int terms;
public:
	SparseMT_DIM3_FAST(int, int, SparseMT_tri* a, int);
	void Transpose();
	void printMT();
};

#endif
