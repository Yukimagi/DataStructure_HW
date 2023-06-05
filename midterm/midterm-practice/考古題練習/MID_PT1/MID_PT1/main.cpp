#include <iostream>  
using namespace std;
#define NEW2D(H, W, TYPE) (TYPE **)new2d(H, W, sizeof(TYPE))//(TYPE**)

void** new2d(int h, int w, int size) {
    int i;
    void** p;
    p = (void**)new char[h * sizeof(void*) + h * w * size];
    for (i = 0; i < h; i++)
        p[i] = ((char*)(p + h)) + i * w * size;
    return p;
}
int main()
{
    int row=0;
    int col=0;
    cin >> row >> col;
    int** A = NEW2D(row, col,int);
    int x;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            cin >> x;
            A[i][j] = x;
        }
    }
    int row2 = 0;
    int col2 = 0;
    cin >> row2 >> col2;
    int** B = NEW2D(row2, col2, int);
    int y;
    for (int i = 0; i < row2; i++) {
        for (int j = 0; j < col2; j++) {
            cin >> y;
            B[i][j] = y;
        }
    }
    if (col != row2) {
        cout << "第一個matrix column != 第二個matrix row" << endl;
    }
    else {
        int** C = NEW2D(row, col2, int);
        for (int i = 0; i < row; i++) {
            fill(C[i], C[i] + col2, 0);
        }
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col2; j++) {
                for (int k = 0; k < col; k++) {
                    C[i][j] = C[i][j]+( A[i][k] * B[k][j]);
                }
            }
        }
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col2; j++) {
                cout << C[i][j]<<" ";
            }
            cout << endl;
        }
        delete C;
    }
    delete A;
    delete B;
    
}