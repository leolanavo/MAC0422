#include <list>
#include <iostream>
#include <string>
#include <typeinfo>

using namespace std;

typedef struct {
	int base, size;
	string pid;
} alloc;

int main () {
	alloc a = {1, 2, "p1"}, b = {3, 4, "p2"}, c = {5, 6, "p3"};
	list<alloc> l; 
	l.push_back(a);
	l.push_back(b);
	l.push_back(c);

	list<alloc>::iterator it = l.begin();
	cout << typeid(a).name() << endl;
	cout << typeid(*(it)).name() << endl;

	if (a == *(it))
		cout << "Hell" << endl;
	else
		cout << "Heaven" << endl;
}