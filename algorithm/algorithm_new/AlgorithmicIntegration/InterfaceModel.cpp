#include "InterfaceModel.h"

#include <iostream>

bool JDeviceGroupList::ParseJson(const char* json)
{
	Json::Reader jsondt;
	Json::Value root;
	if (!jsondt.parse(json, root)) {
		return false;
	}

	return ParseJson(root);
}

bool JDeviceGroupList::ParseJson(Json::Value jsonOt)
{

	Json::Value &result = jsonOt["result"];
	Json::Value &data = result["data"];

	for (int index = 0; index < data.size(); ++index)
	{
		Json::Value & OrganizeList = data[index];

		Json::Value &SubEquipments = OrganizeList["SubEquipments"];
	
		for (int subIndex = 0; subIndex < SubEquipments.size(); ++subIndex)
		{
			Json::Value& Sub = SubEquipments[subIndex];

			if (Sub["SubEquipmentInfoID"].isNull())
			{
				continue;
			}
			//if (Sub["SUID"].isNull())
			//{
			//	continue;
			//}
			//if (Sub["ICMSSubEquipmentID"].isNull())
			//{
			//	continue;
			//}

			std::shared_ptr<JDeviceNode> device_node(new JDeviceNode());

			device_node->EquipmentInfoID = Sub["EquipmentInfoID"].asCString();

			device_node->ICMSSubEquipmentID = Sub["ICMSSubEquipmentID"].asInt();
//#if WIN32
//			device_node->SUID = _atoi64(Sub["SUID"].asCString());
//#else
//			device_node->SUID = atoll(Sub["SUID"].asCString());
//#endif
			device_node->SubEquipmentInfoID = Sub["SubEquipmentInfoID"].asCString();

			auto DetailedSet = Sub["DetailedSet"].asString();
			if (DetailedSet.size() > 0)
			{
				Json::Reader jsondt1;
				Json::Value root1;
				if (!jsondt1.parse(DetailedSet, root1)) {
					return false;
				}

				Json::Value va = root1["va"];
				for (int al_id = 0; al_id < va.size(); al_id++) {
					device_node->algorithm_ids.push_back(va[al_id].asInt());
				}

			}
			
			m_device_list.push_back(device_node);
		}
	}

	return true;
}