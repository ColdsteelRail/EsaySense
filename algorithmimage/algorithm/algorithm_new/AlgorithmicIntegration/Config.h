#pragma once

#include <string>
#include <vector>

struct AlgorithmConfigItem {
	int algorithm_id;
	int algorithm_begin;
	int algorithm_end;
};

class SettingConfig
{
public:
	SettingConfig();
	~SettingConfig();
	static SettingConfig & GetInstance();
public:
	void AnalysisAlgorithmString(std::string id, std::string range);
	//std::vector<AlgorithmConfigItem>m_algorithm_config;
	void AnalysisDeviceIds(std::string ids);

public:
	std::string InstanceAddr;
	int InstancePort;
	std::string modelArgs;
	std::string roi;
	int analysisFrequency;
	std::string controlFlag;
	std::string event_id;
public:
	std::string m_ip;
	int m_port;
	int m_frameflag;
	std::string m_username;
	std::string m_password;
	int m_handle_begin;
	int m_handle_end;

public:
	std::string m_upload_ip;
	int m_upload_port;
public:
	std::string m_alarm_ip;
	int m_alarm_port;
	std::string m_alarm_username;
	std::string m_alarm_password;
	std::string m_alarm_host;
	std::string m_alarm_nodeid;

public:
	int m_gpu_id;
	int m_algorithm_type;
	std::string m_algorithm_file;
	std::string m_python_path;
	std::vector<std::string> m_device_ids;
public:
	std::string m_ftp_host;
	std::string m_ftp_user;
	std::string m_ftp_pwd;
	std::string m_ftp_dir;
};
