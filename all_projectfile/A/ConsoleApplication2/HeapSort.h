using namespace std;
//HeapSortClass�A�ϥ�template�y�k�i�H�䴩�h���O�ƧǡC
template<class IT, class function>
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