#include<iostream>
#include<iomanip>
#include<fstream>
#include<string>
#include<sstream>
#include<cfloat>
#include"DataFrame.h"
#include"HeapSort.h"
using namespace std;
//宣告儲存的結構，陣列大小最大為儲存一百萬個資料。
//arr儲存原始資料,arr2儲存根據日期不重複的資料，tmp3會暫存抽樣(每5筆抽1次)的資料。
//allprice儲存所有價格(開盤價格、當日最高價、當日最低價、收盤價格)及其出現的日期，在第10題會將其從小到大排序。
const int MAXN = 1000000;
DataFrame arr[MAXN], arr2[MAXN], tmp3[MAXN];
DataFrame2 allprice[MAXN];
double arrDayilyreturn[MAXN], arrIntradayreturn[MAXN];
int arr_size, allprice_size, Dayilyreturn_size, Intradayreturn_size;
int arr_size2, arr_size3;
int main()
{ //宣告一個檔案輸入流fin，開啟TWII_withRepeatedData.csv。
    ifstream fin;
    fin.open("datasets/problem1/TWII_withRepeatedData.csv");
    //若開檔失敗(檔案不存在或其他原因)，則不執行程式並在錯誤顯示欄中顯示開啟失敗
    if (!fin.is_open()) { std::cerr << "Error opening file\n"; return -1; }
    //宣告一個檔案輸出流fout，開啟output.txt輸出結果。
    ofstream fout, outfortest;
    fout.open("output.txt");
    //若開檔失敗(檔案不存在或其他原因)，則不執行程式並在錯誤顯示欄中顯示開啟失敗
    if (!fout.is_open()) { cerr << "Error opening file\n"; return -1; }
    //宣告一個std::string，表示輸入csv檔的資料。
    string LINE;
    //一開始先輸入日期、開盤價格、當日最高價、當日最低價、收盤價格，等等欄位並捨棄，使讀取資料能順利處理。
    getline(fin, LINE);
    DataFrame pre;
    //第1題 在去除有重複日期的資料(先讀到的保留)的程式
    while (getline(fin, LINE))
    {
        for (auto& i : LINE)i = (i == ',') ? ' ' : i;
        istringstream sin(LINE);
        DataFrame tmp;
        sin >> tmp.d >> tmp.Open_price >> tmp.High_price >> tmp.Low_price >> tmp.Close_price;
        arr[arr_size] = tmp;
        pre = tmp;
        arr_size++;
    }
    //首先將原始資料根據日期從小到大排序。
    HeapSortClass<DataFrame, compareWithDate>::HeapSort(arr, arr + arr_size);
    Date tt;
    //將排序後的資料只塞第一個發現的日期，後面發現的都不放。
    for (int i = 0; i < arr_size; i++)
    {
        if (tt == arr[i].d)continue;
        arr2[arr_size2++] = arr[i];
        tt = arr[i].d;
    }
    //開始每5筆資料抽1次塞到tmp3當中
    for (int i = 0; i < arr_size2; i += 5)tmp3[arr_size3++] = arr2[i];
    //接著將arr2覆蓋成tmp3。
    arr_size2 = arr_size3;
    for (int i = 0; i < arr_size2; i++)arr2[i] = tmp3[i];
    fout << "刪完每5個選1個的後20筆資料是:" << endl;
    for (int i = arr_size2 - 20; i < arr_size2; i++)fout << arr2[i] << endl;
    fout << "抽樣後沒重複(日期)的資料有 " << arr_size2 << " 筆" << endl;
    HeapSortClass<DataFrame, compareWithclose_price>::HeapSort(arr2, arr2 + arr_size2);
    for (int i = 0; i < arr_size2; i++)fout << arr2[i] << endl;
    //第2題 用Close_price排序出最小的前10筆資料
    fout << fixed << setprecision(5) << "最小(指Close_price)的前十筆資料為:" << endl;
    for (int i = 0; i < 10; i++)fout << arr2[i] << endl;
    //第3題 用Close_price排序出最大的前10筆資料
    fout << fixed << setprecision(5) << "最大(指Close_price)的前十筆資料為:" << endl;
    for (int i = arr_size2 - 10; i < arr_size2; i++)fout << arr2[i] << endl;
    //第4題 用Close_price找出中位數資料
    fout << "中位數(指Close_price)為:" << endl;
    fout << fixed << setprecision(5) << arr2[arr_size2 / 2] << endl;
    fout << fixed << setprecision(5) << arr2[arr_size2 / 2 + 1] << endl;
    //第5題 用Date排序，並計算出每天的daily return
    HeapSortClass<DataFrame, compareWithDate>::HeapSort(arr2, arr2 + arr_size2);
    double MAX, MIN;
    Date MAXDate, MINDate;
    MAX = DBL_MIN;
    MIN = DBL_MAX;
    for (int i = 1; i < arr_size2 - 1; i++)
    {
        double dailyreturn = (arr2[i + 1].Close_price - arr2[i].Close_price) / arr2[i].Close_price * 100.0;
        arrDayilyreturn[Dayilyreturn_size++] = dailyreturn;
        fout << fixed << setprecision(5) << "第" << i + 1 << "天的daily return為:" << dailyreturn << endl;
        if (MAX < dailyreturn) { MAX = dailyreturn; MAXDate = arr2[i].d; }
        if (MIN > dailyreturn) { MIN = dailyreturn; MINDate = arr2[i].d; }
    }
    fout << fixed << setprecision(5) << "daily return的最大值為: " << MAX << " " << MAXDate << endl;
    fout << fixed << setprecision(5) << "daily return的最小值為: " << MIN << " " << MINDate << endl;
    //第6題 用Date排序，並計算出每天的intraday return
    MAXDate = Date();
    MINDate = Date();
    MAX = DBL_MIN;
    MIN = DBL_MAX;
    for (int i = 0; i < arr_size2; i++)
    {
        double intradayreturn = (arr2[i].Close_price - arr2[i].Open_price) / arr2[i].Open_price * 100.0;
        arrIntradayreturn[Intradayreturn_size++] = intradayreturn;
        fout << fixed << setprecision(5) << "第" << i + 1 << "天的intraday return為:" << intradayreturn << endl;
        if (MAX < intradayreturn) { MAX = intradayreturn; MAXDate = arr2[i].d; }
        if (MIN > intradayreturn) { MIN = intradayreturn; MINDate = arr2[i].d; }
    }
    fout << fixed << setprecision(5) << "intraday return的最大值為: " << MAX << " " << MAXDate << endl;
    fout << fixed << setprecision(5) << "intraday return的最小值為: " << MIN << " " << MINDate << endl;
    //第7題 用Date排序，並畫出出每天的close price (使用python的matplotlib)
    stringstream ss;
    outfortest.open("test4.txt", std::ios::out); //若找不到則新增txt檔
    for (int i = 0; i < arr_size2; i++)ss << " " << arr2[i].Close_price;
    outfortest << ss.str().c_str();
    ss.str("");
    outfortest.close(); //關閉test1.txt
    //第8題 畫出出每天的 daily return (使用python的matplotlib)
    outfortest.open("test5.txt", std::ios::out); //若找不到則新增txt檔
    for (int i = 0; i < Dayilyreturn_size; i++)ss << " " << arrDayilyreturn[i];
    outfortest << ss.str().c_str();
    ss.str("");
    outfortest.close(); //關閉test2.txt
    //第9題 畫出出每天的 intraday return (使用python的matplotlib)
    outfortest.open("test6.txt", std::ios::out); //若找不到則新增txt檔
    for (int i = 0; i < Intradayreturn_size; i++)ss << " " << arrIntradayreturn[i];
    outfortest << ss.str().c_str();
    ss.str("");
    outfortest.close(); //關閉test3.txt

    //第10題 根據有數字的四個欄位找出最小數字、最大數字、中位數。
    for (int i = 0; i < arr_size2; i++)
    {
        allprice[allprice_size].price = arr2[i].Open_price;
        allprice[allprice_size].d = arr2[i].d;
        allprice_size++;

        allprice[allprice_size].price = arr2[i].High_price;
        allprice[allprice_size].d = arr2[i].d;
        allprice_size++;

        allprice[allprice_size].price = arr2[i].Low_price;
        allprice[allprice_size].d = arr2[i].d;
        allprice_size++;

        allprice[allprice_size].price = arr2[i].Close_price;
        allprice[allprice_size].d = arr2[i].d;
        allprice_size++;
    }
    HeapSortClass<DataFrame2, cmpforprice>::HeapSort(allprice, allprice + allprice_size);
    fout << "最小的price為:" << allprice[0] << endl;
    fout << "最大的price為:" << allprice[allprice_size - 1] << endl;
    fout << "中位數的price為:" << allprice[allprice_size / 2] << " 和 " << allprice[allprice_size / 2 + 1] << endl;
}