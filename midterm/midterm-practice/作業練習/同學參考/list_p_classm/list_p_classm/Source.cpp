#include"Header.h"
#include<string>

int main() {
	Term t;
	string str;
	int temp = 0;
	string sort;
	for (int i = 0; i < 2; i++) {
		Polynomial a, b, c;
		while (1)
		{
			cin >> t.coef;
			char ch = cin.get();
			if (ch == '\n')
			{
				t.exp = 0;
				a.poly.InsertBack(t);
				break;
			}
			cin.ignore();//©¿²¤ x^
			cin >> t.exp;
			a.poly.InsertBack(t);
			ch = cin.get();
			if (ch == '\n')
				break;
			cin.ignore();
			cin.ignore();
		}
		temp = 0;
		while (1)
		{
			cin >> t.coef;
			char ch = cin.get();
			if (ch == '\n')
			{
				t.exp = 0;
				b.poly.InsertBack(t);
				break;
			}
			cin.ignore();
			cin >> t.exp;
			b.poly.InsertBack(t);
			ch = cin.get();
			if (ch == '\n')
				break;
			cin.ignore();
			cin.ignore();
		}
		c = a + b;
		cin >> sort;
		if (sort == "ascending") {
			c.poly.Reverse();
		}
			c.poly.show();
	}

	/*
	Polynomial a;
	Term temp;
	temp.Set(3, 14);
	a.poly.InsertBack(temp);
	a.poly.show();

	string str1;
	string str2;
	getline(cin, str1);
	string sub1 = str1.substr(0, str1.find("x"));
	cout << sub1 << endl;
	sub1 = str1.substr(str1.find("^") + 1, str1.length());
	cout << sub1 << endl;
	string sub2 = str1.substr(str1.find(" + ") + 3, str1.length());
	cout << sub2 << endl;
	*/
}