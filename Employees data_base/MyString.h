#pragma once
#include <iostream>
#include <cstring>	  //memcpy, strcpy_s, strcmp, strlen
#include <utility>    // move

class MyString
{
private:
	size_t length_;
	size_t capacity_;
	char* str_;

	void resize_str_();		// Resize string double

public:
	// Constructors
	MyString();									// Default constructor
	MyString(const char* c_str);				// Constructor with c-string
	MyString(const MyString& other);			// Copy constructor
	MyString(MyString&& other) noexcept;		// Move constructor

	// Destructor
	~MyString();

	// Copy and move assignment operators
	MyString& operator=(const MyString& other);
	MyString& operator=(MyString&& other) noexcept;

	// Get
	const char* get_str() const;
	const size_t get_len() const;
	const size_t get_capacity() const;

	void input_str();		// Get string by one simbol
};