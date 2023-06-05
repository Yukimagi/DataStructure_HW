/*�D�حn�D:
Given a sparse matrix A, transpose it by the following three methods:
Using traditional 2-dimensional array representation
Using the ��Transpose�� method in the textbook
Using the ��FastTranspose�� method in the textbook*/
#include<iostream>
#include"SparseMT.h"
#include"SparseMT_DIM3_FAST.h"
using namespace std;
/*�b�����@�~���A���F�F��i�H�����ϥ��ܼƩ�}�C�ܼƸ̡A���ɱ`����:
* ex:
* int rowSize[col]={0};//�`�Ƥ�����ϥ�this�Ѫk(�̫�n�O�odelete<�̤U��>)
* �n��:int* rowSize = new int[column];
  https://blog.csdn.net/nanke_yh/article/details/128466375?spm=1001.2101.3001.6661.1&utm_medium=distribute.pc_relevant_t0.none-task-blog-2%7Edefault%7ECTRLIST%7ERate-1-128466375-blog-121346269.235%5Ev27%5Epc_relevant_default_base1&depth_1-utm_source=distribute.pc_relevant_t0.none-task-blog-2%7Edefault%7ECTRLIST%7ERate-1-128466375-blog-121346269.235%5Ev27%5Epc_relevant_default_base1&utm_relevant_index=1
*/
//Method of Fast Transpose
SparseMT_DIM3_FAST::SparseMT_DIM3_FAST(int r, int c, SparseMT_term* a, int s) :SparseMT(r, c), terms(s) {

    array = new SparseMT_term[terms];//�e�q��terms

    for (int i = 0; i < terms; i++) {
        array[i] = a[i];
    }
};

void SparseMT_DIM3_FAST::Transpose() {

    int* rowSize = new int[column];//space:column(�Ĥ@��)
    int* rowStart = new int[column];//space:column(�ĤG��)
    fill(rowSize, rowSize + column, 0);  // ��l��

    for (int i = 0; i < terms; i++) {
        //time:terms
        rowSize[array[i].col_term]++;
    }

    rowStart[0] = 0;

    for (int i = 1; i < column; i++) {
        //time:column
        rowStart[i] = rowStart[i - 1] + rowSize[i - 1];
    }

    SparseMT_term* swapMT = new SparseMT_term[terms];//space:�e�q��terms(�s��m�᪺)(�Ĥ@��)

    for (int i = 0; i < terms; i++)
    {
        //time:terms
        int index = rowStart[array[i].col_term];//space:�e�q��terms(i)(�s��m�᪺)(�Ĥ@��)
        swapMT[index].col_term = array[i].row_term;
        swapMT[index].row_term = array[i].col_term;
        swapMT[index].val = array[i].val;

        rowStart[array[i].col_term]++;
    }

    delete[] array;
    array = swapMT;

    //�W�����F�����������Ŷ��ݭn����
    delete[] rowSize;
    rowSize = NULL;
    delete[] rowStart;
    rowStart = NULL;
}

/// <summary>
/// ���ե�
/// </summary>

void SparseMT_DIM3_FAST::printMT() {
    cout << "DIM3_Fast_Transpose �}�C�G" << endl;
    for (int i = 0; i < terms; i++)
    {
        cout << array[i].row_term << "  " << array[i].col_term << "  " << array[i].val << endl;
    }
}