/*�D�حn�D:
Given a sparse matrix A, transpose it by the following three methods:
Using traditional 2-dimensional array representation
Using the ��Transpose�� method in the textbook
Using the ��FastTranspose�� method in the textbook*/
#include<iostream>
#include"SparseMT.h"
#include"SparseMT_DIM3.h"
using namespace std;
/*�b�����@�~���A���F�F��i�H�����ϥ��ܼƩ�}�C�ܼƸ̡A���ɱ`����:
* ex:
* int rowSize[col]={0};//�`�Ƥ�����ϥ�this�Ѫk(�̫�n�O�odelete<�̤U��>)
* �n��:int* rowSize = new int[column];
  https://blog.csdn.net/nanke_yh/article/details/128466375?spm=1001.2101.3001.6661.1&utm_medium=distribute.pc_relevant_t0.none-task-blog-2%7Edefault%7ECTRLIST%7ERate-1-128466375-blog-121346269.235%5Ev27%5Epc_relevant_default_base1&depth_1-utm_source=distribute.pc_relevant_t0.none-task-blog-2%7Edefault%7ECTRLIST%7ERate-1-128466375-blog-121346269.235%5Ev27%5Epc_relevant_default_base1&utm_relevant_index=1
*/
//Method of Transpose
SparseMT_DIM3::SparseMT_DIM3(int r, int c, SparseMT_term* a, int s) :SparseMT(r, c), terms(s) {

    array = new SparseMT_term[terms];//�e�q��terms

    for (int i = 0; i < terms; i++) {
        array[i] = a[i];
    }

};

void SparseMT_DIM3::Transpose() {

    SparseMT_term* swapMT = new SparseMT_term[terms];//space:O(terms)�e�q��terms(�s��m�᪺)
    int num = 0;

    for (int i = 0; i < column; i++)
    {
        for (int j = 0; j < terms; j++)
        {
            //time:O(column*term)
            if (array[j].col_term == i)
            {
                swapMT[num].col_term = array[j].row_term;
                swapMT[num].row_term = array[j].col_term;
                swapMT[num].val = array[j].val;
                num++;
            }
        }
    }

    delete[] array;
    array = swapMT;
};



/// <summary>
/// ���ե�
/// </summary>

void SparseMT_DIM3::printMT() {
    cout << "DIM3_Transpose �}�C�G" << endl;
    for (int i = 0; i < terms; i++)
    {
        cout << array[i].row_term << "  " << array[i].col_term << "  " << array[i].val << endl;
    }

}