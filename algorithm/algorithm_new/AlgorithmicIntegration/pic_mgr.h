#pragma once
#include"WorkerThread.h"
#include<list>
#include"mutex.h"
#include"myThread.h"
using namespace std;
class pic_mgr
{
public:
	pic_mgr();
	~pic_mgr();
	static pic_mgr * instace();
	void push(std::shared_ptr<FrameNode>);
private:
	void run();
	myThread thread_;
	MutexObject cslist_;
	std::list<std::shared_ptr<FrameNode>> list_frame_;

};

