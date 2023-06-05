/*題目要求:
Given a sparse matrix A, transpose it by the following three methods:
Using traditional 2-dimensional array representation
Using the “Transpose” method in the textbook
Using the “FastTranspose” method in the textbook*/
#include<iostream>
#include <windows.h>//微秒
#include"SparseMT.h"
//#include<time.h>//ms
//double START, END;//設開始、結束時間
//START = clock();//設開始時間於目前的編譯時間
//END = clock();
//END-START 
//#include<cstring>//fill的其他方法->memset(MT2D[i], 0, c * sizeof(int));//利用memset(MT2D[i]塞c個0)->初始化


using namespace std;

/*在本次作業中，為了達到可以直接使用變數於陣列變數裡，但時常報錯:
* ex:
* int rowSize[col]={0};//常數中不能使用this解法(最後要記得delete<最下面>)
* 要改:int* rowSize = new int[column];
  https://blog.csdn.net/nanke_yh/article/details/128466375?spm=1001.2101.3001.6661.1&utm_medium=distribute.pc_relevant_t0.none-task-blog-2%7Edefault%7ECTRLIST%7ERate-1-128466375-blog-121346269.235%5Ev27%5Epc_relevant_default_base1&depth_1-utm_source=distribute.pc_relevant_t0.none-task-blog-2%7Edefault%7ECTRLIST%7ERate-1-128466375-blog-121346269.235%5Ev27%5Epc_relevant_default_base1&utm_relevant_index=1
*/
SparseMT::SparseMT() {

};

SparseMT::SparseMT(int r_2, int c_2) :row(r_2), column(c_2) {
    row = r_2;
    column = c_2;

};

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
    //由於本來使用課本的time.h會發現有一些出來的執行時間為0，因此我使用更小單位的測時間方法(微秒)

    LARGE_INTEGER START, END;
    QueryPerformanceCounter(&START);  

    //轉置後的結果
    int** swapMT = new int* [column];//=>int swapMT[column]

    for (int i = 0; i < column; i++)
    {
        swapMT[i] = new int[row];
        fill(swapMT[i], swapMT[i] + row, 0);//初始化
    }

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            if (MT2D[i][j] != 0)//將非0值存入
            {
                swapMT[j][i] = MT2D[i][j];
            }
        }
       
    }

    delete[] MT2D;
    MT2D = swapMT;

    QueryPerformanceCounter(&END);
    cout << (double)(END.QuadPart - START.QuadPart)  <<" 微秒\n"; 
};


SparseMT_tri::SparseMT_tri() {

};
SparseMT_tri::SparseMT_tri(int r, int c, int tval): row_tri(r), col_tri(c), val(tval) {
    row_tri = r;
    col_tri = c;
    val = tval;

};
SparseMT_DIM3::SparseMT_DIM3(int r, int c, SparseMT_tri* a, int s) :SparseMT(r, c), terms(s) {

    array = new SparseMT_tri[terms];//容量為terms

    for (int i = 0; i < terms; i++) {
        array[i] = a[i];
    }

};

void SparseMT_DIM3::Transpose() {   
    //由於本來使用課本的time.h會發現有一些出來的執行時間為0，因此我使用更小單位的測時間方法(微秒)

    LARGE_INTEGER START, END;
    QueryPerformanceCounter(&START);

    SparseMT_tri* swapMT = new SparseMT_tri[terms];//容量為terms(存轉置後的)
    int num = 0;

    for (int i = 0; i < column; i++)
    {
        for (int j = 0; j < terms; j++)
        {
            if (array[j].col_tri == i)
            {
                swapMT[num].col_tri = array[j].row_tri;
                swapMT[num].row_tri = array[j].col_tri;
                swapMT[num].val = array[j].val;
                num++;
            }
        }
    }

    delete[] array;
    array = swapMT;

    QueryPerformanceCounter(&END);
    cout << (double)(END.QuadPart - START.QuadPart) << " 微秒\n";
};
SparseMT_DIM3_FAST::SparseMT_DIM3_FAST(int r, int c, SparseMT_tri* a, int s) :SparseMT(r, c), terms(s) {

    array = new SparseMT_tri[terms];//容量為terms

    for (int i = 0; i < terms; i++) {
        array[i] = a[i];
    }
};

void SparseMT_DIM3_FAST::Transpose() {
    //由於本來使用課本的time.h會發現有一些出來的執行時間為0，因此我使用更小單位的測時間方法(微秒)

    LARGE_INTEGER START, END;
    QueryPerformanceCounter(&START);

    int* rowSize = new int[column];

    int* rowStart = new int[column];
    fill(rowSize, rowSize + column, 0);  // 初始化

    for (int i = 0; i < terms; i++) {
        rowSize[array[i].col_tri]++;
    }

    rowStart[0] = 0;

    for (int i = 1; i < column; i++) {
        rowStart[i] = rowStart[i - 1] + rowSize[i - 1];
    }

    SparseMT_tri* swapMT = new SparseMT_tri[terms];//容量為terms(存轉置後的)

    for (int i = 0; i < terms; i++)
    {
        int index = rowStart[array[i].col_tri];
        swapMT[index].col_tri = array[i].row_tri;
        swapMT[index].row_tri = array[i].col_tri;
        swapMT[index].val = array[i].val;
 
        rowStart[array[i].col_tri]++;
    }

    delete[] array;
    array = swapMT;

    QueryPerformanceCounter(&END);
    cout << (double)(END.QuadPart - START.QuadPart) << " 微秒\n";

    //上面為了不報錯做的空間需要釋放
    delete[] rowSize;
    rowSize = NULL;
    delete[] rowStart;
    rowStart = NULL;
}







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

void SparseMT_DIM3::printMT() {
    cout << "DIM3_Transpose 陣列：" << endl;
    for (int i = 0; i < terms; i++)
    {
        cout << array[i].row_tri << "  " << array[i].col_tri << "  " << array[i].val << endl;
    }
    
}

void SparseMT_DIM3_FAST::printMT() {
    cout << "DIM3_Fast_Transpose 陣列：" << endl;
    for (int i = 0; i < terms; i++)
    {
        cout << array[i].row_tri << "  " << array[i].col_tri << "  " << array[i].val <<endl;
    }
}