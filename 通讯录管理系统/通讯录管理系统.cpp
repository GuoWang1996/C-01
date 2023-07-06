#include <iostream>
using namespace std;

#define MAX 100
//�����ϵ�˽ṹ��
struct Person
{
	//����
	string m_Name;
	//�Ա�
	int m_Sex;
	//����
	int m_Age;
	//�绰
	string m_Phone;
	//סַ
	string m_Addr;
};

//���ͨѶ¼�ṹ��
struct Addressbooks
{
	//ͨѶ¼�б������ϵ������
	struct Person personArray[MAX];
	//ͨѶ¼�е�ǰ��¼��ϵ�˸���
	int m_Size;
};
//1�������ϵ��
void addPerson(Addressbooks* abs) {
	//�ж�ͨѶ¼�Ƿ�������������˾Ͳ������
	if (abs->m_Size == MAX) {
	cout<<"ͨѶ¼�������޷���ӣ�"<<endl;
	return;
	}
	else {
		//��Ӿ�����ϵ��

		//����
		string name;
		cout << "������������" << endl;
		cin >> name;
		abs->personArray[abs->m_Size].m_Name = name;


		//�Ա�
		int sex;
		cout << "�������Ա�" << endl;
		cout << "1 --- ��" << endl;
		cout << "2 --- Ů" << endl;
		cout << "3 --- ����" << endl;
		cout << "��ѡ��" << endl;
		cin >> sex;
		abs->personArray[abs->m_Size].m_Sex = sex;

		//����
		int age;
		cout << "���������䣺" << endl;
		cin >> age;
		abs->personArray[abs->m_Size].m_Age = age;

		//�绰
		string phone;
		cout << "��������ϵ�绰��" << endl;
		cin >> phone;
		abs->personArray[abs->m_Size].m_Phone = phone;

		//סַ
		string address;
		cout << "�������ͥסַ��" << endl;
		cin >> address;
		abs->personArray[abs->m_Size].m_Addr = address;

		//����ͨѶ¼����
		abs->m_Size++;
		cout << "��ӳɹ���" << endl;

		system("pause");
		system("cls");//��������0
	}
}
//2����ʾ������ϵ��
void showPerson(Addressbooks* abs) {
	//�ж�ͨѶ¼�������Ƿ�Ϊ0�����Ϊ0����ʾ��¼Ϊ��
	if (abs->m_Size == 0) {
		cout<<"��ǰ��¼Ϊ��"<<endl;
	}
	//�����Ϊ0����ʾ��¼����ϵ����Ϣ
	else
	{
		for(int i=0;i<abs->m_Size;i++)
		{
			cout<<"������"<<abs->personArray[i].m_Name<<"\t";
			if (abs->personArray[i].m_Sex==1)
			{
				cout << "�Ա�:��"  << "\t";
			}
			else
			if (abs->personArray[i].m_Sex == 2)
			{
				cout << "�Ա�:Ů" << "\t";
			}
			else
			{
				cout << "�Ա�:δ֪" << "\t";
			}
			cout<<"����:"<<abs->personArray[i].m_Age<<"\t";
			cout<<"�绰:"<<abs->personArray[i].m_Phone<<"\t";
			cout<<"סַ:"<<abs->personArray[i].m_Addr<<endl;
		}
		system("pause");
		system("cls");//��������0
	}
}
//����ָ����ϵ�˵��±�
int isIndex(string name, Addressbooks* abs)
{
	//����ָ����ϵ�˵��±�
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
			cout << "���޴���" << endl;
			system("pause");
			system("cls");//��������0
		}

	}
	return -1;
}
//3��ɾ��ָ����ϵ��
void deletePerson(Addressbooks* abs) 
{
	if (abs->m_Size==0)
	{
		cout << "��ǰ��¼Ϊ��" << endl;
		system("pause");
		system("cls");//��������0
		return; 
	}
	//����
	string name;
	cout << "������ɾ����ϵ�˵�������" << endl;
	cin >> name;
	//����ָ����ϵ�˵��±�
	int index = isIndex(name, abs);
	//�ж�index�Ƿ�Ϊ-1�����Ϊ-1��˵�����Ҳ���ָ����ϵ��
	if (index == -1)
	{
		return;
	}
	//ɾ��ָ����ϵ�˵���Ϣ
	for (int i = index; i < abs->m_Size; i++)
	{
		//����ǰ��
		abs->personArray[i] = abs->personArray[i + 1];
	}
	//����ͨѶ¼�е���Ա��
	abs->m_Size--;
	cout << "ɾ���ɹ�" << endl;
	system("pause");
	system("cls");//��������0
}
//4������ָ����ϵ��
void findPerson(Addressbooks* abs)
{
	//����
	string name;
	cout << "�����������ϵ�˵�������" << endl;
	cin >> name;
	//����ָ����ϵ�˵��±�
	int index = isIndex(name, abs);
	//��ʾָ����ϵ�˵���Ϣ
	cout << "������" << abs->personArray[index].m_Name << "\t";
	if (abs->personArray[index].m_Sex == 1)
	{
		cout << "�Ա�:��" << "\t";
	}
	else
		if (abs->personArray[index].m_Sex == 2)
		{
			cout << "�Ա�:Ů" << "\t";
		}
		else
		{
			cout << "�Ա�:δ֪" << "\t";
		}
	cout << "����:" << abs->personArray[index].m_Age << "\t";
	cout << "�绰:" << abs->personArray[index].m_Phone << "\t";
	cout << "סַ:" << abs->personArray[index].m_Addr << endl;
	system("pause");
	system("cls");//��������0
}
//5���޸�ָ����ϵ��
void modifyPerson(Addressbooks*abs)
{

}
//6�����������ϵ��


void showMenu() {
	std::cout << "***** 1�������ϵ�� *****\n";
	std::cout << "***** 2����ʾ��ϵ�� *****\n";
	std::cout << "***** 3��ɾ����ϵ�� *****\n";
	std::cout << "***** 4��������ϵ�� *****\n";
	std::cout << "***** 5���޸���ϵ�� *****\n";
	std::cout << "***** 6�������ϵ�� *****\n";
	std::cout << "***** 0���˳�ͨѶ¼ *****\n";
}

int main()
{
	//����ͨѶ¼�ṹ�����
	struct Addressbooks abs;
	//��ʼ��ͨѶ¼�е�ǰ��Ա����
	abs.m_Size = 0;

	//�û�ѡ��Ĺ������
	int select = 0;
	while (true)
	{
		showMenu();
		cin >> select;
		switch (select)
		{
		case 1: //�����ϵ��
			addPerson(&abs);
			break;
		case 2://��ʾ��ϵ��
			showPerson(&abs);
			break;
		case 3://ɾ����ϵ��
			deletePerson(&abs);
			break;
		case 4://������ϵ��
			findPerson(&abs);
			break;
		case 5://�޸���ϵ��
			modifyPerson();
			break;
		case 6://�����ϵ��
			break;
		case 0://�˳�ͨѶ¼
			cout << "��ӭ�´�ʹ��" << endl;
			return 0;
			break;
		default:
			break;
		}
	}

}