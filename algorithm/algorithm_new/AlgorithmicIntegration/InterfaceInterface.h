#pragma once

#include "NetLibSDK.h"
#include "InterfaceModel.h"

#include <string>


class AlarmParse
{
public:
	std::string alarmdescribe;
	int alarmlevel;
	int alarmmodule;
	std::string alarmtime;
	std::string alarmname;
	int alarmtype;		//��ӦС��
	std::string alarmuuid;
	int id;
	std::string sourceId;
	int sourcetype;		//��Ӧ����

	//bool ParseJson(const char* jsonStr);
};


//������dll�ӿ�  ����
class InterfaceInterface
{
public:
	static long Login(std::string ip, int port, std::string username, std::string password);
	static InterfaceInterface* GetInstance();

private:
	InterfaceInterface();
	~InterfaceInterface();

	static InterfaceInterface* m_interface_dll;
	void Init();

public:
	void SdkDestory();

public:
	void GetTsAddr(long hplay, NET_TSADDR_INFO &info);

public://��Ƶ�ڵ�
	//��ȡ�豸��֯�ṹ��
	bool GetOrganizationStructureTree();
	int GetDeviceCount();
	std::string GetDeviceUUID(int index);
	std::string GetDeviceUUID(int algorithm_id, int index);

	bool m_is_getdevice_finish;
public:
	JDeviceGroupList m_device_list;

public://����sdk
	//�Ƿ��½�ɹ�
	bool CheckLogin();

	//ʵʱ
	long RealPlay(std::string uuid, long long suid, int id, int level, int width, int height, Notify notify_cb, RealDataCallBack decode_cb, void* userdata);
	long RealStop(long hplay);
	const char* GetLastFrame(long hplay, int &rgb24len);
	long Snapshot(long hplay, const char* filename);
	long StartRecord(long h_realplay, const char *filename);
	long StopRecord(long h_realplay);
	long StartSpeak(long h_realplay);
	long StopSpeak(long h_realplay);
	long GetResolution(long h_realplay, int &w, int &h);

	//�ϴ�
	bool UUID2SuibID(const char* uuid, SUB_ID_INFO & subid);
	
	//����
	long DealAlarmLog(SYS_ID_INFO &id, int alarmtype, const char  * UserName, const char * DutyMan, const char * Detail);

private:
	static long g_login;
};

