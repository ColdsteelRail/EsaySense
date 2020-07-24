#ifndef _NETLIB_SDK_H_
#define _NETLIB_SDK_H_

#include "stdint.h"

#ifdef WIN32
#ifdef NETDEVICESDK_EXPORTS
#define NETLIB_API extern "C"  __declspec(dllexport) 
#else 
#define NETLIB_API extern "C"  __declspec(dllimport)
#endif
#else
#define NETLIB_API
#endif


#ifdef WIN32
#pragma warning(disable:4335 4200 4005 4508 4101 4700 4244 4267 4200 4312 4010 4091 4616 4311 4018 4482 4305 4129 4065 4805 4114 4060 4996)
#endif

#ifndef TG_LOC_IP_MAX_LEN
#define TG_LOC_IP_MAX_LEN            (32)
#endif



#ifndef IN
#define IN
#endif

#ifndef OUT
#define OUT
#endif

#ifndef UPGRADE_SERVER_PORT
#define UPGRADE_SERVER_PORT			12000
#define UPGRADE_TCP_PORT			8010
#endif

// ���Ⱥ궨��
#define BUILDTIME_LEN   64

#ifndef IPC_USE_NAME_LEN
#define IPC_USE_NAME_LEN            (16)
#endif

#ifndef IPC_USE_PASSWD_LEN
#define IPC_USE_PASSWD_LEN            (16)
#endif
#pragma pack(push,4)


typedef enum{
	NET_DEVICE_DEVICE_IPC,
	NET_DEVICE_DEVICE_4G,
	NET_DEVICE_DEVICE_EMBEDDED_LVS,
	NET_DEVICE_DEVICE_PC_LVS,
}NET_DEVICE_TYPE;

typedef enum
{
	NET_DEVICE_FRAME_VIDEO_I=1,
	NET_DEVICE_FRAME_VIDEO_P,
	NET_DEVICE_FRAME_VIDEO_B,
	NET_DEVICE_FRAME_AUDIO,
	NET_DEVICE_FRAME_META,
}NET_DEVICE_FRAMETYPE;


typedef enum
{
	NET_DEVICE_FRAME_EXT_audio_value = 100,//��������ֵ
}NET_DEVICE_FRAMETYPE_EXT;



typedef enum
{
	NET_DEVICE_DATA_TYPE_YUV420 = 1,
	NET_DEVICE_DATA_TYPE_RGB24,
	NET_DEVICE_DATA_TYPE_RGB565,
	NET_DEVICE_DATA_TYPE_H264,

	NET_DEVICE_DATA_TYPE_PCM=16,
	NET_DEVICE_DATA_TYPE_AAC,
	NET_DEVICE_DATA_TYPE_G711A,
	NET_DEVICE_DATA_TYPE_G711U,
	NET_DEVICE_DATA_TYPE_G726,
}NET_DEVICE_DATATYPE;

typedef enum
{
	NET_DEVICE_RECORD_FILETYPE_TG,
	NET_DEVICE_RECORD_FILETYPE_MP4,
}NET_DEVICE_RECORD_FILETYPE;

typedef enum
{
	NET_DEVICE_RECORD_VIDEOTYPE_MANNUL = 0,
	NET_DEVICE_RECORD_VIDEOTYPE_PIAN = 1,
	NET_DEVICE_RECORD_VIDEOTYPE_VIDEOBREVIRY = 2,
	NET_DEVICE_RECORD_VIDEOTYPE_ALARM = 3,
	NET_DEVICE_RECORD_VIDEOTYPE_ALL = 0xff,
}NET_DEVICE_RECORD_VIDEOTYPE;


typedef enum{
	NET_PTZ_CTL_LIGHT_PWRON  =   2,
	NET_PTZ_CTL_WIPER_PWRON  =   3,

	NET_PTZ_CTL_TILT_SET	=	19, //������λ
	NET_PTZ_CTL_PAN_SET		=	20,  //ˮƽ��λ
	NET_PTZ_CTL_TILT_UP		= 21,
	NET_PTZ_CTL_TILT_DOWN,
	NET_PTZ_CTL_PAN_LEFT,
	NET_PTZ_CTL_PAN_RIGHT,
	NET_PTZ_CTL_UP_LEFT,
	NET_PTZ_CTL_UP_RIGHT,
	NET_PTZ_CTL_DOWN_LEFT,
	NET_PTZ_CTL_DOWN_RIGHT,
	NET_PTZ_CTL_PAN_AUTO,
	NET_PTZ_CTL_ZOOM_SET = 30,//�佹��λ
	NET_PTZ_CTL_ZOOM_IN_P = 31,//�佹������
	NET_PTZ_CTL_ZOOM_OUT_P,//�佹����Զ
	NET_PTZ_CTL_FOCUS_NEAR,//�۽�
	NET_PTZ_CTL_FOCUS_FAR,
	NET_PTZ_CTL_IRIS_OPEN,
	NET_PTZ_CTL_IRIS_CLOSE,
	NET_PTZ_CTL_FOCUS_AUTO,

	NET_PTZ_GOTO_PRESET	=	41,	/* ����ת��Ԥ�õ� */
	NET_PTZ_ADD_PRESET	=	42,	/* ���Ԥ�õ� */
	NET_PTZ_DEL_PRESET	=	43,	/* ɾ��Ԥ�õ� */
	NET_PTZ_RUN_SEQ		=	47,	/* ��ʼѲ�� */
	NET_PTZ_STOP_SEQ	=	48,	/* ֹͣѲ�� */

	NET_PTZ_CTL_PTZ_MOVE_STOP=100
}NET_PTZ_CTL;

