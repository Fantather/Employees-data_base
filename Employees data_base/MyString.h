#pragma once
#include <iostream>
#include <cstring>	  //memcpy, strcpy_s, strcmp, strlen

class MyString
{
private:
	size_t length;
	size_t capacity;
	char* str;

public:
	// Constructors
	MyString();
	MyString(const char* input_str);

	// Copy constructor and assignment operator
	MyString(const MyString& other);
	MyString& operator=(const MyString& other);

	// Move constructor and assignment operator
	MyString(MyString&& other) noexcept;
	MyString& operator=(MyString&& other) noexcept;

	// Destructor
	~MyString();
};