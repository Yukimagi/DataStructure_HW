#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <cfloat>
#include <algorithm>
using namespace std;

struct Node
{
  string data; // 元素值
  Node *left;  // 指向左子節點的指針
  Node *right; // 指向右子節點的指針
};

// 定義一個insert函數，用於將元素插入到二元搜尋樹中
bool insert(Node *&root, const string &s)
{
  // root是二元搜尋樹的根節點，s是要插入的元素值
  // 如果根節點為空，則創建一個新節點，存放元素值和空指針，並將根節點指向它
  if (root == nullptr)
  {
    root = new Node;
    root->data = s;
    root->left = nullptr;
    root->right = nullptr;
    return true; // 返回true表示插入成功
  }
  // 如果根節點不為空，則比較根節點與要插入的元素值的大小
  if (s < root->data)
  {                               // 如果要插入的元素值小於根節點的值
    return insert(root->left, s); // 遞迴地在左子樹中插入
  }
  else if (s > root->data)
  {                                // 如果要插入的元素值大於根節點的值
    return insert(root->right, s); // 遞迴地在右子樹中插入
  }
  else
  {               // 如果要插入的元素值等於根節點的值
    return false; // 返回false表示插入失敗，因為該元素已經存在於二元搜尋樹中
  }
}

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
  // cout << "開始二元搜尋找第" << mid << "格" << endl;
  // cout << "目標是" << Target.getencode() << endl;
  // cout << "這格是" << a[mid].getencode() << endl;
  // cout << ((cmp(a[mid],Target))?"結果是小於":"結果是大於等於") << endl;
  if (cmp(a[mid], Target))
    return BinarySearch2(a, mid, R, Target, cmp);
  return BinarySearch2(a, L, mid, Target, cmp);
}

//宣告一個DataFrame行別
//encode為根據2_3_4_5欄位的編碼
//encode2為根據1_6欄位的編碼
//Date為日期
//deal_price為成交價格
//使用OOP風格撰寫程式，有封裝。
class DataFrame_Base
{
public:
    //DataFrame_Base();
    virtual void setencode(string) = 0;
    virtual void setencode2(string) = 0;
    virtual void setDate(string) = 0;
    virtual void setdeal_price(double) = 0;
    virtual const string getencode() = 0;
    virtual const string getencode2() = 0;
    virtual const string getDate() = 0;
    virtual const double getdeal_price() = 0;
private:
    string encode, encode2, Date;
    double strike_price, deal_price;
};

class DataFrame :public DataFrame_Base
{
public:
    DataFrame() :encode(""), encode2(""), Date(""), strike_price(0.0), deal_price(0.0) {};
    void setencode(string s)override { encode = s; };
    void setencode2(string s)override { encode2 = s; };
    void setDate(string s)override { Date = s; };
    void setdeal_price(double p)override { deal_price = p; };
    const string getencode()override { return encode; };
    const string getencode2()override { return encode2; };
    const string getDate()override { return Date; };
    const double getdeal_price()override { return deal_price; };
private:
    string encode, encode2, Date;
    double strike_price, deal_price;
};

struct cmpForencoding
{
  bool operator()(DataFrame &a, DataFrame &b)
  {
    if (a.getencode() != b.getencode())
      return a.getencode() < b.getencode();
    if (a.getDate() != b.getDate())
      return a.getDate() < b.getDate();
    if (a.getdeal_price() != b.getdeal_price())
      return a.getdeal_price() < b.getdeal_price();
    return a.getencode2() < b.getencode2();
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
  return (a.getencode() == b.getencode());
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
    fout << "maximum return 為" << MAX << " " << "Pt date=" << unionData2[MAXINDEX].getencode2() << "price" << " " << Pt_check_big << " " << "Pt-1 date=" << unionData2[MAXINDEX - 1].getencode2() << "price" << " " << Pt_1_check_big << endl;
    fout << "minimum return 為" << MIN << " " << "Pt date=" << unionData2[MININDEX].getencode2() << "price" << " " << Pt_check_small << " " << "Pt-1 date=" << unionData2[MININDEX - 1].getencode2() << "price" << " " << Pt_1_check_small << endl;
    fout.close();
}