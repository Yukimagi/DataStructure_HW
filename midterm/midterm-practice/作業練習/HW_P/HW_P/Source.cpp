#include"Header.h"
#include<iostream>
#include<string>
#include<time.h>
using namespace std;
void show(char x) {
	switch (x) {
	case'+':
		cout << "ADD" << endl;
		break;
	case'-':
		cout << "SUB" << endl;
		break;
	case'*':
		cout << "MUL" << endl;
		break;
	case'/':
		cout << "DIV" << endl;
		break;
	default:
		cout << "???" << endl;
		break;
	}
}
int main() {
	Stack <char> stack(100);
	string in;
	cin >> in;
	bool check = false;
	for (int i = 0; i < in.length(); i++) {
		if (in[i] == '+' || in[i] == '-' || in[i] == '*' || in[i] == '/') {
			if (in[i] == '*' || in[i] == '/') {
				stack.push(in[i]);
				check = true;
			}
			else {
				if (!stack.isEmpty()) {
					show(stack.stack_top());
					stack.pop();
				}
				stack.push(in[i]);
			}
		}
		else {
			cout << "PUSH" << " " << in[i] << endl;
			if (check) {
				show(stack.stack_top());
				stack.pop();
				check = false;
			}
		}
	}
	while (!stack.isEmpty()) {
		show(stack.stack_top());
		stack.pop();
	}
	return 0;
}