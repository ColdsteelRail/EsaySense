#pragma once
#include <string>
#include <vector>
class RedisAgent
{
public:
	RedisAgent(void);
	~RedisAgent(void);

	void* connect_redis(unsigned int no);
	void set_redis(std::string ip,unsigned int port,std::string pwd, unsigned int no, unsigned int private_no);

	std::string redis_get_value(std::string key);
	std::string redis_get_evalsha(const std::string & script);
	int redis_eval( int num);
	int redis_eval( const char * str,const std::vector<std::string> & keys ,std::vector<std::string> & argvs);
	
	void redis_del_value(std::string key);
	bool redis_set_value(std::string key,std::string value);
	bool redis_lock(const char *key,const char *value);
	bool redis_unlock(const char *key,const char *value);
	bool redis_list_push(const char * name,const char *value);
	bool redis_list_pop(const char * name,std::string &value);
private:
   	void * m_redis_get_context;
	void * m_redis_set_context;

	std::string m_redis_ip;
	unsigned int m_port;
	std::string m_redis_pwd;
	unsigned int m_no;
	unsigned int m_private_no;
	std::string m_eval_key;
	std::string m_eval_SCRIPT;


	std::string m_eval_unlock_key;
	std::string m_eval_unlock_SCRIPT;
};


