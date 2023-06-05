#include<iostream>
#include<iomanip>
#include<fstream>
#include<string>
#include<sstream>
#include<cfloat>
#include<ctime>
#include <windows.h>
#include"DataFrame.h"
#include"HeapSort.h"

using namespace std;
//宣告讀取一行的LINE,以及第1欄到第6欄的變數
string LINE, date, c2, c3, c4, c5, c6;
//arr代表原始資料，unionData代表根據encode不重複的資料，unionData2儲存有關TXO_9900_201705_C的資料。
DataFrame arr[1000000], unionData[1000000], unionData2[1000000];
int arr_size, union_size, union_size2, union_size3;
double price;
int main()
{ //宣告一個檔案輸入流fin。
    ifstream fin;
    fin.open("datasets/problem2/OptionsDaily_2017_05_15.csv");
    //若開檔成功則讀取檔案，先讀取csv檔前兩行並捨棄以確保資料正確讀取。
    if (fin.is_open())
    {
        getline(fin, LINE);
        getline(fin, LINE);
        while (getline(fin, LINE))
        {
            for (auto& i : LINE)i = (i == ',') ? ' ' : i;
            istringstream sin(LINE);
            sin >> date >> c2 >> c3 >> c4 >> c5 >> c6 >> price;
            arr[arr_size].setDate(date);
            arr[arr_size].setencode(c2 + "_" + c3 + "_" + c4 + "_" + c5);
            arr[arr_size].setencode2(date + "_" + c6);
            arr[arr_size].setdeal_price(price);
            arr_size++;
        }
    }
    fin.close();
    fin.clear();
    cout << "load file complete!" << endl;
    ofstream fout;
    fout.open("output.txt");
    if (!fout.is_open()) { cerr << "can't not open the file!" << endl; return -1; }
    HeapSortClass<DataFrame, cmpForencoding>::HeapSort(arr,arr+arr_size);
    cout << "比較尋找TXO_10000_201705_C的效率" << endl;
    cout << "線性搜尋法執行1次的耗時為:";
    DataFrame target;
    target.setencode("TXO_10000_201705_C");
    LARGE_INTEGER START1, END1;//開始與結束時間(設在main是為了達到class專注做transpose即可)
    QueryPerformanceCounter(&START1);
    for (int i = 0; i < 1; i++)
    {
        for (int j = 0; j < arr_size; j++)
        {
            if (arr[i] == target)
                break;
        }
    }
    QueryPerformanceCounter(&END1);
    cout << (double)(END1.QuadPart - START1.QuadPart) << " 微秒\n";
    cout << "Linear Search complete!" << endl;
    cout << "二元搜尋法執行1次的耗時為:";
    int index;
    LARGE_INTEGER START2, END2;//開始與結束時間(設在main是為了達到class專注做transpose即可)
    QueryPerformanceCounter(&START2);
    for (int i = 0; i < 1; i++)
    {
        index = BinarySearch(arr, -1, arr_size, target);
    }
    QueryPerformanceCounter(&END2);
    cout << (double)(END2.QuadPart - START2.QuadPart) << " 微秒\n";
    cout << "Binary Search complete!" << endl;
    fout.close();
    
}