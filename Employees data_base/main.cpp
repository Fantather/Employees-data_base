#include "EmployeeDatabase.h"
#include "work_with_array.h"
#include "work_with_file.h"
#include "MyString.h"
using namespace std;

// То что вместо собственноручного string можно возвращать Константный значения я понял уже когда написал её

int main() {
	const char* file_name = "employees.txt";

	/*MyString file_name(FILE_NAME);
	cout << "Enter file name:";
	file_name.input_str();
	cout << endl;*/

	EmployeeDatabase db;

	if (db.load_from_file(file_name) == false) {
		cout << "File not found, creating new database\n";
		db.add_employee("John", "Doe", 30);
		db.add_employee("Jane", "Smith", 25);
		db.add_employee("Alice", "Johnson", 20);
		db.add_employee("Bob", "Brown", 35);
		db.add_employee("Charlie", "Davis", 40);
		db.add_employee("Eve", "Wilson", 22);
		db.add_employee("Frank", "Garcia", 29);
		db.add_employee("Grace", "Martinez", 31);
		db.add_employee("Hannah", "Lopez", 27);
		db.add_employee("Isaac", "Gonzalez", 33);
	}

	cout << "Size of the database: " << db.get_size() << endl;
	db.print_database();

	cout << "---------------------\n";


}
	

//Задание
//Напишите информационную систему "Сотрудники".
//Программа должна обеспечивать ввод данных, редактирование данных сотрудника, удаление сотрудника, поиск сотрудника по фамилии
//вывод информации обо всех сотрудниках, указанного возраста, или фамилия которых начинается на указанную букву.Организуйте возможность сохранения найденной информации в файл.
//Также весь список сотрудников сохраняется в файл(при выходе из программы – автоматически, в процессе исполнения программы – по команде пользователя).
//При старте программы происходит загрузка списка сотрудников из указанного пользователем файла.