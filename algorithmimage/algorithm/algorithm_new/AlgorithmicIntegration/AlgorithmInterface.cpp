#include "AlgorithmInterface.h"

#include "Common.h"
#include <assert.h>

#ifndef WIN32
#include <unistd.h>
#include <sys/time.h>
#include <time.h>
#define Sleep(dwMilliseconds) usleep(dwMilliseconds*1000);
#else
#include <io.h>    
#include <direct.h>
#endif



#ifdef WIN32
#define GetTickCount_ timeGetTime
#else
unsigned long GetTickCount_()

{
	struct timespec ts = { 0 };
	clock_gettime(CLOCK_MONOTONIC, &ts);//此处可以判断一下返回
	return (ts.tv_sec * 1000 + ts.tv_nsec / (1000 * 1000));
}
#endif


AlgorithmInterface::AlgorithmInterface()
{
	m_algorithm_fun = NULL;
}

AlgorithmInterface::~AlgorithmInterface()
{

}

bool AlgorithmInterface::PrepareAlgorithm(int algorithm_id)
{
	if (1 == SettingConfig::GetInstance().m_algorithm_type) {
		//C++
#ifndef NO_USE_CPP_ALGORITH	//关闭C++
		double gpuUsage;
		char *algoName;
		m_algorithm_cpp_fun = new LiquidLevelAlgorithm();
		int ret = m_algorithm_cpp_fun->AlgorithmGetProperty(&gpuUsage, &algoName);
		if (ret == FAILED)
		{
			std::cout << "AlgorithmGetProperty" << std::endl;
			return false;
		}
		std::cout << "GPU usage:" << gpuUsage << "algo name:" << algoName << std::endl;
		ret = m_algorithm_cpp_fun->AlgorithmInitModle(SettingConfig::GetInstance().m_gpu_id, "/tmp/algo.log");
		if (ret == FAILED)
		{
			std::cout << "AlgorithmInitModle" << std::endl;
			return false;
		}
#else
		return false;
#endif
	}
	else if (2 == SettingConfig::GetInstance().m_algorithm_type) {
#ifndef NO_USE_CPP_ALGORITH	//关闭C++
		double gpuUsage;
		char *algoName;
		m_algorithm_cpp_fun = new SmokeDetectAlgorithm();
		int ret = m_algorithm_cpp_fun->AlgorithmGetProperty(&gpuUsage, &algoName);
		if (ret == FAILED)
		{
			std::cout << "AlgorithmGetProperty" << std::endl;
			return false;
		}
		std::cout << "GPU usage:" << gpuUsage << "algo name:" << algoName << std::endl;
		ret = m_algorithm_cpp_fun->AlgorithmInitModle(SettingConfig::GetInstance().m_gpu_id, "/tmp/log.txt");
		if (ret == FAILED)
		{
			std::cout << "AlgorithmInitModle" << std::endl;
			return false;
		}
#else
		return false;
#endif
	}
	else {
		//python算法
		//assert(m_algorithm_fun == NULL)
		m_algorithm_fun = ipython::GetPythonFun(SettingConfig::GetInstance().m_gpu_id,SettingConfig::GetInstance().m_algorithm_file, "AlgorithmRun",
			SettingConfig::GetInstance().modelArgs, SettingConfig::GetInstance().InstanceAddr, std::to_string(SettingConfig::GetInstance().InstancePort), SettingConfig::GetInstance().roi);
		if (m_algorithm_fun == NULL) {
			std::cout << "GetPythonFun AlgorithmRun failed" << std::endl;
			exit(0);
		}
	}

	return true;
}
std::string AlgorithmInterface::InputFrame(std::string uuid, unsigned char* rgb, int width, int height, long long timestamp, std::vector<int>& alarm_ids, std::string dynamicArgs)
{
	//std::cout << "InputFrame type:" << SettingConfig::GetInstance().m_algorithm_type << std::endl;
	if (1 == SettingConfig::GetInstance().m_algorithm_type || 2 == SettingConfig::GetInstance().m_algorithm_type) {
#ifndef NO_USE_CPP_ALGORITH
		CV_FRAME imageFrame;
		imageFrame.cols = width;
		imageFrame.rows = height;
		imageFrame.data = rgb;
		PROCESS_RESULT processResult;
		//std::cout << "AlgorithmRun begin" << std::endl;
		m_algorithm_cpp_fun->AlgorithmRun((char*)uuid.c_str(), timestamp, &imageFrame, &processResult);
		//std::cout << "AlgorithmRun end" << std::endl;

		for (int i = 0; i < processResult.resultLen; i++) {
			if (*processResult.result !=0)
			{
				alarm_ids.push_back(*processResult.result);
			}
			
			processResult.result++;
		}

		return processResult.detectResult;
#else
		return "";
#endif
	}
	else {
		//算法计算
		//std::cout << "ipython::RunPython" << std::endl;
		int time = GetTickCount_();
		auto result = ipython::RunPython(m_algorithm_fun, uuid, (unsigned char*)rgb, width, height, timestamp, alarm_ids, dynamicArgs);
		time = GetTickCount_() - time;
		if (time>100)
		{
			std::cout << "ipython::RunPython  time :" << time << "pts: " << timestamp << std::endl;
		}
		return result;
	}

	return "";
}
