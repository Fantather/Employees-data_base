#include "MyString.h"


// Resize string double
void MyString::resize_str_()
{
	if (length < capacity - 1) return; // No need to resize

	size_t new_capacity = capacity * 2;
	char* new_str = new char[new_capacity];

	memcpy(new_str, str, capacity);

	delete[] str;
	str = new_str;
	capacity = new_capacity;
}

// Default constructor
MyString::MyString() : length(0), capacity(1), str(new char[capacity]()) {}

// Constructor with c-string
MyString::MyString(const char* c_str)
{
	if (c_str == nullptr)
	{
		str = new char[1];
		str[0] = '\0';
		length = 0;
		capacity = 1;
	}

	else
	{
		length = strlen(c_str);
		capacity = length + 1;
		str = new char[capacity];
		memcpy(str, c_str, capacity);
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

// Move constructor
MyString::MyString(MyString&& other) noexcept
{
	str = other.str;
	length = other.length;
	capacity = other.capacity;

	other.str = new char[1];
	other.length = 0;
	other.capacity = 1;
	other.str[0] = '\0';
}

// Destructor
MyString::~MyString()
{
	delete[] str;
}

// Copy assignment operator
MyString& MyString::operator=(const MyString& other)
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

void MyString::input_str()
{
	delete[] str;
	length = 0;
	capacity = 256;
	str = new char[capacity];
	char ch;
	while (std::cin.get(ch) && ch != '\n')
	{
		resize_str_();
		str[length++] = ch;
	}
	str[length] = '\0';
}
