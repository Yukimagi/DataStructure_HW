/*�D�حn�D:
Given a sparse matrix A, transpose it by the following three methods:
Using traditional 2-dimensional array representation
Using the ��Transpose�� method in the textbook
Using the ��FastTranspose�� method in the textbook*/

#include<iostream>
#include"SparseMT.h"
#include"SparseMT_DIM2.h"
using namespace std;
/*�b�����@�~���A���F�F��i�H�����ϥ��ܼƩ�}�C�ܼƸ̡A���ɱ`����:
* ex:
* int rowSize[col]={0};//�`�Ƥ�����ϥ�this�Ѫk(�̫�n�O�odelete<�̤U��>)
* �n��:int* rowSize = new int[column];
  https://blog.csdn.net/nanke_yh/article/details/128466375?spm=1001.2101.3001.6661.1&utm_medium=distribute.pc_relevant_t0.none-task-blog-2%7Edefault%7ECTRLIST%7ERate-1-128466375-blog-121346269.235%5Ev27%5Epc_relevant_default_base1&depth_1-utm_source=distribute.pc_relevant_t0.none-task-blog-2%7Edefault%7ECTRLIST%7ERate-1-128466375-blog-121346269.235%5Ev27%5Epc_relevant_default_base1&utm_relevant_index=1
*/
//�ǲΤG���x�}��m
SparseMT_DIM2::SparseMT_DIM2(int r, int c, int** a) :SparseMT(r, c), MT2D(a) {

    MT2D = new int* [row];          //=> int MT2D[row];<������]�b�̤W�h���ѡA�w�ץ�>

    for (int i = 0; i < row; i++)
    {
        MT2D[i] = new int[c];
        fill(MT2D[i], MT2D[i] + c, 0);//��l��
    }

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++) {
            MT2D[i][j] = a[i][j];
        }
    }
    //�|������Ŷ�(����|)
};

void SparseMT_DIM2::Transpose() {
    //��m�᪺���G
    int** swapMT = new int* [column];//=>int swapMT[column]
    //SPACE:�W������column��swapMT
    for (int i = 0; i < column; i++)
    {
        swapMT[i] = new int[row];//SPACE:�o�̤S����column����row�ӪŶ�(column*row)
        fill(swapMT[i], swapMT[i] + row, 0);//��l��
    }

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            //TIME:row*column
            if (MT2D[i][j] != 0)//�N�D0�Ȧs�J
            {
                swapMT[j][i] = MT2D[i][j];
            }
        }

    }

    delete[] MT2D;
    MT2D = swapMT;
};



/// <summary>
/// ���ե�
/// </summary>
void SparseMT_DIM2::printMT() {
    cout << "DIM2_Transpose �}�C�G" << endl;
    for (int i = 0; i < column; i++) {
        for (int j = 0; j < row; j++) {
            cout << *(*(MT2D + i) + j) << "\t";
        }
        cout << endl;
    }

}