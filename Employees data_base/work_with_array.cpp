#include "work_with_array.h"

// Allocates memory for a new string and copies the content of the input string into it.
char* deep_copy(const char* input_str)
{
	if (input_str == nullptr) return nullptr;

	size_t length = strlen(input_str) + 1;
	char* copy_str = new char[length];

	memcpy(copy_str, input_str, length);
	return copy_str;
}

inline void resize_arr(char*& str, size_t& arr_capacity)
{
	if (str == nullptr) return;

	size_t new_size = strlen(str) * 2;
	char* new_arr = new char[new_size];

	strcpy_s(new_arr, new_size, str);

	delete[] str;
	str = new_arr;
	arr_capacity = new_size;
}

// Get string by one simbol
// Must be nullptr, delete if str is not nullptr
// Return by linl String and it capacity
void get_str(char*& arr, size_t& length, size_t& capacity)
{
	delete[] arr;
	length = 0;
	capacity = 256;

	arr = new char[capacity];
	char ch;

	while (std::cin.get(ch) && ch != '\n')
	{
		if (length >= capacity - 1)
		{
			resize_arr(arr, capacity);
		}

		arr[length++] = ch;
	}

	arr[length] = '\0';
}
