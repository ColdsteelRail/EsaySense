#ifndef FILE_OPERATION_H
#define FILE_OPERATION_H

#include <iostream>
#include <functional>
#include <string>

namespace cm {
	bool is_dir(char* dir_path);
	void mk_dir(char* dir_path);
	bool ergodic_dir(const char* dir_path, const std::function<bool(std::string, std::string)> &func);
	void get_exe_dir(char* file_path, int size);
	char *fgetl(FILE *fp);
}

#endif