typedef enum{
	NET_DEVICE_OSD_TYPE_TIME,
	NET_DEVICE_OSD_TYPE_TEXT,
	NET_DEVICE_OSD_TYPE_LOGO,
}NET_DEVICE_OSD_TYPE;

typedef enum{
	NET_DEVICE_H264_MAIN_STREAM  = 0x01,
	NET_DEVICE_H264_SUB_STREAM   = 0x02,
	NET_DEVICE_AUDIO_STREAM      = 0x04,
	NET_DEVICE_H265_MAIN_STREAM  = 0x08,
	NET_DEVICE_H265_SUB_STREAM   = 0x10,
	NET_DEVICE_VIDEO_LOW_STREAM  = 0x20,
	NET_DEVICE_VIDEO_ORIG_STREAM = 0x40,
}NET_DEVICE_STREAM_TYPE;


typedef enum
{
	DRAW_ASPECT_RATION_DEFAULT  = 0,
	DRAW_ASPECT_RATION_FULL,
	DRAW_ASPECT_RATION_4_3,
	DRAW_ASPECT_RATION_16_9,
}NET_DEVICE_DRAW_ASPECT_RATION;


typedef enum{
	TG_NET_DEVICE_ERROR_SUCCESS			 =0,

	TG_DEVICE_NOLOGIN                    =-1       ,
	TG_DEVICE_NET_MSG_OK                 = 0       ,
	TG_DEVICE_NET_MSG_ERR                = 1       ,
	TG_DEVICE_UNSUPPORT_MSG_ERR          = 2       ,
	TG_DEVICE_MSG_WAIT_ERR 				 = 3       ,

	TG_DEVICE_DEV_NO_FIND_ERR            = 100     ,
	TG_DEVICE_GET_LOC_IP_ERR                       ,

	TG_DEVICE_NET_MSG_TYPE_ERR           = 200     ,
	TG_DEVICE_NET_MSG_LEN_ERR                      ,

	TG_DEVICE_NET_TRANS_TYPE_ERR         = 300     ,

	TG_DEVICE_LOGIN_PWD_ERR              = 1000    ,
	TG_DEVICE_LOGIN_USERNAME_ERR                   ,
	TG_DEVICE_SESSION_ID_ERR                       ,
	TG_DEVICE_SESSION_TIMEOUT                      ,



	TG_DEVICE_STREAM_TYPE_ERR            = 2000    ,
	TG_DEVICE_CHANNEL_NUM_ERR                      ,




	TG_DEVICE_ENC_PARAM_ERR              = 3000    ,


	TG_DEVICE_IPC_URL_ERR                = 4000    ,
	TG_DEVICE_IPC_USERNAME_ERR                     ,
	TG_DEVICE_IPC_PWD_ERR                          ,

	NET_DEVICE_ERROR_TIMEOUT,
}NET_DEVICE_RESULT;


typedef enum
{
	NET_USERAUTH_CODEC_realplay			= 0x0100,//ʵʱԤ��
	NET_USERAUTH_CODEC_eqtopt			= 0x0101,//�豸����
	NET_USERAUTH_CODEC_ptzf				= 0x0102,//��̨����
	NET_USERAUTH_CODEC_speak			= 0x0103,//�Խ�
	NET_USERAUTH_CODEC_VoiceBroadcast	= 0x0104,//�����㲥
	NET_USERAUTH_CODEC_deviceconfig		= 0x0105,//Զ������
	NET_USERAUTH_CODEC_record			= 0x0106,//��ͣ¼��
	NET_USERAUTH_CODEC_playback			= 0x0107,//�����ط�
	NET_USERAUTH_CODEC_videodownload	= 0x0108,//��Ƶ����
	NET_USERAUTH_CODEC_log				= 0x0109,//��־��ѯ
	NET_USERAUTH_CODEC_videowall		= 0x0110,//����ǽ
	NET_USERAUTH_CODEC_map				= 0x0111,//���ӵ�ͼ
	NET_USERAUTH_CODEC_duty				= 0x0112,//�������
	NET_USERAUTH_CODEC_datadisplay		= 0x0113,//�ۺ�����
	NET_USERAUTH_CODEC_minimize			= 0x0114,//��С��
	NET_USERAUTH_CODEC_close			= 0x0115,//�˳�
}NET_USERAUTH_CODEC;

typedef struct
{
	NET_DEVICE_TYPE devicetype;
	unsigned long long deviceid;
	char devicename[32];
	char deviceip[32];
	int deviceport;
}NET_DEVICE_FINDDEVICEINFO, *LPNET_DEVICE_FINDDEVICEINFO;

typedef void (*FindDeviceCallBack) (LPNET_DEVICE_FINDDEVICEINFO deviceInfo, void* userdata);

typedef struct
{
	char host[128];
	int port;
	char username[32];
	char password[32];
}NET_LOGIN_INFO, *LPNET_LOGIN_INFO;



typedef struct
{
	uint64_t pts;
	uint32_t frame_len;
	uint16_t frame_ext_len;
	uint16_t frame_number;
	uint16_t frame_width;	//if audio frame this is bits_per_sample
	uint16_t frame_height;	//if audio frame this is channels
	uint8_t	 fps;		//if audio frame this is  sample  khz
	uint8_t	frame_ext_type;
	uint8_t frame_type;
	uint8_t encode_type;

}NET_FRAMEINFO, *LPNET_FRAMEINFO;

