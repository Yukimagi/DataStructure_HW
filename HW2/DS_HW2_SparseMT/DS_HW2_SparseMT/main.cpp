/*題目要求:
Given a sparse matrix A, transpose it by the following three methods:
Using traditional 2-dimensional array representation
Using the “Transpose” method in the textbook
Using the “FastTranspose” method in the textbook*/
#include <algorithm>
#include<iostream>
#include"SparseMT.h"
#include"SparseMT_DIM2.h"
#include"SparseMT_DIM3.h"
#include"SparseMT_DIM3_FAST.h"
#include <windows.h>//微秒(由於ms會太大(產生0)因此改微渺)
//#include<time.h>//ms
//double START, END;//設開始、結束時間
//START = clock();//設開始時間於目前的編譯時間
//END = clock();
//END-START 
//#include<cstring>//fill的其他方法->memset(MT2D[i], 0, c * sizeof(int));//利用memset(MT2D[i]塞c個0)->初始化

using namespace std;

int main()
{
    int r_2d, c_2d;
    cin >> r_2d >> c_2d;
    int** arrDIM2 = new int* [r_2d];//動態建立
    SparseMT_term** swapArr = new SparseMT_term * [r_2d * c_2d];

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
        swapArr[num] = new SparseMT_term(row, col, val);//在將值存到class
        num++;

       cout << "(" << row << ", " << col << ", " << val << ")" 
           << " becomes " << "(" << col << ", " << row << ", " 
           << val << ") " << "in the transpose\n";
    }

    SparseMT_term* arr = new SparseMT_term[num];

    for (int i = 0; i < num; i++)
    {
        arr[i] = *swapArr[i];
    }
    delete[] swapArr;
    //多形的使用
    SparseMT* Matrix;

    SparseMT_DIM2 X(r_2d, c_2d, arrDIM2);
    Matrix=&X;

    //由於本來使用課本的time.h會發現有一些出來的執行時間為0，因此我使用更小單位的測時間方法(微秒)
    LARGE_INTEGER START1, END1;//開始與結束時間(設在main是為了達到class專注做transpose即可)
    QueryPerformanceCounter(&START1);

    Matrix->Transpose();//進行2維矩陣轉置(時間計算)

    QueryPerformanceCounter(&END1);
    cout << (double)(END1.QuadPart - START1.QuadPart) << " 微秒\n";
    //Matrix->printMT();//測試用
    //cout<<endl;

    SparseMT_DIM3 Y(r_2d, c_2d, arr, num);
    Matrix = &Y;

    LARGE_INTEGER START2, END2;//開始與結束時間(設在main是為了達到class專注做transpose即可)
    QueryPerformanceCounter(&START2);

    Matrix->Transpose();//進行3維矩陣轉置_transpose(時間計算)

    QueryPerformanceCounter(&END2);
    cout << (double)(END2.QuadPart - START2.QuadPart) << " 微秒\n";
    //Matrix->printMT();//測試用
    //cout<<endl;

    SparseMT_DIM3_FAST Z(r_2d, c_2d, arr, num);
    Matrix = &Z;

    LARGE_INTEGER START3, END3;//開始與結束時間(設在main是為了達到class專注做transpose即可)
    QueryPerformanceCounter(&START3);

    Matrix->Transpose();//進行3維矩陣轉置_fast_transpose(時間計算)

    QueryPerformanceCounter(&END3);
    cout << (double)(END3.QuadPart - START3.QuadPart) << " 微秒\n";
    //Matrix->printMT();//測試用
    //cout<<endl;
   
    delete[] arrDIM2;
    delete[] arr;
    
    return 0;
}