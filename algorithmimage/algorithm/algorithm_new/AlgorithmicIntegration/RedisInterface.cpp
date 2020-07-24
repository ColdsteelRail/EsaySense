#include "RedisInterface.h"


#include "Common.h"
#include "mqlib.h"
#include "Utils/cm_string_coding.h"
#include "Utils/systime.h"
#include "json/json.h"




RedisInterface* RedisInterface::m_redis_instance = NULL;

RedisInterface* RedisInterface::GetInstance()
{
	if (m_redis_instance == NULL)
	{
		m_redis_instance = new RedisInterface();
		m_redis_instance->Init();
	}

	return m_redis_instance;
}

RedisInterface::RedisInterface()
{
	m_is_ok = false;
}

RedisInterface::~RedisInterface()
{

}

bool RedisInterface::Init()
{
	std::cout << "set_redis ip:" << SettingConfig::GetInstance().m_alarm_ip << " port:" << SettingConfig::GetInstance().m_alarm_port << " password:" << SettingConfig::GetInstance().m_alarm_password << std::endl;
	m_redis_agent = new RedisAgent();
	m_redis_agent->set_redis(SettingConfig::GetInstance().m_alarm_ip, SettingConfig::GetInstance().m_alarm_port, "", 0, 1);

	m_is_ok = true;

	return true;
}
#define DEFINE_STATUS_NOTIFY			1194
#define DEFINE_ALRAM_NOTIFY				1196


void RedisInterface::Send(std::string uuid, std::string alarmuuid, std::string starttime, std::string endtime, int algorithm_id, const char *pNodeid,int alarmflag)
{
	if (!m_is_ok)
		return;


	Json::Value alarmInfo;
	Json::Value dateInfo;
	Json::FastWriter writer;
	

	dateInfo["sourceId"] = uuid;

	std::string str;
	//cm::cm_string_gb2312_to_utf8("摄像头1", strlen("摄像头1"), str);
	dateInfo["alarmname"] = "camera1";

	//if (algorithm_id == 0)
	//	cm::cm_string_gb2312_to_utf8("介质泄漏报警", strlen("介质泄漏报警"), str);
	//else
	//	cm::cm_string_gb2312_to_utf8("介质泄漏报警", strlen("介质泄漏报警"), str);

	dateInfo["alarmmodule"] = MQ_NODE_TYPE_IS;
	dateInfo["sourcetype"] = 0x02;//写死
	dateInfo["alarmtype"] = algorithm_id;//按照算法文档填写
	dateInfo["alarmtime"] = starttime;
	dateInfo["alarmendtime"] = endtime;
	dateInfo["alarmdescribe"] = "aa";
	dateInfo["alarmlog"] = 0x01;//写死 是否报警入库开关
	dateInfo["alarmuuid"] = alarmuuid;
	dateInfo["alarmflag"] = alarmflag;
	alarmInfo["data"] = dateInfo;
	alarmInfo["SUID"] = "100003";//写死
	alarmInfo["msgType"] = DEFINE_ALRAM_NOTIFY;
	
	string strJson = writer.write(alarmInfo);
	//std::cout << "call redis_list_push" << std::endl;
	int ret = m_redis_agent->redis_list_push("alarmlist", strJson.c_str());
	if (!ret) {
		std::cout << "redis_list_push return false key:alarmlist value:" << strJson.c_str() << std::endl;
	}
	else {
		std::cout << "redis_list_push return true key:alarmlist value:" << strJson.c_str() << std::endl;
	}
}

void RedisInterface::Send(string strJson) 
{
	int ret = m_redis_agent->redis_list_push("detectlist", strJson.c_str());
	if (!ret) {
		std::cout << "redis_list_push return false key:detectlist value:" << strJson.c_str() << std::endl;
	}
	else {
		std::cout << "redis_list_push return true key:detectlist value:" << strJson.c_str() << std::endl;
	}
}
