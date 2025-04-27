// Потерял другую версию при переустановке системы, так что сейчас буду заполнять функциями по мере необходимости
#pragma once
#include <iostream>
#include <cstring>	//memcpy, strcpy_s
#include <algorithm> // copy

char* deep_copy(const char* user_string);


void resize_arr(char*& str, size_t& arr_capacity);


