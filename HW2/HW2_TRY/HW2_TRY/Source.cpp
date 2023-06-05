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
{// �T���աA<�C�A��A��>�A�����X�A�䤤�C�P�欰�D�t��ơA
	// �åB�����զX�O�ߤ@���F�Ȥ]�O�Ӿ�ơC
	int cols, terms, rows, capacity;  // �̤j�e�q
	term* smArray;
public:

	SparseMatrix(int r, int c, int t);
	// �غc�l�禡�A�إߤ@�Ӧ�r�Cc��åB�㦳��t�ӫD�s�����e�q

	SparseMatrix Transpose();
	//�^�ǱN *this���C�ӤT���ժ���P�C�洫�᪺SparseMatrix
	SparseMatrix FastTranspose();

	SparseMatrix Add(SparseMatrix b);
	// �p�G *this�Mb�����פ@�ˡA����N��۹����������ۥ[�A
	// ��Y�A�㦳�ۦP�C�M�檺�ȷ|�Q�^�ǡF�_�h���ܥ�X�ҥ~�C

	//SparseMatrix Multiply(SparseMatrix b);
	// �p�G*this������ƩMb�����C�Ƥ@�˦h���ܡA����^�Ǫ��x�}d�N�O *this�Mb
	//�]�̾�d[i][j]=�U(a[i][k]�Db[k][j]�A�䤤d[i][j]�O�� (i, j) �Ӥ����^�ۭ������G�Ck���d��
	// �q0��*this����ƴ�1�F�p�G���@�˦h���ܡA����N��X�ҥ~�C
	void StoreSum(const int sum, const int r, const int c);
	void print();
};



SparseMatrix SparseMatrix::Transpose()
{// �^��*this����m�x�}
	double START, END;
	START = clock();
	SparseMatrix b(cols, rows, terms); // b.smArray���e�q��terms
	if (terms > 0)
	{// �D�s���x�}
		int currentB = 0;
		for (int c = 0; c < cols; c++)  // �ھڦ����m
			for (int i = 0; i < terms; i++)
				// �M��ò��ʦb��c�檺��
				if (smArray[i].col == c)
				{
					b.smArray[currentB].row = c;
					b.smArray[currentB].col = smArray[i].row;
					b.smArray[currentB++].value = smArray[i].value;
				}
	} // if (terms > 0) ����
	END = clock();
	
	cout << endl << "�i��B��Ҫ�O���ɶ��G" << (double)(END - START)  << " ms" << endl;
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
{// �bO(terms + cols)���ɶ����^�� *this����m�x�}
	double START, END;
	START = clock();
	SparseMatrix b(cols, rows, terms);
	if (terms > 0)
	{// �D�s���x�}
		int* rowSize = new int[cols];
		int* rowStart = new int[cols];
		// �p��rowSize[i] = b����i�C������
		fill(rowSize, rowSize + cols, 0);  // ��l��
		for (int i = 0; i < terms; i++) rowSize[smArray[i].col]++;

		// rowStart[i] = b����i�C���_�l��m
		rowStart[0] = 0;
		for (int i = 1; i < cols; i++) rowStart[i] = rowStart[i - 1] + rowSize[i - 1];

		for (int i = 0; i < terms; i++)
		{// �q *this�ƻs��b
			int j = rowStart[smArray[i].col];
			b.smArray[j].row = smArray[i].col;
			b.smArray[j].col = smArray[i].row;
			b.smArray[j].value = smArray[i].value;
			rowStart[smArray[i].col]++;
		} // for����
		delete[] rowSize;
		delete[] rowStart;
	} // if����
	END = clock();
	cout << START << endl;
	cout << END<<endl;
	cout << endl << "�{������Ҫ�O�G" << (double)clock() / CLOCKS_PER_SEC << " S";
	cout << endl << "�i��B��Ҫ�O���ɶ��G" << (double)(END - START) << "ms" << endl;
	return b;
}

void SparseMatrix::StoreSum(const int sum, const int r, const int c)
{// �p�Gsum != 0�A���򥦥H�ΩM���@�_�Ƕi�Ӫ��Cr�B��c����m�N�s�� *this��
	// �̫�@�Ӷ�
	if (sum != 0) {
		//if (terms == capacity)
		//    ChangeSize1D(2*capacity); // �[���e�q
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