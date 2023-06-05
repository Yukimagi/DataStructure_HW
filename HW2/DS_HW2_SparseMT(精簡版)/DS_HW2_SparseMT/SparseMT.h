/*�ѩ�ҥ������D�جOclass�]������.h*/
/*�D�حn�D:
Given a sparse matrix A, transpose it by the following three methods:
Using traditional 2-dimensional array representation
Using the ��Transpose�� method in the textbook
Using the ��FastTranspose�� method in the textbook*/
#ifndef SPARSEMT_H
#define SPARSEMT_H
class SparseMT;			//�̰�CLASS(�Ω�h�ήi�{)
class SparseMT_DIM2;	//�ഫ�G��
class SparseMT_tri;		//�T�����Q�~��CLASS
class SparseMT_DIM3;	//�T����Transpose
class SparseMT_DIM3_FAST;//�T����fast Transpose

class SparseMT {
protected:
	int row;
	int column;
public:
	SparseMT();
	SparseMT(int, int);
	virtual void Transpose() = 0;//�h�� �µ�禡
	virtual void printMT() = 0;//�h�� �µ�禡
};

class SparseMT_DIM2 :public SparseMT {
private:
	int** MT2D;	//�ʺA�إߡG�ʺA�إߪ��}�C����O���V���Ъ����СC
public:
	SparseMT_DIM2(int, int, int**);
	void Transpose();
	void printMT();
};

class SparseMT_tri {
	friend class SparseMT_DIM3;//�ϥ�friend
	friend class SparseMT_DIM3_FAST;
private:
	int row_tri;
	int col_tri;
	int val;

public:
	SparseMT_tri();
	SparseMT_tri(int, int, int);
};

class  SparseMT_DIM3 : public SparseMT {//�ѩ�n�h�ΡA�]���N�ҥ�������class�A�I�s�P�W�������禡
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
