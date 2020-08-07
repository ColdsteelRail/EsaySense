#pragma once
#ifndef _MTHREAD_NEW_H_
#define _MTHREAD_NEW_H_
#include <functional>
#include<thread>
#include<chrono>
class  myThread
{
public:
	typedef std::function<void()> ThreadFunc;
	myThread()
	{
		run_ = false;
	}
	virtual ~myThread()
	{
		Stop();
	}
	bool Start(const ThreadFunc& fun, unsigned int dwStackSize = 512 * 1024)
	{
		Stop();
		run_ = true;
		thread_ = std::thread(fun);
		return true;
	}
	// if dwMilliseconds == 0 will unit waite
	//void Wait(unsigned int dwMilliseconds);
	void Stop()//1 NotifyStop 2 wait(0) 3 close 
	{
		NotifyStop();
		
		if (thread_.joinable())
			thread_.join();
	}
	int GetCurTheadId()
	{
		thread_.get_id();
	}
	bool IsRuning()
	{
		return thread_.joinable();
	}
	static void Sleep(int millisecond)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(millisecond));
	}
	//inline int  GetThreadId(){return _pid;}
	inline bool IsWorking() { return run_; }
	inline void NotifyStop() { run_ = false; }
private:

	std::thread thread_;
	volatile bool run_;
};
#endif
