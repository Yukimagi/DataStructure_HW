#include<iostream>
using namespace std;
#define NEW2D(H,W,TYPE)(TYPE**)new2d(H,W,sizeof(TYPE))
void** new2d(int h, int w, int size) {
	void** p;
	p = (void**)new char[sizeof(void*) * h + h * w * size];
	for (int i = 0; i < h; i++) {
		p[i] = (char*)(h + p) + i * w * size;
	}
	return p;
}
int main() {
	int row, col, n;
	cin >> row >> col >> n;
	int** A = NEW2D(col, row, int);
	for (int i = 0; i < col; i++) {
		fill(A[i], A[i] + row, 0);
	}
	int row2, col2, m;
	cin >> row2 >> col2 >> m;
	int** B = NEW2D(col2, row2, int);
	for (int i = 0; i < col2; i++) {
		fill(B[i], B[i] + row2, 0);
	}
	for (int i = 0; i < n; i++) {
		int r;
		int c;
		int v;
		cin >> r >> c >> v;
		A[c][r] = v;
	}
	for (int i = 0; i < m; i++) {
		int r;
		int c;
		int v;
		cin >> r >> c >> v;
		B[c][r] = v;
	}
	int** C = NEW2D(col, row2, int);
	for (int i = 0; i < col; i++) {
		fill(C[i], C[i] + row2, 0);
	}
	for (int i = 0; i < col; i++) {
		for (int j = 0; j < row2; j++) {
			for (int k = 0; k < row; k++) {
				C[i][j] = C[i][j] + A[i][k] * B[k][j];
			}
		}
	}
	cout << col <<" "<< row2 << endl;
	for (int i = 0; i < col; i++) {
		for (int j = 0; j < row2; j++) {
			cout << C[i][j] << " ";
		}
		cout << endl;
	}
}