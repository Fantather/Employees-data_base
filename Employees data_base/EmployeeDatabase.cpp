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
bool EmployeeDatabase::_check_load(size_t read, size_t expected, FILE* file, const char* what) const
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
// Delete name and surname. Set them to nullptr. Set age to 0
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

// Destructor
EmployeeDatabase::MyString::~MyString()
{
	delete[] str;
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

		if (other.str)
		{
			length = other.length;
			capacity = other.capacity;
			str = new char[capacity];
			memcpy(str, other.str, capacity);
		}

		else
		{
			str = nullptr;
			length = 0;
			capacity = 0;
		}
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

// Get string by one simbol
void EmployeeDatabase::MyString::input_str() 
{
	delete[] str;
	length = 0;
	capacity = 25;
	str = new char[capacity];
	char ch;
	while (std::cin.get(ch) && ch != '\n')
	{
		resize_str_();
		str[length++] = ch;
	}
	str[length] = '\0';
}

void EmployeeDatabase::MyString::resize_str_()
{
	if (length < capacity - 1) return; // No need to resize

	size_t new_capacity = capacity * 2;
	char* new_str = new char[new_capacity];

	memcpy(new_str, str, length + 1);

	delete[] str;
	str = new_str;
	capacity = new_capacity;
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
	std::cout << "Yes(1)/No(2)\n";
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

// Clear cin buffer
void EmployeeDatabase::_clear_cin()
{
	if (std::cin.fail()) {
		std::cin.clear(); // clear the error flag
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard invalid input
	}
	else
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard valid input
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
EmployeeDatabase::EmployeeDatabase() : database_size(0), database_capacity(DEFAULT_DATABASE_CAPACITY), database(new Employee[database_capacity]) {}

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

// Get database size
const size_t EmployeeDatabase::get_size() const { return database_size; }


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

// Method speak with user and ask for confirmation using _user_validation() method and for search using _search_by_age()
void EmployeeDatabase::my_interface()
{
	std::cout << "\n\n---------------------\n\n";
	int answer = 0;

	while (true)
	{
		// Print menu
		std::cout << "Menu:\n";
		std::cout << "1. Search employee by name\n";
		std::cout << "2. Search employee by surname\n";
		std::cout << "3. Search employee by index\n";
		std::cout << "4. Add employee\n\n";

		std::cout << "5. Change employee name by index\n";
		std::cout << "6. Change employee surname by index\n";
		std::cout << "7. Change employee age by index\n";
		std::cout << "8. Change employee name by surname\n";
		std::cout << "9. Change employee surname by surname\n";
		std::cout << "10. Change employee age by surname\n\n";

		std::cout << "11. Print all employees\n";
		std::cout << "12. Print employees by age\n";
		std::cout << "13. Print employees by first letter of surname\n";

		std::cout << "14. Save database to file\n\n";

		std::cout << "15. delete employee by index\n\n";

		std::cout << "0. Exit";
		std::cout << "\n\n---------------------\n\n";

		// Get user answer
		std::cout << "Enter your choice: ";
		std::cin >> answer;
		if (std::cin.fail()) {
			std::cin.clear(); // clear the error flag
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard invalid input
			std::cout << "Invalid input, try again\n";
			continue;
		}

		switch (answer)
		{
		case 1: 
		{
			size_t index_name;
			std::cout << "Enter employee name: ";
			char name[100];
			std::cin >> name;
			index_name = search_by_name(name);

			if (index_name == Err) {
				std::cout << "\nEmployee not found\n\n";
			}
			else {
				std::cout << "\nEmployee with index " << index_name << " :\n";
				print_employee(index_name);
			}
			break;
		}

		case 2:
		{
			size_t index_surname;
			std::cout << "Enter employee surname: ";
			char surname[100];
			std::cin >> surname;
			index_surname = search_by_surname(surname);

			if (index_surname == Err) {
				std::cout << "\nEmployee not found\n\n";
			}
			else {
				std::cout << "\nEmployee with index " << index_surname << " :\n";
				print_employee(index_surname);
			}
			break;
		}

		case 3:{
			std::cout << "Enter employee index: ";
			size_t index;
			std::cin >> index;

			if (index >= database_size) {
				std::cout << "\nEmployee not found\n\n";
			}
			else {
				std::cout << "\nEmployee with index " << index << " :\n";
				print_employee(index);
			}
			break;
		}

		case 4:
		{
			std::cout << "Enter employee name: ";
			MyString input_name;
			input_name.input_str();
		    
			std::cout << "Enter employee surname: ";
			MyString input_surname;
			input_surname.input_str();

			std::cout << "Enter employee age: ";
			int input_age;
			std::cin >> input_age;
			_clear_cin();

			add_employee(input_name.str, input_surname.str, input_age);
			break;
		}

		case 5:
		{
			std::cout << "Enter employee index: ";
			size_t index_name;
			std::cin >> index_name;
			if (index_name >= database_size) {
				std::cout << "\nEmployee not found\n\n";
			}
			else {
				std::cout << "Enter new employee name: ";
				MyString input_name;
				input_name.input_str();
				set_name(input_name.str, index_name);
			}
			break;
		}

		}
	}
}


// --- Save and load ---

// Save the database to a file
// If the file is not opened, return false and close the file
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
		std::cerr << "\nSave database_size error\n";
		return false;
	}

	// Save database_capacity
	if (!_check_save(fwrite(&database_capacity, sizeof(size_t), 1, file), 1, file, "\nSave database_capacity error\n")) {
		return false;
	}

	// Save obj from Database
	for (size_t i = 0; i < database_size; i++)
	{
		// Save Employee name
		size_t name_len = database[i].name ? strlen(database[i].name) : 0;

		// Save length of name. Return false if the name is not nullptr and Save was not successful 
		if (!_check_save(fwrite(&name_len, sizeof(size_t), 1, file), 1, file, "Length name save")) {
			return false;
		}

		if (name_len > 0 && !_check_save(fwrite(database[i].name, sizeof(char), name_len, file), name_len, file, "Name save")) {
			return false;
		}

		// Save Employee surname
		size_t surname_len = database[i].surname ? strlen(database[i].surname) : 0;

		// Save length of surname
		if (!_check_save(fwrite(&surname_len, sizeof(size_t), 1, file), 1, file, "Length surname save")) {
			return false;
		}

		if (surname_len > 0 && !_check_save(fwrite(database[i].surname, sizeof(char), surname_len, file), surname_len, file, "Surname save")) {
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


// Load the database from a file
// If the file is not opened, return false and close the file
// If the file is empty, return true and create deafault database
bool EmployeeDatabase::load_from_file(const char* file_name)
{
	FILE* file = nullptr;
	if (fopen_s(&file, file_name, "rb") != 0) {
		std::cerr << "\nInvalid open file to read\n";
		return false;
	}

	// Check if the file is empty
	fseek(file, 0, SEEK_END);
	size_t file_size = ftell(file);
	rewind(file);

	if (file_size == 0) {
		database_size = 0;
		database_capacity = DEFAULT_DATABASE_CAPACITY;
		fclose(file);
		return true;
	}

	// Load database_size
	if (!_check_load(fread(&database_size, sizeof(size_t), 1, file), 1, file, "Load database_size")) {
		return false;
	}

	// Load database_capacity
	if (!_check_load(fread(&database_capacity, sizeof(size_t), 1, file), 1, file, "Load database_capacity")) {
		return false;
	}

	// If the database_capacity is more than the default capacity, delete the old array and create a new one
	// Else clear the old array using the clear() method of the Employee struct
	if (database_capacity > DEFAULT_DATABASE_CAPACITY) {
		delete[] database;
		database = new Employee[database_capacity];
	}

	else {
		for (size_t i = 0; i < database_size; i++) {
			database[i].clear();
		}
	}

	// Load Employees
	for (size_t i = 0; i < database_size; i++)
	{
		// Load length of name
		size_t name_len;

		if (!_check_load(fread(&name_len, sizeof(size_t), 1, file), 1, file, "Load length of employee.name")) {
			return false;
		}

		// Load name
		if (name_len > 0)
		{
			database[i].name = new char[name_len + 1];

			if (!_check_load(fread(database[i].name, sizeof(char), name_len, file), name_len, file, "Load employee.name")) {
				return false;
			}

			database[i].name[name_len] = '\0';
		}

		else
		{
			database[i].name = nullptr;
		}

		// Load length of surname
		size_t surname_len;

		if (!_check_load(fread(&surname_len, sizeof(size_t), 1, file), 1, file, "Load length of employee.surname")) {
			return false;
		}

		// Load name
		if (surname_len > 0)
		{
			database[i].surname = new char[surname_len + 1];

			if (!_check_load(fread(database[i].surname, sizeof(char), surname_len, file), surname_len, file, "Load employee.surname")) {
				return false;
			}

			database[i].surname[surname_len] = '\0';
		}

		else 
		{
			database[i].surname = nullptr;
		}


		// Load age
		if (!_check_load(fread(&database[i].age, sizeof(database[i].age), 1, file), 1, file, "Load employee.age")) {
			return false;
		}
	}

	fclose(file);
	return true;
}
