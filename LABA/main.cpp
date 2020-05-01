#include "smart_home.hpp"
#include <iostream>
#include <string.h>
#include <stdlib.h>

using namespace std;

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		cout << "wrong start!" << endl;
		return 0;
	}
	smart_home* mas;
	int n;
	smart_home* buf = NULL;
	char buff[1000];
	mas = loadFile(argv[1], &n);
	int mode, num, res, vk;
	char* na;
	do
	{
		mode = Menu();
		switch (mode)
		{
		case 1:
			cout << "Device's name: ";
			cin.getline(buff, 999);
			na = new char[strlen(buff) + 1];
			na[0] = '\0';
			strcpy_s(na, (strlen(buff) + 1) * sizeof(char), buff);
			cout << "Device's number: ";
			cin.getline(buff, 999);
			num = atoi(buff);
			cout << "Device's status: ";
			cin.getline(buff, 999);
			vk = atoi(buff);
			buf = new smart_home(num, na, vk);
			cout << "2" << endl;
			mas = add(mas, n, *buf);
			n++;
			delete na;
			delete buf;
			buf = NULL;

			if (saveFile(argv[1], mas, n) == 0)
			{
				cout << "sothing wrong!" << endl;
				return 0;
			}
			break;
		case 2:
			cout << "Number for remove: ";
			cin.getline(buff, 999);
			num = atoi(buff);
			mas = Delete(mas, &n, num);
			if (saveFile(argv[1], mas, n) == 0)
			{
				cout << "sothing wrong!" << endl;
				return 0;
			}
			break;

		case 3:
			cout << "What status of device you want to find? 0 - off, 1 - on" << endl;
			cin.getline(buff, 999);
			num = atoi(buff);
			res = find(mas, n, num);
			if (res == -1)
				cout << "Device not found!" << endl;
			else
				cout << "Device's number:" << res << endl;
			break;
		case 4:
			cout << "List of Devices:" << endl;
			for (int i = 0; i < n; i++)
			{
				cout << "Device " << i + 1 << endl;
				mas[i].print();
			}
			break;

		case 5:
			cout << "Number for edit: ";
			cin.getline(buff, 999);
			num = atoi(buff);
			mas = edit(mas, n, num);
			if (saveFile(argv[1], mas, n) == 0)
			{
				cout << "sothing wrong!" << endl;
				return 0;
			}
			break;
		case 6:
			break;
		default:
			cout << "wrong input, try again" << endl;
		}
	} while (mode != 6);
	return 0;
}