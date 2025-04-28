#include "EmployeeDatabase.h"
// ----------- save and load Database --------------

// Check if the data is written correctly
// Return "true" if the data is written correctly, close the file and return "false" if not
// Must be announcer earlier than the other methods
// Expected the number of elements that was written in the file, that was expected to be written, ptr to file, and what was written
bool EmployeeDatabase::_check_save(size_t written, size_t expected, FILE* file, const char* what) const
{
	if (written != expected) {
		std::cerr << "\nError writing to file while saving " << what << "\n";
		fclose(file);
		return false;
	}

	return true;
}

// Check if the data is read correctly
// Return "true" if the data is read correctly, close the file and return "false" if not
// Must be announcer earlier than the other methods
// Expected the number of elements that was read from the file, that was expected to be read, ptr to file, and what was read
bool EmployeeDatabase::_check_read(size_t read, size_t expected, FILE* file, const char* what) const
{
	if (read != expected) {
		std::cerr << "\nError reading from file while loading " << what << "\n";
		fclose(file);
		return false;
	}
	return true;
}



// --------------------- Employee methods -------------------------------
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
		delete[] this->name;
		delete[] this->surname;
		this->age = 0;

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

// ------------------------------ MyString methods ------------------------------
// Constructor
EmployeeDatabase::MyString::MyString(const char* input_str)
{
	if (input_str == nullptr) {
		str = nullptr;
		length = 0;
		capacity = 0;
	}
	else if (input_str[0] == '\0') {
		str = new char[1];
		str[0] = '\0';
		length = 0;
		capacity = 1;
	}
	else {
		length = strlen(input_str);
		capacity = length + 1;
		str = new char[capacity];
		memcpy(str, input_str, capacity);
	}
}

// Copy constructor
EmployeeDatabase::MyString::MyString(const MyString& other)
{
	length = other.length;
	capacity = other.capacity;
	str = new char[capacity];
	memcpy(str, other.str, capacity);
}

// Copy assignment operator
EmployeeDatabase::MyString& EmployeeDatabase::MyString::operator=(const MyString& other)
{
	if (this != &other) {
		delete[] str;
		length = other.length;
		capacity = other.capacity;
		str = new char[capacity];
		memcpy(str, other.str, capacity);
	}
	return *this;
}

// Move constructor
EmployeeDatabase::MyString::MyString(MyString&& other) noexcept
{
	str = other.str;
	length = other.length;
	capacity = other.capacity;
	other.str = nullptr;
	other.length = 0;
	other.capacity = 0;
}

// Move assignment operator
EmployeeDatabase::MyString& EmployeeDatabase::MyString::operator=(MyString&& other) noexcept
{
	if (this != &other) {
		delete[] str;
		str = other.str;
		length = other.length;
		capacity = other.capacity;
		other.str = nullptr;
		other.length = 0;
		other.capacity = 0;
	}
	return *this;
}

