#include "MyString.h"


// Resize string double
void MyString::resize_str_()
{
	if (length_ < capacity_ - 1) return; // No need to resize

	size_t new_capacity = capacity_ * 2;
	char* new_str = new char[new_capacity];

	memcpy(new_str, str_, length_ + 1);

	delete[] str_;
	str_ = new_str;
	capacity_ = new_capacity;
}

// -------- Constuctors --------

// Default constructor
MyString::MyString() : length_(0), capacity_(1), str_(new char[capacity_]()) {}

// Constructor with c-string
MyString::MyString(const char* c_str)
{
	if (c_str == nullptr)
	{str_[length_] = '\0';
		str_ = new char[1]();
		length_ = 0;
		capacity_ = 1;
	}

	else
	{
		length_ = strlen(c_str);
		capacity_ = length_ + 1;
		str_ = new char[capacity_];
		memcpy(str_, c_str, length_);
		str_[length_] = '\0';
	}
}

// Copy constructor
MyString::MyString(const MyString& other)
{
	length_ = other.length_;
	capacity_ = other.capacity_;
	str_ = new char[capacity_];
	memcpy(str_, other.str_, capacity_);
}

// Move constructor
MyString::MyString(MyString&& other) noexcept
{
	str_ = other.str_;
	length_ = other.length_;
	capacity_ = other.capacity_;

	other.str_ = nullptr;
	other.length_ = 0;
	other.capacity_ = 0;
}

// Destructor
MyString::~MyString()
{
	delete[] str_;
}

// Copy assignment operator
MyString& MyString::operator=(const MyString& other)
{
	if (this != &other) {
		delete[] str_;

		length_ = other.length_;
		capacity_ = other.capacity_;
		str_ = new char[capacity_];

		memcpy(str_, other.str_, capacity_);
	}
	return *this;
}



// Move assignment operator
MyString& MyString::operator=(MyString&& other) noexcept
{
	if (this != &other) {
		delete[] str_;
		str_ = other.str_;
		length_ = other.length_;

		capacity_ = other.capacity_;
		other.str_ = nullptr;
		other.length_ = 0;
		other.capacity_ = 0;
	}
	return *this;
}

// Getters
// Return const values
const char* MyString::get_str() const { return str_; }
const size_t MyString::get_len() const { return length_; }
const size_t MyString::get_capacity() const { return capacity_; }

void MyString::input_str()
{
	delete[] str_;
	length_ = 0;
	capacity_ = 25;
	str_ = new char[capacity_];
	char ch;
	while (std::cin.get(ch) && ch != '\n')
	{
		resize_str_();
		str_[length_++] = ch;
	}
	str_[length_] = '\0';
}
