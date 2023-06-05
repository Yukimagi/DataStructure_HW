/*題目要求:
Given a sparse matrix A, transpose it by the following three methods:
Using traditional 2-dimensional array representation
Using the “Transpose” method in the textbook
Using the “FastTranspose” method in the textbook*/
#include <algorithm>
#include<iostream>
#include <windows.h>//微秒
#include"SparseMT.h"
using namespace std;
/*在本次作業中，為了達到可以直接使用變數於陣列變數裡，但時常報錯:
* ex:
* int rowSize[col]={0};//常數中不能使用this解法(最後要記得delete<最下面>)
* 要改:int* rowSize = new int[column];
  https://blog.csdn.net/nanke_yh/article/details/128466375?spm=1001.2101.3001.6661.1&utm_medium=distribute.pc_relevant_t0.none-task-blog-2%7Edefault%7ECTRLIST%7ERate-1-128466375-blog-121346269.235%5Ev27%5Epc_relevant_default_base1&depth_1-utm_source=distribute.pc_relevant_t0.none-task-blog-2%7Edefault%7ECTRLIST%7ERate-1-128466375-blog-121346269.235%5Ev27%5Epc_relevant_default_base1&utm_relevant_index=1
*/
SparseMT::SparseMT() {//最基本CLASS(用於多形展現)

};

SparseMT::SparseMT(int r_2, int c_2) :row(r_2), column(c_2) {
    row = r_2;
    column = c_2;
};

SparseMT_term::SparseMT_term() {//term

};
SparseMT_term::SparseMT_term(int r, int c, int tval): row_term(r), col_term(c), val(tval) {
    row_term = r;
    col_term = c;
    val = tval;

};

