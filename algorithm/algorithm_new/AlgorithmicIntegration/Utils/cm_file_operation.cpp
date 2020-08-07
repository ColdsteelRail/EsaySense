#include "cm_file_operation.h"


#ifdef WIN32
#include <io.h>
#include <sys/stat.h>
#include <Windows.h>
#include <direct.h>
#else
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#endif

#ifndef INT_MAX
#define INT_MAX       2147483647
#endif

namespace cm {

	bool is_dir(char* dir_path)
	{
#ifdef WIN32
		struct _stat buf = { 0 };
		int ret = _stat(dir_path, &buf);
#else
		struct stat buf = { 0 };
		int ret = stat(dir_path, &buf);
#endif
		if (ret != 0) {
			return false;
		}

		if (buf.st_mode & S_IFDIR) {
			return true;
		}

		return false;
	}

	void mk_dir(char* dir_path)
	{
#ifdef WIN32
		_mkdir(dir_path);
#else 
		mkdir(dir_path, 0755);
#endif
	}

#ifdef WIN32
	bool ergodic_dir(const char* dir_path, const std::function<bool(std::string, std::string)> &func)
	{
		intptr_t handle_file;
		struct _finddata_t findData;
		std::string str_dir_path = dir_path;
		std::string str_file_path;

		handle_file = _findfirst((str_dir_path + "/*").c_str(), &findData);
		if (handle_file == -1) {
			return false;
		}
		do
		{
			if (findData.attrib & _A_SUBDIR)
			{
				continue;
			}
			else {
				str_file_path = str_dir_path + "/" + findData.name;
				if (!func(str_file_path, findData.name)) {
					break;
				}
			}
		} while (_findnext(handle_file, &findData) == 0);
		_findclose(handle_file);

		return true;
	}
#else
	bool ergodic_dir(const char* dir_path, const std::function<bool(std::string, std::string)> &func) 
	{
		DIR *dfd;
		std::string str_dir_path = dir_path;
		std::string str_file_path;

		struct dirent *dp;
		if ((dfd = opendir(dir_path)) == NULL)
		{
			return false;
		}
		while ((dp = readdir(dfd)) != NULL)
		{
			if (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0)//еп╤о
				continue;

			if (dp->d_type == DT_DIR) {
				
				std::string str_child_dir_path = str_dir_path + "/" + dp->d_name;

				ergodic_dir(str_child_dir_path.c_str(), func);

				continue;
			}

			if (dp->d_type == DT_REG) {
				str_file_path = str_dir_path + "/" + dp->d_name;
				if (!func(str_file_path, dp->d_name)) {
					break;
				}
			}

		}
		closedir(dfd);
	}
#endif

	void get_exe_dir(char* file_path, int size)
	{
#ifdef WIN32
		GetModuleFileNameA(NULL, file_path, size);
		auto tmp = strrchr(file_path, '\\');
		if (tmp != NULL) {
			file_path[tmp - file_path] = '\0';
		}
#else
		getcwd(file_path, size);
#endif
		return;
	}

	char *fgetl(FILE *fp)
	{
		if (feof(fp)) return 0;
		size_t size = 512;
		char* line = (char*)malloc(size * sizeof(char));
		if (!fgets(line, size, fp)) {
			free(line);
			return 0;
		}

		size_t curr = strlen(line);

		while ((line[curr - 1] != '\n') && !feof(fp)) {
			if (curr == size - 1) {
				size *= 2;
				line = (char*)realloc(line, size * sizeof(char));
				if (!line) {
					printf("Malloc error %ld\n", size);
					return NULL;
				}
			}
			size_t readsize = size - curr;
			if (readsize > INT_MAX) readsize = INT_MAX - 1;
			fgets(&line[curr], readsize, fp);
			curr = strlen(line);
		}
		if (curr >= 2)
			if (line[curr - 2] == 0x0d) line[curr - 2] = 0x00;

		if (curr >= 1)
			if (line[curr - 1] == 0x0a) line[curr - 1] = 0x00;

		return line;
	}
}