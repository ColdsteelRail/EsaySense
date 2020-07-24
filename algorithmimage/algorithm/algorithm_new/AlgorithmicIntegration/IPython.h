#pragma once

#include "Python.h"
#include "ndarrayobject.h"
#include <string>
#include <vector>

namespace ipython{
	extern bool InitPython();
	extern void UnInitPython();
	extern bool InitThread();
	extern bool UnInitThread();
	extern PyObject* GetPythonFun(int GPUid,std::string file_name, std::string fun_name, std::string modelArgs,
		 std::string algorithmInstanceAddress, std::string algorithmInstancePort, std::string roi);
	extern std::string RunPython(PyObject* fun, std::string uuid, unsigned char* rgb, int width, int height, long long timestamp, std::vector<int>& alarm_ids);
}