typedef void(*RealDataCallBack)(long h_realplay, char *buf, int size, LPNET_FRAMEINFO frameInfo, void* userdata);
typedef void(*Notify)(long h_play, char *key,void* value, void* userdata);

typedef struct{
	long long SUID;
	int    id; 

}SUB_ID_INFO;

typedef struct{
	char UUID[64];
	long long SUID;
	int    id; 

}SYS_ID_INFO;

typedef struct
{
	int width;
	int height;
	NET_DEVICE_DATATYPE format;
}NET_DECODE_FORMAT;


typedef struct 
{
	SYS_ID_INFO channel;
	int  level;
	int  enable_mata;//�Ƿ��������Ԫ����
	void* hwnd;
	NET_DECODE_FORMAT decode_format;
	RealDataCallBack encode_cb;
	RealDataCallBack decode_cb;
	Notify notify_cb;
	void* userdata;
}NET_DEVICE_CLIENTINFO, *LPNET_DEVICE_CLIENTINFO;
typedef struct
{
	char ip[32];
	int port;

}NET_TSADDR_INFO;
typedef struct
{
	SYS_ID_INFO channel;
	int region;//1:����;2:ǰ���豸
	NET_DEVICE_RECORD_VIDEOTYPE videotype;
	char starttime[64];
	char endtime[64];

}NET_DEVICE_FILE_LIST_REQ;

typedef struct
{
	char fileid[256];
	NET_DEVICE_RECORD_FILETYPE filetype;
	NET_DEVICE_RECORD_VIDEOTYPE videotype;
	char starttime[64];
	char endtime[64];
	int filesize;
	SYS_ID_INFO channel;
	int region;//1 loc ,2 dev
	int vodtype;//1 time ,2 fileid
}NET_DEVICE_RECORD_FILE_INFO, *LPNET_DEVICE_RECORD_FILE_INFO;

typedef struct  
{
}NET_DEVICE_PER_MEDIUM_INFO, *LPNET_DEVICE_PER_MEDIUM_INFO;


typedef struct{
	int year;
	int month;
	int day;
	int hour;
	int minute;
	int second;
	int weekday;
}NET_TIME, *LPNET_TIME;

typedef struct{
	char preset_name[32];
	char preset_uuid[64];
	//char preset_token[64];
	int preset_id;
}NET_PTZ_PRESET_INFO, *LPNET_PTZ_PRESET_INFO;

typedef struct
{
	NET_DEVICE_OSD_TYPE type;
	int channel;		
	int block;
	int enable;
	int x;
	int y;
	int width;
	int height;
	int color;
	char *data;
	int data_size;
}NET_DEVICE_OSD_INFO, *LPNET_DEVICE_OSD_INFO;

typedef struct{

	SYS_ID_INFO channel;
	NET_DEVICE_STREAM_TYPE streamtype;
	char channel_name[32];
}NET_DEVICE_CHANNEL_INFO, *LPNET_DEVICE_CHANNEL_INFO;


#define MAX_GROUP_EQT_NUM 16
typedef struct{
	SYS_ID_INFO SubEquipmentIDGroup[MAX_GROUP_EQT_NUM];
	char group_name[128];
	int enable;
	
}NET_GROUP_INFO;
#define MAX_GROUP_NUM 8
typedef struct{
	NET_GROUP_INFO group[MAX_GROUP_NUM];
	char name[128];
	int  WndNum;//��������������������ʾ��
	int  sec;
}NET_GROUP_POLLING_INFO;
#define MAX_GROUPPOLLING_NUM 64
typedef struct{
	char name[MAX_GROUPPOLLING_NUM][256];
    int size;

}NET_GROUP_POLLING_SET;

#define MAX_CRUISE_PRESETID_NUM 8
typedef struct
{
	char cruise_uuid[64];//uuid Ψһ��ʶ
	SYS_ID_INFO preset_id[MAX_CRUISE_PRESETID_NUM];//Ŀǰֻ��SYS_ID_INFO::UUID ��Ч
	char name[64];
	int beLoop;			//�Ƿ�ѭ��
	int loopStopTime;		//ͣ��ʱ�� ��
	int loopDelayTime;		//Ѳ�����ʱ�� ��
	int speed;
	int cruise_number;
}NET_CRUISE_INFO;

#define MAX_CRUISE_NUM 6
typedef struct
{
	NET_CRUISE_INFO cruises[MAX_CRUISE_NUM];
	SYS_ID_INFO subeqt_id;

}NET_CRUISE_INFO_SET;
typedef void(*tgExceptionNotify) (long h_login,long h_Type,char *value,long context);

//////////////////////////////////////////////////////////////////////////



typedef struct
{
	unsigned short year;
	unsigned char  month;
	unsigned char  day;
	unsigned char  hour;
	unsigned char  minute;
	unsigned char  second;
	unsigned char  weekday;
}NET_DEVICE_TIMEINFO;



