

#include "Config.h"
#include "Utils/inifile.h"
#include "Utils/cm_file_operation.h"
#include <memory.h>
static SettingConfig * stc_SettingConfig = 0;
SettingConfig & SettingConfig::GetInstance()
{
	if (!stc_SettingConfig)
	{
		stc_SettingConfig = new SettingConfig;

	}
	return *stc_SettingConfig;
}

SettingConfig::SettingConfig()
{
	printf("SettingConfig load ");
	char path[265];
	memset(path, 0, 265);
	//cm::get_exe_dir(path, 265);
	strcat(path, "./SettingConfig.ini");
	cout << "ini path:" << path << endl;

	IniFile ini_file(path);
	modelArgs = ini_file.readStrEnv("MODEL_ARGS","{\"arg1\":1,\"arg2\":2}");
	InstanceAddr = ini_file.readStrEnv("ALGORITHM_INSTANCE_ADDRESS","localhost");
	InstancePort = ini_file.readIntEnv("ALGORITHM_INSTANCE_PORT",8001);
	roi = ini_file.readStrEnv("ROI","[[50,50],[450.500]]");
	analysisFrequency = ini_file.readIntEnv("ANALYSIS_FREQUENCY", 5);
	controlFlag = ini_file.readStrEnv("CONTROL_FLAG", "start");
	event_id = ini_file.readStrEnv("EVENT_ID","ffasfa234sa");

	ini_file.setSection("Config");
	m_ip = ini_file.readStrEnv("CONFIG_IP_ADDRESS", "171.221.175.153");
	m_port = ini_file.readIntEnv("CONFIG_PORT", 12000);
	m_username = ini_file.readStrEnv("CONFIG_USER_NAME", "admin");
	m_password = ini_file.readStrEnv("CONFIG_PASS_WORD", "admin");
	m_handle_begin = ini_file.readIntEnv("HANDLE_INDEX_BEGIN", 1);
	m_handle_end = ini_file.readIntEnv("HANDLE_INDEX_END", 1);

	ini_file.setSection("Upload");
	m_upload_ip = ini_file.readStrEnv("UPLOAD_IP_ADDRESS", "171.221.175.153");
	m_upload_port = ini_file.readIntEnv("UPLOAD_PORT", 12000);

	ini_file.setSection("Alarm");
	m_alarm_ip = ini_file.readStrEnv("ALARM_IP_ADDRESS", "171.221.175.153");
	m_alarm_port = ini_file.readIntEnv("ALARM_PORT", 5672);
	m_alarm_username = ini_file.readStrEnv("Username", "icms");
	m_alarm_password = ini_file.readStrEnv("Password", "icms");
	m_alarm_host = ini_file.readStrEnv("Vhost", "icmhs");
	m_alarm_nodeid = ini_file.readStrEnv("NodeId", "600200");

	ini_file.setSection("Algorithm");
	m_gpu_id = ini_file.readIntEnv("GPUID", 0);
	m_python_path = ini_file.readStrEnv("Python_path", "/home/roo/miniconda3");

	m_frameflag = ini_file.readIntEnv("frame_flag", 2);
	m_algorithm_type = ini_file.readIntEnv("Algorithm_type", 3);
	m_algorithm_file = ini_file.readStrEnv("ALGORITHM_SO_NAME", "test_python");
	std::string device_id = ini_file.readStrEnv("DEVICE_ID", "1,");
	AnalysisDeviceIds(device_id);


	ini_file.setSection("ftp");

	m_ftp_host = ini_file.readStrEnv("ftp_host", "127.0.0.1");
	m_ftp_user = ini_file.readStrEnv("ftp_user", "ftptest");
	m_ftp_pwd = ini_file.readStrEnv("ftp_pwd", "123456");
	m_ftp_dir = ini_file.readStrEnv("ftp_dir", "/home/ftptest/");
	//m_ftp_dir = ini_file.readStr("ftp_dir", "/home/roo/miniconda3");
	//std::string algorithm_id = ini_file.readStr("Algorithm_id", "");
	//std::string algorithm_range = ini_file.readStr("Algorithm_range", "");

	//std::cout << "Algorithm_id:" << algorithm_id << " Algorithm_range" << algorithm_range << std::endl;
	std::cout << "frame_flag:" << m_frameflag << std::endl;
	//AnalysisAlgorithmString(algorithm_id, algorithm_range);

	std::cout << "stream server IP:" << m_ip << " port:" << m_port << std::endl;
	std::cout << "stream device_ids count:" << m_device_ids.size();
	for (int i = 0; i < m_device_ids.size(); i++) {
		std::cout << "device_id:" << m_device_ids[i] << std::endl;
	}

	//std::cout << "stream algorithm_id count:" << m_algorithm_config.size();
	//for (int i = 0; i < m_algorithm_config.size(); i++) {
	//	std::cout << "algorithm_id:" << m_algorithm_config[i].algorithm_id << " begin index;" << m_algorithm_config[i].algorithm_begin << " end index:" << m_algorithm_config[i].algorithm_end;
	//}
	std::cout << std::endl;
}

SettingConfig::~SettingConfig()
{
}

void SettingConfig::AnalysisDeviceIds(std::string id)
{
	string::size_type pos1 = 0, pos2 = 0;
	pos2 = id.find(",");
	
	while (string::npos != pos2) {
		auto s_id = id.substr(pos1, pos2 - pos1);

		m_device_ids.push_back(s_id);

		pos1 = pos2 + 1;
		pos2 = id.find(",", pos1);
	}
}

void SettingConfig::AnalysisAlgorithmString(std::string id, std::string range)
{
	string::size_type pos1, pos2, pos_range_1, pos_range_2;
	pos1 = 0;
	pos2 = id.find(",");
	pos_range_1 = 0;
	pos_range_2 = 0;
	while (string::npos != pos2) {

		int i_id = atoi(id.substr(pos1, pos2 - pos1).c_str());

		pos_range_2 = range.find("-", pos_range_1);
		if (string::npos == pos_range_2)
			break;
		int range_begin = atoi(range.substr(pos_range_1, pos_range_2 - pos_range_1).c_str());
		pos_range_1 = pos_range_2 + 1;

		pos_range_2 = range.find(",", pos_range_1);
		if (string::npos == pos_range_2)
			break;
		int range_end = atoi(range.substr(pos_range_1, pos_range_2 - pos_range_1).c_str());
		pos_range_1 = pos_range_2 + 1;

		AlgorithmConfigItem aci;
		aci.algorithm_id = i_id;
		aci.algorithm_begin = range_begin;
		aci.algorithm_end = range_end;

		//m_algorithm_config.push_back(aci);

		pos1 = pos2 + 1;
		pos2 = id.find(",", pos1);
	}
}
