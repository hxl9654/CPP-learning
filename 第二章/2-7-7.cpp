#include<iostream>
using namespace std;
void show(int, int);
int main()
{
	int h, m;
	cout << "Enter the number of hours: ";
	cin >> h;
	cout << "Enter the number of minutes: ";
	cin >> m;
	show (h, m);
	return 0;
}
void show(int h, int m)
{
	cout << h << ":" << m;
}
