#include<iostream>
double cov(double);
int main()
{
	using namespace std;
	cout << "Enter the number of light years: ";
	double ly;
	cin >> ly;
	double au = cov(ly);
	cout << ly << " light years = " << au << " astronomical units";
	return 0;
}
double cov(double ly)
{
	return ly * 63240;
}
