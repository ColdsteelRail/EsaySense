// AlgorithmicIntegration.cpp: 定义应用程序的入口点。
//

#include "Common.h"
#include "WorkerThread.h"
#include "InterfaceInterface.h"
#include "UploadInterface.h"
#include "Utils/cm_thread.h"

#include "socketReciver.h"
#include "NetLibSDK.h"
#include "IPython.h"
#include "RedisInterface.h"
#include"pic_mgr.h"
#ifndef WIN32
#include <unistd.h>
#include <sys/time.h>
#include <time.h>
#define Sleep(dwMilliseconds) usleep(dwMilliseconds*1000);
#else
#include <io.h>    
#include <direct.h>
#endif

#ifdef _WIN32
#include <objbase.h>
#else
#include <uuid/uuid.h>
#endif
#include <algorithm>  
static string GetUUID()
{
	char szGUID[64];
#ifdef WIN32
	GUID uuid;
	CoCreateGuid(&uuid);
	sprintf(szGUID, "%08X-%04X-%04x-%02X%02X-%02X%02X%02X%02X%02X%02X",
		uuid.Data1, uuid.Data2, uuid.Data3, uuid.Data4[0], uuid.Data4[1], uuid.Data4[2],
		uuid.Data4[3], uuid.Data4[4], uuid.Data4[5], uuid.Data4[6], uuid.Data4[7]);
#else
	uuid_t uuid;
	char str[36];

	uuid_generate(uuid);
	uuid_unparse(uuid, szGUID);

#endif
 


	string strAlarmLogId(szGUID);
	transform(strAlarmLogId.begin(), strAlarmLogId.end(), strAlarmLogId.begin(), ::tolower);
	return strAlarmLogId;
}
using namespace std;


bool LoginServer(std::string ip, int port, std::string username, std::string password);
bool GetDeviceList();
void StartWork();




