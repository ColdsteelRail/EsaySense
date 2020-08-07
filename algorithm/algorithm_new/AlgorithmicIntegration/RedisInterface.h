#pragma once

#include "RedisAgent.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


class RedisInterface
{
public:
	static RedisInterface* GetInstance();

private:
	RedisInterface();
	~RedisInterface();

	static RedisInterface* m_redis_instance;
public:
	bool Init();
	void Send(std::string uuid, std::string alarmuuid, std::string starttime, std::string endtime, int algorithm_id, const char *pNodeid, int alarmflag);
	void Send(std::string strJson);
private:
	bool m_is_ok;
	RedisAgent *m_redis_agent;

};