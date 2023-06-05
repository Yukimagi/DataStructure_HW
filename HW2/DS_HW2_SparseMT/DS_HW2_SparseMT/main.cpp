/*�D�حn�D:
Given a sparse matrix A, transpose it by the following three methods:
Using traditional 2-dimensional array representation
Using the ��Transpose�� method in the textbook
Using the ��FastTranspose�� method in the textbook*/
#include <algorithm>
#include<iostream>
#include"SparseMT.h"
#include"SparseMT_DIM2.h"
#include"SparseMT_DIM3.h"
#include"SparseMT_DIM3_FAST.h"
#include <windows.h>//�L��(�ѩ�ms�|�Ӥj(����0)�]����L��)
//#include<time.h>//ms
//double START, END;//�]�}�l�B�����ɶ�
//START = clock();//�]�}�l�ɶ���ثe���sĶ�ɶ�
//END = clock();
//END-START 
//#include<cstring>//fill����L��k->memset(MT2D[i], 0, c * sizeof(int));//�Q��memset(MT2D[i]��c��0)->��l��

using namespace std;

int main()
{
    int r_2d, c_2d;
    cin >> r_2d >> c_2d;
    int** arrDIM2 = new int* [r_2d];//�ʺA�إ�
    SparseMT_term** swapArr = new SparseMT_term * [r_2d * c_2d];

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
        swapArr[num] = new SparseMT_term(row, col, val);//�b�N�Ȧs��class
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
    //�h�Ϊ��ϥ�
    SparseMT* Matrix;

    SparseMT_DIM2 X(r_2d, c_2d, arrDIM2);
    Matrix=&X;

    //�ѩ󥻨Өϥνҥ���time.h�|�o�{���@�ǥX�Ӫ�����ɶ���0�A�]���ڨϥΧ�p��쪺���ɶ���k(�L��)
    LARGE_INTEGER START1, END1;//�}�l�P�����ɶ�(�]�bmain�O���F�F��class�M�`��transpose�Y�i)
    QueryPerformanceCounter(&START1);

    Matrix->Transpose();//�i��2���x�}��m(�ɶ��p��)

    QueryPerformanceCounter(&END1);
    cout << (double)(END1.QuadPart - START1.QuadPart) << " �L��\n";
    //Matrix->printMT();//���ե�
    //cout<<endl;

    SparseMT_DIM3 Y(r_2d, c_2d, arr, num);
    Matrix = &Y;

    LARGE_INTEGER START2, END2;//�}�l�P�����ɶ�(�]�bmain�O���F�F��class�M�`��transpose�Y�i)
    QueryPerformanceCounter(&START2);

    Matrix->Transpose();//�i��3���x�}��m_transpose(�ɶ��p��)

    QueryPerformanceCounter(&END2);
    cout << (double)(END2.QuadPart - START2.QuadPart) << " �L��\n";
    //Matrix->printMT();//���ե�
    //cout<<endl;

    SparseMT_DIM3_FAST Z(r_2d, c_2d, arr, num);
    Matrix = &Z;

    LARGE_INTEGER START3, END3;//�}�l�P�����ɶ�(�]�bmain�O���F�F��class�M�`��transpose�Y�i)
    QueryPerformanceCounter(&START3);

    Matrix->Transpose();//�i��3���x�}��m_fast_transpose(�ɶ��p��)

    QueryPerformanceCounter(&END3);
    cout << (double)(END3.QuadPart - START3.QuadPart) << " �L��\n";
    //Matrix->printMT();//���ե�
    //cout<<endl;
   
    delete[] arrDIM2;
    delete[] arr;
    
    return 0;
}