//#include <vector>
std::vector<ChannelInfo *> gb_ChannelInfo;
int main()
{
	char chPath[1024] = { 0 };
#ifdef WIN32

	int cnt = ::GetModuleFileName(NULL, chPath, 1024);
	if (cnt <= 0)
	{
		printf("***Error***\n");
		exit(-1);
	}

#else
	
	int cnt = readlink("/proc/self/exe", chPath, 1024);
	if (cnt < 0 || cnt >= 1024)
	{
		printf("***Error***\n");
		exit(-1);
	}
#endif

	if (cnt <= 0)
	{
		printf("Get the current path failed\n");
		return -1;
	}

	int count = 0;
	char modename[128] = { 0 };

	for (int i = cnt; i >= 0; --i)
	{
		if (chPath[i] == '\\' || chPath[i] == '/')
		{
			strcpy(modename, &chPath[i + 1]);
			chPath[i + 1] = '\0';
			break;
		}
	}
	cnt = strlen(modename);
	for (int i = cnt; i >= 0; --i)
	{
		if (modename[i] == '.')
		{
			modename[i] = '\0';
			break;
		}
	}

	int ret = ::chdir(chPath);
	char cchdir[1024] = { 0 };
	::getcwd(cchdir, 1000);


	cout << "step1 python init" << "dir: "<<cchdir<<endl;
	if (!ipython::InitPython())
		return 0;

	//PythonTest();
	//return 0;

	//登陆服务器
	cout << "step2 login server ip:" << SettingConfig::GetInstance().m_ip << " port :" << SettingConfig::GetInstance().m_port << " username:" << SettingConfig::GetInstance().m_username << " password:" << SettingConfig::GetInstance().m_password << endl;
	if (!LoginServer(SettingConfig::GetInstance().m_ip, SettingConfig::GetInstance().m_port, SettingConfig::GetInstance().m_username, SettingConfig::GetInstance().m_password))
		return 0;

	cout << "step3 Get device list" << endl;
	if (!GetDeviceList())
		return 0;

	cout << "step4 start work" << endl;
	StartWork();

	std::thread socket_serv;
	std::string dynamicArgs = "nothing"; 
	socket_serv = std::thread(socketServer, dynamicArgs);


	while (true) {

		bool  hasframe = false;
		for (size_t i = 0; i < gb_ChannelInfo.size(); i++)
		{
			std::shared_ptr<FrameNode> frame_node = gb_ChannelInfo[i]->get_frame();
			if (!frame_node)
			{
				continue;
			}
			hasframe = true;

			std::vector<int> alarm_ids;
			auto result = gb_ChannelInfo[i]->algorithmInterface->InputFrame(gb_ChannelInfo[i]->uuid, (uint8_t*)frame_node->rgb_buf, frame_node->width, frame_node->height, frame_node->pts,alarm_ids, dynamicArgs);
			if (result != "")
			{

				Json::Reader reader;
				Json::Value root;
				if (reader.parse(result, root))
				{
					if (!root["boxes"].isNull() && root["boxes"].size() > 0 && root["boxes"].isArray())
					{
						root["timeStamps"] = (uint64_t)frame_node->pts;
						root["cameraID "] = gb_ChannelInfo[i]->uuid;
						Json::FastWriter writer;
						result = writer.write(root);
						//std::cout << "InputFrameToAlgorithm result:" << result << std::endl;
						//root["boxes"].size(>0;
						//if (SettingConfig::GetInstance().m_algorithm_type!=2)
						{
							if (!UploadInterface::GetInstance()->IsConnect(gb_ChannelInfo[i]->uuid, 0)) {
								//建立上传算法信息链接
								SUB_ID_INFO subid;
								InterfaceInterface::GetInstance()->UUID2SuibID(gb_ChannelInfo[i]->uuid.c_str(), subid);
								UploadInterface::GetInstance()->AddConnection(gb_ChannelInfo[i]->uuid, 0, subid.SUID, subid.id, frame_node->hplay);
							}

							UploadInterface::GetInstance()->Upload(gb_ChannelInfo[i]->uuid, 0, (char*)result.c_str(), result.size(), frame_node->pts);
						}

					}
					else
					{
						std::cout << "InputFrameToAlgorithm result!!!!!!!!!!!!!!!!!!!!!:" << result << std::endl;
						RedisInterface::GetInstance()->Send(result);
					}
				}



			}
			else {
				//std::cout << "result = null RunPython" << std::endl;
			}
			bool alarm = false;
			if (alarm_ids.size() > 0)
			{
				alarm = true;
				gb_ChannelInfo[i]->alarm_id = alarm_ids[0];
			}

			int flag = gb_ChannelInfo[i]->get_alarm(alarm, SettingConfig::GetInstance().m_frameflag);
			if (flag == ALARM_STATE_BEGIN || flag == ALARM_STATE_END)
			{
				CPreciseTime time(true);
				if (flag == ALARM_STATE_BEGIN)
				{
					gb_ChannelInfo[i]->alarmstarttime = time.Format();
					gb_ChannelInfo[i]->alarmendtime = gb_ChannelInfo[i]->alarmstarttime;
					flag = 0x01;
					gb_ChannelInfo[i]->alarmuuid = GetUUID();
					sprintf(frame_node->filename,"%s.jpg", gb_ChannelInfo[i]->alarmuuid.c_str());
					//pic_mgr::instace()->push(frame_node);
				
				}
					
				else
				{
					gb_ChannelInfo[i]->alarmendtime = time.Format();
					flag = 0x02;
				}
					
				//std::cout << "RedisInterface::GetInstance()->Send alarm_ids size:" << alarm_ids.size() << "alarm_id:" << alarm_ids[0] << std::endl;
				RedisInterface::GetInstance()->Send(gb_ChannelInfo[i]->uuid, gb_ChannelInfo[i]->alarmuuid, gb_ChannelInfo[i]->alarmstarttime, gb_ChannelInfo[i]->alarmendtime,gb_ChannelInfo[i]->alarm_id, NULL, flag);
			}
		}
		
		if (!hasframe)
		{
			cm::cm_sleep(10);
		}
		
	}

	ipython::UnInitPython();

	return 0;
}

//登陆
bool LoginServer(std::string ip, int port, std::string username, std::string password)
{
	InterfaceInterface::Login(ip, port, username, password);

	int count = 0;
	while (true) {
		count++;
		if (InterfaceInterface::GetInstance()->CheckLogin()) {
			break;
		}

		if (count > 20)
		{
			cout << "登陆服务器失败" << endl;
			getchar();
			return false;
		}

		cm::cm_sleep(200);
	}

	cout << "登陆服务器成功" << endl;
	return true;
}

//获取视频列表
bool GetDeviceList()
{
	InterfaceInterface::GetInstance()->GetOrganizationStructureTree();

	int count = 0;
	while (true) {
		count++;
		if (InterfaceInterface::GetInstance()->m_is_getdevice_finish) {
			break;
		}

		if (count > 20)
		{
			cout << "获取设备列表超时" << endl;
			getchar();
			return false;
		}

		cm::cm_sleep(200);
	}

	std::cout << "获取设备列表成功 device cout:" << InterfaceInterface::GetInstance()->m_device_list.m_device_list.size() <<endl;
	for (int i = 0; i < InterfaceInterface::GetInstance()->m_device_list.m_device_list.size(); i++) {
		auto item = InterfaceInterface::GetInstance()->m_device_list.m_device_list[i];
		std::cout << "device algorithm_id:" << item->SubType << "device uuid:" << item->EquipmentInfoID << endl;
	}

	return true;
}


