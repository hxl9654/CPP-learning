#include<iostream>
using namespace std;
class sum
{
public:
    void add(int a);
    int get();
private:
    int s = 0;
};
void sum::add(int a)
{
    s += a;
}
int sum::get()
{
    return s;
}
int main()
{
    sum s;
    for(int i = 0; i < 5; i++)
    {
        int t;
        cin >> t;
        s.add(t);
    }
    cout << s.get();
    return 0;
}
