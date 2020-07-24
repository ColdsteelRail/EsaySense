#pragma once

#include "IPython.h"
#include "JIAlgorithm.hpp"

#define NO_USE_CPP_ALGORITH
#ifndef NO_USE_CPP_ALGORITH
#include "LiquidLevelAlgorithm.hpp"
#include "SmokeDetectAlgorithm.hpp"
#endif
#include <string>
#include <vector>

class JIAlgorithm;



class AlgorithmInterface
{

public:
	AlgorithmInterface();
	~AlgorithmInterface();


public:
	bool PrepareAlgorithm(int algorithm_id);
	std::string InputFrame(std::string uuid, unsigned char* rgb, int width, int height, long long timestamp, std::vector<int>& alarm_ids);

private:
	int m_algorithm_id;
	PyObject* m_algorithm_fun;
	JIAlgorithm* m_algorithm_cpp_fun;
};
