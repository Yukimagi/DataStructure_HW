#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <cfloat>
#include <algorithm>
using namespace std;
struct Date
{
  string OriginalDate;
  int Year, month, day;
  Date();
};
Date::Date()
{
  OriginalDate = "empty date";
  Year = 0;
  month = 0;
  day = 0;
}
bool operator==(const Date &a, const Date &b)
{
  return (a.Year == b.Year && a.month == b.month && a.day == b.day);
}
bool operator!=(const Date &a, const Date &b)
{
  if (a.Year != b.Year)
    return true;
  if (a.month != b.month)
    return true;
  return a.day != b.day;
}
bool operator<(const Date &a, const Date &b)
{
  if (a.Year != b.Year)
    return a.Year < b.Year;
  if (a.month != b.month)
    return a.month < b.month;
  return a.day < b.day;
}
bool operator>(const Date &a, const Date &b)
{
  if (a.Year != b.Year)
    return a.Year > b.Year;
  if (a.month != b.month)
    return a.month > b.month;
  return a.day > b.day;
}
istream &operator>>(istream &xin, Date &a)
{
  xin >> a.OriginalDate;
  // fout << "Year = "  << a.OriginalDate.substr(0,4) << endl;
  // fout << "Month = " << a.OriginalDate.substr(4,2) << endl;
  // fout << "dat = "   << a.OriginalDate.substr(6,2) << endl;

  a.Year = stoi(a.OriginalDate.substr(0, 4));
  a.month = stoi(a.OriginalDate.substr(4, 2));
  a.day = stoi(a.OriginalDate.substr(6, 2));
  return xin;
}
ostream &operator<<(ostream &xout, const Date &a)
{
  xout << a.OriginalDate;
}
struct DataFrame
{
  Date d;
  double Open_price, High_price, Low_price, Close_price;
  DataFrame();
};
DataFrame::DataFrame()
{
  Open_price = -1;
  High_price = -1;
  Low_price = -1;
  Close_price = -1;
}
ostream &operator<<(ostream &xout, const DataFrame &a)
{
  xout << a.d << " " << a.Open_price << " " << a.High_price << " " << a.Low_price << " " << a.Close_price;
}
bool operator!=(const DataFrame &a, const DataFrame &b)
{
  return (a.d != b.d) || (a.Close_price != b.Close_price) || (a.High_price != b.High_price) || (a.Low_price != b.Low_price) || (a.Open_price != b.Open_price);
}
struct DataFrame2
{
  Date d;
  double price;
  DataFrame2();
};
DataFrame2::DataFrame2()
{
  price = -1;
}
ostream &operator<<(ostream &xout, const DataFrame2 &a)
{
  xout << a.d << " " << a.price;
}

struct compareWithclose_price
{
  bool operator()(const DataFrame &a, const DataFrame &b)
  {
    return a.Close_price < b.Close_price;
  }
};

struct compareWithDate
{
  bool operator()(const DataFrame &a, const DataFrame &b)
  {
    return a.d < b.d;
  }
};
struct cmpforprice
{
  bool operator()(const DataFrame2 &a, const DataFrame2 &b)
  {
    if (a.price != b.price)
      return a.price < b.price;
    return a.d < b.d;
  }
};

template <class IT, class function = greater<IT>>
class HeapSortClass
{
private:
  static function cmp;

public:
  static void restore(IT Heap[], int s, int t);
  static void HeapSort(IT *b, IT *e);
};

