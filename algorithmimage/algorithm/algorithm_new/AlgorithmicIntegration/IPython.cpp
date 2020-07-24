#include "IPython.h"

#include "Utils/cm_thread.h"

#include <iostream>
#include <vector>
#include<string>
//#include <opencv2/opencv.hpp>
//#include <opencv2/videoio.hpp>
//using namespace cv;

namespace ipython {

	PyGILState_STATE state;

	bool InitPython()
	{
#if WIN32
		Py_SetPythonHome(L"C:\\ProgramData\\Anaconda3\\envs\\tensorflow");
#else 
		//Py_SetPythonHome(L"/home/ubuntu/miniconda3");
		Py_SetPythonHome(L"/root/miniconda3");
#endif
		
		Py_Initialize();
		if (!Py_IsInitialized()) //检测是否初始化成功
		{
			std::cout << "python init failed" << std::endl;
			return false;
		}
		// 初始化线程支持	
		PyEval_InitThreads();
		// 启动子线程前执行，为了释放PyEval_InitThreads获得的全局锁，否则子线程可能无法获取到全局锁。
		//PyEval_ReleaseThread(PyThreadState_Get());

		import_array();
		//PyRun_SimpleString("import tensorflow as tf");
		//PyRun_SimpleString("import numpy as np");

		PyRun_SimpleString("import sys");
		//PyRun_SimpleString("import cv2");
		PyRun_SimpleString("sys.path.append('./')");
		PyRun_SimpleString("print(sys.path)");

		PyGILState_Ensure();
		//PyRun_SimpleString("print(cv2.__version__)");
		//PyRun_SimpleString("cv2.imread('test.jpg')");
		//PyRun_SimpleString("print(123)");

		return true;
	}

	void UnInitPython() {
		//PyGILState_Ensure();
		//Py_Finalize();
	}

	bool InitThread() {
		//state = PyGILState_Ensure();
		return true;
	}

	bool UnInitThread() {
		//PyGILState_Release(state);
		return true;
	}

	PyObject* GetPythonFun(int GPUid,std::string file_name, std::string fun_name, std::string modelArgs, 
		std::string algorithmInstanceAddress, std::string  algorithmInstancePort, std::string roi)
	{

		std::cout << " PyImport_ImportModule call file_name: " << file_name <<  std::endl;

		PyObject *pModule = NULL, *pDict = NULL;
		pModule = PyImport_ImportModule(file_name.c_str());
		if (!pModule)
		{
			std::cout << file_name << " PyImport_ImportModule failed "  << std::endl;
			exit(0);
		}

		pDict = PyModule_GetDict(pModule);
		if (!pDict) {
			std::cout << file_name << "PyModule_GetDict failed" << std::endl;
			exit(0);
		}

	
		PyObject* pValue = NULL;
		PyObject* pFunc2 = NULL;
		pFunc2 = PyDict_GetItemString(pDict, "AlgorithmGetProperty");
		std::string filename;
		if (pFunc2 && PyCallable_Check(pFunc2))
		{
			pValue = PyEval_CallObject(pFunc2, NULL);
			if (pValue != NULL)
			{
							int rlt0;
							double rlt1;
							char* rlt2=0;
							PyArg_ParseTuple(pValue, "i|d|s", &rlt0, &rlt1, &rlt2);
							if(rlt2)
								filename = rlt2;
							std::cout << rlt0 << "c++:  GPUUseup is: " << rlt1 << "    AlgName is: " << filename << std::endl;
			}
		}

		//PyObject* pValue = NULL;
		PyObject* pArg = PyTuple_New(6);
		int GPUID = GPUid;
		char logPath[1024] = {0};
		char modelArgs_[1024*4] = {0};
		char algorithmInstanceAddress_[1024] = {0};
		char algorithmInstancePort_[1024] = {0};
		char roi_[1024] = {0};

		sprintf(logPath, "log/%s.log", filename.c_str());
		sprintf(modelArgs_, "%s", modelArgs.c_str());
		sprintf(algorithmInstanceAddress_, "%s", algorithmInstanceAddress.c_str());
		sprintf(algorithmInstancePort_, "%s", algorithmInstancePort.c_str());
		sprintf(roi_, "%s", roi.c_str());
		

		PyTuple_SetItem(pArg, 0, Py_BuildValue("i", GPUID));
		PyTuple_SetItem(pArg, 1, Py_BuildValue("s", logPath));
		PyTuple_SetItem(pArg, 2, Py_BuildValue("s", modelArgs_));
		PyTuple_SetItem(pArg, 3, Py_BuildValue("s", algorithmInstanceAddress_));
		PyTuple_SetItem(pArg, 4, Py_BuildValue("s", algorithmInstancePort_));
		PyTuple_SetItem(pArg, 5, Py_BuildValue("s", roi_));
		/*PyObject**/ pFunc2 = PyDict_GetItemString(pDict, "AlgorithmInitModle");
		if (pFunc2 && PyCallable_Check(pFunc2)) {
			pValue = PyEval_CallObject(pFunc2, pArg);
			if (pValue != NULL)
			{
				int rlt;
				PyArg_Parse(pValue, "i", &rlt);
				std::cout << "AlgorithmInitModle return :" << rlt << std::endl;
			}
			else {
				std::cout << "PyEval_CallObject AlgorithmInitModle return NULL" << std::endl;
			}
		}
		else {
			std::cout << "PyDict_GetItemString AlgorithmInitModle failed" << std::endl;
			exit(0);
		}


		PyObject* pFunc = PyDict_GetItemString(pDict, "AlgorithmRun");
		if (!pFunc || !PyCallable_Check(pFunc))
		{
			std::cout << file_name << "PyDict_GetItemString " << fun_name << " failed" << std::endl;
			exit(0);
		}

		return pFunc;

		//return (PyObject*)1;
	}

