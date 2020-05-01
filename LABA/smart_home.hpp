#pragma once
#include <iostream>
#include <fstream>

using namespace std;

class smart_home {
	int number;
	char* name;
	int vkl; //1 - on, 0 - off
public:
	smart_home();
	smart_home(int nu, char* na, int v);
	smart_home(const smart_home& s);
	~smart_home();

	void print();
	smart_home& operator=(const smart_home& item);
	friend smart_home* add(smart_home* mas, int n, smart_home& item); // mas - массив структур, n - размерность массива структур, item - новое устройство, которое добавляем в массив
	friend smart_home* Delete(smart_home* mas, int* n, int num); // num - номер удаляемого устройства
	friend smart_home* edit(smart_home* mas, int n, int num);
	friend int find(smart_home* mas, int n, int status); // status - какие устроства мы ищем 0 - выключенные, 1 - вулючённые
	friend istream& operator>>(istream& in, smart_home& s);
	friend ostream& operator<<(ostream& out, smart_home& s);
};
int Menu();
smart_home* loadFile(char* way, int* n);
int saveFile(char* way, smart_home* mas, int n);