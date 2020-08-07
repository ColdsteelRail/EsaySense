#pragma once

#include "json/json.h"

#include <string>
#include <vector>
#include <memory>

class JDeviceNode;

class JDeviceNode
{
public:
	std::string SubEquipmentInfoID;	//uuid
	std::string EquipmentInfoID;
	long long SUID;				//ͨ����Ϣ
	int ICMSSubEquipmentID;		//ͨ����Ϣ
	std::string SubName;			//������ʾ
	int SubType;				//����ͷ����(����ͼ��) 0x0100 ͨ��(����ͷ)  0x0200 ̽ͷ  0x0300 ���
	std::string SubNumber;
	std::string OnOff;
	std::string Assident;			//֧����Щ����1��̨��2����3��ˢ, 4�ƹ�
	int SubDetailedType;		//SubType������  0x0100ͨ��(����ͷ)��0x0001 ���� 0x0002 ǹ�� 0x0003 ���� 0x0004 ת̨�׹� 0x0005 ת̨����
	std::string DetailedSet;
	std::string DistributeFlag;
	std::string RemarkInfo;
	std::vector<int> algorithm_ids;
	int SubCode;
};

class JDeviceGroupList
{
public:
	int state;
	std::string status;

	std::vector<std::shared_ptr<JDeviceNode>> m_device_list;

	bool ParseJson(const char* json);
	bool ParseJson(Json::Value jsonOt);
};
