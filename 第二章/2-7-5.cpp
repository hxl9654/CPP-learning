#include<iostream>
double tempcov(double);
int main()
{
	using namespace std;
	cout << "Please enter a Celsius value: ";
	double temp;
	cin >> temp;
	cout << temp << " degrees Celsius is " << tempcov(temp) << " degree Fahrenheit.";
	return 0;
}
double tempcov(double c)
{
	double s;
	s = 1.8 * c + 32;
	return s;
}
