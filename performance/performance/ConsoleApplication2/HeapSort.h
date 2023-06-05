#include<iostream>
#include<iomanip>
#include<fstream>
#include<string>
#include<sstream>
#include<cfloat>
using namespace std;
//HeapSortClass�A�ϥ�template�y�k�i�H�䴩�h���O�ƧǡC
template<class IT, class function = less<IT>>
class HeapSortClass
{
private:
    static function cmp;
public:
    static void restore(IT Heap[], int s, int t);
    static void HeapSort(IT* b, IT* e);
};
//HeapSortClass���w�]�غc�l�A�p�G���S�]�w���ܴN�O�ھڬY��Ʊq�p��j�Ƨ�(�Y���ۭq���O�h���t�~�g��ƪ���)
template<typename IT, typename function>
function HeapSortClass<IT, function>::cmp = function();
//HeapSortClass���A���̤p���F���bHeap���̳��ݡA
//�ݦ^HeapSort�ݭn��for�j�鰵n���q�᭱���e�N�̤p���F����O���Heap�����ݡC
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
//HeapSort������޿�A�����N��Ӱ}�C��Ʀ�heap�H��C
//�A�N�̤p���������O���}�C��arr[0],arr[1],arr[2]...
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
//�ŧi�@��DataFrame��O
//encode���ھ�2_3_4_5��쪺�s�X
//encode2���ھ�1_6��쪺�s�X
//Date�����
//deal_price���������
//�ϥ�OOP���漶�g�{���A���ʸˡC
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
//�c�ƪ��غc�l�Mgetter,setter�ŧi�C
DataFrame::DataFrame() :encode(""), encode2(""), Date(""), strike_price(0.0), deal_price(0.0) {}
void DataFrame::setencode(string s) { encode = s; }
void DataFrame::setencode2(string s) { encode2 = s; }
void DataFrame::setDate(string s) { Date = s; }
void DataFrame::setdeal_price(double p) { deal_price = p; }
const string DataFrame::getencode() { return encode; }
const string DataFrame::getencode2() { return encode2; }
const string DataFrame::getDate() { return Date; }
const double DataFrame::getdeal_price() { return deal_price; }
//��ƪ���ADataFrame�ΨӪ�ܱƧǮɪ������k�A�NHeapSortClass���γo�Ӫ�ܴN�O�ھ�encoding�q�p��j�ƧǡC
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
//��ƪ���ADataFrame�ΨӪ�ܱƧǮɪ������k�A�NHeapSortClass���γo�Ӫ�ܴN�O�ھڦ������q�p��j�ƧǡC
struct cmpForlessDeal_price
{
    bool operator()(DataFrame& a, DataFrame& b)
    {
        return a.getdeal_price() < b.getdeal_price();
    }
};
//��ƪ���ADataFrame�ΨӪ�ܱƧǮɪ������k�A�NHeapSortClass���γo�Ӫ�ܴN�O�ھڦ������q�j��p�ƧǡC
struct cmpForgreaterDeal_price
{
    bool operator()(DataFrame& a, DataFrame& b)
    {
        return a.getdeal_price() > b.getdeal_price();
    }
};
//��ƪ���ADataFrame�ΨӪ�ܱƧǮɪ������k�A�NHeapSortClass���γo�Ӫ�ܴN�O�ھڤ���q�p��j�ƧǡC
struct cmpForDate
{
    bool operator()(DataFrame& a, DataFrame& b)
    {
        return a.getDate() < b.getDate();
    }
};
//��ƪ���ADataFrame�ΨӪ�ܱƧǮɪ������k�A�NHeapSortClass���γo�Ӫ�ܴN�O�ھ�encode2�q�p��j�ƧǡC
struct cmpForencode2
{
    bool operator()(DataFrame& a, DataFrame& b)
    {
        return a.getencode2() < b.getencode2();
    }
};
//��ƪ���ADataFrame�ΨӪ�ܨ�Ӹ�ƬO�_�۵��A�ϥ�encode�P�_�C
bool operator==(DataFrame& a, DataFrame& b)
{
    return (a.getencode() == b.getencode());
}
//��ƪ���ADataFrame�ΨӪ�ܨ�Ӹ�ƬO�_�p��A�ϥ�encode�P�_�C
bool operator<(DataFrame& a, DataFrame& b)
{
    return a.getencode() < b.getencode();
}