#include "InterfaceInterface.h"

#include "Utils/cm_string_coding.h"
#include <memory.h>
#include <iostream>
InterfaceInterface* InterfaceInterface::m_interface_dll = NULL;
long InterfaceInterface::g_login = 0;

InterfaceInterface::InterfaceInterface()
{
	m_is_getdevice_finish = false;
}


InterfaceInterface::~InterfaceInterface()
{
}

long InterfaceInterface::Login(std::string ip, int port, std::string username, std::string password)
{
	if (g_login != 0) {
		NetLib_Logout(g_login);
		g_login = 0;
	}


	NetLib_Init([](bool timeout, const char* jsonStr, void* context) {
		int i = 123;
		if (timeout)
		{

		}



	}, NULL);

	NET_LOGIN_INFO info;
	memset(&info, 0, sizeof(info));
	info.port = port;
	strcpy(info.host, ip.c_str());
	strcpy(info.username, username.c_str());
	strcpy(info.password, password.c_str());
	//std::string utf8_str;
	//cm::cm_string_gb2312_to_utf8((char*)ip.c_str(), ip.size(), utf8_str);
	//strcpy(info.host, utf8_str.c_str());
	//cm::cm_string_gb2312_to_utf8((char*)username.c_str(), ip.size(), utf8_str);
	//strcpy(info.username, utf8_str.c_str());
	//cm::cm_string_gb2312_to_utf8((char*)password.c_str(), ip.size(), utf8_str);
	//strcpy(info.password, utf8_str.c_str());

	g_login = NetLib_Login(&info);

	m_interface_dll->Init();

	return g_login;
}


InterfaceInterface* InterfaceInterface::GetInstance()
{
	if (m_interface_dll == NULL)
	{
		m_interface_dll = new InterfaceInterface;
	}

	return m_interface_dll;
}

void InterfaceInterface::Init()
{
	if (g_login <= 0)
		return;

}

void InterfaceInterface::SdkDestory()
{
	g_login = 0;
	NetLib_Destroy();
}

void InterfaceInterface::GetTsAddr(long hplay, NET_TSADDR_INFO &info)
{
	if (g_login <= 0) {
		std::cout << "NetLib_GetTsAddr g_login < 0" << std::endl;
		return;
	}

	NetLib_GetTsAddr(hplay, info);
}

bool InterfaceInterface::CheckLogin()
{
	if (g_login <= 0)
		return false;

	return NetLib_checkLogin(g_login);
}

bool InterfaceInterface::GetOrganizationStructureTree()
{
	if (g_login <= 0)
		return false;

	NetLib_GetOrganizeListInfo(g_login, [](bool timeout, const char* jsonStr, void* context) {
		
		if (jsonStr == NULL)
			return;
		//std::cout << jsonStr << std::endl;
		if (InterfaceInterface::GetInstance()->m_device_list.ParseJson(jsonStr))
		{
			InterfaceInterface::GetInstance()->m_is_getdevice_finish = true;
		}


	}, this);


	return true;
}

int InterfaceInterface::GetDeviceCount()
{
	return m_device_list.m_device_list.size();
}
std::string InterfaceInterface::GetDeviceUUID(int index)
{
	if (m_device_list.m_device_list.size() <= index)
		return "";

	return m_device_list.m_device_list[index]->SubEquipmentInfoID;
}

std::string InterfaceInterface::GetDeviceUUID(int algorithm_id, int index)
{
	int count = 0;
	for (int i = 0; i < m_device_list.m_device_list.size(); i++)
	{
		for (int j = 0; j < m_device_list.m_device_list[i]->algorithm_ids.size(); j++) {
			if (m_device_list.m_device_list[i]->algorithm_ids[j] == algorithm_id) {
				if (index == count) {
					return m_device_list.m_device_list[index]->SubEquipmentInfoID;
				}
				count++;
			}
		}
	}
	return "";
}

#pragma region 实时流

long InterfaceInterface::RealPlay(std::string uuid, long long suid, int id, int level, int width, int height, Notify notify_cb, RealDataCallBack decode_cb, void* userdata)
{
	if (g_login <= 0)
		return -1;

	NET_DEVICE_CLIENTINFO info1 = { 0 };
	info1.enable_mata = 0;
	info1.hwnd = NULL;
	strcpy(info1.channel.UUID, uuid.c_str());
	info1.channel.SUID = suid;
	info1.channel.id = id;
	info1.level = level;
	info1.decode_format.width = width;
	info1.decode_format.height = height;
	info1.decode_format.format = NET_DEVICE_DATA_TYPE_RGB24; //NET_DEVICE_DATA_TYPE_RGB565;
	info1.notify_cb = notify_cb;
	info1.decode_cb = decode_cb;
	info1.userdata = userdata;
	long hPlay = NetLib_StartRealPlay(g_login, &info1);
	if (hPlay > 0)
	{
		NetLib_SetDrawAspectRatio(hPlay, DRAW_ASPECT_RATION_FULL);
		//NetLib_SetDrawAspectRatio(g_hPlay, DRAW_ASPECT_RATION_16_9);
		return hPlay;
	}

	return -1;
}

long InterfaceInterface::RealStop(long hplay)
{
	if (g_login <= 0)
		return -1;

	return NetLib_StopRealPlay(g_login, hplay);
}

const char* InterfaceInterface::GetLastFrame(long hplay, int &rgb24len)
{
	return NetLib_GetLastFrame(hplay, rgb24len);
}

long InterfaceInterface::Snapshot(long hplay, const char* filename)
{
	if (g_login <= 0)
		return -1;

	return NetLib_Snapshot(hplay, /*"D:\\test_file\\capture\\123.jpg"*/filename);
}
long InterfaceInterface::StartRecord(long hplay, const char *filename)
{
	if (g_login <= 0)
		return -1;

	return NetLib_StartRecord(hplay, filename);
}
long InterfaceInterface::StopRecord(long h_realplay)
{
	if (g_login <= 0)
		return -1;

	return NetLib_StopRecord(h_realplay);
}

long InterfaceInterface::StartSpeak(long h_realplay)
{
	return NetLib_StartSpeak(h_realplay);
}

long InterfaceInterface::StopSpeak(long h_realplay)
{
	return NetLib_StopSpeak(h_realplay);
}

long InterfaceInterface::GetResolution(long h_realplay, int &w, int &h)
{
	return NetLib_GetResolution(h_realplay, w, h);
}

#pragma endregion

bool InterfaceInterface::UUID2SuibID(const char* uuid, SUB_ID_INFO & subid)
{
	if (g_login <= 0)
		return false;

	return NetLib_UUID2SUBID(g_login, uuid, subid);
}

#pragma region 报警

long InterfaceInterface::DealAlarmLog(SYS_ID_INFO &id, int alarmtype, const char  * UserName, const char * DutyMan, const char * Detail)
{
	if (g_login <= 0)
		return -1;

	return NetLib_DealAlarmLogBySubid(g_login, id, alarmtype, UserName, DutyMan, Detail);

}
#pragma endregion

