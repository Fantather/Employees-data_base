#pragma once
#include <iostream>
#include <cstring>	  //memcpy, strcpy_s, strcmp, strlen
#include <algorithm>  // copy, max
#include <utility>    // move
#include <limits>	  // numeric_limits
#include <cstdio>     // FILE*, fopen, fwrite, fread, fclose

constexpr auto DEFAULT_CHILD_AGE = 7;
constexpr auto DEFAULT_DATABASE_CAPACITY = 5;

class EmployeeDatabase{
	// --- Check save and load Database ---
	bool _check_save(size_t written, size_t expected, FILE* file, const char* what) const; // Check if the data is written correctly
	bool _check_load(size_t read, size_t expected, FILE* file, const char* what) const; // Check if the data is read correctly

	// ------------------- Employee -----------------
    struct Employee {
        char* surname;
        char* name;
        unsigned char age;

		// Constructors
        Employee();
        Employee(const char* user_name);
        Employee(const char* user_name, const char* user_surname);
        Employee(const char* user_name, const char* user_surname, int user_age);

		// Copy constructor and assignment operator
        Employee(const Employee& other);
        Employee& operator=(const Employee& other);

        // Move
        Employee(Employee&& other) noexcept;
        Employee& operator=(Employee&& other) noexcept;

		// Destructor
        ~Employee();

		// Clear all data in the Employee object
        void clear();
    };

	// ------------------- MyString -----------------
	struct MyString
	{
		size_t length;
		size_t capacity;
		char* str;

		// Constructors
		MyString() : length(0), capacity(0), str(nullptr) {}
		MyString(const char* input_str);

		// Destructor
		~MyString();

		// Copy constructor and assignment operator
		MyString(const MyString& other);
		MyString& operator=(const MyString& other);

		// Move constructor and assignment operator
		MyString(MyString&& other) noexcept;
		MyString& operator=(MyString&& other) noexcept;

		// Get string by one simbol
		void input_str();		

		// Resize string double
		void resize_str_();
	};


	// ------------------- Class -----------------
private:
	size_t database_size;
	size_t database_capacity;
    Employee* database;
	static constexpr size_t Err = static_cast<size_t>(-1);     // For invalid returns

	// --- Private methods ---
	static char* _deep_copy(const char* input_str);              // Deep copy of a string

    static unsigned char _validate_age(const unsigned char user_age);  // Check if the age is valid for initialize Employees
    static unsigned char _validate_age(const int user_age);
	bool _check_age(const unsigned char user_age) const;          // Check if the age is valid
	bool _check_age(const int user_age) const;
	int _user_validation(const size_t index) const;     // Get user answer
	void _clear_cin();            // Clear cin buffer
    
	void _check_resize();       // Check if the array needs to be resized
	void _resize_database();    // Double the size of the DataBase array

    // --- Internal search helpers ---
    bool _search_by_name(const char* search_name, size_t& index);
    bool _search_by_surname(const char* search_name, size_t& index);

public:
	// Constructors
    EmployeeDatabase();
    EmployeeDatabase(const char* user_name);
    EmployeeDatabase(const char* user_name, const char* user_surname);
    EmployeeDatabase(const char* user_name, const char* user_surname, int user_age);

	// Copy constructor and assignment operator
	EmployeeDatabase(const EmployeeDatabase& other);   
	EmployeeDatabase& operator=(const EmployeeDatabase& other);

	// Destructor
    ~EmployeeDatabase();

    // Add
    void add_employee(const char* user_name);
    void add_employee(const char* user_name, const char* user_surname);
    void add_employee(const char* user_name, const char* user_surname, const unsigned char user_age);
    void add_employee(const char* user_name, const char* user_surname, const int user_age);

    // Setters
	void set_name(const char* user_name, const size_t index);               // Change name by index
	void set_name(const char* user_name, const char* search_name);          // Change name by search name

	void set_surname(const char* user_surname, const size_t index);         // Change surname by index
	void set_surname(const char* user_surname, const char* search_surname); // Change surname by search surname

	void set_age(const unsigned char user_age, const size_t index);         // Change age by index
	void set_age(const int user_age, const size_t index);
	void set_age(const unsigned char user_age, const char* search_surname); // Change age by search surname
	void set_age(const int user_age, const char* search_surname);

    // Getters
	MyString get_name(const size_t index) const;
	MyString get_surname(const size_t index) const;
    int get_age(const size_t index) const;
	const size_t get_size() const; // Get size of the database

    // Print
	void print_employee(const size_t index) const;          // Print employee by index
	void print_database() const;                            // Print all employees
	void print_by_age(const unsigned char user_age) const;  // Print all employees by age
	void print_by_age(const int user_age) const;
	void print_by_surname_letter(const char& ch) const;     // Print all employees by first letter of surname

	// Delete
	void delete_employee(const size_t index); // Delete employee by index
    
	// --- Interface methods ---
    size_t search_by_name(const char* search_name);
    size_t search_by_surname(const char* search_surname);
	void my_interface();		// Interface for user

	// --- Save and load ---
	bool save_to_file(const char* file_name) const; // Save all employees to file
	bool load_from_file(const char* file_name);		// Load EmployeeDatabase from file
};