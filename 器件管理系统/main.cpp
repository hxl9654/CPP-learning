#include "stdafx.h"
#include<iostream>
#include<fstream>
#include<cstdlib>
#include<stdexcept>
#include<exception>
#include<string>

using namespace std;
/*//////////////////////////////////////////////////////////////////////////////////
 *��  ����NotFinishException
 *��  �ܣ�����δ����쳣��
 *��  �ߣ�������
 *��  ����1.0
 *��  �ڣ�2015-11-04
*///////////////////////////////////////////////////////////////////////////////////
class NotFinishException : public exception
{
public:
	NotFinishException() throw() { }
	virtual ~NotFinishException() throw() { }
	NotFinishException(string msg) throw() { message = msg; }
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
class NoValueException : public exception
{
public:
	NoValueException() throw() { }
	virtual ~NoValueException() throw() { }
	NoValueException(string msg) throw() { message = msg; }
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
class ThingBase
{
public:
	string name;    //������������
	int num;        //�������
	double value;   //��������
	virtual void increase(int n);   //������⣨n��������
	virtual void decrease(int n);   //�������⣨n��������
	virtual double getValueSum();   //��ȡ���������ܼ�ֵ�����أ��ܼ�ֵ��
};
void ThingBase::increase(int n)
{
	throw NoValueException("num");
}
void ThingBase::decrease(int n)
{
	throw NoValueException("num");
}
double ThingBase::getValueSum()
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
class Thing_withoutNum : public ThingBase
{
public:
	virtual double getValueSum();   //��ȡ���������ܼ�ֵ�����أ��ܼ�ֵ��
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
class Thing_withoutValue : public ThingBase
{
public:
	virtual void increase(int n);    //������⣨n��������
	virtual void decrease(int n);   //�������⣨n��������
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
class Thing : public ThingBase
{
public:
	virtual void increase(int n);   //������⣨n��������
	virtual void decrease(int n);   //�������⣨n��������
	virtual double getValueSum();    //��ȡ���������ܼ�ֵ�����أ��ܼ�ֵ��
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
struct Things {
	ThingBase* thing;
	int type;
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
	cout << endl << endl << "\t\t\t\t��ӭʹ����������ϵͳ" << endl << endl;
	cout << "----------------------------------------------------------------------------" << endl << endl;
	cout << "\t1.¼��������Ϣ" << endl << "\t2.ɾ����������" << endl << "\t3.��ѯ������Ϣ" << endl;
	cout << "\t4.�޸�������Ϣ" << endl << "\t5.�������������" << endl << "\t6.���ļ���������" << endl;
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
	while (t == ' ' || t == '\n' || t == '\r')
		cin >> t;
	if (t == 'y' || t == 'Y')
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
	if (name == "" || name.length() == 0)
		return false;
	Things* p = head.next;
	while (p)
	{
		if (p->thing->name == name)break;
		p = p->next;
	}
	if (p)
		return false;
	else return true;
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
	switch (t)
	{
	case(0) : return;
	case(1) :
	{
		string name;
		int num;
		double value;
	lable_Devices_new11:
		cout << "���������������ƣ�";
		cin >> name;
		if (!CheckName(name))goto lable_Devices_new11;
	lable_Devices_new12:
		cout << "������������������";
		cin >> num;
		if (num <= 0)goto lable_Devices_new12;
	lable_Devices_new13:
		cout << "�����������ļ�ֵ��";
		cin >> value;
		if (value <= 0)goto lable_Devices_new13;

		Things* p = &head;
		Things* add = (Things*)malloc(sizeof(Things));
		while (p->next)
			p = p->next;
		p->next = add;

		Thing* a = new Thing();
		a->name = name;
		a->num = num;
		a->value = value;

		add->type = 1;
		add->thing = a;
		add->next = NULL;
		return;
	}
	case(2) :
	{
		string name;
		int num;
	lable_Devices_new21:
		cout << "���������������ƣ�";
		cin >> name;
		if (!CheckName(name))goto lable_Devices_new21;
	lable_Devices_new22:
		cout << "������������������";
		cin >> num;
		if (num <= 0)goto lable_Devices_new22;

		Things* p = &head;
		Things* add = (Things*)malloc(sizeof(Things));
		while (p->next)
			p = p->next;
		p->next = add;

		Thing_withoutValue* a = new Thing_withoutValue();
		a->name = name;
		a->num = num;

		add->type = 2;
		add->thing = a;
		add->next = NULL;
		return;
	}
	case(3) :
	{
		string name;
		double value;
	lable_Devices_new31:
		cout << "���������������ƣ�";
		cin >> name;
		if (!CheckName(name))goto lable_Devices_new31;
	lable_Devices_new32:
		cout << "�����������ļ�ֵ��";
		cin >> value;
		if (value <= 0)goto lable_Devices_new32;

		Things* p = &head;
		Things* add = (Things*)malloc(sizeof(Things));
		while (p->next)
			p = p->next;
		p->next = add;

		Thing_withoutNum* a = new Thing_withoutNum();
		a->name = name;
		a->value = value;

		add->type = 3;
		add->thing = a;
		add->next = NULL;
		return;
	}
	case(4) :
	{
		string name;
	lable_Devices_new41:
		cout << "���������������ƣ�";
		cin >> name;
		if (!CheckName(name))goto lable_Devices_new41;

		Things* p = &head;
		Things* add = (Things*)malloc(sizeof(Things));
		while (p->next)
			p = p->next;
		p->next = add;

		ThingBase* a = new ThingBase();
		a->name = name;

		add->type = 4;
		add->thing = a;
		add->next = NULL;
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
	system("cls");
	string name;
	cout << "������Ҫɾ�����������ƣ�";
	cin >> name;

	Things* p = head.next;
	Things* q = &head;
	while (p)
	{
		if (p->thing->name == name)break;
		q = p;
		p = p->next;
	}
	if (p)
	{
		cout << "��ȷ����Ҫɾ������������Ϣ��" << endl;
		cout << "���ƣ�" << p->thing->name << endl;
		if (p->type == 1 || p->type == 2)
			cout << "������" << p->thing->num << endl;
		if (p->type == 1 || p->type == 3)
			cout << "��ֵ��" << p->thing->value << endl;
		cout << "��ȷ��Ҫɾ����������(Y/N):";
		char t;
		cin >> t;
		if (t == 'y' || t == 'Y')
		{
			q->next = p->next;
			free(p);
		}
	}
	else
	{
		cout << "δ�ҵ�������";
		system("pause");
	}
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
	system("cls");
	cout << "��ѡ��Ҫ���еĲ�����" << endl;
	cout << "1.������������嵥��2.��ѯ�ض�������0.�������˵�����";
	int t;
	cin >> t;
	switch (t)
	{
	case(0) : return;
	case(1) :
	{
		system("cls");
		Things* q = head.next;
		while (q)
		{
			cout << "���ƣ�" << q->thing->name << endl;
			if (q->type == 1 || q->type == 2)
				cout << "������" << q->thing->num << endl;
			if (q->type == 1 || q->type == 3)
			{
				cout << "��ֵ��" << q->thing->value << endl;
				cout << "�ܼ�ֵ��" << q->thing->getValueSum() << endl;
			}
			cout << endl << endl;
			q = q->next;
		}
		system("pause");
		return;
	}
	case(2) :
	{
	lable_Devices_search2:
		system("cls");
		cout << "������Ҫ��ѯ����������";
		string name;
		cin >> name;
		Things* p = head.next;
		while (p)
		{
			if (p->thing->name == name)break;
			p = p->next;
		}
		if (p)
		{
			cout << "���ƣ�" << p->thing->name << endl;
			if (p->type == 1 || p->type == 2)
				cout << "������" << p->thing->num << endl;
			if (p->type == 1 || p->type == 3)
			{
				cout << "��ֵ��" << p->thing->value << endl;
				if (p->type == 1)
					cout << "�ܼ�ֵ��" << p->thing->getValueSum() << endl;
			}
			cout << endl << endl;
			system("pause");
			return;
		}
		else
		{
			cout << "û���ҵ��������" << endl;
			system("pause");
			goto lable_Devices_search2;
		}
	}
	default:
	{
		cout << "������������������" << endl;
		system("pause");
		Devices_search();
		return;
	}
	}
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
	while (1)
	{
		int c = menu();
		switch (c)
		{
		case(0) :
		{
			if (Exit_confirm())
				return 0;
			else menu();
			break;
		}
		case(1) : Devices_new(); break;
		case(2) : Devices_delete(); break;
		case(3) : Devices_search(); break;
		case(4) : Devices_change(); break;
		case(5) : Devices_io(); break;
		case(6) : File_read(); break;
		case(7) : File_write(); break;
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
