#include <iostream>
#include <ctime>
#include <cstdlib>
#include <stdio.h>
#include<time.h>

using namespace std;

class term {
	friend class SparseMatrix;
private:
	int row, col, value;
};

class SparseMatrix
{// 三元組，<列，行，值>，的集合，其中列與行為非負整數，
	// 並且它的組合是唯一的；值也是個整數。
	int cols, terms, rows, capacity;  // 最大容量
	term* smArray;
public:

	SparseMatrix(int r, int c, int t);
	// 建構子函式，建立一個有r列c行並且具有放t個非零項的容量

	SparseMatrix Transpose();
	//回傳將 *this中每個三元組的行與列交換後的SparseMatrix
	SparseMatrix FastTranspose();

	SparseMatrix Add(SparseMatrix b);
	// 如果 *this和b的維度一樣，那麼就把相對應的項給相加，
	// 亦即，具有相同列和行的值會被回傳；否則的話丟出例外。

	//SparseMatrix Multiply(SparseMatrix b);
	// 如果*this中的行數和b中的列數一樣多的話，那麼回傳的矩陣d就是 *this和b
	//（依據d[i][j]=Σ(a[i][k]．b[k][j]，其中d[i][j]是第 (i, j) 個元素）相乘的結果。k的範圍
	// 從0到*this的行數減1；如果不一樣多的話，那麼就丟出例外。
	void StoreSum(const int sum, const int r, const int c);
	void print();
};



SparseMatrix SparseMatrix::Transpose()
{// 回傳*this的轉置矩陣
	double START, END;
	START = clock();
	SparseMatrix b(cols, rows, terms); // b.smArray的容量為terms
	if (terms > 0)
	{// 非零的矩陣
		int currentB = 0;
		for (int c = 0; c < cols; c++)  // 根據行來轉置
			for (int i = 0; i < terms; i++)
				// 尋找並移動在第c行的項
				if (smArray[i].col == c)
				{
					b.smArray[currentB].row = c;
					b.smArray[currentB].col = smArray[i].row;
					b.smArray[currentB++].value = smArray[i].value;
				}
	} // if (terms > 0) 結束
	END = clock();
	
	cout << endl << "進行運算所花費的時間：" << (double)(END - START)  << " ms" << endl;
	return b;
}
SparseMatrix SparseMatrix::Add(SparseMatrix b)
{
	SparseMatrix c(rows, cols, cols * rows);

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			int sum = 0;

			for (int t = 0; t < capacity; t++)
			{
				if (smArray[t].row == i && smArray[t].col == j)
					sum += smArray[t].value;
			}
			for (int t = 0; t < b.capacity; t++) {
				if (b.smArray[t].row == i && b.smArray[t].col == j)
					sum += b.smArray[t].value;
			}
			c.StoreSum(sum, i, j);

		}
	}
	return c;
}

void  SparseMatrix::print()
{


	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			int sum = 0;
			for (int t = 0; t < capacity; t++)
			{
				if (smArray[t].row == i && smArray[t].col == j)
				{
					sum += smArray[t].value;
				}
			}
			cout << sum << "\t";
		}
		cout << '\n';
	}

}

SparseMatrix SparseMatrix::FastTranspose()
{// 在O(terms + cols)的時間內回傳 *this的轉置矩陣
	double START, END;
	START = clock();
	SparseMatrix b(cols, rows, terms);
	if (terms > 0)
	{// 非零的矩陣
		int* rowSize = new int[cols];
		int* rowStart = new int[cols];
		// 計算rowSize[i] = b的第i列之項數
		fill(rowSize, rowSize + cols, 0);  // 初始化
		for (int i = 0; i < terms; i++) rowSize[smArray[i].col]++;

		// rowStart[i] = b的第i列之起始位置
		rowStart[0] = 0;
		for (int i = 1; i < cols; i++) rowStart[i] = rowStart[i - 1] + rowSize[i - 1];

		for (int i = 0; i < terms; i++)
		{// 從 *this複製到b
			int j = rowStart[smArray[i].col];
			b.smArray[j].row = smArray[i].col;
			b.smArray[j].col = smArray[i].row;
			b.smArray[j].value = smArray[i].value;
			rowStart[smArray[i].col]++;
		} // for結束
		delete[] rowSize;
		delete[] rowStart;
	} // if結束
	END = clock();
	cout << START << endl;
	cout << END<<endl;
	cout << endl << "程式執行所花費：" << (double)clock() / CLOCKS_PER_SEC << " S";
	cout << endl << "進行運算所花費的時間：" << (double)(END - START) << "ms" << endl;
	return b;
}

void SparseMatrix::StoreSum(const int sum, const int r, const int c)
{// 如果sum != 0，那麼它以及和它一起傳進來的列r、行c的位置就存成 *this的
	// 最後一個項
	if (sum != 0) {
		//if (terms == capacity)
		//    ChangeSize1D(2*capacity); // 加倍容量
		smArray[terms].row = r;
		smArray[terms].col = c;
		smArray[terms++].value = sum;
	}
}

SparseMatrix::SparseMatrix(int r, int c, int t) {
	rows = r;
	cols = c;
	capacity = t;
	smArray = new term[t];
}

int main() {
	SparseMatrix A(3, 3, 9), B(3, 3, 9), C(3, 3, 9);
	A.StoreSum(2, 0, 0);
	A.StoreSum(4, 1, 1);
	A.StoreSum(5, 2, 0);
	A.StoreSum(4, 2, 2);
	cout << "A\n";
	A.print();
	B = A.Transpose();
	cout << "B\n";
	B.print();
	C = A.FastTranspose();
	cout << "C\n";
	C.print();
	system("pause");
}