	std::string RunPython(PyObject* fun, std::string uuid, unsigned char* rgb, int width, int height, long long timestamp, std::vector<int>& alarm_ids, std::string dynamicArgs)//add
	{
		//const char* video_inpath = "input.mp4";
		//VideoCapture capture;
		//capture.open(video_inpath);
		//Mat inMat;
		//capture >> inMat;
		//if (inMat.empty()) {
		//	std::cout << "inMat.empty() is true" << std::endl;
		//	exit(0);
		//}
		//else {
		//	std::cout << "inMat read size:" << inMat.rows << " " << inMat.cols << std::endl;
		//}


//#ifndef _Debug_
		char* rlt6 = "";
		PyObject* pValue = NULL;
		PyObject* pArg = PyTuple_New(4);//change
		PyObject* pList = PyList_New(0);

		npy_intp dims[] = { height, width, 3 }; //给定维度信息
		pList = PyArray_SimpleNewFromData(3, dims, NPY_UINT8, rgb);

		long timeStamps = (long)(timestamp/1000);

		PyTuple_SetItem(pArg, 0, Py_BuildValue("s", uuid.c_str()));
		PyTuple_SetItem(pArg, 1, Py_BuildValue("l", timeStamps));
		PyTuple_SetItem(pArg, 2, pList);
		PyTuple_SetItem(pArg, 3, dynamicArgs.c_str());//add

		//std::cout << "PyEval_CallObject begin" << " fun"<< fun << std::endl;
		pValue = PyEval_CallObject(fun, pArg);
		//std::cout << "PyEval_CallObject end" << pValue << std::endl;
		if (!PyCallable_Check(fun)) {
			std::cout << "PyCallable_Check false" << std::endl;
		}
		int rlt4;
		PyObject* rlt5;
		int rlt7;
		int rlt8;
		PyArrayObject* ret_array;
		if (pValue != NULL) {
			
			PyArg_ParseTuple(pValue, "i|O|s|i|i|O", &rlt4, &rlt5, &rlt6, &rlt7, &rlt8, &ret_array);
			//std::cout << "c++:  ret is:" << rlt4 << std::endl;
			for (int i = 0; i < PyList_Size(rlt5); i++)
			{
				PyObject * rltp = PyList_GetItem(rlt5, i);
				int rlti = int(PyLong_AsLong(rltp));
				if (rlti!=0)
				{
					alarm_ids.push_back(rlti);
				}
				//std::cout << "c++:  result contains alarm_id: " << rlti << std::endl;
				
				
				double* ptr = (double*)PyArray_DATA(ret_array);   //RGB image pointer
    				int num_dim = PyArray_NDIM(ret_array);            //image channels
    				npy_intp* pdim = PyArray_DIMS(ret_array);         //image shape

				Py_DECREF(rltp);
			}
			//Py_DECREF(rlt5);
		}
		else {
			std::cout << "PyEval_CallObject return null" << std::endl;
		}
		Py_CLEAR(pValue);
                //Py_CLEAR(pArg);
                //Py_CLEAR(pList);
                //Py_CLEAR(rlt5);
		//printf("=====================================");
                //Py_CLEAR(ret_array);
		//printf("+++++++++++++++++++++++++++++++++++++");

		return rlt6;
#//else
//		return "";
//#endif
	}

}
