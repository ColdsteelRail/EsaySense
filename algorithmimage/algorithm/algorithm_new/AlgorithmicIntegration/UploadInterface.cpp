#include "UploadInterface.h"

#include "Common.h"
#include "transferlib.h"
#include "InterfaceInterface.h"

#include <iostream>

UploadInterface* UploadInterface::m_upload_instance = NULL;

UploadInterface* UploadInterface::GetInstance()
{
	if (m_upload_instance == NULL)
	{
		m_upload_instance = new UploadInterface();
	}

	return m_upload_instance;
}


UploadInterface::UploadInterface()
{
	
}

UploadInterface::~UploadInterface()
{

}

bool UploadInterface::IsConnect(std::string uuid, int alarm_id)
{
	std::string key = uuid + "_" + std::to_string(alarm_id);
	auto iter = m_map_upload_connetion.find(key);
	if (iter == m_map_upload_connetion.end()) {
		return false;
	}
	return true;
}

void UploadInterface::AddConnection(std::string uuid, int alarm_id, long long suid, int id, long hplay)
{
	std::string key = uuid + "_" + std::to_string(alarm_id);

	NET_TSADDR_INFO info = { 0 };
	InterfaceInterface::GetInstance()->GetTsAddr(hplay, info);
	std::cout << "GetTsAddr hplay:" << hplay << std::endl;
	std::cout << "tslib_stream_start ip:" << info.ip << " port:" << info.port << " suid;" << suid << " id:" << id << "alarm_id:"<< alarm_id<<std::endl;
	void* cnn = tslib_stream_start(info.ip, info.port, suid, id, DEFINE_MATA_MIX_START_LEVEL + alarm_id);
	if (cnn == NULL) {
		std::cout << "tslib_stream_start Ê§°Ü" << std::endl;
		return;
	}

	m_map_upload_connetion[key] = cnn;
}

bool UploadInterface::Upload(std::string uuid, int alarm_id, char* json, int len, long long pts)
{
	std::string key = uuid + "_" + std::to_string(alarm_id);

	auto iter = m_map_upload_connetion.find(key);
	if (iter == m_map_upload_connetion.end()) {
		std::cout << "m_map_upload_connetion.find  not find" << std::endl;
		return false;
	}

	void* handle = iter->second;
	if (tslib_push_meta(handle, json, len, pts) <= 0) {
		std::cout << "tslib_push_meta failed len:" << len << " json:" << json << std::endl;
		tslib_stream_end(handle);
		m_map_upload_connetion.erase(iter);
		return false;
	}

	//std::cout << "tslib_push_meta len:" << len << " json:" << json << std::endl;

	return true;
}