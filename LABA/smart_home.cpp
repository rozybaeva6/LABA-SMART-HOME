#include "smart_home.hpp"
#include <stdlib.h>
#include <string.h>

smart_home::smart_home()
{
	number = 0;
	name = NULL;
	vkl = 0;
}

smart_home::smart_home(int nu, char* na, int v)
{
	number = nu;
	name = new char[strlen(na) + 1];
	name[0] = '\0';
	strcpy_s(name, (strlen(na) + 1) * sizeof(char), na);
	vkl = v;
}

smart_home::smart_home(const smart_home& s)
{
	number = s.number;
	name = new char[strlen(s.name) + 1];
	name[0] = '\0';
	strcpy_s(name, (strlen(s.name) + 1) * sizeof(char), s.name);
	vkl = s.vkl;
}

smart_home::~smart_home()
{
	delete name;
}

smart_home& smart_home::operator=(const smart_home& item)
{
	number = item.number;
	name = new char[strlen(item.name) + 1];
	name[0] = '\0';
	strcpy_s(name, (strlen(item.name) + 1) * sizeof(char), item.name);
	vkl = item.vkl;
	return *this;
}

smart_home* add(smart_home* mas, int n, smart_home& item)
{
	smart_home* res = new smart_home[n + 1];
	for (int i = 0; i < n; i++)
		res[i] = mas[i];
	res[n].number = item.number;
	res[n].vkl = item.vkl;
	res[n].name = new char[strlen(item.name) + 1];
	res[n].name[0] = '\0';
	strcpy_s(res[n].name, (strlen(item.name) + 1) * sizeof(char), item.name);
	return res;
}

smart_home* Delete(smart_home* mas, int* n, int num)//звездочка у н, нужна для того, чтобы сохранился изначальный размер массив
{
	if (num < 0)
		return mas;
	int i, j;
	for (i = 0; i < *n && mas[i].number != num; i++)
		;
	if (i == *n)
		return mas;
	j = i;
	smart_home* res = new smart_home[*n - 1];
	int a = 0;
	for (i = 0; i < *n; i++)
	{
		if (i != j)
			res[a++] = mas[i];

		/*mas[i].number = mas[i + 1].number;
		mas[i].vkl = mas[i + 1].vkl;
		delete mas[i].name;
		mas[i].name = new char[strlen(mas[i + 1].name) + 1];
		mas[i].name[0] = '\0';
		strcpy_s(mas[i].name, (strlen(mas[i+1].name)+1)*sizeof(char), mas[i + 1].name);*/
	}
	//mas = (smart_home*)realloc(mas, (*n - 1)*sizeof(smart_home));
	(*n)--;
	return res;
}

int find(smart_home* mas, int n, int status)
{
	smart_home* tmp;
	char buf[1000];
	int tmpSize, i, res; //tmpSize - размерность массива tmp
	tmp = NULL;
	tmpSize = 0;
	res = -1;
	for (i = 0; i < n; i++)
		if (mas[i].vkl == status)
		{
			tmp = (smart_home*)realloc(tmp, (tmpSize + 1) * sizeof(smart_home));
			tmp[tmpSize].number = mas[i].number;
			tmp[tmpSize].vkl = mas[i].vkl;
			tmp[tmpSize].name = new char[strlen(mas[i].name) + 1];
			tmp[tmpSize].name[0] = '\0';
			strcpy_s(tmp[tmpSize].name, (strlen(mas[i].name) + 1) * sizeof(char), mas[i].name);
			tmpSize++;
		}
	cout << "Found:" << endl;
	for (i = 0; i < tmpSize; i++)
	{
		cout << tmp[i].name << " : ";
		if (tmp[i].vkl == 0)
			cout << "off" << endl;
		else
			cout << "on" << endl;
	}
	cout << "Input Name of device: " << endl;
	cin.getline(buf, 999);
	for (i = 0; i < tmpSize; i++)
		if (strcmp(buf, tmp[i].name) == 0)
		{
			res = tmp[i].number;
			break;
		}
	delete tmp;
	return res;
}

istream& operator>>(istream& in, smart_home& s)
{
	char buf[1000];
	in.getline(buf, 999);
	s.number = atoi(buf);
	in.getline(buf, 999);
	s.name = new char[strlen(buf) + 1];
	s.name[0] = '\0';
	strcpy_s(s.name, (strlen(buf) + 1) * sizeof(char), buf);
	in.getline(buf, 999);
	s.vkl = atoi(buf);
	return in;
}

ostream& operator<<(ostream& out, smart_home& s)
{
	out << s.number << endl << s.name << endl << s.vkl << endl;
	return out;
}

smart_home* loadFile(char* way, int* n)
{
	ifstream in(way);
	if (!in.is_open())
		return NULL;
	char buf[10];
	in.getline(buf, 9);
	*n = atoi(buf);
	smart_home* res = new smart_home[*n];
	for (int i = 0; i < *n; i++)
		in >> res[i];
	in.close();
	return res;
}


int saveFile(char* way, smart_home* mas, int n)
{
	ofstream out(way);
	if (!out.is_open())
		return 0;
	out << n << endl;
	for (int i = 0; i < n; i++)
		out << mas[i];
	out.close();
	return 1;
}

void smart_home::print()
{
	cout << "Device number: " << number << endl << "Device name: " << name << endl << "Device status: ";
	if (vkl == 1)
		cout << "on" << endl;
	else
		cout << "off" << endl;
}

smart_home* edit(smart_home* mas, int n, int num)
{
	if (num < 0)
		return mas;
	int i;
	for (i = 0; i < n && mas[i].number != num; i++)
		;
	if (i == n)
		return mas;
	int mode;
	char buf[1000];
	cout << "What you want to edit? 1 - Device number, 2 - Device name, 3 - Device status" << endl;
	cin.getline(buf, 999);
	mode = atoi(buf);
	switch (mode)
	{
	case 1:
		cout << "Current number: " << mas[i].number << endl << "New number: ";
		cin.getline(buf, 999);
		mas[i].number = atoi(buf);
		break;
	case 2:
		cout << "Current name: " << mas[i].name << endl << "New name: ";
		cin.getline(buf, 999);
		delete mas[i].name;
		mas[i].name = new char[strlen(buf) + 1];
		mas[i].name[0] = '\0';
		strcpy_s(mas[i].name, (strlen(buf) + 1) * sizeof(char), buf);
		break;
	case 3:
		cout << "Current status: ";
		if (mas[i].vkl == 1)
			cout << "on" << endl;
		else
			cout << "off" << endl;
		cout << "New number (1 - on, 0 - off): ";
		cin.getline(buf, 999);
		mas[i].vkl = atoi(buf);
		break;
	default:
		return mas;
	}
	cout << "Edit complete" << endl;
	return mas;
}

int Menu()
{
	int a = 0;
	char buf[10];
	while (a < 1 || a> 6)
	{
		cout << "1: Add new device" << endl << "2: Remove device" << endl << "3: Find device" << endl << "4: Print the List of Devices" << endl << "5: Edit device" << endl << "6: Complete the work" << endl;
		cin.getline(buf, 9);
		a = atoi(buf);
	}
	return a;
}