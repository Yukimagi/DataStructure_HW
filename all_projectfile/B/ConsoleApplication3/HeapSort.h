using namespace std;
//HeapSortClass，使用template語法可以支援多型別排序。
template<class IT, class function>
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