/********��������*******/
#define DEFINE_CONFIG_MOTIONDETECT_Param						1007 //�ƶ�������
#define DEFINE_CONFIG_TIME_Param								1008 //ʱ������
#define DEFINE_CONFIG_VIDEO_EFFECT_Param						1009 //��Ƶ��������
#define DEFINE_CONFIG_FOCUSMODE									1010 //�����豸�۽�ģʽ
#define DEFINE_CONFIG_CAMERA_SETUPCF							1011 //������ǶȲ���
#define DEFINE_CONFIG_CHANNEL_STATUS							1012 //��������״̬��Ϣ
#define DEFINE_CONFIG_HIDE_ALARM_Param							1013 //�ڵ���������
#define DEFINE_CONFIG_TRAVERSE_PLANE_Param						1014 //Խ�籨������
#define DEFINE_CONFIG_FIELD_DETECTION_Param						1015 //�������ֱ�������
#define DEFINE_CONFIG_LINGER_Param								1016 //�ǻ���ⱨ������
#define DEFINE_CONFIG_PEOPLE_GATHER_Param						1017 //��Ա�ۼ���������
#define DEFINE_CONFIG_OSD_Param									1018 //OSD���ò���
#define DEFINE_CONFIG_GET_SMART_ABILITY							1019 //��ȡͨ�������������ò���
#define ST_DEV_VIDEO_EFFECT_PARAMS_NOSET 101	//��ʶ�����ö�Ӧ������

struct ST_CAMAR_CFG
{
	int angle_h;//ˮƽ�Ƕ�
	int angle_v;//��ֱ�Ƕ�
	int focus;//����ֵ
	int zoom;//����ֵ
};



struct ST_DEV_VIDEO_EFFECT_PARAMS
{
	char m_dwBrightValue;			//���ȣ�ȡֵ��Χ[0,100]
	char m_dwContrastValue;			//�Աȶȣ�ȡֵ��Χ[0,100]
	char m_dwSaturationValue;		//���Ͷȣ�ȡֵ��Χ[0,100]
	char m_byDayNightFilterType;	//��ҹ�л���0-���죬1-ҹ��2-�Զ�����������ģʽ����3-��ʱ��4-�������봥����5-�Զ�ģʽ2���޹�������ͨ����Ƶ�������ж���ҹģʽ�����ǹ�������
	char m_fogThroughMode;			//��͸ģʽ 0-�����ã�1-�Զ�ģʽ��2-����ģʽ//���Ըò���
	char m_opticalFog;				// 0- �����ù�ѧ͸��1- ���ù�ѧ͸��

	char res1;
	char res2;
};

#define ST_DEV_MAX_TIME_INTERVAL_NUM	8	//һ�����8��ʱ������
//�����ȫ��Ļ������ÿ�ʼʱ��Ϊ0��0��ֹͣʱ��Ϊ24��0��ע�����ʱ��һ��Ҫ���ڿ�ʼʱ��
struct ST_DEV_SCHEDTIME
{
	char    byStartHour;			//��ʼʱ��[0,23],��λСʱ
	char    byStartMin;				//��ʼʱ��[0,59]
	char    byStopHour;				//����ʱ�䣬��λСʱ,[0,24]ʱ,�������ӱ���Ϊ0
	char    byStopMin;				//����ʱ�䣬��λ���ӣ�[0,59]
};

struct ST_DEV_MOTIONDETECT_PARAMS
{
	bool beEnable;							//�Ƿ����ƶ����,true:������false:�ر�
	/*
	0x00: ����Ӧ
	0x01: �������Ͼ���
	0x02: ��������
	0x04: �ϴ�����
	0x08: �����������
	0x10: Jpegץͼ���ϴ�EMail
	0x20: �������ⱨ��������
	0x40: �������ӵ�ͼ(Ŀǰ��PCNVR֧��)
	0x200��ץͼ���ϴ�ftp 
	0x1000��ץͼ�ϴ����ƴ洢
	E.g. dwHandleType==0x01|0x04 ��ʾ���ñ�������ʱ�����������Ͼ��沢�ҽ�������Ϣ�ϴ�����
	*/
	int dwHandleType;						//��������ʽ
	int beEnableRecord;						//�Ƿ�������¼��
	int recordChannel[32];					//��������ͨ���������豸�ϵ�ͨ����������
	float startX;							//���Ͻ�x���꣬ȡֵ[0.0,1.0]
	float startY;							//���Ͻ�y���꣬ȡֵ[0.0,1.0]
	float endX;								//���½�x���꣬ȡֵ[0.0,1.0]
	float endY;								//���½�y���꣬ȡֵ[0.0,1.0]
	unsigned char byMotionSensitive;		//�ƶ���������ȣ�ȡֵ��Χ[0,5]����ȡֵΪ0xff��ʾ�رգ�ֵԽ��Խ���� 
	bool beAllDay;							//ture����ʾȫ�쿪��������Ϊfalse
	ST_DEV_SCHEDTIME day[7][ST_DEV_MAX_TIME_INTERVAL_NUM];	//����ʱ�䣬ȫ��ʱֻ��ÿһ��ĵ�һ���ṹ�壬������ֵ���ṹ��˵��
	//ͬһ��Ĳ�ͬʱ��β������ص�
};

struct ST_DEV_HIDEALARM_PARAMS
{
	int enable;							//�Ƿ������ڵ�������0- ��1- �������ȣ�2- �������ȣ�3- �������� 
	/*
	0x00: ����Ӧ
	0x01: �������Ͼ���
	0x02: ��������
	0x04: �ϴ�����
	0x08: �����������
	0x10: Jpegץͼ���ϴ�EMail
	0x20: �������ⱨ��������
	0x40: �������ӵ�ͼ(Ŀǰ��PCNVR֧��)
	0x200��ץͼ���ϴ�ftp 
	0x1000��ץͼ�ϴ����ƴ洢
	E.g. dwHandleType==0x01|0x04 ��ʾ���ñ�������ʱ�����������Ͼ��沢�ҽ�������Ϣ�ϴ�����
	*/
	int dwHandleType;						//��������ʽ
	int areaTopLeftX;						//�������Ͻ�X����,������Ϊ��λ��ʵ����Ƶ�ֱ���
	int areaTopLeftY;						//�������Ͻ�Y���꣬������Ϊ��λ��ʵ����Ƶ�ֱ���
	int areaWidth;							//�����,������Ϊ��λ
	int areaHeight;							//�����,������Ϊ��λ
	bool beAllDay;							//ture����ʾȫ�쿪��������Ϊfalse
	ST_DEV_SCHEDTIME day[7][ST_DEV_MAX_TIME_INTERVAL_NUM];	//����ʱ�䣬ȫ��ʱֻ��ÿһ��ĵ�һ���ṹ�壬������ֵ���ṹ��˵��
	//ͬһ��Ĳ�ͬʱ��β������ص�
};

