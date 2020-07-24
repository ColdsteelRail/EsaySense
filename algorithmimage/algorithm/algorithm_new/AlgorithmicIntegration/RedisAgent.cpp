
#include "RedisAgent.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include "hiredis/hiredis.h"


RedisAgent::RedisAgent(void)
{
	std::string s;
	s += "if redis.call('get',KEYS[1]) == ARGV[1] then\n";
	s +=     "return redis.call('del',KEYS[1])\n";
	s +="else\n";
	s +=     "return 0\n";
	s +="end\n";
	m_eval_unlock_SCRIPT = s;
	m_redis_get_context=0;
	m_redis_set_context=0;
}

RedisAgent::~RedisAgent(void)
{
	if (m_redis_get_context)
	{
		redisFree((redisContext*)m_redis_get_context);
		m_redis_get_context =0;
	}

	if (m_redis_set_context)
	{
		redisFree((redisContext*)m_redis_set_context);
		m_redis_set_context =0;
	}
}

void* RedisAgent::connect_redis(unsigned int no)
{
	redisContext* context = redisConnect(m_redis_ip.c_str(),m_port);
	if(context && context->err == 0)
	{
		redisReply* reply = NULL;
		if(m_redis_pwd.length() > 0)
		{
			reply= (redisReply*) redisCommand((redisContext *)context, "AUTH %s", m_redis_pwd.c_str()); 
			if (reply->type == REDIS_REPLY_ERROR) 
			{ 
				printf("Redis Authentication failed !!!! \n");
				freeReplyObject(reply); 
				return NULL;
			} 
			freeReplyObject(reply);
		}

		reply= (redisReply*) redisCommand((redisContext *)context, "SELECT %d", no); 
		if (!reply || reply->type == REDIS_REPLY_ERROR)
		{ 
			printf("Redis SELECT failed !!!! {SELECT %d} \n", no);
			freeReplyObject(reply); 
			return NULL;
		} 
		freeReplyObject(reply); 

		return context;
	}
	printf("Redis redisConnect failed !!!!%s,%d,%s,%d %s\n", m_redis_ip.c_str(), m_port, m_redis_pwd.c_str(), m_no, context->errstr);
	return NULL;
	
}

void RedisAgent::set_redis(std::string ip,unsigned int port,std::string pwd, unsigned int no, unsigned int private_no)
{
	m_redis_ip = ip;
	m_port = port;
	m_redis_pwd = pwd;
	m_no = no;
	m_private_no = private_no;

	//m_redis_get_context = connect_redis(m_no); 
	//m_redis_set_context = connect_redis(m_no); 
}
std::string RedisAgent::redis_get_evalsha(const std::string & script)
{
	redisReply* r = (redisReply*)redisCommand((redisContext *)m_redis_get_context, "SCRIPT LOAD %s", script.c_str());
	if(!r)
	{
		m_redis_get_context = connect_redis(m_no);// redisConnect(m_redis_ip.c_str(),m_port);
		return "";
	}
	if (r->type != REDIS_REPLY_STRING)
	{
		freeReplyObject(r);
		return "";
	}
	std::string s = r->str;
	if(r)
	{
		freeReplyObject(r);
	}
	return  std::move(s);
}
std::string RedisAgent::redis_get_value(std::string key)
{
 //	boost::mutex::scoped_lock lock(Redismutex_);
 	redisReply* r = (redisReply*)redisCommand((redisContext *)m_redis_get_context, "GET %s", key.c_str());
 	if(!r)
 	{
 		m_redis_get_context = connect_redis(m_no);// redisConnect(m_redis_ip.c_str(),m_port);
 		return "";
 	}
 	if (r->type != REDIS_REPLY_STRING)
 	{
 		freeReplyObject(r);
 		return "";
 	}
 	std::string s = r->str;
 	if(r)
 	{
 		freeReplyObject(r);
 	}
 	return  std::move(s);
}
int RedisAgent::redis_eval( const char * str,const std::vector<std::string> & keys ,std::vector<std::string> & argvs)
{
	
	redisReply* r = 0;
	//r = (redisReply*)redisCommand((redisContext *)m_redis_get_context, "set","sale_num:pr.id:1",0);
	std::string sEVAL;
	sEVAL +=str;
	//sEVAL +="\"";
	
	char snum[32]={0};
	sprintf(snum," %d",keys.size());

	sEVAL += snum;
	for (int i=0;i<keys.size();i++)
	{
		sEVAL += " ";
		sEVAL+=keys[i];
	}

	for (int i=0;i<argvs.size();i++)
	{
		sEVAL += " ";
		sEVAL+=argvs[i];
	}

	r = (redisReply*)redisCommand((redisContext *)m_redis_set_context, "EVAL %s %d %s %s %s",str,keys.size(),
		keys[0].c_str(),keys[1].c_str(),argvs[0].c_str());
	int ret = 0;
	if(r)
	{
		ret = r->integer;
		if (r->integer !=1)
		{
			int a=0;
		}
		freeReplyObject(r);

	}
	else
	{
		m_redis_set_context = connect_redis(m_no);
	}
	return  ret;
}
int RedisAgent::redis_eval(int num)
{
	redisReply* r = 0;
	if (m_eval_key.size()==0)
	{

		r = (redisReply*)redisCommand((redisContext *)m_redis_set_context, "EVAL %s 2 fe fff %d",m_eval_SCRIPT.c_str(),num);
		m_eval_key = redis_get_evalsha(m_eval_SCRIPT);
	}
	else
	{
		r = (redisReply*)redisCommand((redisContext *)m_redis_set_context, "EVALSHA %s 0 %d",m_eval_key.c_str(),num);
	}

	int ret = 0;
	if(r)
	{
		ret = r->integer;
		if (r->integer !=1)
		{
			int a=0;
		}
		freeReplyObject(r);
	
	}
	else
	{
		m_redis_set_context = connect_redis(m_no);
	}
	return  ret;
}
bool RedisAgent::redis_set_value(std::string key,std::string value)
{
	redisReply* r = (redisReply*)redisCommand((redisContext *)m_redis_set_context, "SET %s %s", key.c_str(),value.c_str());
	if(r)
	{
		freeReplyObject(r);
	}
	else
	{
		m_redis_set_context = connect_redis(m_no);
		return false;
	}
	return  true;
}
bool RedisAgent::redis_lock(const char *key,const char *value)
{
	bool ret = false;
	redisReply* r = (redisReply*)redisCommand((redisContext *)m_redis_set_context, "SET %s %s EX 10 NX", key,value);
	if(r)
	{
		if (r->str && strcmp(r->str ,"OK")==0)
		{
			ret = true;
		}
		freeReplyObject(r);

	}
	else
	{
		m_redis_set_context = connect_redis(m_no);
	}
	return  ret;
}

