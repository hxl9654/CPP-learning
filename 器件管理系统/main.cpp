#include<iostream>
#include<fstream>
#include<cstdlib>
using namespace std;
class thing
{
public:
    string name = "";
    int num = 0;
    double value = 0;
    void increase(int n);
    void decrease(int n);
    double getValueSum();
};
void thing::increase(int n)
{
    num += n;
}
void thing::decrease(int n)
{
    num -= n;
}
double thing::getValueSum()
{
    return value * num;
}
/*//////////////////////////////////////////////////////////////////////////////////
 *函数名：menu
 *功  能：显示程序菜单，并返回用户的选择。
 *参  数：空
 *返回值：一个整形变量，表示用户的选择。
 *作  者：何相龙
 *版  本：1.0
 *日  期：2015-11-04
*///////////////////////////////////////////////////////////////////////////////////
int menu()
{
    system("cls");
    cout << "欢迎使用器件管理系统，请选择您要进行的操作：" << endl;
    cout << "1.录入新器件。2.删除已有器件。3.查询器件信息。4.修改器件信息。5.器件出库与入库。" << endl;
    cout << "6.从文件读入数据。7.保存数据到文件。0.退出系统。" << endl;
    int n;
    cin >> n;
    return n;
}
/*//////////////////////////////////////////////////////////////////////////////////
 *函数名：Exit_confirm
 *功  能：显示程序退出确认，返回用户的选择。
 *参  数：空
 *返回值：一个逻辑型变量，表示用户的选择。
 *作  者：何相龙
 *版  本：1.0
 *日  期：2015-11-04
*///////////////////////////////////////////////////////////////////////////////////
bool Exit_confirm()
{
    system("cls");
    cout << "您确定要退出本系统吗？所有未保存的数据将丢失！确定请输入Y，取消请输入N：" << end;
    char t = ' ';
    while(t == ' ' || t == '\n' || t == '\r')
        cin >> t;
    if(t == 'y' || t == 'Y')
        return true;
    else return false;
}
/*//////////////////////////////////////////////////////////////////////////////////
 *函数名：main
 *功  能：程序主函数
 *参  数：空
 *返回值：一个整形变量，表示程序运行状态（正常情况返回0）。
 *作  者：何相龙
 *版  本：1.0
 *日  期：2015-11-04
*///////////////////////////////////////////////////////////////////////////////////
int main()
{
    while(1)
    {
        int c = menu();
        switch(c)
        {
            case(0):
                {
                    if(Exit_confirm())
                        return 0;
                    else menu();
                    break;
                }
            case(1):Devices_new();break;
            case(2):Devices_delete();break;
            case(3):Devices_search();break;
            case(4):Devices_change();break;
            case(5):Devices_io();break;
            case(6):File_read();break;
            case(7):File_write();break;
            default:WrongInput();menu();break;
        }
    }
    return 0;
}
