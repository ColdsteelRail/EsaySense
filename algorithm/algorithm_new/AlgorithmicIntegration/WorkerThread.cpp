

#include "WorkerThread.h"
#include "InterfaceInterface.h"
#include "Common.h"
#include "UploadInterface.h"
#include "RedisInterface.h"

#include "Utils/cm_thread.h"
#include "transferlib.h"
#include <iostream>
#include <stdlib.h>

#include <mqlib.h>
#include "json/json.h"
void* ThreadProcAlgorithm0(void* param)
{
	return 0;
}

WorkerThread* WorkerThread::m_worker_thread = NULL;

WorkerThread* WorkerThread::GetInstance()
{
	if (m_worker_thread == NULL)
	{
		m_worker_thread = new WorkerThread();
	}

	return m_worker_thread;
}


WorkerThread::WorkerThread()
{
	timer_.SetSpan(15000);
	m_buf_lock = cm::CreateLock();
	m_file = 0;
	//m_file = fopen("./data.rgb","wb");
}

WorkerThread::~WorkerThread()
{
}

//bool WorkerThread::PrepareAlgorithm()
//{
//	if (m_algorithm_fun != NULL)
//		return true;
//
//	m_algorithm_fun = ipython::GetPythonFun(SettingConfig::GetInstance().m_algorithm_file, "AlgorithmRun");
//	if (m_algorithm_fun == NULL)
//		return false;
//
//	std::cout << "load PrepareAlgorithm success" << std::endl;
//
//	return true;
//}


void WorkerThread::PushAlgorithm(std::string key, AlgorithmInterface* alit)
{
	m_map_algorithms[key] = alit;
}

void WorkerThread::StartThread()
{
	
	return;
	cm_pthread_t *m_tensorflow_thd = new cm_pthread_t();
	cm_pthread_create(m_tensorflow_thd, NULL, ThreadProcAlgorithm0, this);
}

std::string WorkerThread::InputFrameToAlgorithm(std::string uuid, int algorithm_id, unsigned char* rgb, int width, int height, long long timestamp, std::vector<int>& alarm_ids, std::string dynamicArgs)
{
	std::string key = uuid + "_" + std::to_string(algorithm_id);
	auto iter = m_map_algorithms.find(key);
	if (iter == m_map_algorithms.end()) {
		std::cout << "InputFrameToAlgorithm not find uuid:" << uuid << " algorithm_id:" << algorithm_id << std::endl;
		return "";
	}
	//if (m_file && uuid== "36")
	//{
	//	fwrite(rgb, width*height * 3, 1, m_file);
	//}
	return iter->second->InputFrame(uuid, rgb, width, height, timestamp, alarm_ids);
}