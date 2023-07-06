#include <iostream>
using namespace std;

#define MAX 100
//设计联系人结构体
struct Person
{
	//姓名
	string m_Name;
	//性别
	int m_Sex;
	//年龄
	int m_Age;
	//电话
	string m_Phone;
	//住址
	string m_Addr;
};

//设计通讯录结构体
struct Addressbooks
{
	//通讯录中保存的联系人数组
	struct Person personArray[MAX];
	//通讯录中当前记录联系人个数
	int m_Size;
};
//1、添加联系人
void addPerson(Addressbooks* abs) {
	//判断通讯录是否已满，如果满了就不再添加
	if (abs->m_Size == MAX) {
	cout<<"通讯录已满，无法添加！"<<endl;
	return;
	}
	else {
		//添加具体联系人

		//姓名
		string name;
		cout << "请输入姓名：" << endl;
		cin >> name;
		abs->personArray[abs->m_Size].m_Name = name;


		//性别
		int sex;
		cout << "请输入性别：" << endl;
		cout << "1 --- 男" << endl;
		cout << "2 --- 女" << endl;
		cout << "3 --- 其他" << endl;
		cout << "请选择：" << endl;
		cin >> sex;
		abs->personArray[abs->m_Size].m_Sex = sex;

		//年龄
		int age;
		cout << "请输入年龄：" << endl;
		cin >> age;
		abs->personArray[abs->m_Size].m_Age = age;

		//电话
		string phone;
		cout << "请输入联系电话：" << endl;
		cin >> phone;
		abs->personArray[abs->m_Size].m_Phone = phone;

		//住址
		string address;
		cout << "请输入家庭住址：" << endl;
		cin >> address;
		abs->personArray[abs->m_Size].m_Addr = address;

		//更新通讯录人数
		abs->m_Size++;
		cout << "添加成功！" << endl;

		system("pause");
		system("cls");//清屏操作0
	}
}
//2、显示所有联系人
void showPerson(Addressbooks* abs) {
	//判断通讯录中人数是否为0，如果为0，提示记录为空
	if (abs->m_Size == 0) {
		cout<<"当前记录为空"<<endl;
	}
	//如果不为0，显示记录的联系人信息
	else
	{
		for(int i=0;i<abs->m_Size;i++)
		{
			cout<<"姓名："<<abs->personArray[i].m_Name<<"\t";
			if (abs->personArray[i].m_Sex==1)
			{
				cout << "性别:男"  << "\t";
			}
			else
			if (abs->personArray[i].m_Sex == 2)
			{
				cout << "性别:女" << "\t";
			}
			else
			{
				cout << "性别:未知" << "\t";
			}
			cout<<"年龄:"<<abs->personArray[i].m_Age<<"\t";
			cout<<"电话:"<<abs->personArray[i].m_Phone<<"\t";
			cout<<"住址:"<<abs->personArray[i].m_Addr<<endl;
		}
		system("pause");
		system("cls");//清屏操作0
	}
}
//查找指定联系人的下标
int isIndex(string name, Addressbooks* abs)
{
	//查找指定联系人的下标
	int index = 0;
	for (int i = 0; i < abs->m_Size; i++)
	{
		if (abs->personArray[i].m_Name == name)
		{
			index = i;
			return index;
		}
		else
		{
			cout << "查无此人" << endl;
			system("pause");
			system("cls");//清屏操作0
		}

	}
	return -1;
}
//3、删除指定联系人
void deletePerson(Addressbooks* abs) 
{
	if (abs->m_Size==0)
	{
		cout << "当前记录为空" << endl;
		system("pause");
		system("cls");//清屏操作0
		return; 
	}
	//姓名
	string name;
	cout << "请输入删除联系人的姓名：" << endl;
	cin >> name;
	//查找指定联系人的下标
	int index = isIndex(name, abs);
	//判断index是否为-1，如果为-1，说明查找不到指定联系人
	if (index == -1)
	{
		return;
	}
	//删除指定联系人的信息
	for (int i = index; i < abs->m_Size; i++)
	{
		//数据前移
		abs->personArray[i] = abs->personArray[i + 1];
	}
	//更新通讯录中的人员数
	abs->m_Size--;
	cout << "删除成功" << endl;
	system("pause");
	system("cls");//清屏操作0
}
//4、查找指定联系人
void findPerson(Addressbooks* abs)
{
	//姓名
	string name;
	cout << "请输入查找联系人的姓名：" << endl;
	cin >> name;
	//查找指定联系人的下标
	int index = isIndex(name, abs);
	//显示指定联系人的信息
	cout << "姓名：" << abs->personArray[index].m_Name << "\t";
	if (abs->personArray[index].m_Sex == 1)
	{
		cout << "性别:男" << "\t";
	}
	else
		if (abs->personArray[index].m_Sex == 2)
		{
			cout << "性别:女" << "\t";
		}
		else
		{
			cout << "性别:未知" << "\t";
		}
	cout << "年龄:" << abs->personArray[index].m_Age << "\t";
	cout << "电话:" << abs->personArray[index].m_Phone << "\t";
	cout << "住址:" << abs->personArray[index].m_Addr << endl;
	system("pause");
	system("cls");//清屏操作0
}
//5、修改指定联系人
void modifyPerson(Addressbooks*abs)
{

}
//6、清空所有联系人


void showMenu() {
	std::cout << "***** 1、添加联系人 *****\n";
	std::cout << "***** 2、显示联系人 *****\n";
	std::cout << "***** 3、删除联系人 *****\n";
	std::cout << "***** 4、查找联系人 *****\n";
	std::cout << "***** 5、修改联系人 *****\n";
	std::cout << "***** 6、清空联系人 *****\n";
	std::cout << "***** 0、退出通讯录 *****\n";
}

int main()
{
	//创建通讯录结构体变量
	struct Addressbooks abs;
	//初始化通讯录中当前人员个数
	abs.m_Size = 0;

	//用户选择的功能序号
	int select = 0;
	while (true)
	{
		showMenu();
		cin >> select;
		switch (select)
		{
		case 1: //添加联系人
			addPerson(&abs);
			break;
		case 2://显示联系人
			showPerson(&abs);
			break;
		case 3://删除联系人
			deletePerson(&abs);
			break;
		case 4://查找联系人
			findPerson(&abs);
			break;
		case 5://修改联系人
			modifyPerson();
			break;
		case 6://清空联系人
			break;
		case 0://退出通讯录
			cout << "欢迎下次使用" << endl;
			return 0;
			break;
		default:
			break;
		}
	}

}