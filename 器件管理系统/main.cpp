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
 *��������menu
 *��  �ܣ���ʾ����˵����������û���ѡ��
 *��  ������
 *����ֵ��һ�����α�������ʾ�û���ѡ��
 *��  �ߣ�������
 *��  ����1.0
 *��  �ڣ�2015-11-04
*///////////////////////////////////////////////////////////////////////////////////
int menu()
{
    system("cls");
    cout << "��ӭʹ����������ϵͳ����ѡ����Ҫ���еĲ�����" << endl;
    cout << "1.¼����������2.ɾ������������3.��ѯ������Ϣ��4.�޸�������Ϣ��5.������������⡣" << endl;
    cout << "6.���ļ��������ݡ�7.�������ݵ��ļ���0.�˳�ϵͳ��" << endl;
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
    cout << "��ȷ��Ҫ�˳���ϵͳ������δ��������ݽ���ʧ��ȷ��������Y��ȡ��������N��" << end;
    char t = ' ';
    while(t == ' ' || t == '\n' || t == '\r')
        cin >> t;
    if(t == 'y' || t == 'Y')
        return true;
    else return false;
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
            default:WrongInput();menu();break;
        }
    }
    return 0;
}
