#include"Header.h"
#include<iostream>
using namespace std;
void show() {

}
int main() {
	int ns, cap, ex;
	cin >> ns >> cap >> ex;
	Stack<string>* stac = new Stack<string>[ns];
	for (int i = 0; i < ns; i++) {
		stac[i].MAX(cap);
	}
	for (int i = 0; i < ex; i++) {
		string s;
		string s1;
		int a;
		cin >> s;
		if (s == "add") {
			cin >> s1;
			for (int i = 0; i < ns; i++) {
				if (!stac[i].isFull()) {
					stac[i].Push(s1);
					break;
				}
			}
		}
		else if (s == "removeAtStack") {
			cin >> a;
			if (stac[a].isEmpty()) {
				cout << "-1" << endl;
			}
			else {
				cout << stac[a].stack_top() << endl;
				stac[a].Pop();
			}
		}
		else {
			for (int i = ns - 1; i > -1; i--) {
				//cout << stac[2].stack_top() << endl;
				if (!stac[i].isEmpty()) {
					cout << stac[i].stack_top() << endl;
					stac[i].Pop();
					break;
				}
			}
		}
	}
	if (stac[0].isEmpty()) {
		cout << -1 << endl;
	}
}