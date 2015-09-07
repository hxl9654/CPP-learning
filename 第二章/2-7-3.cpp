#include<iostream>
using namespace std;
void showA();
void showB();
int main()
{
	showA();
	showA();
	showB();
	showB();
	return 0;
}
void showA()
{
	cout << "There blind mice" << endl;
}
void showB()
{
	cout << "See how they run" << endl;
}