struct ST_DEV_TRAVERSE_PLANE_DETECTION_PARAMS
{
	int enable;							//ʹ��Խ����⹦�ܣ�0- ��1- �� 
	/*
	0x00: ����Ӧ
	0x01: �������Ͼ���
	0x02: ��������
	0x04: �ϴ�����
	0x08: �����������
	0x10: Jpegץͼ���ϴ�EMail
	0x20: �������ⱨ��������
	0x40: �������ӵ�ͼ(Ŀǰ��PCNVR֧��)
	0x200��ץͼ���ϴ�ftp
	0x400: �齹��������۽�
	0x800: PTZ��������(�������Ŀ��)
	0x1000��ץͼ�ϴ����ƴ洢
	E.g. dwHandleType==0x01|0x04 ��ʾ���ñ�������ʱ�����������Ͼ��沢�ҽ�������Ϣ�ϴ����ġ�
	*/
	int dwHandleType;						//��������ʽ
	int beEnableRecord;						//�Ƿ�������¼��
	int recordChannel[32];					//��������ͨ���������豸�ϵ�ͨ����������
	int bySensitivity;						//�����ȣ�ȡֵ��Χ��[1,5] ������Smart IPC��ȡֵ��ΧΪ[1,100]�� 
	float startX;							//��ʼX�����꣬ȡֵ��Χ[0.0,1.0] 
	float startY;							//��ʼY�����꣬ȡֵ��Χ[0.0,1.0] 
	float endX;								//����X�����꣬ȡֵ��Χ[0.0,1.0] 
	float endY;								//����Y�����꣬ȡֵ��Χ[0.0,1.0] 
	int dwCrossDirection;					//��Խ����0:˫��1���������� ��2���������� 
	bool beAllDay;							//ture����ʾȫ�쿪��������Ϊfalse
	ST_DEV_SCHEDTIME day[7][ST_DEV_MAX_TIME_INTERVAL_NUM];	//����ʱ�䣬ȫ��ʱֻ��ÿһ��ĵ�һ���ṹ�壬������ֵ���ṹ��˵��
	//ͬһ��Ĳ�ͬʱ��β������ص�
};

struct IntelligentPoint
{
	float x;								//�����㷨����ʹ�õ������X���꣬ȡֵ[0.0,1.0]
	float y;								//�����㷨����ʹ�õ������Y���꣬ȡֵ[0.0,1.0]
};

