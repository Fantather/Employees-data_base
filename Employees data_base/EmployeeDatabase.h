#pragma once
#include <iostream>
#include <cstring>	//memcpy, strcpy_s, strcmp
#include <algorithm> // copy, min

#define Err static_cast<size_t>(-1)     // For invalid returns

class EmployeeDatabase{
	// ------------------- Struct -----------------
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

	// ------------------- Class -----------------
private:
	Employee* database;
	size_t database_size;
	size_t database_capacity;

	// --- Private methods ---
	static char* _deep_copy(const char* input_str);              // Deep copy of a string
    static unsigned char _validate_age(const unsigned char user_age);  // Check if the age is valid
    static unsigned char _validate_age(const int user_age);
    int _user_validation(const size_t index) const;
    
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
    void set_name(const char* user_name, const size_t index);
    void set_name(const char* user_name, const char* search_name);
	void set_surname(const char* user_surname, const size_t index);

    // Getters
    char* get_name(const size_t index) const;
    char* get_surname(const size_t index) const;
    int get_age(const size_t index) const;

    // Print
    void print_employee(const size_t index) const;
    void print_database() const;
    
	// --- Interface methods ---
    size_t search_by_name(const char* search_name);
    size_t search_by_surname(const char* search_surname);
    
};