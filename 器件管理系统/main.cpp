#include<iostream>
#include<fstream>
#include<cstdlib>
#include<stdexcept>
#include<exception>
using namespace std;
/*//////////////////////////////////////////////////////////////////////////////////
 *类  名：NotFinishException
 *功  能：功能未完成异常。
 *作  者：何相龙
 *版  本：1.0
 *日  期：2015-11-04
*///////////////////////////////////////////////////////////////////////////////////
class NotFinishException: public exception
{
public:
    const char *what() const throw();
};
const char * NotFinishException::what() const throw()
{
    return "该功能未完成";
}
/*//////////////////////////////////////////////////////////////////////////////////
 *类  名：NoValueException
 *功  能：无相应属性异常。
 *作  者：何相龙
 *版  本：1.1
 *日  期：2015-11-04
 *说  明：增加异常的备注
 *版  本：1.0
 *日  期：2015-11-04
*///////////////////////////////////////////////////////////////////////////////////
class NoValueException: public exception
{
public:
    NoValueException() throw() { }
    virtual ~NoValueException() throw(){ }
    NoValueException(string msg) throw(){message = msg;}
    const char *what() const throw();
private:
    string message;
};
const char * NoValueException::what() const throw()
{
    return "该对象相应属性";
}
/*//////////////////////////////////////////////////////////////////////////////////
 *类  名：base
 *功  能：器件的信息基类。
 *作  者：何相龙
 *版  本：1.0
 *日  期：2015-11-04
*///////////////////////////////////////////////////////////////////////////////////
class Base
{
public:
    string name;    //该器件的名字
    virtual void increase(int n) const;   //器件入库（n：数量）
    virtual void decrease(int n) const;   //器件出库（n：数量）
    virtual double getValueSum() const;   //获取该器件的总价值（返回：总价值）
};
void Base::increase(int n) const
{
    throw NoValueException("num");
}
void Base::decrease(int n) const
{
    throw NoValueException("num");
}
double Base::getValueSum() const
{
    throw NoValueException("value");
}
/*//////////////////////////////////////////////////////////////////////////////////
 *类  名：thing_withoutNum
 *功  能：存储器件（仅一件）的信息。
 *作  者：何相龙
 *版  本：1.0
 *日  期：2015-11-04
*///////////////////////////////////////////////////////////////////////////////////
class Thing_withoutNum: public Base
{
public:
    double value;       //器件单价
    double getValueSum();   //获取该器件的总价值（返回：总价值）
};
double Thing_withoutNum::getValueSum()
{
    return value;
}
/*//////////////////////////////////////////////////////////////////////////////////
 *类  名：thing_withoutValue
 *功  能：存储器件（无价值）的信息。
 *作  者：何相龙
 *版  本：1.0
 *日  期：2015-11-04
*///////////////////////////////////////////////////////////////////////////////////
class Thing_withoutValue: public Base
{
public:
    int num;            //库存数量
    void increase(int n);   //器件入库（n：数量）
    void decrease(int n);   //器件出库（n：数量）
};
void Thing_withoutValue::increase(int n)
{
    num += n;
}
void Thing_withoutValue::decrease(int n)
{
    num -= n;
}
/*//////////////////////////////////////////////////////////////////////////////////
 *类  名：thing
 *功  能：存储器件的信息。
 *作  者：何相龙
 *版  本：1.1
 *日  期：2015-11-04
 *描  述：建立基类，改为从基类继承。
 *版  本：1.0
 *日  期：2015-11-04
*///////////////////////////////////////////////////////////////////////////////////
class Thing: public Base
{
public:
    int num;            //库存数量
    double value;       //器件单价
    void increase(int n);   //器件入库（n：数量）
    void decrease(int n);   //器件出库（n：数量）
    double getValueSum();   //获取该器件的总价值（返回：总价值）
};
void Thing::increase(int n)
{
    num += n;
}
void Thing::decrease(int n)
{
    num -= n;
}
double Thing::getValueSum()
{
    return value * num;
}
/*//////////////////////////////////////////////////////////////////////////////////
 *函数名：menu
 *功  能：显示程序菜单，并返回用户的选择。
 *参  数：空
 *返回值：一个整形变量，表示用户的选择。
 *作  者：何相龙
 *版  本：1.1
 *日  期：2015-11-04
 *描  述：修改并美化菜单界面。
 *版  本：1.0
 *日  期：2015-11-04
 *描  述：创建菜单。
*///////////////////////////////////////////////////////////////////////////////////
int menu()
{
    system("cls");
    cout  << endl  << endl << "\t\t\t\t欢迎使用器件管理系统" << endl  << endl;
    cout << "----------------------------------------------------------------------------" << endl << endl;
    cout << "\t1.录入器件信息" << endl << "\t2.删除已有器件" << endl << "\t3.查询器件信息" << endl;
    cout << "\t4.修改器件信息" << endl << "\t5.器件出库与入库" << endl<< "\t6.从文件读入数据" << endl;
    cout << "\t7.保存数据到文件" << endl << "\t0.退出系统" << endl << endl << endl;
    cout << "请选择您要进行的操作：";
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
    cout << "您确定要退出本系统吗？所有未保存的数据将丢失！" << endl;
    cout << "确定请输入Y，取消请输入N：";
    char t = ' ';
    while(t == ' ' || t == '\n' || t == '\r')
        cin >> t;
    if(t == 'y' || t == 'Y')
        return true;
    else return false;
}
/*//////////////////////////////////////////////////////////////////////////////////
 *函数名：Devices_new
 *功  能：录入新器件信息，创建新器件
 *参  数：空
 *返回值：无
 *作  者：何相龙
 *版  本：1.0
 *日  期：2015-11-04
*///////////////////////////////////////////////////////////////////////////////////
void Devices_new()
{
    throw NotFinishException();
}
/*//////////////////////////////////////////////////////////////////////////////////
 *函数名：Devices_delete
 *功  能：删除器件库中的器件
 *参  数：空
 *返回值：无
 *作  者：何相龙
 *版  本：1.0
 *日  期：2015-11-04
*///////////////////////////////////////////////////////////////////////////////////
void Devices_delete()
{
    throw NotFinishException();
}
/*//////////////////////////////////////////////////////////////////////////////////
 *函数名：Devices_search
 *功  能：查询器件库中的器件
 *参  数：空
 *返回值：无
 *作  者：何相龙
 *版  本：1.0
 *日  期：2015-11-04
*///////////////////////////////////////////////////////////////////////////////////
void Devices_search()
{
    throw NotFinishException();
}
/*//////////////////////////////////////////////////////////////////////////////////
 *函数名：Devices_change
 *功  能：修改器件库中的器件信息
 *参  数：空
 *返回值：无
 *作  者：何相龙
 *版  本：1.0
 *日  期：2015-11-04
*///////////////////////////////////////////////////////////////////////////////////
void Devices_change()
{
    throw NotFinishException();
}
/*//////////////////////////////////////////////////////////////////////////////////
 *函数名：Devices_new
 *功  能：器件的进出库操作
 *参  数：空
 *返回值：无
 *作  者：何相龙
 *版  本：1.0
 *日  期：2015-11-04
*///////////////////////////////////////////////////////////////////////////////////
void Devices_io()
{
    throw NotFinishException();
}
/*//////////////////////////////////////////////////////////////////////////////////
 *函数名：File_read
 *功  能：从文件读取信息
 *参  数：空
 *返回值：无
 *作  者：何相龙
 *版  本：1.0
 *日  期：2015-11-04
*///////////////////////////////////////////////////////////////////////////////////
void File_read()
{
    throw NotFinishException();
}
/*//////////////////////////////////////////////////////////////////////////////////
 *函数名：File_write
 *功  能：保存信息到文件
 *参  数：空
 *返回值：无
 *作  者：何相龙
 *版  本：1.0
 *日  期：2015-11-04
*///////////////////////////////////////////////////////////////////////////////////
void File_write()
{
    throw NotFinishException();
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
            default:
                {
                    cout << "输入有误，请重新输入。" << endl;
                    system("pause");
                    menu();
                    break;
                }
        }
    }
    return 0;
}
