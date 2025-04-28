#pragma once
#include <iostream>
#include <cstring>	  //strlen
#include <cstdio>     // FILE*, fopen, fwrite, fread, fclose

// Open file and check
FILE* open_file(const char* file_name, const char* mode);

// Check if the data is written or read correctly
// Must be announcer earlier than the other functions				
static bool write_or_error(size_t written, size_t expected, FILE* f, const char* what);		// Function for checking the result of writing to a file
static bool read_or_error(size_t read, size_t expected, FILE* f, const char* what);			// Function for checking the result of reading from a file