struct ST_DEV_FIELD_DETECTION_PARAMS
{
	int enable;							//ʹ������������⹦�ܣ�0- ��1- �� 
	/*
	0x00: ����Ӧ
	0x01: �������Ͼ���
	0x02: ��������
	0x04: �ϴ�����
	0x08: �����������
	0x10: Jpegץͼ���ϴ�EMail
	0x20: �������ⱨ��������
	0x40: �������ӵ�ͼ(Ŀǰ��PCNVR֧��)
	0x200��ץͼ���ϴ�ftp
	0x400: �齹��������۽�
	0x800: PTZ��������(�������Ŀ��)
	0x1000��ץͼ�ϴ����ƴ洢
	E.g. dwHandleType==0x01|0x04 ��ʾ���ñ�������ʱ�����������Ͼ��沢�ҽ�������Ϣ�ϴ����ġ�
	*/
	int dwHandleType;						//��������ʽ
	int beEnableRecord;						//�Ƿ�������¼��
	int recordChannel[32];					//��������ͨ���������豸�ϵ�ͨ����������
	int bySensitivity;						//�����Ȳ�����ȡֵ��Χ��[1,100]  
	int duration;							//��Ϊ�¼�����ʱ����ֵ���ж���Ч������ʱ�䡣��ͬ���豸ȡֵ��Χ��ͬ�����ܷ�����Ϊ1~120�루Ĭ�ϣ�5�룩��ATM�豸Ϊ1~1200�룬Smart IPCΪ1��100�� 
	int dwPointNum;							//��Ч�������ĿǰȡֵΪ-1��ȫ����0�������������4����ʵ�ľ�����������
	IntelligentPoint strucPoints[10];		//����α߽�㣬���ֵΪ10��,dwPointNumΪ-1��0ʱ����Ҫ�������飬Ϊ4ʱ˳ʱ�밴Ҫ���������� 
	bool beAllDay;							//ture����ʾȫ�쿪��������Ϊfalse
	ST_DEV_SCHEDTIME day[7][ST_DEV_MAX_TIME_INTERVAL_NUM];	//����ʱ�䣬ȫ��ʱֻ��ÿһ��ĵ�һ���ṹ�壬������ֵ���ṹ��˵��
//ͬһ��Ĳ�ͬʱ��β������ص�
};
struct ST_DEV_LINGER_PARAMS
{
	int enable;							//ʹ���ǻ���⹦�ܣ�0- ��1- �� 
	/*
	0x00: ����Ӧ
	0x01: �������Ͼ���
	0x02: ��������
	0x04: �ϴ�����
	0x08: �����������
	0x10: Jpegץͼ���ϴ�EMail
	0x20: �������ⱨ��������
	0x40: �������ӵ�ͼ(Ŀǰ��PCNVR֧��)
	0x200��ץͼ���ϴ�ftp
	0x400: �齹��������۽�
	0x800: PTZ��������(�������Ŀ��)
	0x1000��ץͼ�ϴ����ƴ洢
	E.g. dwHandleType==0x01|0x04 ��ʾ���ñ�������ʱ�����������Ͼ��沢�ҽ�������Ϣ�ϴ����ġ�
	*/
	int dwHandleType;						//��������ʽ
	int beEnableRecord;						//�Ƿ�������¼��
	int recordChannel[32];					//��������ͨ���������豸�ϵ�ͨ����������
	int bySensitivity;						//�����Ȳ�����ȡֵ��Χ��[1,100]  
	int byTimeThreshold;					//ʱ����ֵ��ȡֵ��Χ��[0,10]����λ��s 
	int dwPointNum;							//��Ч�������ĿǰȡֵΪ-1��ȫ����0�������������4����ʵ�ľ�����������
	IntelligentPoint strucPoints[10];		//����α߽�㣬���ֵΪ10 ,dwPointNumΪ-1��0ʱ����Ҫ�������飬Ϊ4ʱ˳ʱ�밴Ҫ����������
	bool beAllDay;							//ture����ʾȫ�쿪��������Ϊfalse
	ST_DEV_SCHEDTIME day[7][ST_DEV_MAX_TIME_INTERVAL_NUM];	//����ʱ�䣬ȫ��ʱֻ��ÿһ��ĵ�һ���ṹ�壬������ֵ���ṹ��˵��
	//ͬһ��Ĳ�ͬʱ��β������ص�
};
struct ST_DEV_PEOPLE_GATHER_PARAMS
{
	int enable;							//ʹ����Ա�ۼ���⹦�ܣ�0- ��1- �� 
	/*
	0x00: ����Ӧ
	0x01: �������Ͼ���
	0x02: ��������
	0x04: �ϴ�����
	0x08: �����������
	0x10: Jpegץͼ���ϴ�EMail
	0x20: �������ⱨ��������
	0x40: �������ӵ�ͼ(Ŀǰ��PCNVR֧��)
	0x200��ץͼ���ϴ�ftp
	0x400: �齹��������۽�
	0x800: PTZ��������(�������Ŀ��)
	0x1000��ץͼ�ϴ����ƴ洢
	E.g. dwHandleType==0x01|0x04 ��ʾ���ñ�������ʱ�����������Ͼ��沢�ҽ�������Ϣ�ϴ����ġ�
	*/
	int dwHandleType;						//��������ʽ
	int beEnableRecord;						//�Ƿ�������¼��
	int recordChannel[32];					//��������ͨ���������豸�ϵ�ͨ����������
	int byObjectOccup ;						//ռ�ȣ��������ռ�û��趨��������ı�����ֵ����ȡֵ��Χ��[1,100] 
	int dwPointNum;							//��Ч�������ĿǰȡֵΪ-1��ȫ����0�������������4����ʵ�ľ�����������
	IntelligentPoint strucPoints[10];		//����α߽�㣬���ֵΪ10 ,dwPointNumΪ-1��0ʱ����Ҫ�������飬Ϊ4ʱ˳ʱ�밴Ҫ����������
	bool beAllDay;							//ture����ʾȫ�쿪��������Ϊfalse
	ST_DEV_SCHEDTIME day[7][ST_DEV_MAX_TIME_INTERVAL_NUM];	//����ʱ�䣬ȫ��ʱֻ��ÿһ��ĵ�һ���ṹ�壬������ֵ���ṹ��˵��
	//ͬһ��Ĳ�ͬʱ��β������ص�
};
struct ST_DEV_OSD_PARAMS
{
	int enable;	//ʹ��OSD���ܣ�Ԥ����ͼ�����Ƿ���ʾ�ַ���0������ʾ��1����ʾ����ʾ����ΧΪ704*576�������ַ��Ĵ�СΪ32*32�� 
	int dataLen;					//�ַ�����
	int startX;						//�ַ���ʾλ�õ�x���� 
	int startY;						//�ַ���ʾλ�õ�y���� 
	char data[44];					//Ҫ��ʾ���ַ����� 
};
typedef void(*MsgCallBack)(bool timeout ,const char* jsonStr, void* context);

enum
{
	SUBEQT_STATE_fault = 0x01,
	SUBEQT_STATE_onlive = 0x02,
	SUBEQT_STATE_offlive = 0x03,
	SUBEQT_STATE_alarm = 0x04,
};

typedef void(*NetLib_SubEqtStateCallBack) (const SYS_ID_INFO & channel,int state,void* context);
/*
{
"msgType":1,   //
"errCode":0,    //
"data":
	{
		"clientHandle":123,
		"nodeid":1234567,
		"camJson":
				{
					"esName":"tongguan",
					
				}
	}
}
*/
#pragma pack(pop)


NETLIB_API long NetLib_Init(MsgCallBack msgcb,void*msgctx,bool init_playsdk = true);
NETLIB_API long NetLib_InitWnd(void* hwnd);
NETLIB_API long NetLib_Destroy();
NETLIB_API long NetLib_Login(LPNET_LOGIN_INFO deviceinfo);
NETLIB_API bool NetLib_checkLogin(long h_login);

