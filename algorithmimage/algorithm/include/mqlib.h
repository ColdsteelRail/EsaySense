
#ifndef _MQLIB_C_H_
#define _MQLIB_C_H_

#ifdef WIN32
#ifdef _I_MQLIB_API
#define I_MQLIB_API_MODE __declspec(dllexport)
#else
#define I_MQLIB_API_MODE __declspec(dllimport)

#ifndef _I_MQLIB_API
#pragma comment(lib,"LibRabbitMqSDK.lib")
#endif
#endif
#else
#define I_MQLIB_API_MODE
#endif
#include <stdint.h>

typedef enum
{
	MQ_NODE_TYPE_SYS = 0,
	MQ_NODE_TYPE_GW,
	MQ_NODE_TYPE_MS,
	MQ_NODE_TYPE_ES,
	MQ_NODE_TYPE_TS,
	MQ_NODE_TYPE_AS,
	MQ_NODE_TYPE_TSS,//�������
	MQ_NODE_TYPE_STOR,
	MQ_NODE_TYPE_IS,//���ܷ���
	MQ_NODE_TYPE_VOD,
	MQ_NODE_TYPE_error=32,
}MQ_NODE_TYPE;
#pragma pack(push,4)
struct msg_info_t
{
	char user_id[32];
	char message_id[32];
	char nodeid[32];//�ظ���ϢĿ��nodeid
	char NodeType[4];//�ظ���ϢĿ��NodeType
	unsigned int expiration_sec;//��Ϣ���浽��Ϣ���е�ʱ����Ϊ��λ,expiration_sec Ϊ0 ��ʾ��Զ�����ڶ����У����Ǳ����ѵ�
	int len;
	char *msg;
};

#pragma pack(pop)
typedef void(*msg_read_cb)(msg_info_t* msg_info,void * ctx);
#ifdef __cplusplus
extern "C" {
#endif
	I_MQLIB_API_MODE	bool mqlib_init(const char * strIp, int port, const char *  strUser, const char *  strPass, const char *  strVhost);
	I_MQLIB_API_MODE	bool mqlib_start(MQ_NODE_TYPE nodeType, const char *pLocalNodeid, msg_read_cb cb, void *pUser,bool recvdata = true);
	//Persistent �Ƿ����л������̣�Ĭ��ֻ���ڴ�
	// pNodeid == null or nodeType == MQ_NODE_TYPE_SYS  
	I_MQLIB_API_MODE	bool mqlib_send(msg_info_t *pMsgInfo, MQ_NODE_TYPE nodeType, const char *pNodeid,bool Persistent = false);
#ifdef __cplusplus
}
#endif

#endif
