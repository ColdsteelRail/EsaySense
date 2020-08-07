#pragma once

#include "AlgorithmInterface.h"
#include "Utils/cm_thread_critical_region.h"
#include "Utils/cm_buffer_pool.h"
#include "NetLibSDK.h"


#include <memory>
#include <string>
#include <string.h>
#include <map>
#include <list>
#include <queue>
//#include <Python.h>
#include"Utils/systime.h"
#pragma pack(push,4)

struct FrameNode {
	char filename[64];
	unsigned long long pts;
	long hplay;
	int size;
	int width;
	int height;
	int algorithm_id;
	char rgb_buf[0];
};

#pragma pack(pop)
#define ALARM_STATE_BEGIN 1
#define ALARM_STATE_ING 2
#define ALARM_STATE_END	3
#define ALARM_STATE_NO	4
#define ALARM_STATE_UNKOWN	5

struct ChannelInfo {
	std::string uuid;
	std::string alarmuuid;
	std::string alarmstarttime;
	std::string alarmendtime;
	int algorithm_id;
	long hplay;
	int frame_num;
	int frame_flag;
	int no_alarm_flag;
	int alarm_cur;
	int alarm_id;
	AlgorithmInterface * algorithmInterface;
	std::list<std::shared_ptr<FrameNode>> m_buf_queue;
	cm::CBaseLock* m_buf_lock;
private:
	CMilliSecTimer timer_;
public:
	ChannelInfo()
	{
		alarm_id = 0;
		frame_flag = 0;
		frame_num = 0;
		no_alarm_flag = 0;
		alarm_cur = ALARM_STATE_NO;
		timer_.SetSpan(1);
	}
	int get_alarm(bool alarm, int m_framflag)
	{
		int alarm_new = alarm_cur;

		switch (alarm_cur)
		{
		case ALARM_STATE_NO:
			{
				if (alarm)
				{
					if(timer_.IsTrigger())
					{
						alarm_cur = ALARM_STATE_BEGIN;
					}
				
				}
			}
			break;
		case ALARM_STATE_BEGIN:
			{
				if (alarm )
				{
					alarm_cur = ALARM_STATE_ING;
					no_alarm_flag = 0;
				}
				else
				{
					no_alarm_flag++;
					if (no_alarm_flag * m_framflag >= 50)
					{
						alarm_cur = ALARM_STATE_END;
						timer_.SetSpan(30000);//报警结束后，设置时间保护，时间保护内不报警
					}

				}
			}
			break;
		case ALARM_STATE_ING:
			{
				if (alarm)
				{
					no_alarm_flag = 0;
				}
				else
				{
					no_alarm_flag++;
					if (no_alarm_flag * m_framflag >= 50)
					{
						alarm_cur = ALARM_STATE_END;
						timer_.SetSpan(30000);//报警结束后，设置时间保护，时间保护内不报警
					}
				}
	
			}
			break;
		case ALARM_STATE_END:
			{
				if (alarm)
				{
					if (timer_.IsTrigger())
						alarm_cur = ALARM_STATE_BEGIN;//报警结束后，产生新报警后，时间保护外开始报警
					else
						alarm_cur = ALARM_STATE_NO;//报警结束后，产生新报警后，时间保护内不报警
				}
				else
				{
					alarm_cur = ALARM_STATE_NO;
				}
			}
			break;
	
		default:
			{
				printf("%d,%d\n", alarm, alarm_cur);
				return ALARM_STATE_UNKOWN;
			}
		}
		//printf(" %d,%d -> %d\n", alarm,  alarm_new,alarm_cur);
		return alarm_cur;

	}
	void push_frame(char*buf, int size, LPNET_FRAMEINFO frameInfo)
	{

		frame_num++;

		if (frame_flag !=0)
		{
			if ((frame_num%frame_flag) != 0)
			{
				//printf(" %d push_frame !!!!!!!!!!!!!!!!!!!!!!!!!!!!\n" frame_num);
				return;
			}

		}
		//printf("%d push_frame \n", frame_num);
		//return;
		FrameNode * frame= (FrameNode*)malloc(sizeof(FrameNode) + size);
		std::shared_ptr<FrameNode> frame_node(frame, std::bind(free, frame));
		//frame_node->uuid = uuid;
		//frame_node->rgb_buf = m_buffer_pool.GetBuffer(size);
		memcpy((void*)frame_node->rgb_buf, buf, size);
		frame_node->size = size;
		frame_node->width = frameInfo->frame_width;
		frame_node->height = frameInfo->frame_height;
		frame_node->algorithm_id = algorithm_id;
		frame_node->pts = frameInfo->pts;
		frame_node->hplay = hplay;


		m_buf_lock->Lock();
		if (m_buf_queue.size()>1)
		{
			m_buf_queue.clear();
		}
		m_buf_queue.push_back(frame_node);
		m_buf_lock->Unlock();
	}
	std::shared_ptr<FrameNode> get_frame()
	{
		std::shared_ptr<FrameNode> frame;
		m_buf_lock->Lock();
		if (m_buf_queue.size() > 0)
		{
			frame = m_buf_queue.front();
			m_buf_queue.pop_front();
		}
		m_buf_lock->Unlock();
		return frame;
	}
};

class WorkerThread 
{
public:
	static WorkerThread* GetInstance();

private:
	WorkerThread();
	~WorkerThread();

	static WorkerThread* m_worker_thread;

public:
	void PushAlgorithm(std::string key, AlgorithmInterface* alit);
	std::string InputFrameToAlgorithm(std::string uuid, int algorithm_id, unsigned char* rgb, int width, int height, long long timestamp, std::vector<int>& alarm_ids, std::string dynamicArgs);
	//帧队列

	//bool PrepareAlgorithm();
	void StartThread();
private:
	//bool m_is_algorithm_ready[5];
	
public:
	//PyObject* m_algorithm_fun;
	FILE * m_file;
	CMilliSecTimer timer_;
	std::map<std::string, AlgorithmInterface*> m_map_algorithms;
	std::queue<std::shared_ptr<FrameNode>> m_buf_queue;
	cm::CBaseLock* m_buf_lock;
	cm::CBufferPool m_buffer_pool;
};


