#include"Header.h"
#include<iostream>
using namespace std;
void show() {
	
}
int main() {
	int ns,cap,ex;
	cin >> ns >> cap >> ex;
	Stack<int>* stac = new Stack<int>[ns];
	for (int i = 0; i < ns; i++) {
		stac[i].MAX(cap);
	}
	for (int i = 0; i < ex; i++) {
		string s;
		int a;
		cin >> s;
		if (s == "add") {
			cin >> a;
			for (int i = 0; i < ns; i++) {
				if (!stac[i].isFull()) {
					stac[i].Push(a);
					break;
				}
			}
		}
		else if(s=="removeAtStack") {
			cin >> a;
			cout << stac[a].stack_top()<<endl;
			stac[a].Pop();
		}
		else {
			for (int i = ns-1; i >-1; i--) {
				if (!stac[i].isEmpty()) {
					cout << stac[a].stack_top()<<endl;
					stac[a].Pop();
					break;
				}
			}
		}
	}
	if (stac[0].isEmpty()) {
		cout << -1 << endl;
	}
}