template <typename IT, typename function>
function HeapSortClass<IT, function>::cmp = function();
template <class IT, class function>
void HeapSortClass<IT, function>::restore(IT Heap[], int s, int t)
{
  IT val = Heap[s];
  int child = 2 * s + 1;
  while (child <= t)
  {
    if (child < t && cmp(Heap[child], Heap[child + 1]))
      child++;
    if (cmp(val, Heap[child]))
    {
      Heap[s] = Heap[child];
      s = child;
      child = 2 * s + 1;
    }
    else
      break;
  }
  Heap[s] = val;
}
template <class IT, class function>
void HeapSortClass<IT, function>::HeapSort(IT *b, IT *e)
{
  int n = e - b;
  for (int i = n / 2 - 1; i >= 0; i--)
  {
    restore(b, i, n - 1);
  }
  for (int i = n - 1; i >= 1; i--)
  {
    swap(b[0], b[i]);
    restore(b, 0, i - 1);
  }
}
const int MAXN = 1000000;
DataFrame arr[MAXN], arr2[MAXN], tmp3[MAXN], tmp4[MAXN];
DataFrame2 allprice[MAXN];
double arrDayilyreturn[MAXN], arrIntradayreturn[MAXN];
int arr_size, allprice_size, Dayilyreturn_size, Intradayreturn_size;
int arr_size2;
int main()
{
  ifstream fin;
  fin.open("datasets/problem1/TWII_withRepeatedData.csv");
  if (!fin.is_open())
  {
    std::cerr << "Error opening file\n";
    return -1;
  }
  ofstream fout, outfortest;
  fout.open("output.txt");
  if (!fout.is_open())
  {
    cerr << "Error opening file\n";
    return -1;
  }
  string LINE;
  getline(fin, LINE);
  DataFrame pre;
  // 第1題 在去除有重複日期的資料(先讀到的保留)的程式
  while (getline(fin, LINE))
  {
    for (auto &i : LINE)
      i = (i == ',') ? ' ' : i;
    istringstream sin(LINE);
    DataFrame tmp;
    sin >> tmp.d >> tmp.Open_price >> tmp.High_price >> tmp.Low_price >> tmp.Close_price;
    // if (pre.d==tmp.d)continue;
    arr[arr_size] = tmp;
    pre = tmp;
    arr_size++;
  }
  HeapSortClass<DataFrame, compareWithDate>::HeapSort(arr, arr + arr_size);
  Date tt;
  for (int i = 0; i < arr_size; i++)
  {
    if (tt == arr[i].d)
      continue;
    arr2[arr_size2++] = arr[i];
    tt = arr[i].d;
  }
  fout << "沒重複(日期)的資料有 " << arr_size2 << " 筆" << endl;
  HeapSortClass<DataFrame, compareWithclose_price>::HeapSort(arr2, arr2 + arr_size2);
  // 第2題 用Close_price排序出最小的前10筆資料
  fout << fixed << setprecision(5) << "最小(指Close_price)的前十筆資料為:" << endl;
  for (int i = 0; i < 10; i++)
    fout << arr2[i] << endl;
  // 第3題 用Close_price排序出最大的前10筆資料
  fout << fixed << setprecision(5) << "最大(指Close_price)的前十筆資料為:" << endl;
  for (int i = arr_size2 - 10; i < arr_size2; i++)
    fout << arr2[i] << endl;
  // 第4題 用Close_price找出中位數資料
  fout << "中位數(指Close_price)為:" << endl;
  fout << fixed << setprecision(5) << arr2[arr_size2 / 2] << endl;
  fout << fixed << setprecision(5) << arr2[arr_size2 / 2 + 1] << endl;
  // 第5題 用Date排序，並計算出每天的daily return
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
    if (MAX < dailyreturn)
    {
      MAX = dailyreturn;
      MAXDate = arr2[i].d;
    }
    if (MIN > dailyreturn)
    {
      MIN = dailyreturn;
      MINDate = arr2[i].d;
    }
  }
  fout << fixed << setprecision(5) << "daily return的最大值為: " << MAX << " " << MAXDate << endl;
  fout << fixed << setprecision(5) << "daily return的最小值為: " << MIN << " " << MINDate << endl;
  // 第6題 用Date排序，並計算出每天的intraday return
  MAXDate = Date();
  MINDate = Date();
  MAX = DBL_MIN;
  MIN = DBL_MAX;
  for (int i = 0; i < arr_size2; i++)
  {
    double intradayreturn = (arr2[i].Close_price - arr2[i].Open_price) / arr2[i].Open_price * 100.0;
    arrIntradayreturn[Intradayreturn_size++] = intradayreturn;
    fout << fixed << setprecision(5) << "第" << i + 1 << "天的intraday return為:" << intradayreturn << endl;
    if (MAX < intradayreturn)
    {
      MAX = intradayreturn;
      MAXDate = arr2[i].d;
    }
    if (MIN > intradayreturn)
    {
      MIN = intradayreturn;
      MINDate = arr2[i].d;
    }
  }
  fout << fixed << setprecision(5) << "intraday return的最大值為: " << MAX << " " << MAXDate << endl;
  fout << fixed << setprecision(5) << "intraday return的最小值為: " << MIN << " " << MINDate << endl;
  // 第7題 用Date排序，並畫出出每天的close price (使用python的matplotlib)
  stringstream ss;
  outfortest.open("test1.txt", std::ios::out); // 若找不到則新增txt檔
  for (int i = 0; i < arr_size2; i++)
    ss << " " << arr2[i].Close_price;
  outfortest << ss.str().c_str();
  ss.str("");
  outfortest.close(); // 關閉test1.txt
  // 第8題 畫出出每天的 daily return (使用python的matplotlib)
  outfortest.open("test2.txt", std::ios::out); // 若找不到則新增txt檔
  for (int i = 0; i < Dayilyreturn_size; i++)
    ss << " " << arrDayilyreturn[i];
  outfortest << ss.str().c_str();
  ss.str("");
  outfortest.close(); // 關閉test2.txt
  // 第9題 畫出出每天的 intraday return (使用python的matplotlib)
  outfortest.open("test3.txt", std::ios::out); // 若找不到則新增txt檔
  for (int i = 0; i < Intradayreturn_size; i++)
    ss << " " << arrIntradayreturn[i];
  outfortest << ss.str().c_str();
  ss.str("");
  outfortest.close(); // 關閉test3.txt

  // 第10題 根據有數字的四個欄位找出最小數字、最大數字、中位數。
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