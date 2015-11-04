#include<iostream>
#include<fstream>
#include<cstdlib>
#include<stdexcept>
#include<exception>
using namespace std;
/*//////////////////////////////////////////////////////////////////////////////////
 *��  ����NotFinishException
 *��  �ܣ�����δ����쳣��
 *��  �ߣ�������
 *��  ����1.0
 *��  �ڣ�2015-11-04
*///////////////////////////////////////////////////////////////////////////////////
class NotFinishException: public exception
{
public:
    NotFinishException() throw() { }
    virtual ~NotFinishException() throw(){ }
    NotFinishException(string msg) throw(){message = msg;}
    const char *what() const throw();
private:
    string message;
};
const char * NotFinishException::what() const throw()
{
    return "�ù���δ���";
}
/*//////////////////////////////////////////////////////////////////////////////////
 *��  ����NoValueException
 *��  �ܣ�����Ӧ�����쳣��
 *��  �ߣ�������
 *��  ����1.1
 *��  �ڣ�2015-11-04
 *˵  ���������쳣�ı�ע
 *��  ����1.0
 *��  �ڣ�2015-11-04
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
    return "�ö���û����Ӧ����";
}
/*//////////////////////////////////////////////////////////////////////////////////
 *��  ����Base
 *��  �ܣ���������Ϣ���ࡣ
 *��  �ߣ�������
 *��  ����1.0
 *��  �ڣ�2015-11-04
