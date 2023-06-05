/*題目要求:
Given a sparse matrix A, transpose it by the following three methods:
Using traditional 2-dimensional array representation
Using the “Transpose” method in the textbook
Using the “FastTranspose” method in the textbook*/
#include <algorithm>
#include<iostream>
#include"SparseMT.h"
//#include <windows.h>//微秒
//#include<time.h>//ms
//#include<cstring>//memset
using namespace std;

int main()
{
    int r_2d, c_2d;
    cin >> r_2d >> c_2d;
    int** arrDIM2 = new int* [r_2d];//動態建立
    SparseMT_tri** swapArr = new SparseMT_tri * [r_2d * c_2d];

    int row,col,val;
    int num = 0;

    for (int i = 0; i < r_2d; i++)
    {
        arrDIM2[i] = new int[c_2d];
        fill(arrDIM2[i], arrDIM2[i] + c_2d, 0);//初始化
    }
   
    while (cin >> row >> col >> val)
    {
        arrDIM2[row][col] = val;//以二元陣列方式存入
        swapArr[num] = new SparseMT_tri(row, col, val);//在將值存到class
        num++;

       cout << "(" << row << ", " << col << ", " << val << ")" 
           << " becomes " << "(" << col << ", " << row << ", " 
           << val << ") " << "in the transpose\n";
    }

    SparseMT_tri* arr = new SparseMT_tri[num];

    for (int i = 0; i < num; i++)
    {
        arr[i] = *swapArr[i];
    }
    delete[] swapArr;
    //多形的使用
    SparseMT* Matrix;

    SparseMT_DIM2 X(r_2d, c_2d, arrDIM2);
    Matrix=&X;
    Matrix->Transpose();//進行2維陣列轉置(時間計算)
    //Matrix->printMT();//測試用
    //cout<<endl;

    SparseMT_DIM3 Y(r_2d, c_2d, arr, num);
    Matrix = &Y;
    Matrix->Transpose();//進行3維陣列轉置_transpose(時間計算)
    //Matrix->printMT();//測試用
    //cout<<endl;

    SparseMT_DIM3_FAST Z(r_2d, c_2d, arr, num);
    Matrix = &Z;
    Matrix->Transpose();//進行3維陣列轉置_fast_transpose(時間計算)
    //Matrix->printMT();//測試用
    //cout<<endl;
   
    delete[] arrDIM2;
    delete[] arr;
    
    return 0;
}