// Destructor
EmployeeDatabase::MyString::~MyString()
{
	delete[] str;
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
// I using this method for initialize Employees
unsigned char EmployeeDatabase::_validate_age(const unsigned char user_age)
{
	if (user_age > 123)
		return DEFAULT_CHILD_AGE;    // For childishness
	else
		return user_age;
}

unsigned char EmployeeDatabase::_validate_age(const int user_age)
{
	if (user_age < 0)
		return 0;

	return _validate_age(static_cast<const unsigned char>(user_age));
}

// Check if the age is valid
bool EmployeeDatabase::_check_age(const unsigned char user_age) const
{
	if (user_age > 123)
		return false;
	else
		return true;
}

bool EmployeeDatabase::_check_age(const int user_age) const
{
	if (user_age < 0)
		return false;

	return _check_age(static_cast<const unsigned char>(user_age));
}

// Get user answer
// Retutn 1 if the employee is found, 2 if not
// If the answer is invalid, ask again
int EmployeeDatabase::_user_validation(const size_t index) const
{
	std::cout << "Is this the employee you are looking for?\n";
	std::cout << "Yes(1)/No(2)";
	print_employee(index);

	int answer;
	while (true)
	{
		std::cin >> answer;
		if (std::cin.fail()) {
			std::cin.clear(); // clear the error flag
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard invalid input
			std::cout << "Invalid input, try again\n";
			continue;
		}
		if (answer == 1 || answer == 2)
			return answer;
		else
			std::cout << "Invalid answer, try again\n";
	}
}




// Check if the array needs to be resized
// Double the size of the array using the _resize_database() method
void EmployeeDatabase::_check_resize()
{
	if (database_size + 1 > database_capacity) {
		this->_resize_database();
	}
}

// Double the size of the DataBase array
void EmployeeDatabase::_resize_database()
{
	Employee* old_data_base = database;

	database_capacity *= 2;
	database = new Employee[database_capacity];

	for (size_t i = 0; i < database_size; i++) {
		database[i] = std::move(old_data_base[i]);
	}

	delete[] old_data_base;
}


// --- Internal search helpers ---
// These functions are called by public interface methods (searchByName, searchBySurname etc.)
// and perform low-level search with resumable support (using startIndex)

// Search name
// If the name is found, return true and set the index to the found index
// If the name is not found, return false and set the index to Err
// Nullptr check is done in the public interface method search_by_name()
bool EmployeeDatabase::_search_by_name(const char* search_name, size_t& index)
{
	while (index < database_size) {
		if(strcmp(database[index].name, search_name) == 0)
			return true;
		
		index++;
	}

	index = Err;
	return false;
}

// Search surname
// If the surname is found, return true and set the index to the found index
// If the surname is not found, return false and set the index to Err
// Nullptr check is done in the public interface method search_by_surname()
bool EmployeeDatabase::_search_by_surname(const char* search_name, size_t& index)
{
	while (index < database_size) {
		if (strcmp(database[index].surname, search_name) == 0)
			return true;

		index++;
	}

	index = Err;
	return false;
}



// --- Public methods ---
// --- Constuctors ---
EmployeeDatabase::EmployeeDatabase() : database_size(0), database_capacity(5), database(new Employee[database_capacity]) {}

EmployeeDatabase::EmployeeDatabase(const char* user_name) 
	: EmployeeDatabase()
{
	database[0].name = _deep_copy(user_name);
	database_size = 1;
}

EmployeeDatabase::EmployeeDatabase(const char* user_name, const char* user_surname)
	: EmployeeDatabase(user_name)
{
	database[0].surname = _deep_copy(user_surname);
}

EmployeeDatabase::EmployeeDatabase(const char* user_name, const char* user_surname, int user_age)
	: EmployeeDatabase(user_name, user_surname)
{
	database[0].age = _validate_age(user_age);
}

// Copy constructor
EmployeeDatabase::EmployeeDatabase(const EmployeeDatabase& other) 
	: database_size(other.database_size), database_capacity(other.database_capacity)
{
	database = new Employee[other.database_capacity];
	std::copy(other.database, other.database + database_size, database);
}

// Copy assignment operator
// If capacity is not enough, delete the old array and create a new one or rewrite the old one and clear extra objects
EmployeeDatabase& EmployeeDatabase::operator=(const EmployeeDatabase& other)
{
	if (this != &other) {
		if (database_capacity < other.database_capacity) {
			delete[] database;
			database_capacity = other.database_capacity;
			database = new Employee[database_capacity];
		}

		database_size = other.database_size;

		for (size_t i = 0; i < other.database_size; i++) {
			database[i] = other.database[i];
		}

		for (size_t i = database_size; i < database_capacity; i++) {
			database[i].clear();
		}
	}
	return *this;
}

// Destructor
EmployeeDatabase::~EmployeeDatabase()
{
	delete[] database;
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

	_check_resize();
	database[database_size].name = _deep_copy(user_name);
	database_size++;
}

void EmployeeDatabase::add_employee(const char* user_name, const char* user_surname)
{
	if (user_name == nullptr || user_surname == nullptr) return;

	_check_resize();
	database[database_size].name = _deep_copy(user_name);
	database[database_size].surname = _deep_copy(user_surname);
	database_size++;
}

void EmployeeDatabase::add_employee(const char* user_name, const char* user_surname, const unsigned char user_age)
{
	if (user_name == nullptr || user_surname == nullptr) return;

	_check_resize();
	database[database_size].name = _deep_copy(user_name);
	database[database_size].surname = _deep_copy(user_surname);
	database[database_size].age = _validate_age(user_age);
	database_size++;
}

void EmployeeDatabase::add_employee(const char* user_name, const char* user_surname, const int user_age)
{
	if (user_age < 0)
	{
		add_employee(user_name, user_surname, static_cast<unsigned char>(0));
		return;
	}
	add_employee(user_name, user_surname, static_cast<const unsigned char>(user_age));
}


// --- Setters ---

// Change name by index
void EmployeeDatabase::set_name(const char* user_name, const size_t index)
{
	if (user_name == nullptr || index >= database_size) return;
	delete[] database[index].name;
	database[index].name = _deep_copy(user_name);
}

// Change name by search name
// If user_name is nullptr or search_name is nullptr, do nothing
void EmployeeDatabase::set_name(const char* user_name, const char* search_name)
{
	if (user_name == nullptr || search_name == nullptr) return;
	size_t index = search_by_name(search_name);

	if (index == Err) {
		std::cout << "\nEmployee not found\n\n";
		return;
	}

	else
		set_name(user_name, index);
}

// Change surname by index
void EmployeeDatabase::set_surname(const char* user_surname, const size_t index)
{
	if (user_surname == nullptr || index >= database_size) return;
	delete[] database[index].surname;
	database[index].surname = _deep_copy(user_surname);
}

// Change surname by search surname
// If user_surname is nullptr or search_surname is nullptr, do nothing
void EmployeeDatabase::set_surname(const char* user_surname, const char* search_surname)
{
	if (user_surname == nullptr || search_surname == nullptr) return;
	size_t index = search_by_surname(search_surname);

	if (index == Err) {
		std::cout << "\nEmployee not found\n\n";
		return;
	}

	else
		set_surname(user_surname, index);
}

// Change age by index
void EmployeeDatabase::set_age(const unsigned char user_age, const size_t index)
{
	if (user_age > 123 || index >= database_size) return;
	database[index].age = user_age;
}

void EmployeeDatabase::set_age(const int user_age, const size_t index)
{
	if (user_age < 0)
		return;
	set_age(static_cast<const unsigned char>(user_age), index);
}

// Change age by search surname
// If user_age is invalid or search_surname is nullptr, do nothing
void EmployeeDatabase::set_age(const unsigned char user_age, const char* search_surname)
{
	if (_check_age(user_age) == false || search_surname == nullptr) return;
	size_t index = search_by_surname(search_surname);
	if (index == Err) {
		std::cout << "\nEmployee not found\n\n";
		return;
	}
	else
		set_age(user_age, index);
}

void EmployeeDatabase::set_age(const int user_age, const char* search_surname)
{
	set_age(static_cast<const unsigned char>(user_age), search_surname);
}

// --- Getters ---

// Get name by index
// If the index is out of range, return nullptr
EmployeeDatabase::MyString EmployeeDatabase::get_name(const size_t index) const
{
	if (index >= database_size) return MyString();
	return MyString(database[index].name);
}

// Get surname by index
// If the index is out of range, return nullptr
EmployeeDatabase::MyString EmployeeDatabase::get_surname(const size_t index) const
{
	if (index >= database_size) return MyString();
	return MyString(database[index].surname);
}

// Get age by index
// If the index is out of range, return -1
int EmployeeDatabase::get_age(const size_t index) const
{
	if (index >= database_size) return -1;
	return static_cast<int>(database[index].age);
}


// --- Print ---

// Print employee by index
void EmployeeDatabase::print_employee(const size_t index) const
{
	if (index >= database_size) return;
	std::cout << "Name: " << database[index].name << "\n";
	std::cout << "Surname: " << database[index].surname << "\n";
	std::cout << "Age: " << static_cast<int>(database[index].age) << "\n";
}

// Print all employees
void EmployeeDatabase::print_database() const
{
	std::cout << "---------------------\n";
	std::cout << "Total employees: " << database_size << "\n";
	std::cout << "---------------------\n\n";
	for (size_t i = 0; i < database_size; i++) {
		print_employee(i);
		std::cout << "---------------------\n\n";
	}
}

// Print employees by age
void EmployeeDatabase::print_by_age(const unsigned char user_age) const
{
	if (_check_age(user_age) == false) return;
	std::cout << "---------------------\n";
	std::cout << "Employees with age " << static_cast<int>(user_age) << "\n";
	std::cout << "---------------------\n\n";
	for (size_t i = 0; i < database_size; i++) {
		if (database[i].age == user_age)
			print_employee(i);
	}
	std::cout << "---------------------\n\n";
}

void EmployeeDatabase::print_by_age(const int user_age) const
{
	print_by_age(static_cast<const unsigned char>(user_age));
}

// Print employees by first letter of surname
void EmployeeDatabase::print_by_surname_letter(const char& ch) const
{
	std::cout << "---------------------\n";
	std::cout << "Employees with surname starting with " << ch << "\n";
	std::cout << "---------------------\n\n";
	for (size_t i = 0; i < database_size; i++) {
		if (database[i].surname != nullptr && database[i].surname[0] == ch)
			print_employee(i);
	}
	std::cout << "---------------------\n\n";
}



// Delete employee by index
// If the index is out of range, do nothing
// If the index is valid, clear the employee object and move all elements after it to the left
void EmployeeDatabase::delete_employee(const size_t index)
{
	if (index >= database_size) return;

	database[index].clear();
	for (size_t i = index; i < database_size - 1; i++) {
		database[i] = std::move(database[i + 1]);
	}
	database_size--;
}


// --- Search ---

// Method speak with user and ask for confirmation using _user_validation() method and for search using _search_by_name()
// If the name is found, return the index
// If the name is not found, return Err
// If the name is nullptr, return Err
size_t EmployeeDatabase::search_by_name(const char* search_name)
{
	if (search_name == nullptr) return Err;
	size_t index_result = 0;

	while (_search_by_name(search_name, index_result)) {
		int answer = _user_validation(index_result);

		if (answer == 1)
			return index_result;
		else if (answer == 2)
			index_result++;
	}

	return Err;
}

// Method speak with user and ask for confirmation using _user_validation() method and for search using _search_by_surname()
// If the surname is found, return the index
// If the surname is not found, return Err
// If the surname is nullptr, return Err
size_t EmployeeDatabase::search_by_surname(const char* search_surname)
{
	if (search_surname == nullptr) return Err;
	size_t index_result = 0;

	while (_search_by_surname(search_surname, index_result)) {
		int answer = _user_validation(index_result);

		if (answer == 1)
			return index_result;
		else if (answer == 2)
			index_result++;
	}

	return Err;
}


// --- Save and load ---

// 
bool EmployeeDatabase::save_to_file(const char* file_name) const
{
	FILE* file = nullptr;
	if (fopen_s(&file, file_name, "wb") != 0)
	{
		std::cerr << "\nOpen file error\n";
		return false;
	}

	// Save database_size
	if (fwrite(&database_size, sizeof(size_t), 1, file) != 1)
	{
		fclose(file);
		std::cerr << "\nWrite database_size error\n";
		return false;
	}

	// Save obj from Database
	for (size_t i = 0; i < database_size; i++)
	{
		// Save Employee name
		size_t name_len = database[i].name ? strlen(database[i].name) : 0;

		// Save length of name. Return false if the name is not nullptr and Save was not successful 
		if (name_len > 0 && !_check_save(fwrite(&name_len, sizeof(size_t), 1, file), 1, file, "Length name save")) {
			return false;
		}

		if (!_check_save(fwrite(database[i].name, sizeof(char), name_len, file), name_len, file, "Name save")) {
			return false;
		}


		// Save Employee surname
		size_t surname_len = database[i].surname ? strlen(database[i].surname) : 0;

		// Save length of surname
		if (surname_len > 0 && !_check_save(fwrite(&surname_len, sizeof(size_t), 1, file), 1, file, "Length surname save")) {
			return false;
		}

		if (!_check_save(fwrite(database[i].surname, sizeof(char), surname_len, file), name_len, file, "Surname save")) {
			return false;
		}


		// Save Employee age
		if (!_check_save(fwrite(&database[i].age, sizeof(database[i].age), 1, file), 1, file, "Age save")) {
			return false;
		}
	}

	fclose(file);
	return true;
}
