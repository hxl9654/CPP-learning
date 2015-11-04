#include<iostream>
using namespace std;
class shape
{
public :
    double a,b,r;
    virtual void area() = 0;
};
class circle : public shape
{
public:
    circle(double ir)
    {
        r = ir;
    }
    void area();
};
class rectangle : public shape
{
public:
    rectangle(double ia, double ib)
    {
        a = ia;
        b = ib;
    }
    void area();
};
class sque : public shape
{
public:
    sque(double ia)
    {
        a = ia;
    }
    void area();
};
void circle::area()
{cout << "s=" << 3.14 * r *r;}
void rectangle::area()
{cout << "s=" << a * b;}
void sque::area()
{cout << "s=" << a * a;}
int main()
{
    int s = 10;
    int r,a,b;
    shape * c[10];
    cout << "input:";
    cin >> s;
    if(s == 0)
    {
        cout << "input r:";
        cin >> r;
        c[0] = new circle(r);
    }
    else if(s == 1)
    {
        cout << "input a:";
        cin >> a;
        cout << "input b:";
        cin >> b;
        c[0] = new rectangle(a,b);
    }
    else if(s == 2)
    {
        cout << "input a:";
        cin >> a;
        c[0] = new sque(a);
    }
    c[0] -> area();
    for(;;);
    return 0;
}
