#include<iostream>
using namespace std;
class f
{
public:
    void hello();
};
void f::hello()
{
    cout << "hello!";
}
int main()
{
    f f0;
    f0.hello();
    return 0;
}
