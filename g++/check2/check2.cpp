#include "bits/stdc++.h"
using namespace std;

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
template <class arr, class something>
int BinarySearch(arr a, int L, int R, something &&Target)
{
  if (L + 1 == R)
    return -1;
  int mid = (L + R) / 2;
  if (a[mid].getencode() == Target.getencode())
    return mid;
  if (a[mid].getencode() < Target.getencode())
    return BinarySearch(a, mid, R, Target);
  return BinarySearch(a, L, mid, Target);
}

template <class arr, class something, class function>
int BinarySearch2(arr a, int L, int R, something &Target, function cmp)
{
  if (L + 1 == R)
    return L;
  int mid = (L + R) / 2;
  if (cmp(a[mid], Target))
    return BinarySearch2(a, mid, R, Target, cmp);
  return BinarySearch2(a, L, mid, Target, cmp);
}

class DataFrame
{
public:
  DataFrame();
  void setencode(string);
  void setencode2(string);
  void setDate(string);
  void setdeal_price(double);
  const string getencode();
  const string getencode2();
  const string getDate();
  const double getdeal_price();

private:
  string encode, encode2, Date;
  double strike_price, deal_price;
};

DataFrame::DataFrame() : encode(""), encode2(""), Date(""), strike_price(0.0), deal_price(0.0) {}
void DataFrame::setencode(string s) { encode = s; }
void DataFrame::setencode2(string s) { encode2 = s; }
void DataFrame::setDate(string s) { Date = s; }
void DataFrame::setdeal_price(double p) { deal_price = p; }
const string DataFrame::getencode() { return encode; }
const string DataFrame::getencode2() { return encode2; }
const string DataFrame::getDate() { return Date; }
const double DataFrame::getdeal_price() { return deal_price; }
struct cmpForencoding
{
  bool operator()(DataFrame &a, DataFrame &b)
  {
    return a.getencode() < b.getencode();
  }
};
struct cmpForlessDeal_price
{
  bool operator()(DataFrame &a, DataFrame &b)
  {
    return a.getdeal_price() < b.getdeal_price();
  }
};
struct cmpForgreaterDeal_price
{
  bool operator()(DataFrame &a, DataFrame &b)
  {
    return a.getdeal_price() > b.getdeal_price();
  }
};
struct cmpForDate
{
  bool operator()(DataFrame &a, DataFrame &b)
  {
    return a.getDate() < b.getDate();
  }
};
struct cmpForencode2
{
  bool operator()(DataFrame &a, DataFrame &b)
  {
    return a.getencode2() < b.getencode2();
  }
};
bool operator==(DataFrame &a, DataFrame &b)
{
  return a.getencode() == b.getencode();
}
bool operator<(DataFrame &a, DataFrame &b)
{
  return a.getencode() < b.getencode();
}
bool cmpforless(DataFrame &a, DataFrame &b)
{
  return a.getencode() < b.getencode();
}
bool cmpforless2(DataFrame &a, DataFrame &b)
{
  return a.getencode2() <= b.getencode2();
}
bool cmpforgreater2(DataFrame &a, DataFrame &b)
{
  return a.getencode2() < b.getencode2();
}
string LINE, date, c2, c3, c4, c5, c6;
DataFrame arr[1000000], unionData2[1000000];
int arr_size, union_size2;
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
      for (auto &i : LINE)
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
      for (auto &i : LINE)
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
      for (auto &i : LINE)
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
      for (auto &i : LINE)
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
      for (auto &i : LINE)
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
  // １ 第5題的抓到的資料
  ofstream fout;
  fout.open("self-debug2.txt");
  if (!fout.is_open())
  {
    cerr << "無法創建self-debug2.txt";
    return -1;
  }
  HeapSortClass<DataFrame, cmpForDate>::HeapSort(arr, arr + arr_size);
  for (int i = 0; i < arr_size; i++)
    if (arr[i].getencode() == "TXO_9900_201705_C")
      unionData2[union_size2++] = arr[i];
  // ２ 抓到的資料的最大到最小排序
  HeapSortClass<DataFrame, cmpForgreaterDeal_price>::HeapSort(unionData2, unionData2 + union_size2);
  fout << "最大到最小排序" << endl;
  for (int i = 0; i < union_size2; i++)
    fout << unionData2[i].getencode2() << " " << unionData2[i].getdeal_price() << endl;
  fout << string(60, '-') << endl;
  // ３ 抓到的資料最小到最大的排序
  HeapSortClass<DataFrame, cmpForlessDeal_price>::HeapSort(unionData2, unionData2 + union_size2);
  fout << "最小到最大排序" << endl;
  for (int i = 0; i < union_size2; i++)
    fout << unionData2[i].getencode2() << " " << unionData2[i].getdeal_price() << endl;
  fout << string(60, '-') << endl;
  // tick，顯示日期。
  fout << "顯示 日期_成交日期,Pt,P(t-1),tick" << endl;
  HeapSortClass<DataFrame, cmpForDate>::HeapSort(unionData2, unionData2 + union_size2);
  double MAX = DBL_MIN, MIN = DBL_MAX;
  for (int i = 1; i < union_size2; i++)
  {
    double Pt = unionData2[i].getdeal_price(), Pt_1 = unionData2[i - 1].getdeal_price();
    double RETURN = (Pt - Pt_1) / (Pt_1)*100.0;
    MAX = max(MAX, RETURN);
    MIN = min(MIN, RETURN);
    fout << unionData2[i].getencode2() << ",Pt = " << Pt << ", P(t-1) =" << Pt_1 << ",的 tick-based是 " << RETURN << endl;
  }
  fout << string(60, '-') << endl;
  fout.close();
}