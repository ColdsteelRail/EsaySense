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
	long long SUID;				//通道信息
	int ICMSSubEquipmentID;		//通道信息
	std::string SubName;			//界面显示
	int SubType;				//摄像头类型(界面图标) 0x0100 通道(摄像头)  0x0200 探头  0x0300 输出
	std::string SubNumber;
	std::string OnOff;
	std::string Assident;			//支持那些功能1云台，2除雾，3雨刷, 4灯光
	int SubDetailedType;		//SubType子类型  0x0100通道(摄像头)：0x0001 快球 0x0002 枪机 0x0003 半球 0x0004 转台白光 0x0005 转台红外
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