NETLIB_API long NetLib_Logout(long h_login);
NETLIB_API bool NetLib_UUID2SUBID(long h_login,const char * uuid,SUB_ID_INFO & id);
NETLIB_API void NetLib_SetExceptionCallback(long h_login, tgExceptionNotify pExceptionProc, long userdata);
NETLIB_API void NetLib_SetSubEqtStateCallback(long h_login, NetLib_SubEqtStateCallBack nf, void* userdata);

NETLIB_API void NetLib_GetURL(long h_login,int urltype ,char * str,int strlen);
//��Ƶ���
NETLIB_API const char * NetLib_GetLastFrame(long play,int & rgb24len);

NETLIB_API long NetLib_StartRealPlay(long h_login, LPNET_DEVICE_CLIENTINFO clientinfo);
NETLIB_API long NetLib_StopRealPlay(long h_login, long h_realplay);
NETLIB_API long NetLib_PlaySmooth(long h_realplay,bool PlaySmooth);
NETLIB_API long NetLib_Snapshot(long h_realplay, const char *filename,int *w=0,int *h=0);
NETLIB_API long NetLib_GetTsAddr(long h_realplay,NET_TSADDR_INFO & info);
NETLIB_API long NetLib_SetDrawAspectRatio(long h_realplay, long ratio);
NETLIB_API long NetLib_OpenAudio(long h_realplay);
NETLIB_API long NetLib_CloseAudio(long h_realplay);
NETLIB_API long NetLib_SetVolume(long h_realplay, long volume);
NETLIB_API long NetLib_GetVolume(long h_realplay);
NETLIB_API long NetLib_EnableMeta(long h_realplay,bool enanle);
NETLIB_API bool NetLib_GetMetaStatus(long h_realplay);
NETLIB_API long NetLib_StartRecord(long h_realplay, const char *filename);
NETLIB_API long NetLib_StopRecord( long h_realplay);
NETLIB_API long NetLib_GetResolution( long h_realplay,int &w,int &h);
NETLIB_API long NetLib_SetDisPlayHandle(long h_realplay, void* hwnd);
// �����Խ�
NETLIB_API long NetLib_StartSpeak(long h_realplay);
NETLIB_API long NetLib_StopSpeak(long h_realplay);

// ���ܸ���
NETLIB_API long NetLib_StartTrace(long h_realplay);
NETLIB_API long NetLib_StopTrace(long h_realplay);
//���ֲܾ��Ŵ�
NETLIB_API bool NetLib_IntellZoomEable(long h_realplay);
NETLIB_API long NetLib_StartIntellZoomOut(long h_realplay,int x,int y);
NETLIB_API long NetLib_StartIntellZoomIN(long h_realplay);
// ͼƬƴ��
NETLIB_API bool NetLib_StartMontage(long h_realplay);
//��ѵ
NETLIB_API long NetLib_GetGroupPollingName(long h_login, NET_GROUP_POLLING_SET * set);
NETLIB_API long NetLib_SetGroupPolling(long h_login, NET_GROUP_POLLING_INFO * info);//��ӻ����޸���ѵ
NETLIB_API long NetLib_GetGroupPolling(long h_login, const char * name,NET_GROUP_POLLING_INFO * info);
NETLIB_API long NetLib_SetDefaultGroupPolling(long h_login, const char * name);
NETLIB_API long NetLib_DelGroupPolling(long h_login, const char * name);
NETLIB_API long NetLib_StartGroupPolling(long h_login,NET_GROUP_POLLING_INFO * info,void* *hwnd,int size,Notify notify_cb,void* userdata);
NETLIB_API long NetLib_StopGroupPolling(long h_login);

//Ѳ��
NETLIB_API long NetLib_GetCruiseByChannel(long h_login, const SYS_ID_INFO &channel,NET_CRUISE_INFO_SET * info,MsgCallBack func=0,void * ctx=0);
NETLIB_API long NetLib_GetCruiseByCruiseUUID(long h_login, char *pCruiseUuid,NET_CRUISE_INFO_SET * info);
NETLIB_API long NetLib_AddCruise(long h_login, const SYS_ID_INFO & channel,NET_CRUISE_INFO * info);
NETLIB_API long NetLib_AddPresetIntoCruise(long h_login, char *pCruiseUuid, char *pPresetUuid);
NETLIB_API long NetLib_DelPresetFromCruise(long h_login, char *pCruiseUuid, char *pPresetUuid);
NETLIB_API long NetLib_ModCruise(long h_login, const SYS_ID_INFO & channel,NET_CRUISE_INFO * info);
NETLIB_API long NetLib_DelCruise(long h_login, const char * cruise_uuid);
NETLIB_API long NetLib_StartCruise(long h_login, const SYS_ID_INFO & channel,NET_CRUISE_INFO * info);
NETLIB_API bool NetLib_Cruising(long h_login,const SYS_ID_INFO & channel);
NETLIB_API long NetLib_StopCruise(long h_login, const SYS_ID_INFO & channel);

