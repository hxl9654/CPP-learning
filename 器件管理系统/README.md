# 器件管理系统用户手册  
**作者：何相龙**
## 一、简介  
本系统是一套用于管理器件的轻量级管理系统。有增删查改、出入库、保存数据等功能。  
## 二、运行环境
* Windows 98/XP/7/8/8.1/10 (32/64bit)
* Ubuntu 12.04/14.04
* MS-DOS
* MAC OS
* C++支持的其他平台  

> 注：在非Windows运行环境下，存在不影响功能的跨平台兼容性问题。  

## 三、功能
### 0.主菜单
本系统启动后，自动进入主菜单，用户可以通过键盘输入相应功能编号进行功能选择。如果输入有误，系统将给予相关提示并请求重新输入。  
![](http://i.imgur.com/BOid5gL.png)  
> 图3.0-0 主菜单  

![](http://i.imgur.com/2eAHzI6.png)
> 图3.0-1 输入有误的提示  

### 1.增删查改
##### A.录入器件信息
本系统根据实际管理的需要，将器件分为了普通器件、不计算价值的器件、独一无二的器件、独一无二且不计算价值的器件四大类。根据这四类器件的特征，设计了不同的器件信息录入程序。  

> 1. 普通器件：有名称、数量、价值三个属性
> 2. 不计价值的器件：有名称、数量两个属性
> 3. 独一无二的器件：有名称、价值两个属性
> 4. 独一无二且不计价值的器件：只有名称属性  

![](http://i.imgur.com/JVOZWaf.png)  
> 图3.1-1 器件信息录入  

![](http://i.imgur.com/uNUIek0.png)  
> 图3.1-2 器件信息录入错误的提示  

##### B.删除已有器件
本系统支持从器件库中删除已有的器件，要求用户输入器件名称后，会显示相关信息，并请求用户进行确认。  
![](http://i.imgur.com/7dVTw5i.png)  
> 图3.1-3 删除已有器件  

![](http://i.imgur.com/pGc8xMu.png)
> 图3.1-4 用户输入的器件名不存在时的提示  

##### C.查询器件信息
本系统支持查询所有器件信息和精确查询指定器件信息。  
![](http://i.imgur.com/e6tzCKt.png)   
> 图3.1-5 查询器件信息  

###### a.查询所有已存在的器件
选择该选项，系统将输出数据库中存在的所有器件信息。  
![](http://i.imgur.com/S40oEEU.png)  
> 图3.1-6 查询所有已存在的器件

###### b.精确查询指定器件信息
选择该选项，系统将请求用户输入要查询的器件名，并进行查询。  
![](http://i.imgur.com/6pgKoiS.png)  
> 图3.1-7 精确查询指定器件信息

![](http://i.imgur.com/iX9gDSZ.png)  
> 图3.1-8 器件不存在的提示  

##### D.修改器件信息
本系统支持用户对数据库中存在的器件信息进行修改。用户指定要修改的器件后，将显示该器件的信息，并询问用户要修改的属性。如果该器件没有这个属性，将给出提示。修改成功后，将显示修改后的器件信息。    
![](http://i.imgur.com/V3lkmOb.png)  
> 图3.1-9 修改器件信息

![](http://i.imgur.com/nEAWgww.png)
> 图3.1-10 修改成功后显示的器件信息

![](http://i.imgur.com/HTmLm6O.png)
> 图3.1-11 器件没有相应属性时的提示 

### 2.器件的出库与入库
本系统支持对数据库中有数量属性的器件进行出入库操作。进行出入库操作后，器件数量将改变。
![](http://i.imgur.com/cPvAakx.png)
> 图3.2-0 器件入库

![](http://i.imgur.com/StgcryN.png)
> 图3.2-1 器件出库  

![](http://i.imgur.com/7wTheWh.png)
> 图3.2-2 器件出库时，库存数量不足的提示

![](http://i.imgur.com/1wRmSLO.png)
> 图3.2-3 对物数量属性的器件信息操作时的错误提示

### 3.数据的保存与读取
本系统支持将数据保存到文件和从文件中读取保存的数据。数据存储文件为程序目录下的data.txt文件。
##### A.保存数据到文件
![](http://i.imgur.com/MdxJg9W.png)  
> 图3.3-1 数据保存成功的提示

##### B.从文件读取数据
![](http://i.imgur.com/gWymTLp.png)
> 图3.3-2 数据读取成功的提示

![](http://i.imgur.com/eOREZwo.png)
> 图3.3-3 数据读取失败的提示

### 4.退出系统
在主菜单选择0，将进入退出系统菜单，输入Y即可退出本系统。  
**警告！！！所有未保存的数据将丢失！！！**
![](http://i.imgur.com/2FAlo4T.png)
> 图3.4-0 退出系统

## 四、技术说明
#### 1.数据的存储结构
##### A.本系统采用了带头节点的动态链表进行数据的存储。 
 
```
/*/////////////////////////////////////////////////////////////////////////
 *类型名：Things
 *功  能：存储所有器件信息
 *作  者：何相龙
 *版  本：1.0
 *日  期：2015-11-04
*//////////////////////////////////////////////////////////////////////////
struct Things {
	ThingBase* thing;
	int type;				//1.普通器件；2.不计算价值的器件；3.独一无二的器件；4.独一无二且无价值的器件
	Things* next = NULL;
}head;
```
链表中存储了器件的类型和执行期间对象的指针。  
##### B.器件信息基类（既无价值又独一无二的器件类）
本系统采用了这种最简单的器件作为基类，其他所有种类器件均从本基类派生。
```
/*/////////////////////////////////////////////////////////////////////////
 *类  名：ThingBase
 *功  能：器件的信息基类。
 *作  者：何相龙
 *版  本：1.0
 *日  期：2015-11-04
*//////////////////////////////////////////////////////////////////////////
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
```
##### C.独一无二器件类
独一无二器件类由器件基类派生，并覆盖了基类的虚函数double getValueSum()。
```
/*/////////////////////////////////////////////////////////////////////////
 *类  名：Thing_withoutNum
 *功  能：存储器件（仅一件）的信息。
 *作  者：何相龙
 *版  本：1.0
 *日  期：2015-11-04
*//////////////////////////////////////////////////////////////////////////
class Thing_withoutNum : public ThingBase
{
public:
	virtual double getValueSum();   //获取该器件的总价值（返回：总价值）
};
double Thing_withoutNum::getValueSum()
{
	return value;
}
```
##### D.无价值器件类
无价值器件类由器件基类派生，并覆盖了基类的虚函数void increase(int n)和void decrease(int n)。
```
/*/////////////////////////////////////////////////////////////////////////
 *类  名：Thing_withoutValue
 *功  能：存储器件（无价值）的信息。
 *作  者：何相龙
 *版  本：1.0
 *日  期：2015-11-04
*//////////////////////////////////////////////////////////////////////////
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
```
##### E.普通器件类
普通器件类由器件基类派生，并覆盖了基类的虚函数void increase(int n)、double getValueSum()和void decrease(int n)。
```
/*/////////////////////////////////////////////////////////////////////////
 *类  名：Thing
 *功  能：存储器件的信息。
 *作  者：何相龙
 *版  本：1.1
 *日  期：2015-11-04
 *描  述：建立基类，改为从基类继承。
 *版  本：1.0
 *日  期：2015-11-04
*//////////////////////////////////////////////////////////////////////////
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
```
##### F.多态与虚函数
本程序使用多态与虚函数例子如下，详见B~E：
```
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
```
```
class Thing_withoutNum : public ThingBase
{
public:
	virtual double getValueSum();   //获取该器件的总价值（返回：总价值）
};
double Thing_withoutNum::getValueSum()
{
	return value;
}
```

##### G.存储空间的释放
本程序采用了函数模板void Delete(T)来进行删除相应器件时内存空间的释放。
```
/*/////////////////////////////////////////////////////////////////////////
*函数名：Delete
*功  能：删除对象或机构体，释放内存空间。
*参  数：一个typename型模板指针。
*返回值：空
*作  者：何相龙
*版  本：1.0
*日  期：2015-11-05
*//////////////////////////////////////////////////////////////////////////
template<typename T>
void Delete(T)
{
	free(T);
}
```
#### 2.异常的抛出与捕获
##### A.异常的种类
###### a.NotFinishException
功能未完成编写异常，在开发和功能扩展时使用。
```
/*/////////////////////////////////////////////////////////////////////////
 *类  名：NotFinishException
 *功  能：功能未完成异常。
 *作  者：何相龙
 *版  本：1.1
 *日  期：2015-11-04
 *说  明：增加异常说明。
 *版  本：1.0
 *日  期：2015-11-04
*//////////////////////////////////////////////////////////////////////////
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
```
###### b.NoValueException
器件无相应属性值异常，在对无数量器件进行数量操作、读取无价值器件的价值时抛出。
```
/*/////////////////////////////////////////////////////////////////////////
 *类  名：NoValueException
 *功  能：无相应属性异常。
 *作  者：何相龙
 *版  本：1.1
 *日  期：2015-11-04
 *说  明：增加异常的备注
 *版  本：1.0
 *日  期：2015-11-04
*//////////////////////////////////////////////////////////////////////////
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
```
###### c.underflow_error
算术运算向下溢出，系统自带。
###### d.invalid_argument
向函数传入无效参数，系统自带。
##### B.异常处理举例
###### a.NotFinishException
该异常是中开发过程中提示相应功能未开发完成的，在搭建相应程序框架时增加异常抛出语句，完成该模块编写后删除。故，该异常不进行捕获与处理，直接导致程序崩溃。例如：开发过程中，File_write函数未编写完成，为了消除报错、测试其他模块、同时防止遗忘该模块，编写以下代码。
```
void File_write()
{
    throw NotFinishException();
}
```
###### b.NoValueException
该异常是开发过程中错误调用了非普通器件的相关函数造成，例如：
```
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
```
这是ThingBase类的成员函数。由于该类没有数量、价值属性，所以，调用相关函数时，将抛出异常。目前，程序没有对该异常进行处理。
###### c.underflow_error
该异常是在器件出库操作时，器件库存不足时发生的。发生该异常时，程序将停止出库操作，并给予提示。
```
void Thing_withoutValue::decrease(int n)
{
	if (num < n)
		throw underflow_error("库存不足");
	else num -= n;
}
```
```
catch (underflow_error)
{
	cout << "数量不足。" << endl;
}
```
###### d.invalid_argument
该异常在数据文件读取出错时抛出。发送异常时，程序停止读取数据文件，并进行提示。
```
fin >> name;
if (!CheckName(name))throw invalid_argument("输入文件错误");
fin >> num;
if (num <= 0)throw invalid_argument("输入文件错误");
fin >> value;
if (value <= 0)throw invalid_argument("输入文件错误");
```
```
catch (invalid_argument)
{
	cout << "输入文件格式错误或已损坏，数据读取失败！" << endl;
	system("pause");
	return;
}
```
### 3.输入、输出、清屏与暂停
程序使用iostream::cin进行输入iostream::cout进行输出。system("cls")进行清屏，system("pause")进行暂停。
```
/*/////////////////////////////////////////////////////////////////////////
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
*//////////////////////////////////////////////////////////////////////////
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
```
### 4.cin输入流中非法字符的清除
当用户输入了一个类型错误的数据，程序将清除cin输入流。
```
if (!CheckName(name))
{
	cin.clear();
	cin.ignore();
	goto lable_Devices_new11;
}
```
### 5.器件的查找
本程序采用遍历链表的方式进行器件查找。
```
while (p)
{
	if (p->thing->name == name)break;
	p = p->next;
}
```
### 6.器件的录入
在用户输入器件信息后，系统将分配一个新的内存空间，建立新的链表节点，并插入链表。然后新建器件对象，并初始化器件的属性值。
```
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
```
### 7.器件的修改与删除
先进行器件的查找，然后修改相应属性或删除链表节点、释放内存。
```
cout << "请输入修改后的名称：";
cin >> name;
if (CheckName(name))
	p->thing->name = name;
```
```
if (t == 'y' || t == 'Y')
{
	q->next = p->next;
	free(p);
	cout << "删除成功" << endl;
	system("pause");
}
```
### 8.数据文件的读写
程序对数据文件的读写采用了fstream，具体实现方式为对文件流的操作。
```
ifstream fin(DATA_FILE_NAME);
fin >> name;
fin.close();
```
```
ofstream fout(DATA_FILE_NAME);
fout << 0;
fout.close();
```
##### A.数据文件的写入
将数据以与用户输入格式类似的格式写入到文件。
```
/*/////////////////////////////////////////////////////////////////////////
 *函数名：File_write
 *功  能：保存信息到文件
 *参  数：空
 *返回值：无
 *作  者：何相龙
 *版  本：1.0
 *日  期：2015-11-04
*//////////////////////////////////////////////////////////////////////////
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
```
##### B.数据文件的读取
本程序数据文件的格式与用户录入器件信息的格式类似，故数据文件读取代码与录入器件信息代码类似，本手册不再赘述。
### 9.main函数
本程序main函数仅调用了menu函数获取用户欲进行的操作，然后调用相应函数进行处理。
```
/*/////////////////////////////////////////////////////////////////////////
 *函数名：main
 *功  能：程序主函数
 *参  数：空
 *返回值：一个整形变量，表示程序运行状态（正常情况返回0）。
 *作  者：何相龙
 *版  本：1.0
 *日  期：2015-11-04
*//////////////////////////////////////////////////////////////////////////
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
```

## 五、版本历史
* 2015.11.06 --- 文档1.0版 --- 何相龙