void StartWork()
{
	//准备算法
	//if (!WorkerThread::GetInstance()->PrepareAlgorithm()) {
	//	return;
	//}
	int algorithm_id = 0;

	std::string key = std::to_string(algorithm_id);
	auto algorithm = new AlgorithmInterface();
	if (!algorithm->PrepareAlgorithm(algorithm_id))
	{
		std::cout << "PrepareAlgorithm!!!!!!!!!!!!!!!!" << endl;
		Sleep(5000);
		exit(1);
	}
	

	std::cout << "request stream algorithm_id:" << SettingConfig::GetInstance().m_algorithm_type << endl;

	Sleep(2000);


	for (int i = 0; i < SettingConfig::GetInstance().m_device_ids.size(); i++)
	{
		auto uuid = SettingConfig::GetInstance().m_device_ids[i];
		
		auto channel_info = new ChannelInfo();
		channel_info->uuid = uuid;
		channel_info->algorithm_id = algorithm_id;
		channel_info->m_buf_lock = cm::CreateLock();
		channel_info->algorithmInterface = algorithm;
		channel_info->frame_flag = SettingConfig::GetInstance().m_frameflag;
		gb_ChannelInfo.push_back(channel_info);
	}
	
	for (int i = 0; i < gb_ChannelInfo.size(); i++) {

		
		//码流回调
		Notify notify_cb = [](long h_realplay, char *key, void* value, void* userdata) {
			if (strcmp(key, "stream_cut") == 0)
			{
				cout << "断流回调 stream_cut " << endl;
				//stream_cut
			}
			else if (strcmp(key, "stream_regain") == 0)
			{
				cout << "恢复回调 stream_regain " << endl;
			}
			else if (strcmp(key, "render_stop") == 0)
			{

			}
			else if (strcmp(key, "frame_key") == 0)
			{

			}
		};
		//解码数据回调
		RealDataCallBack decode_cb = [](long h_realplay, char *buf, int size, LPNET_FRAMEINFO frameInfo, void* userdata) {

			//算法分类
			ChannelInfo* channel_info = (ChannelInfo*)userdata;
			channel_info->push_frame(buf, size, frameInfo);
		};
		//请求实时流
		cout << "RealPlay uuid:" << gb_ChannelInfo[i]->uuid << endl;
		long hplay = InterfaceInterface::GetInstance()->RealPlay(gb_ChannelInfo[i]->uuid, 0, 0, 0, 0, 0, notify_cb, decode_cb, gb_ChannelInfo[i]);

		gb_ChannelInfo[i]->hplay = hplay;

		Sleep(1000);
	}
	
}

//开始功能
//void StartWork()
//{
//	//准备算法
//	//if (!WorkerThread::GetInstance()->PrepareAlgorithm()) {
//	//	return;
//	//}
//
//	for (int i = 0; i < SettingConfig::GetInstance().m_algorithm_config.size(); i++) {
//		auto item = SettingConfig::GetInstance().m_algorithm_config[i];
//
//		for (int j = item.algorithm_begin; j <= item.algorithm_end; j++) {
//			auto uuid = InterfaceInterface::GetInstance()->GetDeviceUUID(item.algorithm_id, j);
//			if (uuid == "")
//				break;
//
//			std::string key = uuid + "_" + std::to_string(item.algorithm_id);
//			auto algorithm = new AlgorithmInterface();
//			algorithm->PrepareAlgorithm(item.algorithm_id);
//			WorkerThread::GetInstance()->PushAlgorithm(key, algorithm);
//
//			auto channel_info = new ChannelInfo();
//			channel_info->uuid = uuid;
//			channel_info->algorithm_id = item.algorithm_id;
//
//			std::cout << "request stream algorithm_id:" << item.algorithm_id << " uuid:" << uuid << endl;
//
//			//码流回调
//			Notify notify_cb = [](long h_realplay, char *key, void* value, void* userdata) {
//				if (strcmp(key, "stream_cut") == 0)
//				{
//					cout << "断流回调 stream_cut " << endl;
//					//stream_cut
//				}
//				else if (strcmp(key, "stream_regain") == 0)
//				{
//					cout << "恢复回调 stream_regain " << endl;
//				}
//				else if (strcmp(key, "render_stop") == 0)
//				{
//
//				}
//				else if (strcmp(key, "frame_key") == 0)
//				{
//
//				}
//			};
//			//解码数据回调
//			RealDataCallBack decode_cb = [](long h_realplay, char *buf, int size, LPNET_FRAMEINFO frameInfo, void* userdata) {
//
//				//算法分类
//				ChannelInfo* channel_info = (ChannelInfo*)userdata;
//				WorkerThread::GetInstance()->InputFrame(channel_info->uuid, channel_info->algorithm_id, channel_info->hplay, buf, size, frameInfo);
//			};
//			//请求实时流
//			long hplay = InterfaceInterface::GetInstance()->RealPlay(uuid, 0, 0, 0, 0, 0, notify_cb, decode_cb, channel_info);
//			
//			channel_info->hplay = hplay;
//			if (hplay > 0) {
//			}
//			else {
//				std::cout << "RealPlay failed uuid:" << uuid << std::endl;
//			}
//		}
//	}
//}
