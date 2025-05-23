#include "work_with_file.h"

FILE* open_file(const char* file_name, const char* mode)
{
    FILE* file = nullptr;
    if (fopen_s(&file, file_name, mode) != 0) {
        std::cerr << "\nOpen file Error\n";
        return nullptr;
    }

    return file;
}

// Get number elements that was written in the file, that was expected to be written, ptr to file, and what was written
bool write_or_error(size_t written, size_t expected, FILE* f, const char* what)
{
    if (written != expected) {
        std::fclose(f);
        std::cerr << "Error writing to file while saving " << what << "\n";
        return false;
    }
    return true;
}

// Get number elements that was read from the file, that was expected to be read, ptr to file, and what was read
bool read_or_error(size_t read, size_t expected, FILE* f, const char* what)
{
    if (read != expected) {
        std::fclose(f);
        std::cerr << "������ ������ �� ����� ��� �������� " << what << "\n";
        return false;
    }
    return true;
}
