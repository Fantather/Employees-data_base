#include "EmployeeDatabase.h"
#include "work_with_array.h"
#include "work_with_file.h"
#include "MyString.h"

#include <chrono>
#include <thread>

using namespace std;

void sleep() {
	std::this_thread::sleep_for(std::chrono::seconds(2));  // Пауза 2 секунды
}

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
		db.add_employee("Grace", "Martinez", 33);
		db.add_employee("Hannah", "Soprano", 33);
		db.add_employee("Isaac", "Gonzalez", 33);
	}
	sleep();

	cout << "Size of the database: " << db.get_size() << endl;
	db.print_database();

	sleep();
	sleep();

	cout << "\n---------------------\n";
	cout << "Automithed actions\n";
	cout << "---------------------\n\n";

	cout << "1. Search employee by name John (Yes)\n\n";
	size_t index_name = db.search_by_name("John");
	cout << "\nChange his name to \"Jack\"\n\n";
	db.set_name("Jack", index_name);
	db.print_employee(index_name);

	sleep();
	cout << "\n---------------------\n";
	cout << "\n2. Search employee by surname Doe and Change his surname to \"Smith\"\n (Yes)\n\n";
	db.set_surname("Smith", "Doe");

	cout << "\n---------------------\n";
	cout << "\n3. Add employee\n";
	db.add_employee("Michael", "Brown", 28);
	cout << "We added:\n";
	db.print_employee(db.get_size() - 1);

	sleep();
	cout << "\n---------------------\n";
	cout << "\n4. Change employee age by index\n";
	cout << "Change age to 35\n";
	db.set_age(35, static_cast<size_t>(5));
	db.print_employee(5);

	sleep();
	cout << "\n---------------------\n";
	cout << "\n5. Change employee age by surname\n";
	cout << "Change age to 40\n\n";
	db.set_age(40, "Smith");

	sleep();
	cout << "\n---------------------\n";
	cout << "\n6. Print all employees\n\n";
	db.print_database();

	sleep();
	cout << "\n---------------------\n";
	cout << "\n7. Print employees by age 33\n";
	db.print_by_age(33);

	sleep();
	cout << "\n---------------------\n";
	cout << "\n8. Print employees by first letter of surname 'S'\n";
	db.print_by_surname_letter('S');
	
	sleep();
	cout << "\n---------------------\n";
	cout << "\n9. Save database to file\n";
	if (db.save_to_file(file_name))
		cout << "Database saved to file\n";
	else
		cout << "Error saving database to file\n";

	sleep();
	cout << "\n---------------------\n";
	cout << "\n10. Delete employee by index 5\n";
	db.delete_employee(5);
	db.print_database();

	sleep();
	cout << "\n---------------------\n";
	cout << "\n11. Load database from file\n";
	if (db.load_from_file(file_name))
		cout << "Database loaded from file\n";
	else
		cout << "Error loading database from file\n\n";
	db.print_database();

	cout << "End of automithed actions\n";

	//db.my_interface();
}
	

//Задание
//Напишите информационную систему "Сотрудники".
//Программа должна обеспечивать ввод данных, редактирование данных сотрудника, удаление сотрудника, поиск сотрудника по фамилии
//вывод информации обо всех сотрудниках, указанного возраста, или фамилия которых начинается на указанную букву.Организуйте возможность сохранения найденной информации в файл.
//Также весь список сотрудников сохраняется в файл(при выходе из программы – автоматически, в процессе исполнения программы – по команде пользователя).
//При старте программы происходит загрузка списка сотрудников из указанного пользователем файла.