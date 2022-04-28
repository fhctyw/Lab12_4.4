#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <Windows.h>
#include <vector>
using namespace std;

struct point
{
	double x, y;
	point(double x, double y) : x(x), y(y) {};
	point(string point)
	{
		size_t end_first_num;
		string first_num = point.substr(1, (end_first_num = point.find(',')) - 1);
		x = stod(first_num);
		size_t start_second_num = end_first_num;
		size_t count = point.size() - end_first_num - 2;
		string second_num = point.substr(start_second_num + 1, count);
		y = stod(second_num);
	}
};

enum class typeTriangle { rizno, rivnobed, rivnostor };
string strTypeTriangle[] = { "Різносторонні", "Рівнобедрені", "Рівносторонні" };
typeTriangle getType(point p1, point p2, point p3)
{
	double a = sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
	double b = sqrt(pow(p1.x - p3.x, 2) + pow(p1.y - p3.y, 2));
	double c = sqrt(pow(p2.x - p3.x, 2) + pow(p2.y - p3.y, 2));

	if (abs(a - b) < 1e-6 && abs(a - c) < 1e-6)
		return typeTriangle::rivnostor;
	else if (abs(a - b) < 1e-6 || abs(a - c) < 1e-6 || abs(b - c) < 1e-6)
		return typeTriangle::rivnobed;
	else
		return typeTriangle::rizno;
}


void edit(string path)
{
	fstream file(path, ios::in);
	vector<string> vec;
	if (file.is_open())
	{
		for (string line; getline(file, line);)
			vec.push_back(line);
	}
	else
		cout << "edit()" << endl;
	file.close();

	file = fstream(path, ios::out);
	if (file.is_open())
	{
		for (size_t i = 0; i < vec.size(); i++)
		{
			string line = vec.at(i);

			size_t spos = 0, epos = 0;
			epos = line.find(',', line.find(',', spos) + 1);
			string sp1 = line.substr(spos, epos);
			point p1(sp1);
			spos = epos + 1;
			epos = line.find(',', line.find(',', spos) + 1);
			string sp2 = line.substr(spos, epos - spos);
			point p2(sp2);
			spos = epos + 1;
			epos = line.find(',', line.find(',', spos) + 1);
			string sp3 = line.substr(spos, epos - spos);
			point p3(sp3);

			string type = strTypeTriangle[(int)getType(p1, p2, p3)];

			string process_line = line + ' ' + type + '\n';
			file.write(process_line.c_str(), process_line.length());
		}
	}
	else
		cout << "edit()" << endl;
}



void Input(string path, size_t cnt)
{
	fstream file(path, ios::out);
	if (file.is_open())
	{
		for (size_t i = 0; i < cnt; i++)
		{
			double x1, y1;
			cout << "Перший трикутник x: "; cin >> x1;
			cout << "Перший трикутник y: "; cin >> y1;
			double x2, y2;
			cout << "Другий трикутник x: "; cin >> x2;
			cout << "Другий трикутник y: "; cin >> y2;
			double x3, y3;
			cout << "Третій трикутник x: "; cin >> x3;
			cout << "Третій трикутник y: "; cin >> y3;

			stringstream ss;
			ss << '(' << x1 << ',' << y1 << "),(" << x2 << ',' << y2 << "),(" << x3 << ',' << y3 << ")\n";
			file.write(ss.str().c_str(), ss.str().size());
		}
	}
	else
		cout << "Input()" << endl;
	file.close();
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int choice;
	do
	{
		cout << "1 Створити файл" << endl;
		cout << "2 Написати види трикутників" << endl;
		cout << "3 Відобразити файл" << endl;;
		cout << "0 Вихід" << endl;
		cout << "Вибір: "; cin >> choice;

		if (choice == 1)
		{
			string path;
			cout << "Введіть файл: ";
			cin.get();
			getline(cin, path);
			size_t cnt;
			cout << "Введіть кількість трикутників: "; cin >> cnt;
			Input(path, cnt);
		}
		else if (choice == 2)
		{
			string path;
			cout << "Введіть файл: ";
			cin.get();
			getline(cin, path);
			edit(path);
		}
		else if (choice == 3)
		{
			string path;
			cout << "Введіть файл: ";
			cin.get();
			getline(cin, path);
			
			fstream f(path, ios::in);
			if (f.is_open())
			{
				for (string line; getline(f, line);)
					cout << line << endl;
			}
			else
				cout << "error 3" << endl;
			f.close();
		}

	} while (choice != 0);

	return 0;
}