#include "AlarmInterface.h"

//#include "Common.h"
//
//#include "Utils/cm_string_coding.h"
//#include "Utils/systime.h"
//#include "Json/json.h"
//
//#ifndef WIN32
//#include <string.h>
//#endif
//
//AlarmUpload* AlarmUpload::m_alarm_instance = NULL;
//
//AlarmUpload* AlarmUpload::GetInstance()
//{
//	if (m_alarm_instance == NULL)
//	{
//		m_alarm_instance = new AlarmUpload();
//		m_alarm_instance->Init();
//	}
//
//	return m_alarm_instance;
//}
//
//
//AlarmUpload::AlarmUpload()
//{
//	m_is_ok = false;
//}
//
//AlarmUpload::~AlarmUpload()
//{
//
//}
//
//bool AlarmUpload::Init()
//{
//	if (!mqlib_init(SettingConfig::GetInstance().m_alarm_ip.c_str(), SettingConfig::GetInstance().m_alarm_port, SettingConfig::GetInstance().m_alarm_username.c_str(),
//				    SettingConfig::GetInstance().m_alarm_password.c_str(), SettingConfig::GetInstance().m_alarm_host.c_str()))
//	{
//		m_is_ok = false;
//		std::cout << "mqlib_init failed ip:" << SettingConfig::GetInstance().m_alarm_ip << " port" << SettingConfig::GetInstance().m_alarm_port << std::endl;
//		return false;
//	}
//
//	if (!mqlib_start(MQ_NODE_TYPE_IS, SettingConfig::GetInstance().m_alarm_nodeid.c_str(), NULL, 0))
//	{
//		m_is_ok = false;
//		std::cout << "mqlib_start failed nodeid" << SettingConfig::GetInstance().m_alarm_nodeid << std::endl;
//		return false;
//	}
//
//	m_is_ok = true;
//}
//
//#define DEFINE_STATUS_NOTIFY			1194
//#define DEFINE_ALRAM_NOTIFY				1196
////#ifdef _WIN32
////#include <objbase.h>
////#else
////#include <uuid/uuid.h>
////#endif
////#include <algorithm>  
////static std::string GetUUID()
////{
////	char szGUID[64];
////#ifdef WIN32
////	GUID uuid;
////	CoCreateGuid(&uuid);
////#else
////	TmUUID_t    uuid;
////	TmMsg_CreateUUID(&uuid);
////#endif
////	sprintf(szGUID, "%08X-%04X-%04x-%02X%02X-%02X%02X%02X%02X%02X%02X",
////		uuid.Data1, uuid.Data2, uuid.Data3, uuid.Data4[0], uuid.Data4[1], uuid.Data4[2],
////		uuid.Data4[3], uuid.Data4[4], uuid.Data4[5], uuid.Data4[6], uuid.Data4[7]);
////
////
////	std::string strAlarmLogId(szGUID);
////	transform(strAlarmLogId.begin(), strAlarmLogId.end(), strAlarmLogId.begin(), ::tolower);
////	return strAlarmLogId;
////}
//
//void AlarmUpload::Send(std::string uuid, int algorithm_id, const char *pNodeid)
//{
//	if (!m_is_ok)
//		return;
//
//	Json::Value alarmInfo;
//	Json::Value dateInfo;
//	Json::FastWriter writer;
//	CPreciseTime time(true);
//
//	dateInfo["sourceId"] = uuid;
//
//	std::string str;
//	cm::cm_string_gb2312_to_utf8("…„œÒÕ∑1", strlen("…„œÒÕ∑1"), str);
//	dateInfo["alarmname"] = str;
//	
//	if(algorithm_id == 0)
//		cm::cm_string_gb2312_to_utf8("ΩÈ÷ –π¬©±®æØ", strlen("ΩÈ÷ –π¬©±®æØ"), str);
//	else
//		cm::cm_string_gb2312_to_utf8("ΩÈ÷ –π¬©±®æØ", strlen("ΩÈ÷ –π¬©±®æØ"), str);
//
//	dateInfo["alarmmodule"] = MQ_NODE_TYPE_IS;
//	dateInfo["sourcetype"] = 0x02;//–¥À¿
//	dateInfo["alarmtype"] = algorithm_id;//∞¥’’À„∑®ŒƒµµÃÓ–¥
//	dateInfo["alarmtime"] = time.Format();
//	dateInfo["alarmdescribe"] = str;
//	dateInfo["alarmlog"] = 0x01;//–¥À¿  «∑Ò±®æØ»Îø‚ø™πÿ
//	dateInfo["alarmuuid"] = "";
//
//	alarmInfo["data"] = dateInfo;
//	alarmInfo["SUID"] = "100003";//–¥À¿
//	alarmInfo["msgType"] = DEFINE_ALRAM_NOTIFY;
//
//	string strJson = writer.write(alarmInfo);
//	msg_info_t msgInfo;
//	memset(&msgInfo, 0, sizeof(msg_info_t));
//	msgInfo.msg = (char *)strJson.c_str();
//	msgInfo.len = strJson.size();
//	msgInfo.expiration_sec = 10;
//
//	if (!mqlib_send(&msgInfo, MQ_NODE_TYPE_AS, pNodeid)) {
//		std::cout << "mqlib_send return false" << std::endl;
//	}
//
//}