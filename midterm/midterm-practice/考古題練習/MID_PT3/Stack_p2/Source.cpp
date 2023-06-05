//已完成
#include"Header.h"
#include<iostream>
#include<string>
using namespace std;

void print(char ch) {
	switch (ch)
	{
	case '+':
		cout << "ADD" << endl;
		break;
	case '-':
		cout << "SUB" << endl;
		break;
	case '*':
		cout << "MUL" << endl;
		break;
	case '/':
		cout << "DIV" << endl;
		break;
	default:
		cout << "???" << endl;
		break;
	}
}
int main() {
	Stack<char> oper(100);

	string input;
	bool immed = false;
	cin >> input;
	for (int i = 0; i < input.length(); i++) {
		if (input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/') {
			if (input[i] == '*' || input[i] == '/') {//如果是乘除都直接push
				oper.Push(input[i]);
				immed = true;//數字只有遇到前面有乘除時才需要先把乘除拿出來，因此設為true
			}
			else {//如果是加減
				if (oper.IsEmpty()) {//當是空的直接push
					oper.Push(input[i]);

				}
				else {//但如果不是空的表示前面有運算子要拿出來
					print(oper.Stack_top());
					oper.Pop();
					oper.Push(input[i]);//拿完後再push
				}
			}
		}
		else {
			cout << "PUSH " << input[i] << endl;
			if (immed) {//數字只有遇到前面有乘除時才需要先把乘除拿出來，因此設為true
				print(oper.Stack_top());
				oper.Pop();
				immed = false;//要記得
			}
		}
	}
	while (!oper.IsEmpty()) {//最後將剩下的都pop出來
		print(oper.Stack_top());
		oper.Pop();
	}
	return 0;
}
