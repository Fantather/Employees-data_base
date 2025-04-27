#include "EmployeeDatabase.h"

// --------------------- EmployeeDatabase methods -------------------------------
// --- Constructors and assignment operator ---
EmployeeDatabase::Employee::Employee() : surname(nullptr), name(nullptr), age(0) {}

EmployeeDatabase::Employee::Employee(const char* user_name) : Employee()
{
	name = _deep_copy(user_name);
}

EmployeeDatabase::Employee::Employee(const char* user_name, const char* user_surname) : Employee(user_name)
{
	surname = _deep_copy(user_surname);
}

EmployeeDatabase::Employee::Employee(const char* user_name, const char* user_surname, int user_age) : Employee(user_name, user_surname)
{
	age = _validate_age(user_age);
}

// Copy constructor
EmployeeDatabase::Employee::Employee(const Employee& other) 
	: name(_deep_copy(other.name)), surname(_deep_copy(other.surname)), age(other.age) {}

// Copy assignment operator
EmployeeDatabase::Employee&
EmployeeDatabase::Employee::operator=(const Employee& other)
{
	if (this != &other) {
		delete[] name;
		delete[] surname;

		name = _deep_copy(other.name);
		surname = _deep_copy(other.surname);
		age = other.age;
	}
	return *this;
}

// Move constructor
EmployeeDatabase::Employee::Employee(Employee&& other) noexcept
{
	this->name = other.name;
	this->surname = other.surname;
	this->age = other.age;

	other.name = nullptr;
	other.surname = nullptr;
	other.age = 0;
}

// Move assignment operator
EmployeeDatabase::Employee& EmployeeDatabase::Employee::operator=(Employee&& other) noexcept
{
	if (this != &other) {
		this->name = other.name;
		this->surname = other.surname;
		this->age = other.age;

		other.name = nullptr;
		other.surname = nullptr;
		other.age = 0;
	}
	return *this;
}

// Destructor
EmployeeDatabase::Employee::~Employee()
{
	delete[] name;
	delete[] surname;
}


// --- Methods ---
// Clear all data in the Employee object
void EmployeeDatabase::Employee::clear()
{
	delete[] name;
	delete[] surname;
	age = 0;
	name = nullptr;
	surname = nullptr;
}


// ------------------------------- EmployeeDatabase methods -------------------------------
// --- Private methods ---

// Deep copy a string with memcpy
// If the string is nullptr, return nullptr
char* EmployeeDatabase::_deep_copy(const char* input_str)
{
	if (input_str == nullptr) return nullptr;

	size_t length = strlen(input_str) + 1;
	char* copy_str = new char[length];

	memcpy(copy_str, input_str, length);
	return copy_str;
}

// Check if the age is valid
unsigned char EmployeeDatabase::_validate_age(const unsigned char user_age)
{
	if (user_age > 123)
		return 7;    // For childishness
	else if (user_age < 0)
		return 0;
	else
		return user_age;
}

unsigned char EmployeeDatabase::_validate_age(const int user_age)
{
	return _validate_age(static_cast<const unsigned char>(user_age));
}

// Check if the array needs to be resized
// Double the size of the array using the _resize_database() method
void EmployeeDatabase::_check_resize()
{
	if (data_base_size + 1 > data_base_capacity) {
		this->_resize_database();
	}
}

// Double the size of the DataBase array
void EmployeeDatabase::_resize_database()
{
	Employee* old_data_base = data_base;

	data_base_capacity *= 2;
	data_base = new Employee[data_base_capacity];

	for (size_t i = 0; i < data_base_size; i++) {
		data_base[i] = std::move(old_data_base[i]);
	}
}


// --- Internal search helpers ---
// These functions are called by public interface methods (searchByName, searchBySurname etc.)
// and perform low-level search with resumable support (using startIndex)

// Search name
void EmployeeDatabase::_search_by_name(const char* search_name, size_t& index)
{
	while (index < data_base_size) {
		if (strcmp(data_base[index].name, search_name)) {
			return;
		}
		index++;
	}
	
}



// --- Public methods ---
// --- Constuctors ---
EmployeeDatabase::EmployeeDatabase() : data_base(nullptr), data_base_size(0), data_base_capacity(0) {}

EmployeeDatabase::EmployeeDatabase(const char* user_name) 
	: EmployeeDatabase()
{
	data_base_capacity = 10;
	data_base_size = 1;
	data_base = new Employee[data_base_capacity];
	data_base[0].name = _deep_copy(user_name);
}

EmployeeDatabase::EmployeeDatabase(const char* user_name, const char* user_surname)
	: EmployeeDatabase(user_name)
{
	data_base[0].surname = _deep_copy(user_surname);
}

EmployeeDatabase::EmployeeDatabase(const char* user_name, const char* user_surname, int user_age)
	: EmployeeDatabase(user_name, user_surname)
{
	data_base[0].age = _validate_age(user_age);
}

// Copy constructor
EmployeeDatabase::EmployeeDatabase(const EmployeeDatabase& other) 
	: data_base_size(other.data_base_size), data_base_capacity(other.data_base_capacity)
{
	data_base = new Employee[other.data_base_capacity];
	std::copy(other.data_base, other.data_base + data_base_size, data_base);
}

// Copy assignment operator
// If capacity is not enough, delete the old array and create a new one or rewrite the old one and clear extra objects
EmployeeDatabase& EmployeeDatabase::operator=(const EmployeeDatabase& other)
{
	if (this != &other) {
		if (data_base_capacity < other.data_base_capacity) {
			delete[] data_base;
			data_base_capacity = other.data_base_capacity;
			data_base = new Employee[data_base_capacity];
		}

		data_base_size = other.data_base_size;

		for (size_t i = 0; i < other.data_base_size; i++) {
			data_base[i] = other.data_base[i];
		}

		for (size_t i = data_base_size; i < data_base_capacity; i++) {
			data_base[i].clear();
		}
	}
	return *this;
}

// Destructor
EmployeeDatabase::~EmployeeDatabase()
{
	delete[] data_base;
}



// --- Public methods ---

// Add an employee to the database
// If the array is full, resize it using the _check_resize() method
// If the name or surname is nullptr, do nothing
// If the age is invalid, set it to 0 or 7
// Objects already exists and initialized with default values
void EmployeeDatabase::add_employee(const char* user_name)
{
	if (user_name == nullptr) return;

	data_base[data_base_size].name = _deep_copy(user_name);
	_check_resize();
	data_base_size++;
}

void EmployeeDatabase::add_employee(const char* user_name, const char* user_surname)
{
	if (user_name == nullptr || user_surname == nullptr) return;

	data_base[data_base_size].name = _deep_copy(user_name);
	data_base[data_base_size].surname = _deep_copy(user_surname);
	_check_resize();
	data_base_size++;
}

void EmployeeDatabase::add_employee(const char* user_name, const char* user_surname, const unsigned char user_age)
{
	if (user_name == nullptr || user_surname == nullptr) return;

	data_base[data_base_size].name = _deep_copy(user_name);
	data_base[data_base_size].surname = _deep_copy(user_surname);
	data_base[data_base_size].age = _validate_age(user_age);
	_check_resize();
	data_base_size++;
}

void EmployeeDatabase::add_employee(const char* user_name, const char* user_surname, const int user_age)
{
	add_employee(user_name, user_surname, static_cast<const unsigned char>(user_age));
}

// Change name by index
void EmployeeDatabase::set_name(const char* user_name, const size_t index)
{
	if (user_name == nullptr) return;
	delete[] data_base[index].name;
	data_base[index].name = _deep_copy(user_name);
}