//�ļ�������ط�
NETLIB_API long NetLib_FindFile(long h_login,NET_DEVICE_FILE_LIST_REQ * req,MsgCallBack func,void * ctx); 
NETLIB_API long NetLib_StartPlayBack(long h_login, LPNET_DEVICE_RECORD_FILE_INFO fileinfo, LPNET_DEVICE_CLIENTINFO clientinfo);
NETLIB_API long NetLib_StopPlayBack(long h_vodplay);
NETLIB_API long NetLib_SeekPlayStream(long h_vodplay, const char *seekTime);
NETLIB_API long NetLib_PlayBackFast(long h_vodplay);//���ٲ���
NETLIB_API long NetLib_PlayBackSlow(long h_vodplay);//���ٲ���
NETLIB_API long NetLib_PlayBackNormalSpeed(long h_vodplay);//�����ٶȲ���
NETLIB_API long NetLib_PlayBackKey(long h_vodplay);//�ؼ�֡����
NETLIB_API long NetLib_PlayBackOrPause(long h_vodplay, long pause);//��ͣ���߻ָ�

//¼���ļ�����
NETLIB_API long NetLib_DownLoadFile(long h_login, LPNET_DEVICE_RECORD_FILE_INFO fileinfo, char *filename);
NETLIB_API long NetLib_StopDownLoad( long h_download);
NETLIB_API long NetLib_GetDowndLoadPos(long h_download);

//��̨���ƽӿ�
NETLIB_API long NetLib_PTZControl(long h_login, const SYS_ID_INFO & channel, NET_PTZ_CTL cmd, long speed);//speed 0 ֹͣ
NETLIB_API long NetLib_PTZGetPresetInfo(long h_login,const SYS_ID_INFO & channel,LPNET_PTZ_PRESET_INFO info, int &size,MsgCallBack func=0,void * ctx=0);
NETLIB_API long NetLib_PTZDelPresetInfo(long h_login, const SYS_ID_INFO & channel,const char *preset_uuid);
NETLIB_API long NetLib_PTZModPresetInfo(long h_login, const SYS_ID_INFO & channel,const char *preset_name,int preset_id,const char *preset_uuid);
NETLIB_API long NetLib_PTZAddPresetInfo(long h_login, const SYS_ID_INFO & channel,const char *preset_name,int preset_id,char * uuid_out);//uuid_out:��ӳɹ�Ϊ�����Ԥ�õ��uuid
NETLIB_API long NetLib_PTZGotoPreset(long h_login, const SYS_ID_INFO & channel,const char *pPresetUUID);

//��ȡ��������
NETLIB_API long NetLib_GetDeviceConfig(long h_login, unsigned long dwCommand,const SYS_ID_INFO & lChannel, char * lpOutBuffer, unsigned long dwOutBufferSize, int32_t *nBytesReturned);
NETLIB_API long NetLib_SetDeviceConfig(long h_login, unsigned long dwCommand,const SYS_ID_INFO & lChannel, char * lpInBuffer, unsigned long dwInBufferSize,bool wait_result = false);
//�첽�ص��ӿ�
NETLIB_API void NetLib_GetMeta(long play, uint64_t pts,char **meta,int &len);
NETLIB_API long NetLib_GetOrganizeListInfo(long h_login,MsgCallBack func,void * ctx);
NETLIB_API void NetLib_StartAudioMeta(long h_login,const char * svr,int port);
NETLIB_API long NetLib_GetSubDeviceInfo(long h_login, long long SUID);
NETLIB_API long NetLib_GetChannelInfo(long h_login, int subid,  SYS_ID_INFO &channel);
//UserName �û��� ��DutyMan ������; Detail �����������
NETLIB_API long NetLib_DealAlarmLog(long h_login, const char * logid,const char  * UserName,const char * DutyMan,const char * Detail);
NETLIB_API long NetLib_DealAlarmLogBySubid(long h_login, SYS_ID_INFO &id,int alarmtype,const char  * UserName,const char * DutyMan,const char * Detail);
//////////////////////////////////////////////////////////////////////////
NETLIB_API long NetLib_EnableMetaALL(bool enanle);
NETLIB_API bool NetLib_GetMetaStatusById(const SYS_ID_INFO & channel);
NETLIB_API long NetLib_NotifySelected(const SYS_ID_INFO & channel);
NETLIB_API bool NetLib_CheckUserAuth(long h_login,NET_USERAUTH_CODEC authcodec);
NETLIB_API bool NetLib_CheckSubEqtAuth(long h_login,const char * subeqt_uuid);
#if 0//ע�͵�ҡͷ��ipc������������ؽӿڣ��ò�Ʒ��ʱû�м�������
NETLIB_API long NetLib_GetTransducerCFG(long h_login, char *pData, int dataLen);
NETLIB_API long NetLib_AddTransducer(long h_login, TRANSDUCER_TYPE transducerType, unsigned long long *deviceUUID);
NETLIB_API long NetLib_StopAddTransducer(long h_login, TRANSDUCER_TYPE transducerType, unsigned long long *deviceUUID);
NETLIB_API long NetLib_GetThingsDeviceInfos(long h_login, char *pData, int dataLen);
NETLIB_API long NetLib_SetThingsDeviceInfos(long h_login, TG_THINGS_DVICE_INFOS *pDeviceInfos);
NETLIB_API long NetLib_DelThingsDeviceInfos(long h_login, TG_THINGS_DVICE_INFOS *pDeviceInfos);
NETLIB_API long NetLib_GetAKeyArm(long h_login, int *enable);
NETLIB_API long NetLib_SetAKeyArm(long h_login, int enable);
#endif

NETLIB_API bool NetLib_SnapshotByYUV(char * yuv, int size, int w, int h, const char * filename);
NETLIB_API bool NetLib_SnapshotAndUpload(char * yuv,int size,int w,int h,const char * filename, const char * ftp_dir,const char * ftp, const char * user, const char * pwd);
#endif//_NET_DEVICE_SDK_H_