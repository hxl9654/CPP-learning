#include<iostream>
using namespace std;
class base
{
public:
    void add(int a);
    int get();
    int s = 0;
};
class fun:public base
{
public:
    void div(int a);
};
void fun::div(int a)
{
    s -= a;
}
void base::add(int a)
{
    s += a;
}
int base::get()
{
    return s;
}
int main()
{
    fun s;
    for(int i = 0; i < 5; i++)
    {
        int t;
        cin >> t;
        s.add(t);
    }
    cout << s.get() << endl;
    for(int i = 0; i < 5; i++)
    {
        int t;
        cin >> t;
        s.div(t);
    }
    cout << s.get() << endl;
    return 0;
}
