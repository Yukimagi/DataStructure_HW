/*題目要求:
Given a sparse matrix A, transpose it by the following three methods:
Using traditional 2-dimensional array representation
Using the “Transpose” method in the textbook
Using the “FastTranspose” method in the textbook*/
#include<iostream>
#include"SparseMT.h"
#include"SparseMT_DIM3_FAST.h"
using namespace std;
/*在本次作業中，為了達到可以直接使用變數於陣列變數裡，但時常報錯:
* ex:
* int rowSize[col]={0};//常數中不能使用this解法(最後要記得delete<最下面>)
* 要改:int* rowSize = new int[column];
  https://blog.csdn.net/nanke_yh/article/details/128466375?spm=1001.2101.3001.6661.1&utm_medium=distribute.pc_relevant_t0.none-task-blog-2%7Edefault%7ECTRLIST%7ERate-1-128466375-blog-121346269.235%5Ev27%5Epc_relevant_default_base1&depth_1-utm_source=distribute.pc_relevant_t0.none-task-blog-2%7Edefault%7ECTRLIST%7ERate-1-128466375-blog-121346269.235%5Ev27%5Epc_relevant_default_base1&utm_relevant_index=1
*/
//Method of Fast Transpose
SparseMT_DIM3_FAST::SparseMT_DIM3_FAST(int r, int c, SparseMT_term* a, int s) :SparseMT(r, c), terms(s) {

    array = new SparseMT_term[terms];//容量為terms

    for (int i = 0; i < terms; i++) {
        array[i] = a[i];
    }
};

void SparseMT_DIM3_FAST::Transpose() {

    int* rowSize = new int[column];//space:column(第一次)
    int* rowStart = new int[column];//space:column(第二次)
    fill(rowSize, rowSize + column, 0);  // 初始化

    for (int i = 0; i < terms; i++) {
        //time:terms
        rowSize[array[i].col_term]++;
    }

    rowStart[0] = 0;

    for (int i = 1; i < column; i++) {
        //time:column
        rowStart[i] = rowStart[i - 1] + rowSize[i - 1];
    }

    SparseMT_term* swapMT = new SparseMT_term[terms];//space:容量為terms(存轉置後的)(第一次)

    for (int i = 0; i < terms; i++)
    {
        //time:terms
        int index = rowStart[array[i].col_term];//space:容量為terms(i)(存轉置後的)(第一次)
        swapMT[index].col_term = array[i].row_term;
        swapMT[index].row_term = array[i].col_term;
        swapMT[index].val = array[i].val;

        rowStart[array[i].col_term]++;
    }

    delete[] array;
    array = swapMT;

    //上面為了不報錯做的空間需要釋放
    delete[] rowSize;
    rowSize = NULL;
    delete[] rowStart;
    rowStart = NULL;
}

/// <summary>
/// 測試用
/// </summary>

void SparseMT_DIM3_FAST::printMT() {
    cout << "DIM3_Fast_Transpose 陣列：" << endl;
    for (int i = 0; i < terms; i++)
    {
        cout << array[i].row_term << "  " << array[i].col_term << "  " << array[i].val << endl;
    }
}