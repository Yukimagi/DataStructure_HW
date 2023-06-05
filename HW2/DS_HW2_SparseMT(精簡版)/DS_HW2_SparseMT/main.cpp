/*�D�حn�D:
Given a sparse matrix A, transpose it by the following three methods:
Using traditional 2-dimensional array representation
Using the ��Transpose�� method in the textbook
Using the ��FastTranspose�� method in the textbook*/
#include <algorithm>
#include<iostream>
#include"SparseMT.h"
//#include <windows.h>//�L��
//#include<time.h>//ms
//#include<cstring>//memset
using namespace std;

int main()
{
    int r_2d, c_2d;
    cin >> r_2d >> c_2d;
    int** arrDIM2 = new int* [r_2d];//�ʺA�إ�
    SparseMT_tri** swapArr = new SparseMT_tri * [r_2d * c_2d];

    int row,col,val;
    int num = 0;

    for (int i = 0; i < r_2d; i++)
    {
        arrDIM2[i] = new int[c_2d];
        fill(arrDIM2[i], arrDIM2[i] + c_2d, 0);//��l��
    }
   
    while (cin >> row >> col >> val)
    {
        arrDIM2[row][col] = val;//�H�G���}�C�覡�s�J
        swapArr[num] = new SparseMT_tri(row, col, val);//�b�N�Ȧs��class
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
    //�h�Ϊ��ϥ�
    SparseMT* Matrix;

    SparseMT_DIM2 X(r_2d, c_2d, arrDIM2);
    Matrix=&X;
    Matrix->Transpose();//�i��2���}�C��m(�ɶ��p��)
    //Matrix->printMT();//���ե�
    //cout<<endl;

    SparseMT_DIM3 Y(r_2d, c_2d, arr, num);
    Matrix = &Y;
    Matrix->Transpose();//�i��3���}�C��m_transpose(�ɶ��p��)
    //Matrix->printMT();//���ե�
    //cout<<endl;

    SparseMT_DIM3_FAST Z(r_2d, c_2d, arr, num);
    Matrix = &Z;
    Matrix->Transpose();//�i��3���}�C��m_fast_transpose(�ɶ��p��)
    //Matrix->printMT();//���ե�
    //cout<<endl;
   
    delete[] arrDIM2;
    delete[] arr;
    
    return 0;
}