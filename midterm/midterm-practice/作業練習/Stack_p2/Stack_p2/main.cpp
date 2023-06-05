#include <string>
#include "Stack.h"
#include <iostream>
using namespace std;

#define NEW2D(H, W, TYPE) (TYPE **)new2d(H, W, sizeof(TYPE))

void** new2d(int h, int w, int size) {
	int i;
	void** p;
	p = (void**)new char[h * sizeof(void*) + h * w * size];
	for (i = 0; i < h; i++)
		p[i] = ((char*)(p + h)) + i * w * size;
	return p;
}

struct offsets {
	int a;
	int b;
};
struct Items {
	int x, y, dir; //coordinates and moving directions
};
enum directions { N, NE, E, SE, S, SW, W, NW };

offsets mov[8];

void setDir() {
	mov[0].a = -1; mov[0].b = 0;
	mov[1].a = -1; mov[1].b = 1;
	mov[2].a = 0; mov[2].b = 1;
	mov[3].a = 1; mov[3].b = 1;
	mov[4].a = 1; mov[4].b = 0;
	mov[5].a = 1; mov[5].b = -1;
	mov[6].a = 0; mov[6].b = -1;
	mov[7].a = -1; mov[7].b = -1;
}

int main() {
	setDir();

	string all;
	string str;
	int row = 1, col = 0;
	getline(cin, all);
	col = (all.length() + 1) / 2;
	while ((getline(cin, str)) && !cin.eof()) {
		all += str;
		row++;
	}

	int** data = NEW2D(row + 2, col + 2, int);
	int** mark = NEW2D(row + 2, col + 2, int);
	int p = 0;
	for (int j = 0; j < row + 2; j++) {
		for (int i = 0; i < col + 2; i++) {
			if (j == 0 || j == row + 1 || i == 0 || i == col + 1) {
				data[j][i] = 1;
				mark[j][i] = 1;
			}
		}
	}

	int start_x, start_y;
	int end_x, end_y;
	for (int j = 1; j <= row; j++) {
		for (int i = 1; i <= col; i++) {
			if (all[p] == 'b') {
				data[j][i] = 1;
				mark[j][i] = 1;
			}
			else {
				data[j][i] = 0;
				mark[j][i] = 0;
			}

			if (all[p] == 's') {
				start_x = j;
				start_y = i;
				data[j][i] = 2;
			}
			else if (all[p] == 'e') {
				end_x = j;
				end_y = i;
				data[j][i] = 3;
			}
			p += 2;
		}
		p--;
	}

	//-----------------------------------

	Stack<Items> stac(row * col);
	Items now;
	Items next;

	now.x = start_x;
	now.y = start_y;
	now.dir = E;
	stac.Push(now);
	mark[now.x][now.y] = 1;

	int tried;
	bool check;

	while (!stac.IsEmpty()) {
		now = stac.Newest();
		mark[now.x][now.y] = 1;
		now.dir == E;
		tried = 1;
		check = false;
		while (tried <= 8) {
			if (mark[(now.x + mov[now.dir].a)][(now.y + mov[now.dir].b)] == 0) {
				stac.Pop();//因為之前有放入next要先pop
				stac.Push(now);//再push
				check = true;
				break;
			}
			else {
				now.dir++;
				if (now.dir > 7) {
					now.dir = 0;
				}
			}
			tried++;
		}
		if (check == true) {
			next.x = now.x + mov[now.dir].a;
			next.y = now.y + mov[now.dir].b;
			next.dir = E;
			stac.Push(next);//先放入下一個看是不是end
			if (next.x == end_x && next.y == end_y) {
				break;//全部結束
			}
		}
		else {
			stac.Pop();//不能走一直pop
		}
	}

	//---------------------

	int sym = 0;
	for (int i = 1; i < stac.getTop(); i++) {
		sym = 0;
		switch (stac.getStack()[i - 1].dir) {
		case E:case W:
			sym = 4;
			break;
		case N:case S:
			sym = 5;
			break;
		case NE:case SW:
			sym = 6;
			break;
		case NW:case SE:
			sym = 7;
			break;
		}
		data[(stac.getStack()[i].x)][(stac.getStack()[i].y)] = sym;
	}

	for (int j = 1; j < row + 1; j++) {
		for (int i = 1; i < col + 1; i++) {
			if (data[j][i] == 1) {
				cout << "b" << " ";
			}
			else if (data[j][i] == 2) {
				cout << "s" << " ";
			}
			else if (data[j][i] == 3) {
				cout << "e" << " ";
			}
			else if (data[j][i] == 4) {
				cout << "-" << " ";
			}
			else if (data[j][i] == 5) {
				cout << "|" << " ";
			}
			else if (data[j][i] == 6) {
				cout << "/" << " ";
			}
			else if (data[j][i] == 7) {
				cout << "\\" << " ";
			}
			else {
				cout << data[j][i] << " ";
			}
		}
		cout << endl;
	}

	cout << "Total " << stac.getTop() << " Steps. " << endl;
	return 0;
}