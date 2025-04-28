#include "MyString.h"

// Constructor
MyString::MyString() : length(0), capacity(1), str(new char[capacity]) {
	str[0] = '\0';
}

MyString::MyString(const char* input_str)
{
	if (input_str == nullptr) {
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
MyString::MyString(const MyString& other)
{
	length = other.length;
	capacity = other.capacity;
	str = new char[capacity];
	memcpy(str, other.str, capacity);
}

// Copy assignment operator
MyString& MyString::operator=(const MyString& other)
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
MyString::MyString(MyString&& other) noexcept
{
	str = other.str;
	length = other.length;
	capacity = other.capacity;
	other.str = nullptr;
	other.length = 0;
	other.capacity = 0;
}

// Move assignment operator
MyString& MyString::operator=(MyString&& other) noexcept
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
MyString::~MyString()
{
	delete[] str;
}
