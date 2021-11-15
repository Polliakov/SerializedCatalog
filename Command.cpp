#include <iostream>
#include <string>
#include <sstream>

#include "Table.cpp"
#include "Size.cpp"

using namespace std;

static class Command
{
public:
	static void ShowHelp()
	{
		cout << "print - Вывод каталога." << endl
			 << "add - Добавление элемента в каталог." << endl
			 << "remove <индекс элемента> - Удаление элемента по индексу." << endl
			 << "update <индекс элемента> - Изменение элемента по индексу." << endl
			 << "save <путь> - Сохранение каталога в файл." << endl
			 << "load <путь> - Загрузка каталога из файла." << endl;
	}

	static void Parse(const string& input, string& outCommand, stringstream& outArgs)
	{
		stringstream ss;
		ss << input;
		getline(ss, outCommand, ' ');
		string args;
		getline(ss, args, ' ');
		outArgs << args;
	}

	static Table* GetInput()
	{
		string title;
		cout << "title: ";
		cin >> title;
		cin.ignore(INT16_MAX, '\n');

		string description;
		cout << "description: ";
		getline(cin, description);


		cout << "folding: ";
		bool isFolding = Get<bool>();

		cout << "price: ";
		double price = Get<double>();

		cout << "size:" << endl;
		cout << "  length: ";
		double length = Get<double>();

		cout << "  width: ";
		double width = Get<double>();

		cout << "  height: ";
		double height = Get<double>();

		cout << "weight: ";
		double weight = Get<double>();

		Size size{ length, width, height };
		Table* table = new Table(title, description, price, weight, size, isFolding);

		return table;
	}

private:
	template<typename T>
	static T Get() 
	{
		T result;
		while (true) {
			cin >> result;

			if (cin.fail()) {
				cout << "Ошибка ввода, попробуйте снова" << endl;
				cin.clear();
				cin.ignore(INT16_MAX, '\n');
			}
			else {
				cin.ignore(INT16_MAX, '\n');
				return result;
			}
		}
	}
};