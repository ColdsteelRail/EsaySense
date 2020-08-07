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
	// Returns a python function object
	extern PyObject* GetPythonFun(int GPUid,std::string file_name, std::string fun_name, std::string modelArgs,
		 std::string algorithmInstanceAddress, std::string algorithmInstancePort, std::string roi);
	// Runs a python function and returns a string result
	extern std::string RunPython(PyObject* fun, std::string uuid, unsigned char* rgb, int width, int height, long long timestamp, std::vector<int>& alarm_ids, std::string dynamicArgs);
}

