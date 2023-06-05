//�w����
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
			if (input[i] == '*' || input[i] == '/') {//�p�G�O����������push
				oper.Push(input[i]);
				immed = true;//�Ʀr�u���J��e���������ɤ~�ݭn���⭼�����X�ӡA�]���]��true
			}
			else {//�p�G�O�[��
				if (oper.IsEmpty()) {//��O�Ū�����push
					oper.Push(input[i]);

				}
				else {//���p�G���O�Ū���ܫe�����B��l�n���X��
					print(oper.Stack_top());
					oper.Pop();
					oper.Push(input[i]);//������Apush
				}
			}
		}
		else {
			cout << "PUSH " << input[i] << endl;
			if (immed) {//�Ʀr�u���J��e���������ɤ~�ݭn���⭼�����X�ӡA�]���]��true
				print(oper.Stack_top());
				oper.Pop();
				immed = false;//�n�O�o
			}
		}
	}
	while (!oper.IsEmpty()) {//�̫�N�ѤU����pop�X��
		print(oper.Stack_top());
		oper.Pop();
	}
	return 0;
}
