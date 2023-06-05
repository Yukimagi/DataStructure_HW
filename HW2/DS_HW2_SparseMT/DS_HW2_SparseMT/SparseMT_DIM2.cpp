/*題目要求:
Given a sparse matrix A, transpose it by the following three methods:
Using traditional 2-dimensional array representation
Using the “Transpose” method in the textbook
Using the “FastTranspose” method in the textbook*/

#include<iostream>
#include"SparseMT.h"
#include"SparseMT_DIM2.h"
using namespace std;
/*在本次作業中，為了達到可以直接使用變數於陣列變數裡，但時常報錯:
* ex:
* int rowSize[col]={0};//常數中不能使用this解法(最後要記得delete<最下面>)
* 要改:int* rowSize = new int[column];
  https://blog.csdn.net/nanke_yh/article/details/128466375?spm=1001.2101.3001.6661.1&utm_medium=distribute.pc_relevant_t0.none-task-blog-2%7Edefault%7ECTRLIST%7ERate-1-128466375-blog-121346269.235%5Ev27%5Epc_relevant_default_base1&depth_1-utm_source=distribute.pc_relevant_t0.none-task-blog-2%7Edefault%7ECTRLIST%7ERate-1-128466375-blog-121346269.235%5Ev27%5Epc_relevant_default_base1&utm_relevant_index=1
*/
//傳統二維矩陣轉置
SparseMT_DIM2::SparseMT_DIM2(int r, int c, int** a) :SparseMT(r, c), MT2D(a) {

    MT2D = new int* [row];          //=> int MT2D[row];<報錯原因在最上層註解，已修正>

    for (int i = 0; i < row; i++)
    {
        MT2D[i] = new int[c];
        fill(MT2D[i], MT2D[i] + c, 0);//初始化
    }

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++) {
            MT2D[i][j] = a[i][j];
        }
    }
    //尚未釋放空間(後續會)
};

void SparseMT_DIM2::Transpose() {
    //轉置後的結果
    int** swapMT = new int* [column];//=>int swapMT[column]
    //SPACE:上面產生column個swapMT
    for (int i = 0; i < column; i++)
    {
        swapMT[i] = new int[row];//SPACE:這裡又對應column產生row個空間(column*row)
        fill(swapMT[i], swapMT[i] + row, 0);//初始化
    }

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            //TIME:row*column
            if (MT2D[i][j] != 0)//將非0值存入
            {
                swapMT[j][i] = MT2D[i][j];
            }
        }

    }

    delete[] MT2D;
    MT2D = swapMT;
};



/// <summary>
/// 測試用
/// </summary>
void SparseMT_DIM2::printMT() {
    cout << "DIM2_Transpose 陣列：" << endl;
    for (int i = 0; i < column; i++) {
        for (int j = 0; j < row; j++) {
            cout << *(*(MT2D + i) + j) << "\t";
        }
        cout << endl;
    }

}