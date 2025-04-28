#include "EmployeeDatabase.h"
#include "work_with_array.h"
#include "work_with_file.h"
#include "MyString.h"
using namespace std;

// �� ��� ������ ����������������� string ����� ���������� ����������� �������� � ����� ��� ����� ������� �

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
	

//�������
//�������� �������������� ������� "����������".
//��������� ������ ������������ ���� ������, �������������� ������ ����������, �������� ����������, ����� ���������� �� �������
//����� ���������� ��� ���� �����������, ���������� ��������, ��� ������� ������� ���������� �� ��������� �����.����������� ����������� ���������� ��������� ���������� � ����.
//����� ���� ������ ����������� ����������� � ����(��� ������ �� ��������� � �������������, � �������� ���������� ��������� � �� ������� ������������).
//��� ������ ��������� ���������� �������� ������ ����������� �� ���������� ������������� �����.