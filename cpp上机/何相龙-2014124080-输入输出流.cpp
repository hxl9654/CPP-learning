#include<iostream>
#include<fstream>
using namespace std;
int main()
{
    string a;
    string b;
    cin >> a;
    cout << a << endl;

    ofstream fout("hxl.txt");
    fout << a;
    fout.close();
    ifstream fin("hxl.txt");
    fin >> b;
    cout << b;
    return 0;
}
