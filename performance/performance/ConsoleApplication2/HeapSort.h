#include<iostream>
#include<iomanip>
#include<fstream>
#include<string>
#include<sstream>
#include<cfloat>
using namespace std;
//HeapSortClass，使用template語法可以支援多型別排序。
template<class IT, class function = less<IT>>
class HeapSortClass
{
private:
    static function cmp;
public:
    static void restore(IT Heap[], int s, int t);
    static void HeapSort(IT* b, IT* e);
};
//HeapSortClass的預設建構子，如果都沒設定的話就是根據某資料從小到大排序(若為自訂型別則須另外寫函數物件)
template<typename IT, typename function>
function HeapSortClass<IT, function>::cmp = function();
//HeapSortClass當中，讓最小的東西放在Heap的最頂端，
//待回HeapSort需要用for迴圈做n次從後面往前將最小的東西分別放到Heap的頂端。
template<class IT, class function>
void HeapSortClass<IT, function>::restore(IT Heap[], int s, int t)
{
    IT val = Heap[s];
    int child = 2 * s + 1;
    while (child <= t) {
        if (child < t && cmp(Heap[child], Heap[child + 1]))child++;
        if (cmp(val, Heap[child])) {
            Heap[s] = Heap[child];
            s = child;
            child = 2 * s + 1;
        }
        else break;
    }
    Heap[s] = val;
}
//HeapSort的實際邏輯，首先將整個陣列轉化成heap以後。
//再將最小的元素分別放到陣列的arr[0],arr[1],arr[2]...
template<class IT, class function>
void HeapSortClass<IT, function>::HeapSort(IT* b, IT* e)
{
    int n = e - b;
    for (int i = n / 2 - 1; i >= 0; i--) {
        restore(b, i, n - 1);
    }
    for (int i = n - 1; i >= 1; i--) {
        swap(b[0], b[i]);
        restore(b, 0, i - 1);
    }
}
template<class arr, class something>
int BinarySearch(arr a, int L, int R, something&& Target)
{
    if (L + 1 == R)return -1;
    int mid = (L + R) / 2;
    if (a[mid].getencode() == Target.getencode())return mid;
    if (a[mid].getencode() < Target.getencode())return BinarySearch(a, mid, R, Target);
    return BinarySearch(a, L, mid, Target);
}
//宣告一個DataFrame行別
//encode為根據2_3_4_5欄位的編碼
//encode2為根據1_6欄位的編碼
//Date為日期
//deal_price為成交價格
//使用OOP風格撰寫程式，有封裝。
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
//繁複的建構子和getter,setter宣告。
DataFrame::DataFrame() :encode(""), encode2(""), Date(""), strike_price(0.0), deal_price(0.0) {}
void DataFrame::setencode(string s) { encode = s; }
void DataFrame::setencode2(string s) { encode2 = s; }
void DataFrame::setDate(string s) { Date = s; }
void DataFrame::setdeal_price(double p) { deal_price = p; }
const string DataFrame::getencode() { return encode; }
const string DataFrame::getencode2() { return encode2; }
const string DataFrame::getDate() { return Date; }
const double DataFrame::getdeal_price() { return deal_price; }
//函數物件，DataFrame用來表示排序時的比較方法，將HeapSortClass的用這個表示就是根據encoding從小到大排序。
struct cmpForencoding
{
    bool operator()(DataFrame& a, DataFrame& b)
    {
        if (a.getencode() != b.getencode())return a.getencode() < b.getencode();
        if (a.getDate() != b.getDate())return a.getDate() < b.getDate();
        if (a.getdeal_price() != b.getdeal_price())return a.getdeal_price() < b.getdeal_price();
        return a.getencode2() < b.getencode2();
    }
};
//函數物件，DataFrame用來表示排序時的比較方法，將HeapSortClass的用這個表示就是根據成交價格從小到大排序。
struct cmpForlessDeal_price
{
    bool operator()(DataFrame& a, DataFrame& b)
    {
        return a.getdeal_price() < b.getdeal_price();
    }
};
//函數物件，DataFrame用來表示排序時的比較方法，將HeapSortClass的用這個表示就是根據成交價格從大到小排序。
struct cmpForgreaterDeal_price
{
    bool operator()(DataFrame& a, DataFrame& b)
    {
        return a.getdeal_price() > b.getdeal_price();
    }
};
//函數物件，DataFrame用來表示排序時的比較方法，將HeapSortClass的用這個表示就是根據日期從小到大排序。
struct cmpForDate
{
    bool operator()(DataFrame& a, DataFrame& b)
    {
        return a.getDate() < b.getDate();
    }
};
//函數物件，DataFrame用來表示排序時的比較方法，將HeapSortClass的用這個表示就是根據encode2從小到大排序。
struct cmpForencode2
{
    bool operator()(DataFrame& a, DataFrame& b)
    {
        return a.getencode2() < b.getencode2();
    }
};
//函數物件，DataFrame用來表示兩個資料是否相等，使用encode判斷。
bool operator==(DataFrame& a, DataFrame& b)
{
    return (a.getencode() == b.getencode());
}
//函數物件，DataFrame用來表示兩個資料是否小於，使用encode判斷。
bool operator<(DataFrame& a, DataFrame& b)
{
    return a.getencode() < b.getencode();
}