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
// * @discribe   器件管理系统
// * 本软件作者是何相龙，使用GPL v3许可证进行授权。

#include "stdafx.h"
#include<iostream>
#include<fstream>
#include<cstdlib>
#include<stdexcept>
#include<exception>
#include<string>
using namespace std;

//数据存储文件名
#define DATA_FILE_NAME "data.txt"

/*//////////////////////////////////////////////////////////////////////////////////
 *类  名：NotFinishException
 *功  能：功能未完成异常。
 *作  者：何相龙
 *版  本：1.1
 *日  期：2015-11-04
 *说  明：增加异常说明。
 *版  本：1.0
 *日  期：2015-11-04
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
	return "该对象没有相应属性";
}
/*//////////////////////////////////////////////////////////////////////////////////
 *类  名：ThingBase
 *功  能：器件的信息基类。
 *作  者：何相龙
 *版  本：1.0
 *日  期：2015-11-04
*///////////////////////////////////////////////////////////////////////////////////
class ThingBase
{
public:
	string name;    //该器件的名字
	int num;        //库存数量
	double value;   //器件单价
	virtual void increase(int n);   //器件入库（n：数量）
	virtual void decrease(int n);   //器件出库（n：数量）
	virtual double getValueSum();   //获取该器件的总价值（返回：总价值）
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
 *类  名：Thing_withoutNum
 *功  能：存储器件（仅一件）的信息。
 *作  者：何相龙
 *版  本：1.0
 *日  期：2015-11-04
*///////////////////////////////////////////////////////////////////////////////////
class Thing_withoutNum : public ThingBase
{
public:
	virtual double getValueSum();   //获取该器件的总价值（返回：总价值）
};
double Thing_withoutNum::getValueSum()
{
	return value;
}
/*//////////////////////////////////////////////////////////////////////////////////
 *类  名：Thing_withoutValue
 *功  能：存储器件（无价值）的信息。
 *作  者：何相龙
 *版  本：1.0
 *日  期：2015-11-04
*///////////////////////////////////////////////////////////////////////////////////
class Thing_withoutValue : public ThingBase
{
public:
	virtual void increase(int n);    //器件入库（n：数量）
	virtual void decrease(int n);   //器件出库（n：数量）
};
void Thing_withoutValue::increase(int n)
{
	num += n;
}
void Thing_withoutValue::decrease(int n)
{
	if (num < n)
		throw underflow_error("库存不足");
	else num -= n;
}
/*//////////////////////////////////////////////////////////////////////////////////
 *类  名：Thing
 *功  能：存储器件的信息。
 *作  者：何相龙
 *版  本：1.1
 *日  期：2015-11-04
 *描  述：建立基类，改为从基类继承。
 *版  本：1.0
 *日  期：2015-11-04
*///////////////////////////////////////////////////////////////////////////////////
class Thing : public ThingBase
{
public:
	virtual void increase(int n);   //器件入库（n：数量）
	virtual void decrease(int n);   //器件出库（n：数量）
	virtual double getValueSum();    //获取该器件的总价值（返回：总价值）
};
void Thing::increase(int n)
{
	num += n;
}
void Thing::decrease(int n)
{
	if (num < n)
		throw underflow_error("库存不足");
	else num -= n;
}
double Thing::getValueSum()
{
	return value * num;
}
/*//////////////////////////////////////////////////////////////////////////////////
 *类型名：Things
 *功  能：存储所有器件信息
 *作  者：何相龙
 *版  本：1.0
 *日  期：2015-11-04
*///////////////////////////////////////////////////////////////////////////////////
struct Things {
	ThingBase* thing;
	int type;				//1.普通器件；2.不计算价值的器件；3.独一无二的器件；4.独一无二且无价值的器件
	Things* next = NULL;
}head;
/*//////////////////////////////////////////////////////////////////////////////////
*函数名：Delete
*功  能：删除对象或机构体，释放内存空间。
*参  数：一个typename型模板指针。
*返回值：空
*作  者：何相龙
*版  本：1.0
*日  期：2015-11-05
*///////////////////////////////////////////////////////////////////////////////////
template<typename T>
void Delete(T)
{
	free(T);
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
	cout << endl << endl << "\t\t\t\t欢迎使用器件管理系统" << endl << endl;
	cout << "----------------------------------------------------------------------------" << endl << endl;
	cout << "\t1.录入器件信息" << endl << "\t2.删除已有器件" << endl << "\t3.查询器件信息" << endl;
	cout << "\t4.修改器件信息" << endl << "\t5.器件出库与入库" << endl << "\t6.从文件读入数据" << endl;
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
 *函数名：CheckName
 *功  能：检查器件名是否符合规范、器件名是否已存在
 *参  数：一个字符串，器件名
 *返回值：一个逻辑值，true表示名称符合规范。
 *作  者：何相龙
 *版  本：1.0
 *日  期：2015-11-04
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
 *函数名：Devices_new
 *功  能：录入新器件信息，创建新器件
 *参  数：空
 *返回值：无
 *作  者：何相龙
 *版  本：1.1
 *日  期：2015-11-04
 *说  明：修改链表节点创建方法为动态内存分配。
 *版  本：1.0
 *日  期：2015-11-04
*///////////////////////////////////////////////////////////////////////////////////
void Devices_new()
{
	system("cls");
	cout << endl << "请选择器件类型（1.普通器件；2.不计算价值的器件；3.独一无二的器件；4.独一无二且无价值的器件；0.返回）：";
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
		cout << "请输入器件的名称：";
		cin >> name;
		if (!CheckName(name))
		{
			cin.clear();
			cin.ignore();
			goto lable_Devices_new11;
		}
	lable_Devices_new12:
		cout << "请输入器件的数量：";
		cin >> num;
		if (num <= 0)
		{
			cin.clear();
			cin.ignore();
			goto lable_Devices_new12;
		}
	lable_Devices_new13:
		cout << "请输入器件的价值：";
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
		cout << "请输入器件的名称：";
		fflush(stdin);
		cin >> name;
		if (!CheckName(name))
		{
			cin.clear();
			cin.ignore();
			goto lable_Devices_new21;
		}
	lable_Devices_new22:
		cout << "请输入器件的数量：";
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
		cout << "请输入器件的名称：";
		fflush(stdin);
		cin >> name;
		if (!CheckName(name))
		{
			cin.clear();
			cin.ignore();
			goto lable_Devices_new31;
		}
	lable_Devices_new32:
		cout << "请输入器件的价值：";
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
		cout << "请输入器件的名称：";
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
		cout << "选择有误，请重新选择" << endl;
		cin.clear();
		cin.ignore();
		system("pause");
		Devices_new();
		return;
	}
	}
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
	system("cls");
	string name;
	cout << "请输入要删除的器件名称：";
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
		cout << "请确认你要删除的器件的信息：" << endl;
		cout << "名称：" << p->thing->name << endl;
		if (p->type == 1 || p->type == 2)
			cout << "数量：" << p->thing->num << endl;
		if (p->type == 1 || p->type == 3)
			cout << "价值：" << p->thing->value << endl;
		cout << "你确定要删除该器件吗？(Y/N):";
		char t;
		cin >> t;
		if (t == 'y' || t == 'Y')
		{
			q->next = p->next;
			free(p);
			cout << "删除成功" << endl;
			system("pause");
		}
	}
	else
	{
		cout << "未找到该器件" << endl;
		system("pause");
	}
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
	system("cls");
	cout << "请选择要进行的操作。" << endl;
	cout << "1.输出所有器件清单；2.查询特定器件；0.返回主菜单。：";
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
			cout << "名称：" << q->thing->name << endl;
			if (q->type == 1 || q->type == 2)
				cout << "数量：" << q->thing->num << endl;
			if (q->type == 1 || q->type == 3)
			{
				cout << "价值：" << q->thing->value << endl;
				cout << "总价值：" << q->thing->getValueSum() << endl;
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
		cout << "请输入要查询的器件名：";
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
			cout << "名称：" << p->thing->name << endl;
			if (p->type == 1 || p->type == 2)
				cout << "数量：" << p->thing->num << endl;
			if (p->type == 1 || p->type == 3)
			{
				cout << "价值：" << p->thing->value << endl;
				if (p->type == 1)
					cout << "总价值：" << p->thing->getValueSum() << endl;
			}
			cout << endl << endl;
			system("pause");
			return;
		}
		else
		{
			cout << "没有找到这个器件" << endl;
			system("pause");
			goto lable_Devices_search2;
		}
	}
	default:
	{
		cout << "输入有误，请重新输入" << endl;
		system("pause");
		cin.clear();
		cin.ignore();
		Devices_search();
		return;
	}
	}
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
lable_Devices_change1:
	system("cls");
	cout << "请输入要操作的器件名：";
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
		cout << "名称：" << p->thing->name << endl;
		if (p->type == 1 || p->type == 2)
			cout << "数量：" << p->thing->num << endl;
		if (p->type == 1 || p->type == 3)
			cout << "价值：" << p->thing->value << endl;

		cout << endl << endl;
	lable_Devices_change2:
		cout << "请选择要修改的信息名称（N），数量（Q），价值（V）：";
		char t;
		cin >> t;
		switch (t)
		{
		case('n') :
		case('N') :
		{
		lable_Devices_change3:
			cout << "请输入修改后的名称：";
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
				cout << "该器件不支持该操作" << endl;
				system("pause");
				return;
			}
		lable_Devices_change4:
			cout << "请输入修改后的数量：";
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
				cout << "该器件不支持该操作" << endl;
				system("pause");
				return;
			}
		lable_Devices_change5:
			cout << "请输入修改后的价值：";
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
		cout << "修改后：" << endl << endl;
		cout << "名称：" << p->thing->name << endl;
		if (p->type == 1 || p->type == 2)
			cout << "数量：" << p->thing->num << endl;
		if (p->type == 1 || p->type == 3)
			cout << "价值：" << p->thing->value << endl;

		cout << endl << endl;

		system("pause");
		return;
	}
	else
	{
		cout << "没有找到这个器件" << endl;
		system("pause");
		goto lable_Devices_change1;
	}
}
/*//////////////////////////////////////////////////////////////////////////////////
 *函数名：Devices_io
 *功  能：器件的进出库操作
 *参  数：空
 *返回值：无
 *作  者：何相龙
 *版  本：1.0
 *日  期：2015-11-04
*///////////////////////////////////////////////////////////////////////////////////
void Devices_io()
{
lable_Devices_io1:
	system("cls");
	cout << "请输入要操作的器件名：";
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
		cout << "名称：" << p->thing->name << endl;
		if (p->type == 1 || p->type == 2)
			cout << "数量：" << p->thing->num << endl;
		else
		{
			cout << "该器件不支持此操作" << endl;
			system("pause");
			return;
		}
	lable_Devices_io2:
		cout << "请选择出库（O），入库（I）：";
		char t;
		cin >> t;
		if (t != 'i'&&t != 'I'&&t != 'o'&&t != 'O')
		{
			cin.clear();
			cin.ignore();
			goto lable_Devices_io2;
		}
	lable_Devices_io3:
		cout << "请输入数量：";
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
			cout << "数量不足。" << endl;
		}
		cout << "数量：" << p->thing->num << endl << endl;
		system("pause");
		return;
	}
	else
	{
		cout << "没有找到这个器件" << endl;
		system("pause");
		goto lable_Devices_io1;
	}
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
				if (!CheckName(name))throw invalid_argument("输入文件错误");
				fin >> num;
				if (num <= 0)throw invalid_argument("输入文件错误");
				fin >> value;
				if (value <= 0)throw invalid_argument("输入文件错误");

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
				if (!CheckName(name))throw invalid_argument("输入文件错误");
				fin >> num;
				if (num <= 0)throw invalid_argument("输入文件错误");

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
				if (!CheckName(name))throw invalid_argument("输入文件错误");
				fin >> value;
				if (value <= 0)throw invalid_argument("输入文件错误");

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
				if (!CheckName(name))throw invalid_argument("输入文件错误");

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
				throw invalid_argument("输入文件错误");
			}
			}
		}
		catch (invalid_argument)
		{
			cout << "输入文件格式错误或已损坏，数据读取失败！" << endl;
			system("pause");
			return;
		}
		if (t == 0)break;
	}
	cout << "数据读入成功！" << endl;
	fin.close();
	system("pause");
	return;
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
	cout << "存盘成功！" << endl;
	system("pause");
	fout.close();
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
			cout << "输入有误，请重新输入。" << endl;
			system("pause");
			cin.clear();
			cin.ignore();
			break;
		}
		}
	}
	return 0;
}