*///////////////////////////////////////////////////////////////////////////////////
class Base
{
public:
    string name;    //������������
    virtual void increase(int n) const;   //������⣨n��������
    virtual void decrease(int n) const;   //�������⣨n��������
    virtual double getValueSum() const;   //��ȡ���������ܼ�ֵ�����أ��ܼ�ֵ��
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
 *��  ����Thing_withoutNum
 *��  �ܣ��洢��������һ��������Ϣ��
 *��  �ߣ�������
 *��  ����1.0
 *��  �ڣ�2015-11-04
*///////////////////////////////////////////////////////////////////////////////////
class Thing_withoutNum: public Base
{
public:
    double value;       //��������
    double getValueSum();   //��ȡ���������ܼ�ֵ�����أ��ܼ�ֵ��
};
double Thing_withoutNum::getValueSum()
{
    return value;
}
/*//////////////////////////////////////////////////////////////////////////////////
 *��  ����Thing_withoutValue
 *��  �ܣ��洢�������޼�ֵ������Ϣ��
 *��  �ߣ�������
 *��  ����1.0
 *��  �ڣ�2015-11-04
*///////////////////////////////////////////////////////////////////////////////////
class Thing_withoutValue: public Base
{
public:
    int num;            //�������
    void increase(int n);   //������⣨n��������
    void decrease(int n);   //�������⣨n��������
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
 *��  ����Thing
 *��  �ܣ��洢��������Ϣ��
 *��  �ߣ�������
 *��  ����1.1
 *��  �ڣ�2015-11-04
 *��  �����������࣬��Ϊ�ӻ���̳С�
 *��  ����1.0
 *��  �ڣ�2015-11-04
*///////////////////////////////////////////////////////////////////////////////////
class Thing: public Base
{
public:
    int num;            //�������
    double value;       //��������
    void increase(int n);   //������⣨n��������
    void decrease(int n);   //�������⣨n��������
    double getValueSum();   //��ȡ���������ܼ�ֵ�����أ��ܼ�ֵ��
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
 *��������Things
 *��  �ܣ��洢����������Ϣ
 *��  �ߣ�������
 *��  ����1.0
 *��  �ڣ�2015-11-04
*///////////////////////////////////////////////////////////////////////////////////
struct Things{
        Base* thing;
        Things* next = NULL;
    }head;
/*//////////////////////////////////////////////////////////////////////////////////
 *��������menu
 *��  �ܣ���ʾ����˵����������û���ѡ��
 *��  ������
 *����ֵ��һ�����α�������ʾ�û���ѡ��
 *��  �ߣ�������
 *��  ����1.1
 *��  �ڣ�2015-11-04
 *��  �����޸Ĳ������˵����档
 *��  ����1.0
 *��  �ڣ�2015-11-04
 *��  ���������˵���
*///////////////////////////////////////////////////////////////////////////////////
int menu()
{
    system("cls");
    cout  << endl  << endl << "\t\t\t\t��ӭʹ����������ϵͳ" << endl  << endl;
    cout << "----------------------------------------------------------------------------" << endl << endl;
    cout << "\t1.¼��������Ϣ" << endl << "\t2.ɾ����������" << endl << "\t3.��ѯ������Ϣ" << endl;
    cout << "\t4.�޸�������Ϣ" << endl << "\t5.�������������" << endl<< "\t6.���ļ���������" << endl;
    cout << "\t7.�������ݵ��ļ�" << endl << "\t0.�˳�ϵͳ" << endl << endl << endl;
    cout << "��ѡ����Ҫ���еĲ�����";
    int n;
    cin >> n;
    return n;
}
/*//////////////////////////////////////////////////////////////////////////////////
 *��������Exit_confirm
 *��  �ܣ���ʾ�����˳�ȷ�ϣ������û���ѡ��
 *��  ������
 *����ֵ��һ���߼��ͱ�������ʾ�û���ѡ��
 *��  �ߣ�������
 *��  ����1.0
 *��  �ڣ�2015-11-04
*///////////////////////////////////////////////////////////////////////////////////
bool Exit_confirm()
{
    system("cls");
    cout << "��ȷ��Ҫ�˳���ϵͳ������δ��������ݽ���ʧ��" << endl;
    cout << "ȷ��������Y��ȡ��������N��";
    char t = ' ';
    while(t == ' ' || t == '\n' || t == '\r')
        cin >> t;
    if(t == 'y' || t == 'Y')
        return true;
    else return false;
}
/*//////////////////////////////////////////////////////////////////////////////////
 *��������CheckName
 *��  �ܣ�����������Ƿ���Ϲ淶���������Ƿ��Ѵ���
 *��  ����һ���ַ�����������
 *����ֵ��һ���߼�ֵ��true��ʾ���Ʒ��Ϲ淶��
 *��  �ߣ�������
 *��  ����1.0
 *��  �ڣ�2015-11-04
*///////////////////////////////////////////////////////////////////////////////////
bool CheckName(string name)
{
    throw NotFinishException();
}
/*//////////////////////////////////////////////////////////////////////////////////
 *��������Devices_new
 *��  �ܣ�¼����������Ϣ������������
 *��  ������
 *����ֵ����
 *��  �ߣ�������
 *��  ����1.0
 *��  �ڣ�2015-11-04
*///////////////////////////////////////////////////////////////////////////////////
void Devices_new()
{
    system("cls");
    cout << endl << "��ѡ���������ͣ�1.��ͨ������2.�������ֵ��������3.��һ�޶���������4.��һ�޶����޼�ֵ��������0.���أ���";
    int t;
    cin >> t;
    switch(t)
    {
        case(0):return ;
        case(1):
            {
                string name;
                int num;
                double value;
                lable1:
                cout << "���������������ƣ�";
                cin >> name;
                if(!CheckName(name))goto lable1;
                lable2:
                cout << "������������������";
                cin >> num;
                if(num <= 0)goto lable2;
                lable3:
                cout << "�����������ļ�ֵ��";
                cin >> value;
                if(value <= 0)goto lable3;

                Things* p = &head;
                Things add;
                while(p -> next)
                    p = p -> next;
                p -> next = &add;

                Thing* a = new Thing();
                a -> name = name;
                a -> num = num;
                a -> value = value;

                add.thing = a;
                return;
            }
        case(2):
            {
                string name;
                int num;
                lable4:
                cout << "���������������ƣ�";
                cin >> name;
                if(!CheckName(name))goto lable4;
                lable5:
                cout << "������������������";
                cin >> num;
                if(num <= 0)goto lable5;

                Things* p = &head;
                Things add;
                while(p -> next)
                    p = p -> next;
                p -> next = &add;

                Thing_withoutValue* a = new Thing_withoutValue();
                a -> name = name;
                a -> num = num;

                add.thing = a;
                return;
            }
        case(3):
            {
                string name;
                double value;
                lable6:
                cout << "���������������ƣ�";
                cin >> name;
                if(!CheckName(name))goto lable6;
                lable7:
                cout << "�����������ļ�ֵ��";
                cin >> value;
                if(value <= 0)goto lable7;

                Things* p = &head;
                Things add;
                while(p -> next)
                    p = p -> next;
                p -> next = &add;

                Thing_withoutNum* a = new Thing_withoutNum();
                a -> name = name;
                a -> value = value;

                add.thing = a;
                return;
            }
        case(4):
            {
                string name;
                lable8:
                cout << "���������������ƣ�";
                cin >> name;
                if(!CheckName(name))goto lable8;

                Things* p = &head;
                Things add;
                while(p -> next)
                    p = p -> next;
                p -> next = &add;

                Base* a = new Base();
                a -> name = name;

                add.thing = a;
                return;
            }
        default:
            {
                 cout << "ѡ������������ѡ��" << endl;
                 Devices_new();
                 return;
            }
    }
}
/*//////////////////////////////////////////////////////////////////////////////////
 *��������Devices_delete
 *��  �ܣ�ɾ���������е�����
 *��  ������
 *����ֵ����
 *��  �ߣ�������
 *��  ����1.0
 *��  �ڣ�2015-11-04
*///////////////////////////////////////////////////////////////////////////////////
void Devices_delete()
{
    throw NotFinishException();
}
/*//////////////////////////////////////////////////////////////////////////////////
 *��������Devices_search
 *��  �ܣ���ѯ�������е�����
 *��  ������
 *����ֵ����
 *��  �ߣ�������
 *��  ����1.0
 *��  �ڣ�2015-11-04
*///////////////////////////////////////////////////////////////////////////////////
void Devices_search()
{
    throw NotFinishException();
}
/*//////////////////////////////////////////////////////////////////////////////////
 *��������Devices_change
 *��  �ܣ��޸��������е�������Ϣ
 *��  ������
 *����ֵ����
 *��  �ߣ�������
 *��  ����1.0
 *��  �ڣ�2015-11-04
*///////////////////////////////////////////////////////////////////////////////////
void Devices_change()
{
    throw NotFinishException();
}
/*//////////////////////////////////////////////////////////////////////////////////
 *��������Devices_new
 *��  �ܣ������Ľ��������
 *��  ������
 *����ֵ����
 *��  �ߣ�������
 *��  ����1.0
 *��  �ڣ�2015-11-04
*///////////////////////////////////////////////////////////////////////////////////
void Devices_io()
{
    throw NotFinishException();
}
/*//////////////////////////////////////////////////////////////////////////////////
 *��������File_read
 *��  �ܣ����ļ���ȡ��Ϣ
 *��  ������
 *����ֵ����
 *��  �ߣ�������
 *��  ����1.0
 *��  �ڣ�2015-11-04
*///////////////////////////////////////////////////////////////////////////////////
void File_read()
{
    throw NotFinishException();
}
/*//////////////////////////////////////////////////////////////////////////////////
 *��������File_write
 *��  �ܣ�������Ϣ���ļ�
 *��  ������
 *����ֵ����
 *��  �ߣ�������
 *��  ����1.0
 *��  �ڣ�2015-11-04
*///////////////////////////////////////////////////////////////////////////////////
void File_write()
{
    throw NotFinishException();
}
/*//////////////////////////////////////////////////////////////////////////////////
 *��������main
 *��  �ܣ�����������
 *��  ������
 *����ֵ��һ�����α�������ʾ��������״̬�������������0����
 *��  �ߣ�������
 *��  ����1.0
 *��  �ڣ�2015-11-04
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
                    cout << "�����������������롣" << endl;
                    system("pause");
                    menu();
                    break;
                }
        }
    }
    return 0;
}
