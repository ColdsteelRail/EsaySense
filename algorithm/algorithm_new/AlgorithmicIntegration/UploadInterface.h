#pragma once

#include <map>

class UploadInterface 
{

public:
	static UploadInterface* GetInstance();

private:
	UploadInterface();
	~UploadInterface();

	static UploadInterface* m_upload_instance;

public:
	bool IsConnect(std::string uuid, int alarm_id);
	void AddConnection(std::string uuid, int alarm_id, long long suid, int id, long hplay);

	bool Upload(std::string uuid, int alarm_id, char* json, int len, long long pts);

private:
	std::map<std::string, void*> m_map_upload_connetion;
};