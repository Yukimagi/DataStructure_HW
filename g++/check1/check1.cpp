#include "bits/stdc++.h"
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
  static void restore(IT *, int, int);
  static void HeapSort(IT *, IT *);
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
  int n = (int)(e - b);
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
string LINE;
DataFrame arr[1000000], arr2[1000000], arr3[1000000];
int arr_size, arr_size2, arr_size3;
int main()
{ // 第１題 檔案讀取跟輸出
  ifstream fin;
  ofstream fout;
  // 若找不到檔案則程式停止
  fin.open("datasets/problem1/TWII_withRepeatedData.csv");
  if (!fin.is_open())
  {
    cerr << "找不到這個檔案！";
    return -1;
  }
  fout.open("self-debug.txt");
  if (!fout.is_open())
  {
    cerr << "無法開啟這個文件！";
    return -1;
  }
  // 開始讀檔
  getline(fin, LINE);
  getline(fin, LINE);
  while (getline(fin, LINE))
  {
    for (auto &i : LINE)
      i = (i == ',') ? ' ' : i;
    istringstream sin(LINE);
    DataFrame tmp;
    sin >> tmp.d >> tmp.Open_price >> tmp.High_price >> tmp.Low_price >> tmp.Close_price;
    arr[arr_size] = tmp;
    arr_size++;
  }
  HeapSortClass<DataFrame, compareWithDate>::HeapSort(arr, arr + arr_size);
  Date tt;
  // 刪除重複的到arr2
  for (int i = 0; i < arr_size; i++)
  {
    if (tt == arr[i].d)
      continue;
    arr2[arr_size2++] = arr[i];
    tt = arr[i].d;
  }
  fout << "不重複的資料:" << endl;
  for (int i = 0; i < arr_size2; i++)
    fout << arr2[i] << endl;
  fout << string(20, '-') << endl;
  // 每5筆
  fout << "每5筆抓一個的資料:" << endl;
  for (int i = 0; i < arr_size2; i++)
  {
    if (i % 5 == 0)
      fout << "(5倍數) ";
    fout << arr2[i] << endl;
  }
  fout << string(20, '-') << endl;
  // 養成習慣關掉fin跟fout的視窗。
  fin.close();
  fout.close();
}