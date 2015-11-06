// *   <ThingsManage>  Copyright (C) <2015>  <Xianglong He>
// *   This program is free software: you can redistribute it and/or modify
// *   it under the terms of the GNU General Public License as published by
// *   the Free Software Foundation, either version 3 of the License, or
// *   (at your option) any later version.
// *
// *   This program is distributed in the hope that it will be useful,
// *   but WITHOUT ANY WARRANTY; without even the implied warranty of
// *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// *   GNU General Public License for more details.
// *
// *   You should have received a copy of the GNU General Public License
// *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
// *
// * @author     Xianglong He
// * @copyright  Copyright (c) 2015 Xianglong He. (http://tec.hxlxz.com)
// * @license    http://www.gnu.org/licenses/     GPL v3
// * @version    1.0
// * @discribe   ��������ϵͳ
// * ����������Ǻ�������ʹ��GPL v3���֤������Ȩ��

#include "stdafx.h"
#include<iostream>
#include<fstream>
#include<cstdlib>
#include<stdexcept>
#include<exception>
#include<string>
using namespace std;

//���ݴ洢�ļ���
#define DATA_FILE_NAME "data.txt"

/*//////////////////////////////////////////////////////////////////////////////////
 *��  ����NotFinishException
 *��  �ܣ�����δ����쳣��
 *��  �ߣ�������
 *��  ����1.1
 *��  �ڣ�2015-11-04
 *˵  ���������쳣˵����
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
 *��  ����ThingBase
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
	if (num < n)
		throw underflow_error("��治��");
	else num -= n;
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
	if (num < n)
		throw underflow_error("��治��");
	else num -= n;
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
	int type;				//1.��ͨ������2.�������ֵ��������3.��һ�޶���������4.��һ�޶����޼�ֵ������
	Things* next = NULL;
}head;
/*//////////////////////////////////////////////////////////////////////////////////
*��������Delete
*��  �ܣ�ɾ�����������壬�ͷ��ڴ�ռ䡣
*��  ����һ��typename��ģ��ָ�롣
*����ֵ����
*��  �ߣ�������
*��  ����1.0
*��  �ڣ�2015-11-05
*///////////////////////////////////////////////////////////////////////////////////
template<typename T>
void Delete(T)
{
	free(T);
}
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
	{
		cin >> t;
		cin.clear();
		cin.ignore();
	}
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
 *��  ����1.1
 *��  �ڣ�2015-11-04
 *˵  �����޸�����ڵ㴴������Ϊ��̬�ڴ���䡣
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
		if (!CheckName(name))
		{
			cin.clear();
			cin.ignore();
			goto lable_Devices_new11;
		}
	lable_Devices_new12:
		cout << "������������������";
		cin >> num;
		if (num <= 0)
		{
			cin.clear();
			cin.ignore();
			goto lable_Devices_new12;
		}
	lable_Devices_new13:
		cout << "�����������ļ�ֵ��";
		fflush(stdin);
		cin >> value;
		if (value <= 0)
		{
			cin.clear();
			cin.ignore();
			goto lable_Devices_new13;
		}

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
		fflush(stdin);
		cin >> name;
		if (!CheckName(name))
		{
			cin.clear();
			cin.ignore();
			goto lable_Devices_new21;
		}
	lable_Devices_new22:
		cout << "������������������";
		fflush(stdin);
		cin >> num;
		if (num <= 0)
		{
			cin.clear();
			cin.ignore();
			goto lable_Devices_new22;
		}

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
		fflush(stdin);
		cin >> name;
		if (!CheckName(name))
		{
			cin.clear();
			cin.ignore();
			goto lable_Devices_new31;
		}
	lable_Devices_new32:
		cout << "�����������ļ�ֵ��";
		fflush(stdin);
		cin >> value;
		if (value <= 0)
		{
			cin.clear();
			cin.ignore();
			goto lable_Devices_new32;
		}

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
		fflush(stdin);
		cin >> name;
		if (!CheckName(name))
		{
			cin.clear();
			cin.ignore();
			goto lable_Devices_new41;
		}

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
		cin.clear();
		cin.ignore();
		system("pause");
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
			cout << "ɾ���ɹ�" << endl;
			system("pause");
		}
	}
	else
	{
		cout << "δ�ҵ�������" << endl;
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
		cin.clear();
		cin.ignore();
		Devices_search();
		return;
	}
	}
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
lable_Devices_change1:
	system("cls");
	cout << "������Ҫ��������������";
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
			cout << "��ֵ��" << p->thing->value << endl;

		cout << endl << endl;
	lable_Devices_change2:
		cout << "��ѡ��Ҫ�޸ĵ���Ϣ���ƣ�N����������Q������ֵ��V����";
		char t;
		cin >> t;
		switch (t)
		{
		case('n') :
		case('N') :
		{
		lable_Devices_change3:
			cout << "�������޸ĺ�����ƣ�";
			string name;
			cin >> name;
			if (CheckName(name))
				p->thing->name = name;
			else goto lable_Devices_change3;
			break;
		}
		case('q') :
		case('Q') :
		{
			if (p->type == 3 || p->type == 4)
			{
				cout << "��������֧�ָò���" << endl;
				system("pause");
				return;
			}
		lable_Devices_change4:
			cout << "�������޸ĺ��������";
			int num;
			cin >> num;
			if (num < 0)
			{
				cin.clear();
				cin.ignore();
				goto lable_Devices_change4;
			}
			p->thing->num = num;
			break;
		}
		case('v') :
		case('V') :
		{
			if (p->type == 2 || p->type == 4)
			{
				cout << "��������֧�ָò���" << endl;
				system("pause");
				return;
			}
		lable_Devices_change5:
			cout << "�������޸ĺ�ļ�ֵ��";
			double value;
			cin >> value;
			if (value <= 0)
			{
				cin.clear();
				cin.ignore();
				goto lable_Devices_change5;
			}

			p->thing->value = value;
			break;
		}
		default:goto lable_Devices_change2;
		}
		system("cls");
		cout << "�޸ĺ�" << endl << endl;
		cout << "���ƣ�" << p->thing->name << endl;
		if (p->type == 1 || p->type == 2)
			cout << "������" << p->thing->num << endl;
		if (p->type == 1 || p->type == 3)
			cout << "��ֵ��" << p->thing->value << endl;

		cout << endl << endl;

		system("pause");
		return;
	}
	else
	{
		cout << "û���ҵ��������" << endl;
		system("pause");
		goto lable_Devices_change1;
	}
}
/*//////////////////////////////////////////////////////////////////////////////////
 *��������Devices_io
 *��  �ܣ������Ľ��������
 *��  ������
 *����ֵ����
 *��  �ߣ�������
 *��  ����1.0
 *��  �ڣ�2015-11-04
*///////////////////////////////////////////////////////////////////////////////////
void Devices_io()
{
lable_Devices_io1:
	system("cls");
	cout << "������Ҫ��������������";
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
		else
		{
			cout << "��������֧�ִ˲���" << endl;
			system("pause");
			return;
		}
	lable_Devices_io2:
		cout << "��ѡ����⣨O������⣨I����";
		char t;
		cin >> t;
		if (t != 'i'&&t != 'I'&&t != 'o'&&t != 'O')
		{
			cin.clear();
			cin.ignore();
			goto lable_Devices_io2;
		}
	lable_Devices_io3:
		cout << "������������";
		int n;
		cin >> n;
		if (n < 0)
		{
			cin.clear();
			cin.ignore();
			goto lable_Devices_io3;
		}
		if (t == 'i' || t == 'I')
			p->thing->increase(n);
		else
			try {
			p->thing->decrease(n);
		}
		catch (underflow_error)
		{
			cout << "�������㡣" << endl;
		}
		cout << "������" << p->thing->num << endl << endl;
		system("pause");
		return;
	}
	else
	{
		cout << "û���ҵ��������" << endl;
		system("pause");
		goto lable_Devices_io1;
	}
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
	system("cls");
	ifstream fin(DATA_FILE_NAME);
	int t;
	while (1)
	{
		try
		{
			fin >> t;
			switch (t)
			{
			case(0) : break;
			case(1) :
			{
				string name;
				int num;
				double value;
				fin >> name;
				if (!CheckName(name))throw invalid_argument("�����ļ�����");
				fin >> num;
				if (num <= 0)throw invalid_argument("�����ļ�����");
				fin >> value;
				if (value <= 0)throw invalid_argument("�����ļ�����");

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
				break;
			}
			case(2) :
			{
				string name;
				int num;
				fin >> name;
				if (!CheckName(name))throw invalid_argument("�����ļ�����");
				fin >> num;
				if (num <= 0)throw invalid_argument("�����ļ�����");

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
				break;
			}
			case(3) :
			{
				string name;
				double value;
				fin >> name;
				if (!CheckName(name))throw invalid_argument("�����ļ�����");
				fin >> value;
				if (value <= 0)throw invalid_argument("�����ļ�����");

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
				break;
			}
			case(4) :
			{
				string name;
				fin >> name;
				if (!CheckName(name))throw invalid_argument("�����ļ�����");

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
				break;
			}
			default:
			{
				throw invalid_argument("�����ļ�����");
			}
			}
		}
		catch (invalid_argument)
		{
			cout << "�����ļ���ʽ��������𻵣����ݶ�ȡʧ�ܣ�" << endl;
			system("pause");
			return;
		}
		if (t == 0)break;
	}
	cout << "���ݶ���ɹ���" << endl;
	fin.close();
	system("pause");
	return;
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
	system("cls");
	Things* p = head.next;
	ofstream fout(DATA_FILE_NAME);
	while (p)
	{
		switch (p->type)
		{
		case(1) : fout << 1 << endl << p->thing->name << endl << p->thing->num << endl << p->thing->value << endl; break;
		case(2) : fout << 2 << endl << p->thing->name << endl << p->thing->num << endl; break;
		case(3) : fout << 3 << endl << p->thing->name << endl << p->thing->value << endl; break;
		case(4) : fout << 4 << endl << p->thing->name << endl; break;
		default:break;
		}
		p = p->next;
	}
	fout << 0;
	cout << "���̳ɹ���" << endl;
	system("pause");
	fout.close();
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
			cin.clear();
			cin.ignore();
			break;
		}
		}
	}
	return 0;
}
