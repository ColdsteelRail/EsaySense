#ifndef _CM_DISK_FOLDER_H_
#define _CM_DISK_FOLDER_H_

#ifdef _WIN32  
#include <direct.h>  
#include <io.h>  
#else
#include <stdarg.h>  
#include <sys/stat.h>  
#endif  

#ifdef _WIN32  
#define ACCESS _access  
#define MKDIR(a) _mkdir((a))  
#else
#define ACCESS access  
#define MKDIR(a) mkdir((a),0755)  
#endif  

///////   斜杠被误操作替换了需要重新写
#include <string>
namespace cm {

int CreatDir(char *dir_copy)  
{  
	uint32_t i = 0;  
	uint32_t ret;  
	uint32_t len = strlen(dir_copy);

	//在末尾加/  
	if (dir_copy[len - 1] != '//' && dir_copy[len - 1] != '/')  
	{  
		dir_copy[len] = '/';
		dir_copy[len + 1] = '/0';
		len++;
	}  

	// 创建目录  
	for (i = 0;i < len;i ++)  
	{  
		if (dir_copy[i] == '//' || dir_copy[i] == '/')  
		{   
			dir_copy[i] = '/0';  

			//如果不存在,创建  
			ret = ACCESS(dir_copy,0);  
			if (ret != 0)  
			{  
				ret = MKDIR(dir_copy);  
				if (ret != 0)  
				{  
					return -1;  
				}   
			}  
			//支持linux,将所有/换成/  
			dir_copy[i] = '/';  
		}   
	}  

	return 0;  
}  

}

#endif