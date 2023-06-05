#include<iostream>
#include<iomanip>
#include<fstream>
#include<string>
#include<sstream>
#include<cfloat>
#include"DataFrame.h"
#include"HeapSort.h"
using namespace std;
//宣告讀取一行的LINE,以及第1欄到第6欄的變數
string LINE, date, c2, c3, c4, c5, c6;
DataFrame arr[1000000], unionData[1000000], unionData2[1000000], unionData3[1000000];
int arr_size, union_size, union_size2, union_size3;
double price;
int main()
{
    ifstream fin;
    fin.open("datasets/problem2/OptionsDaily_2017_05_15.csv");
    if (fin.is_open())
    {
        getline(fin, LINE);
        getline(fin, LINE);
        while (getline(fin, LINE))
        {
            for (auto& i : LINE)
                i = (i == ',') ? ' ' : i;
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
    fin.open("datasets/problem2/OptionsDaily_2017_05_16.csv");
    if (fin.is_open())
    {
        getline(fin, LINE);
        getline(fin, LINE);
        while (getline(fin, LINE))
        {
            for (auto& i : LINE)
                i = (i == ',') ? ' ' : i;
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
    fin.open("datasets/problem2/OptionsDaily_2017_05_17.csv");
    if (fin.is_open())
    {
        getline(fin, LINE);
        getline(fin, LINE);
        while (getline(fin, LINE))
        {
            for (auto& i : LINE)
                i = (i == ',') ? ' ' : i;
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
    fin.open("datasets/problem2/OptionsDaily_2017_05_18.csv");
    if (fin.is_open())
    {
        getline(fin, LINE);
        getline(fin, LINE);
        while (getline(fin, LINE))
        {
            for (auto& i : LINE)
                i = (i == ',') ? ' ' : i;
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
    fin.open("datasets/problem2/OptionsDaily_2017_05_19.csv");
    if (fin.is_open())
    {
        getline(fin, LINE);
        getline(fin, LINE);
        while (getline(fin, LINE))
        {
            for (auto& i : LINE)
                i = (i == ',') ? ' ' : i;
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
    // 第1題，先把資料排序後再把重複的資料刪除(不讀取)
    // HeapSortClass<DataFrame,cmpForencoding>::HeapSort(arr,arr+arr_size);
    ofstream fout;
    fout.open("output.txt", ios_base::out);
    fout << "刪除重複之前的size為" << arr_size << endl;
    Node* root = nullptr;
    DataFrame tmp;
    for (int i = 0; i < arr_size; i++)
    {
        if (insert(root, arr[i].getencode()))
            unionData[union_size++] = arr[i];
    }
    fout << "不重複的資料有 " << union_size << endl;

    HeapSortClass<DataFrame, cmpForencoding>::HeapSort(unionData, unionData + union_size);
    // 第2題，確定商品TXO_1000_201706_P是否存在這個資料集中
    DataFrame target;
    target.setencode("TXO_1000_201706_P");
    int index;
    index = BinarySearch(unionData, -1, union_size, target);
    if (index != union_size && target.getencode() == unionData[index].getencode())
        fout << "存在 就在unionData[" << index << "]" << endl;
    else
        fout << "不存在" << endl;
    // 第3題，確定商品TXO_9500_201706_C是否存在這個資料集中
    target.setencode("TXO_9500_201706_C");
    index = BinarySearch(unionData, -1, union_size, target);
    if (index != union_size && target.getencode() == unionData[index].getencode())
        fout << "存在 就在unionData[" << index << "]" << endl;
    else
        fout << "不存在" << endl;

    // 第4題，確定商品GIO_5500_201706_C是否存在這個資料集中
    target.setencode("GIO_5500_201706_C");
    index = BinarySearch(unionData, -1, union_size, target);
    if (index != union_size && target.getencode() == unionData[index].getencode())
        fout << "存在 就在unionData[" << index << "]" << endl;
    else
        fout << "不存在" << endl;

    // 第5題題組 對於TXO_9900_201705_C
    HeapSortClass<DataFrame, cmpForDate>::HeapSort(arr, arr + arr_size);
    for (int i = 0; i < arr_size; i++)
        if (arr[i].getencode() == "TXO_9900_201705_C")
            unionData2[union_size2++] = arr[i];
    // for (int i = 0; i < union_size2; i++)cout << unionData2[i].getDate() << " " << unionData2[i].getencode() << " " << unionData2[i].getdeal_price() << endl;
    HeapSortClass<DataFrame, cmpForencode2>::HeapSort(unionData2, unionData2 + union_size2);
    // a 找出10个最小的价格，以及这些最小价格出现的时间（由第1列（成交日期）和第6列（成交时间）的唯一组合确定）。(5%)
    HeapSortClass<DataFrame, cmpForlessDeal_price>::HeapSort(unionData2, unionData2 + union_size2);
    fout << "找出10個最小的價格:" << endl;
    for (int i = 0; i < 10; i++)
        fout << unionData2[i].getencode2() << " " << unionData2[i].getdeal_price() << " " << endl;
    // b 找出10个最大的价格，以及这些最大价格出现的时间。(5%)
    fout << "找出10個最大的價格:" << endl;
    HeapSortClass<DataFrame, cmpForgreaterDeal_price>::HeapSort(unionData2, unionData2 + union_size2);
    for (int i = 0; i < 10; i++)
        fout << unionData2[i].getencode2() << " " << unionData2[i].getdeal_price() << endl;
    // c 找出该产品的中位数价格。(5%)
    fout << "找出產品的中位數價格:" << endl;
    HeapSortClass<DataFrame, cmpForlessDeal_price>::HeapSort(unionData2, unionData2 + union_size2);
    fout << unionData2[union_size2 / 2].getencode2() << " " << unionData2[union_size2 / 2].getdeal_price() << endl;
    // d 使用第7列（成交价格）的值计算基于跳动的回报率（除了第一个跳动）。然后确定最大和最小回报率是多少，以及它们发生的时间。(5%)
    fout << "使用成交價格的值計算基於跳動的回報率:" << endl;
    HeapSortClass<DataFrame, cmpForDate>::HeapSort(unionData2, unionData2 + union_size2);
    double MAX = DBL_MIN, MIN = DBL_MAX;
    int MAXINDEX, MININDEX;
    double Pt_check_big = 0;
    double Pt_1_check_big = 0;
    double Pt_check_small = 0;
    double Pt_1_check_small = 0;
    for (int i = 1; i < union_size2; i++)
    {
        double Pt = unionData2[i].getdeal_price(), Pt_1 = unionData2[i - 1].getdeal_price();
        double RETURN = (Pt - Pt_1) / (Pt_1) * 100.0;
        if (RETURN > MAX)
        {
            fout << "now MAXRETURN = " << RETURN << " " << unionData2[i].getencode2();
            MAX = RETURN;
            MAXINDEX = i;
            Pt_check_big = Pt;
            Pt_1_check_big = Pt_1;
        }
        if (RETURN < MIN)
        {
            fout << "now MINRETURN = " << RETURN << " " << unionData2[i].getencode2();
            MIN = RETURN;
            MININDEX = i;
            Pt_check_small = Pt;
            Pt_1_check_small = Pt_1;
        }
        fout << "第" << i + 1 << "天的 tick-based是 " << RETURN << endl;
    }
    fout << "maximum return 為" << MAX << " " <<"Pt date=" << unionData2[MAXINDEX].getencode2()<<" " << "price" << " " << Pt_check_big << " " << "Pt-1 date=" << unionData2[MAXINDEX - 1].getencode2() << "price" << " " << Pt_1_check_big << endl;
    fout << "minimum return 為" << MIN << " " << "Pt date=" << unionData2[MININDEX].getencode2() <<" " << "price" << " " << Pt_check_small << " " << "Pt-1 date=" << unionData2[MININDEX - 1].getencode2() << "price" << " " << Pt_1_check_small << endl;
    fout.close();
}