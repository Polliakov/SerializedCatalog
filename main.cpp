#include <iostream>
#include <string>

#include "Command.cpp"
#include "Catalog.cpp"
#include "Table.cpp"
#include "Size.cpp"

using namespace std;

void main()
{
	setlocale(LC_ALL, "rus");
	Catalog catalog("New Catalog");

	auto size = Size{ 80, 70, 70 };
	auto table1 = Table("TestTable0", "Just table!", 100, 20, size, false);
	auto table2 = Table("TestTable1", "The same version of table\nbut now it\'s folding!", 
						999.99, 21.5, size, true);
	catalog.Add(table1);
	catalog.Add(table2);

	while (true) {
		cout << endl;
		cout << "command->";
		string input;
		getline(cin, input);

		if (input.empty()) {
			Command::ShowHelp();
			continue;
		}

		string command;
		stringstream args;
		Command::Parse(input, command, args);
		
		if (command == "print") {
			catalog.Print();
			continue;
		}
		else if (command == "add") {
			catalog.Add(*Command::GetInput());
			continue;
		}
		else if (command == "remove") {
			int index = -1;
			args >> index;

			if (args.fail() || index < 0) {
				cout << "Недопустимый параметр" << endl;
				continue;
			}

			catalog.Delete(index);
			continue;
		}
		else if (command == "update") {
			int index = -1;
			args >> index;

			if (args.fail() || index < 0) {
				cout << "Недопустимый параметр" << endl;
				continue;
			}

			catalog.Update(index, *Command::GetInput());
			continue;
		}
		else if (command == "save") {
			string path;
			args >> path;

			if (catalog.TrySave(path)) {
				cout << "Сохранено успешно" << endl;
			}
			else {
				cout << "Ошибка сохранения" << endl;
			}
			continue;
		}
		else if (command == "load") {
			string path;
			args >> path;
			
			Catalog newCatalog;
			if (catalog.TryLoad(path, newCatalog)) {
				catalog = newCatalog;
				cout << "Загружено успешно" << endl;
			}
			else {
				cout << "Ошибка загрузки" << endl;
			}
			continue;
		}
		else {
			cout << "Неизвестная команда: \"" << command << "\"." << endl;
			continue;
		}
	}
}