bool RedisAgent::redis_unlock(const char *key,const char *value)
{
	bool ret = false;
	redisReply* r  = (redisReply*)redisCommand((redisContext *)m_redis_set_context, "EVAL %s 1 %s %s",m_eval_unlock_SCRIPT.c_str(),key,value);
	if(r)
	{
		ret = r->integer;
		freeReplyObject(r);

	}
	else
	{
		m_redis_set_context = connect_redis(m_no);
	}
	return  ret;
}
void RedisAgent::redis_del_value( std::string key )
{
	redisReply* r = (redisReply*)redisCommand((redisContext *)m_redis_get_context, "del %s", key.c_str());
	if(!r)
	{
		m_redis_get_context = connect_redis(m_no); 
	}
	if(r)
	{
		freeReplyObject(r);
	}
}
bool RedisAgent::redis_list_push(const char * name,const char *value)
{
	if (!m_redis_set_context)
	{
		m_redis_set_context = connect_redis(m_no); 
	}
	if (!m_redis_set_context)
	{
		return false;
	}
	bool ret = false;
	redisReply* r = (redisReply*)redisCommand((redisContext *)m_redis_set_context, "LPUSH %s %s", name,value);
	if(r)
	{
		if (REDIS_REPLY_INTEGER == r->type && r->integer>0)
		{
			ret = true;
		}
		freeReplyObject(r);

		if (!ret)
		{
			redisFree((redisContext*)m_redis_set_context);
			m_redis_set_context =0;
		}
	}
	else
	{
		redisFree((redisContext*)m_redis_set_context);
		m_redis_set_context =0;
	}
	return ret;
}
bool RedisAgent::redis_list_pop(const char * name,std::string &value)
{
	if (!m_redis_get_context)
	{
		m_redis_get_context = connect_redis(m_no); 
	}
	if (!m_redis_get_context)
	{
		return false;
	}
	bool ret = false;
	redisReply* r = (redisReply*)redisCommand((redisContext *)m_redis_get_context, "RPOP %s ", name);
	if (!r)
	{
		redisFree((redisContext*)m_redis_get_context);
		m_redis_get_context =0;
		return false;
	}
	if (r->type != REDIS_REPLY_STRING)
	{
		freeReplyObject(r);
		redisFree((redisContext*)m_redis_get_context);
		m_redis_get_context =0;
		return false;
	}
	value = r->str;
	if(r)
	{
		freeReplyObject(r);
	}
	return true;
}
