#ifndef _NET_DEVICE_PROTOCOL_H_
#define _NET_DEVICE_PROTOCOL_H_

#define     FIND_DEVICE_ADDR    "255.255.255.255"
#define     FIND_DEVICE_PORT    8888

typedef int                     vd_s32;
typedef unsigned int            vd_u32;
typedef long long               vd_s64;
typedef unsigned long long      vd_u64;
typedef char                    vd_char;
typedef unsigned char           vd_u8;
typedef char                    vd_s8;
typedef unsigned short          vd_u16;
typedef short                   vd_s16;

typedef int                     HI_S32;
typedef unsigned int            HI_U32;  
typedef long long               HI_S64;
typedef unsigned long long      HI_U64;
typedef char                    HI_CHAR;
typedef unsigned char           HI_U8;
typedef char                    HI_S8;
typedef unsigned short          HI_U16;
typedef short                   HI_S16;


#pragma pack(push,1)
#define TG_LOC_CTL_PORT                 (10001)     //����������
                                                    
#define TG_LOC_DATA_PORT                (10002)     //����������
                                                    
#define TG_NET_SLICE_MAX_LEN            (1024)      //������Ƭ��󳤶�

#define TG_LOC_IP_MAX_LEN               (32)

#define TG_LOC_CUR_VERSION              (0x1000)

#define TG_NO_SLICE_TAG                 (0xffff)

#define TG_KEEPLIVE_INTERVAL            (5)

#define TG_KEEPLIVE_MAX_TIMES           (3)

#ifndef TG_DEVICE_ID_LEN
    #define TG_DEVICE_ID_LEN            (64)
#endif


#ifndef TG_DEVICE_NAME_LEN
    #define TG_DEVICE_NAME_LEN           (32)
#endif




typedef enum{

    TG_NET_MSG_OK                 = 0       ,
    TG_NET_MSG_ERR                = 1       ,
    TG_UNSUPPORT_MSG_ERR          = 2       ,

    TG_DEV_NO_FIND_ERR            = 100     ,
    TG_GET_LOC_IP_ERR                       ,
                                            
    TG_NET_MSG_TYPE_ERR           = 200     ,
    TG_NET_MSG_LEN_ERR                      ,

    TG_NET_TRANS_TYPE_ERR         = 300     ,

    TG_LOGIN_PWD_ERR              = 1000    ,
    TG_LOGIN_USERNAME_ERR                   ,
    TG_SESSION_ID_ERR                       ,
    TG_SESSION_TIMEOUT                      ,



    TG_STREAM_TYPE_ERR            = 2000    ,
    TG_CHANNEL_NUM_ERR                      ,




    TG_ENC_PARAM_ERR              = 3000    ,


    TG_IPC_URL_ERR                = 4000    ,
    TG_IPC_USERNAME_ERR                     ,
    TG_IPC_PWD_ERR                          ,

    TG_SQLITE_GET_RECORD_ENTRY_ERR = 5000   ,

    TG_FILE_TRANS_FILE_CANNOT_OPEN_ERR = 6000,

    TG_SQLITE_RECORD_PLAN_GET_ERROR = 7000,


}TG_LOC_RESULT_E;

typedef enum{

    TG_LOC_KEEPLIVE_MSG         = 0x100     ,     //keeplive��Ϣ,���ڿ���ͨ��,ÿ��TG_KEEPLIVE_INTERVAL �뷢һ�Σ�˫������������Ӧ����ʽ��
                                                  //�ɿͻ������ȷ����豸�˻�Ӧ�����������TG_KEEPLIVE_MAX_TIMESû�л��,
                                                  //����Ϊpeer�رգ�ֻ��Ҫ��Ϣͷ����������Ϣ��

    TG_LOC_FIND_DEV_ASK         = 0x200     ,     //�豸��������
    TG_LOC_FIND_DEV_ANS                     ,


	TG_MCAST_GET_DEV_INF_ASK                = 0x202     ,     //�ಥ��ȡ�豸��Ϣ����
	TG_MCAST_GET_DEV_INF_ANS                = 0x203     ,     //�ಥ��ȡ�豸��Ϣ�ش�

	TG_MCAST_SET_DEV_INF_ASK                = 0x204     ,     //�ಥ�����豸��Ϣ����
	TG_MCAST_SET_DEV_INF_ANS                = 0x205     ,     //�ಥ�����豸��Ϣ�ش�


    /*ͬ�۱����������*/

    TG_LOC_GET_STREAM_ASK       = 0x1001    ,     //�������������� 
    TG_LOC_GET_STREAM_ANS       = 0x1002    ,     //��������������ش�   
                                                                                     //
    TG_LOC_START_STREAM_ASK     = 0x1003    ,     //����ʼ�������������ͨ���� 
    TG_LOC_START_STREAM_ANS     = 0x1004    ,     //����ʼ����������ش�(����ͨ��) 

    TG_LOC_LOGIN_ASK            = 0x1005    ,
    TG_LOC_LOGIN_ANS            = 0x1006    ,

    TG_SET_SYS_TIME_ASK         = 0x1007    ,
    TG_SET_SYS_TIME_ANS         = 0x1008    ,

    TG_DEV_NET_TYPE_ASK         = 0x1009    ,     //�豸��������ѯ��
    TG_DEV_NET_TYPE_ANS         = 0x100A    ,     //�豸�������ͻش�

    TG_DEV_NET_SET_ASK          = 0x100B    ,     //�����豸��������
    TG_DEV_NET_SET_ANS          = 0x100C    ,     //�����豸����ش�

    TG_DEV_CHAN_INF_ASK         = 0x100D    ,     //��ȡͨ����Ϣ����
    TG_DEV_CHAN_INF_ANS         = 0x100E    ,     //��ȡͨ����Ϣ��Ӧ

    
    TG_SET_OSD_ASK              = 0x100F    ,     //����OSD����
    TG_SET_OSD_ANS              = 0x1010    ,
                                            
    TG_SET_MD_ASK               = 0x1011    ,     //����MV����
    TG_SET_MD_ANS               = 0x1012    ,
                                            
    
    TG_DEV_INTERCOM_INF_ASK     = 0x1013    ,     //ѯ���Ƿ���ԶԽ�����
    TG_DEV_INTERCOM_INF_ANS     = 0x1014    ,     //�Ƿ���ԶԽ��ش�

    TG_DEV_START_INTERCOM_ASK   = 0x1015    ,     //�����Խ�����
    TG_DEV_START_INTERCOM_ANS   = 0x1016    ,     
    
    TG_SET_DEV_ID_ASK           = 0x1017    ,     //�����豸ID����
    TG_SET_DEV_ID_ANS           = 0x1018    ,     //�����豸ID��Ӧ    


    TG_GET_DEV_ID_ASK           = 0x1019    ,    //��ȡ�豸ID����
    TG_GET_DEV_ID_ANS           = 0x101A    ,    //��ȡ�豸ID��Ӧ

    TG_LVS_GET_IPC_ASK          = 0x101B    ,    //��ȡǰ��IPC����Ϣ����
    TG_LVS_GET_IPC_ANS          = 0x101C    ,    //��ȡǰ��IPC����Ϣ��Ӧ

    TG_LVS_SET_IPC_ASK          = 0x101D    ,    //LVS ����ǰ��IPC����������
    TG_LVS_SET_IPC_ANS          = 0x101E    ,    //LVS ����ǰ��IPC�Ļ�Ӧ

    TG_GET_VENC_PARAM_ASK       = 0x101F    ,    //��ȡ��Ƶ�����������
    TG_GET_VENC_PARAM_ANS       = 0x1020    ,    //��ȡ��Ƶ�����������

    TG_FILE_SEARCH_ASK          = 0x1021    ,    //�ļ���������
    TG_FILE_SEARCH_ANS          = 0x1022    ,    //�ļ������ش�

    TG_START_FILE_STREAM_ASK    = 0x1023    ,    //��ʼ�����ļ�������
    TG_START_FILE_STREAM_ANS    = 0x1024    ,    //��ʼ�����ļ����ش�

    TG_FILE_PB_ASK              = 0x1025    ,    //�ļ��ط�����
    TG_FILE_PB_ANS              = 0x1026    ,    //�ļ��طŻش�
    
    TG_FILE_SEEK_ASK            = 0x1027    ,    //�ļ�seek����
    TG_FILE_SEEK_ANS            = 0x1028    ,    //�ļ�seek����

    TG_GET_FILE_INDEX_ASK       = 0x1029    ,    //��ȡ�ļ���������
    TG_GET_FILE_INDEX_ANS       = 0x102A    ,    //��ȡ�ļ�������Ӧ

    TG_GET_RECORD_PROJ_ASK      = 0x102B    ,    //��ȡ¼��ƻ�����
    TG_GET_RECORD_PROJ_ANS      = 0x102C    ,    //��ȡ¼��ƻ���Ӧ

    TG_SET_RECORD_PROJ_ASK      = 0x102D    ,    //����¼��ƻ�����
    TG_SET_RECORD_PROJ_ANS      = 0x102E    ,    //����¼��ƻ���Ӧ


    TG_SET_ENC_LEVEL_ASK        = 0x1030    ,    //���ñ��뼶������
    TG_SET_ENC_LEVEL_ANS        = 0x1031    ,    //���ñ��뼶��ش�

    TG_GET_ENC_LEVEL_ASK        = 0x1032    ,    //��ȡ���뼶������
    TG_GET_ENC_LEVEL_ANS        = 0x1033    ,    //��ȡ���뼶��ش�

    TG_START_RECORD_ASK         = 0x1034    ,    //��ʼ¼������
    TG_START_RECORD_ANS         = 0x1035    ,    //��ʼ¼��ش�

    TG_STOP_RECORD_ASK          = 0x1036    ,    //ֹͣ¼������
    TG_STOP_RECORD_ANS          = 0x1037    ,    //ֹͣ¼��ش�

    TG_MANUAL_SEARCH_DEV_ASK    = 0x1038    ,    //�ֶ������豸����
    TG_MANUAL_SEARCH_DEV_ANS    = 0x1039    ,    //�ֶ������豸�ش�

	TG_GET_REENC_INF_ASK        = 0x103A    ,    //��ȡ�ر���Ϣ����
	TG_GET_REENC_INF_ANS        = 0x103B    ,    //��ȡ�ر���Ϣ��Ӧ

	TG_SET_REENC_INF_ASK        = 0x103C    ,    //�����ر���Ϣ����
	TG_SET_REENC_INF_ANS        = 0x103D    ,    //�����ر���Ϣ�ش�

	TG_DEL_REENC_INF_ASK                    = 0x103E    ,    //ɾ���ر���Ϣ����
	TG_DEL_REENC_INF_ANS                    = 0x103F    ,    //ɾ���ر���Ϣ����



	PA_SET_RF_DEVICE_IP_ASK     = 0x1040    ,         //����RF�豸��ַ����
	PA_SET_RF_DEVICE_IP_ANS     = 0x1041    ,     //����RF�豸��ַ�ش�
	PA_GET_RF_DEVICE_IP_ASK     = 0x1042    ,//��ȡRF�豸IP��ַ����
	PA_GET_RF_DEVICE_IP_ANS     = 0x1043     , //��ȡRF�豸IP��ַ�ش�



    ////////////////
	TG_FILE_STREAM_PB_BY_TIME_RANGE_ASK     = 0x1044    , //����ʱ��ط�¼���ļ�����
	TG_FILE_STREAM_PB_BY_TIME_RANGE_ANS     = 0x1045    , //����ʱ��ط�¼���ļ�Ӧ��

	TG_GET_SYS_TIME_ASK                     = 0x1100    ,   //��ȡϵͳʱ��
	TG_GET_SYS_TIME_ANS                     = 0x1101    ,   //��ȡϵͳʱ��ش�

	TG_GET_STORAGE_ASK                      = 0x1102    ,   //��ȡ�洢��Ϣ����
	TG_GET_STORAGE_ANS                      = 0x1103    ,   //��ȡ�洢��Ϣ����

	TG_DEL_IPC_ASK                          = 0x1104    ,   //ɾ��ǰ��IPC��Ϣ����
	TG_DEL_IPC_ANS                          = 0x1105    ,   //ɾ��ǰ��IPC��Ϣ����

	TG_GET_CHAN_NAME_ASK                    = 0x1106    ,   //��ȡͨ����������
	TG_GET_CHAN_NAME_ANS                    = 0x1107    ,   //��ȡͨ����������

	TG_SET_CHAN_NAME_ASK                    = 0x1108    ,   //����ͨ����������
	TG_SET_CHAN_NAME_ANS                    = 0x1109    ,   //����ͨ����������



	TG_DEVICE_REBOOT_ASK                    = 0x110A    ,   //ϵͳ��������
	TG_DEVICE_REBOOT_ANS                    = 0x110B    ,   //ϵͳ����Ӧ��

	TG_CLEAN_SYS_CACHE_ASK                  = 0x110C    ,   //���ϵͳ��������
	TG_CLEAN_SYS_CACHE_ANS                  = 0x110D    ,   //���ϵͳ����ش�

	TG_CLEAN_HEATPIC_ASK                    = 0x110E    ,   //�������ͼ����
	TG_CLEAN_HEATPIC_ANS                    = 0x110F    ,   //�������ͼ�ش�


	TG_PTZ_CTL_ASK                          = 0x1120    ,   //��̨��������
	TG_PTZ_CTL_ANS                          = 0x1121    ,   //��̨����ش�

	TG_GET_DNS_ASK                          = 0x1122    ,   //��ȡDNS��������
	TG_GET_DNS_ANS                          = 0x1123    ,   //��ȡDNS����ش�

	TG_SET_DNS_ASK                          = 0x1124    ,   //����DNS��������
	TG_SET_DNS_ANS                          = 0x1125    ,   //����DNS����ش�

	TG_GET_NET_INF_ASK                      = 0x1126    ,   //��ȡNET��������
	TG_GET_NET_INF_ANS                      = 0x1127    ,   //��ȡNET����ش�


	TG_GET_SOFT_VERSION_ASK                 = 0x1128    ,   //��ȡ����汾������
	TG_SET_SOFT_VERSION_ANS                 = 0x1129    ,   //��ȡ����汾�Żش�

	TG_SET_GOP_INF_ASK						= 0x112C    ,   //����gop����
	TG_SET_GOP_INF_ANS						= 0x112D    ,   //����gop�ش�
	TG_GET_GOP_INF_ASK						= 0x112E    ,   //��ȡgop����
	TG_GET_GOP_INF_ANS						= 0x112F    ,   //��ȡgop�ش�

	TG_SET_FLIP_ASK                         = 0x1138    ,//���÷�ת����


	//Σ��Ʒ��ض����ڴ�,ʼ��0x1200
	TG_SET_SENSOR_CFG_ASK                       = 0x1201    ,//���ô�������������
	TG_SET_SENSOR_CFG_ANS                       = 0x1202    ,//���ô���������Ӧ��
	TG_GET_SENSOR_CFG_ASK                       = 0x1203    ,//��ȡ��������������
	TG_GET_SENSOR_CFG_ANS                       = 0x1204    ,//��ȡ����������Ӧ��

	TG_GET_CE_CFG_ASK                           = 0x1400    ,//��ȡ�����豸��������
	TG_GET_CE_CFG_ANS                           = 0x1401    ,//��ȡ�����豸���ûش�

	TG_ADD_CE_ASK                               = 0x1402    ,//��������������豸����
	TG_ADD_CE_ANS                               = 0x1403    ,//��������������豸�ش�

	TG_GET_CE_DEVICE_ASK                        = 0x1404    ,//��ȡ�����豸��Ϣ���� 
	TG_GET_CE_DEVICE_ANS                        = 0x1405    ,//��ȡ�����豸��Ϣ�ش�

	TG_SET_CE_DEVICE_ASK                        = 0x1406    ,//���������豸��Ϣ���� 
	TG_SET_CE_DEVICE_ANS                        = 0x1407    ,//���������豸��Ϣ�ش� 

	TG_DEL_CE_DEVICE_ASK                        = 0x1408    ,//ɾ�������豸��Ϣ����
	TG_DEL_CE_DEVICE_ANS                        = 0x1409    ,//ɾ�������豸��Ϣ�ش�

	TG_SET_PRESET_ASK                           = 0x140A    ,//����Ԥ�õ�����
	TG_SET_PRESET_ANS                           = 0x140B    ,//����Ԥ�õ�ش�


	TG_GET_PRESET_ASK                           = 0x140C    ,//��ȡԤ�õ�����
	TG_GET_PRESET_ANS                           = 0x140D    ,//��ȡԤ�õ�ش�

	TG_CE_ALARM_ASK                             = 0x140E    ,//�����豸�����ϱ�
	TG_CE_ALARM_ANS                             = 0x140F    ,
	
	TG_GOTO_PRESET_ASK                          = 0x1410    ,//�����豸��ת����
	TG_GOTO_PRESET_ANS                          = 0x1411    ,//�����豸��ת�ش�
	
	TG_LAYING_STATUS_ASK                        = 0x1412    ,//һ����������
	TG_LAYING_STATUS_ANS                        = 0x1413	,//һ����������
	
	TG_LAYING_GET_STATUS_ASK                    = 0x1414    ,//��ȡһ����������
	TG_LAYING_GET_STATUS_ANS                    = 0x1415    ,//��ȡһ����������
    /*ͬ�����������*/
    
    TG_CLOUD_SET_GW_ASK         = 0x2001    ,     //����ͬ��ϵͳ��������IP���˿ڣ�
    TG_CLOUD_SET_GW_ANS         = 0x2002    ,     //����ͬ��ϵͳ���ػش�

    TG_CLOUD_SET_USERNAME_ASK   = 0x2003    ,     //����ͬ��ϵͳ�����û�������
    TG_CLOUD_SET_USERMANE_ANS   = 0x2004    ,     //����ͬ��ϵͳ�����û����ش�    
                                                       
    TG_SET_DEV_REGION_ASK       = 0x2005    ,     //����ͬ��ϵͳregion��location��������
    TG_SET_DEV_REGION_ANS       = 0x2006    ,                                                 

    TG_CLOUD_GET_GW_ASK         = 0x2007    ,     //��ȡͬ��ϵͳ��������
    TG_CLOUD_GET_GW_ANS         = 0x2008    ,     //��ȡͬ��ϵͳ��������ش�

    TG_CLOUD_GET_USERNAME_ASK   = 0x2009    ,     //��ȡͬ��ϵͳ�����û�������
    TG_CLOUD_GET_USERMANE_ANS   = 0x200A    ,     //��ȡͬ��ϵͳ�����û����ش�   

    TG_GET_DEV_REGION_ASK       = 0x200B    ,     //��ȡͬ��ϵͳregion��location��������
    TG_GET_DEV_REGION_ANS       = 0x200C    ,     //��ȡͬ��ϵͳregion��location���ƻش�    


	TG_GET_PROCESS_NAME_ASK                 = 0x200D    ,     //��ȡ��������ѯ��
	TG_GET_PROCESS_NAME_ANS                 = 0x200E    ,     //��ȡ�������ƻش�

	TG_SET_PROCESS_NAME_ASK                 = 0x200F    ,     //���ù�������ѯ��
	TG_SET_PROCESS_NAME_ANS                 = 0x2010    ,     //���ù������ƻش�



	TG_START_FILE_STREAM_PAUSE_ASK          = 0x1323    ,    //������ͣ����
	TG_START_FILE_STREAM_PAUSE_ANS          = 0x1324    ,    //������ͣ�ش�

	TG_START_FILE_STREAM_RESUME_ASK         = 0x1325    ,    //������ͣ�ָ�����
	TG_START_FILE_STREAM_RESUME_ANS         = 0x1326    ,    //������ͣ�ָ��ش�  
	TG_START_FILE_STREAM_RELOCATE_ASK       = 0x1327    ,    //�����ļ�����
	TG_START_FILE_STREAM_RELOCATE_ANS       = 0x1328    ,    //�����ļ���Ӧ

	TG_FILE_DOWNLOAD_ASK                    = 0x1329    ,    //�ļ���������
	TG_FILE_DOWNLOAD_ANS                    = 0x1330    ,    //�ļ����ػش�

	TG_FILE_DOWNLOAD_STREAM_ASK             = 0x1331    ,    //���������ļ�������
	TG_FILE_DOWNLOAD_STREAM_ANS             = 0x1332    ,    //���������ļ����ش�
                                                             

    /*ͬ�����ݴ������*/

    TG_LOC_H264_TRANS           = 0x3001    ,     //H264���ݴ����������ͨ����
    TG_LOC_AUDIO_TRANS          = 0x3002    ,     //��Ƶ���ݴ����������ͨ����
    TG_LOC_FILE_TRANS           = 0x3003    ,     //�ļ������䷽ʽ����

	/*ͬ��������ʾ*/
	TG_PEOPLECOUNT_SHOW_ASK					= 0x6001    ,     //����ͳ��������ʾ

	TG_GET_CURRENT_UPGRADE_MODE_ASK  		= 0x7000	,	//��ȡ��ǰ������ʽ����
	TG_GET_CURRENT_UPGRADE_MODE_ANS 		= 0x7001	,	//��ȡ��ǰ������ʽ�ش�

	TG_SET_CURRENT_UPGRADE_MODE_ASK 		= 0x7002	,	//���õ�ǰ������ʽ����
	TG_SET_CURRENT_UPGRADE_MODE_ANS 		= 0x7003	,	//���õ�ǰ������ʽ�ش�

	TG_SET_CURRENT_UPGRADE_IPADDR_PORT_ASK	= 0x7004	,	//���õ�ǰ����IP�Ͷ˿�����
	TG_SET_CURRENT_UPGRADE_IPADDR_PORT_ANS	= 0x7005	,	//���õ�ǰ����IP�Ͷ˿ڻش�

}TG_LOC_MSG_TYPE_E;



/**************************************************
 *  
 * ��ý�����ͣ���Ĺ�ϵ,��������+��Ƶ = TG_H264_MAIN_STREAM|TG_AUDIO_STREAM
 *      
 *    
 ***************************************************/

typedef enum{

    TG_H264_MAIN_STREAM  = 0x01,   //ֻ��H264������
    TG_H264_SUB_STREAM   = 0x02,   //ֻ��H264������
    TG_AUDIO_STREAM      = 0x04,   //ֻ����Ƶ��
    TG_H265_MAIN_STREAM  = 0x08,   //��H265������
    TG_H265_SUB_STREAM   = 0x10,   //��H265������
    TG_VIDEO_LOW_STREAM  = 0x20,   //��Ƶѹ����������־
    TG_VIDEO_ORIG_STREAM = 0x40,   //��Ƶѹ��ԭʼ�������޴���

}TG_STREAM_TYPE_E;

typedef enum{ 

    TG_RC_CBR = 0,
    TG_RC_VBR,
    TG_RC_FIXQP

}TG_V_RC_TYPE_E;



typedef enum{

    TG_TRANS_TCP                ,               //�������TCP
    TG_TRANS_UDP                ,               //�������UDP
    TG_TRANS_RTP                ,               //rtp��ʽ����
    TG_TRANS_FTP_PASSIVE        ,               //ftp������ʽ����
    TG_TRANS_FTP_INITIATIVE     ,               //ftp������ʽ����
    
}TG_TRANS_TYPE_E;


typedef enum{

	TG_NET_ETHER        = 0x01,  //��������
	TG_NET_WIFI         = 0x02,  //wifi
	TG_NET_3G           = 0x04,  //3G
	TG_NET_4G           = 0x08,  //4G
	TG_NET_ZIGBEE       = 0x10,  //zigbee

}TG_DEV_NET_TYPE;

typedef enum{

	TG_ETHER_STATIC_STATUS       ,
	TG_ETHER_DHCP_STATUS         ,
	TG_WIFI_AP_STATUS            ,
	TG_WIFI_STA_STATUS           ,
	TG_3G_STATUS                 ,
	TG_4G_STATUS                 ,

}TG_NET_ALLOC_STATUS_E;




typedef struct{

    TG_LOC_MSG_TYPE_E   msg_type;  //msg type
    vd_s32              version;   //�汾�ţ���������
    vd_u32              msg_len;   //msg length,û�н��������ݽṹΪ 0������������

}tg_loc_msg_head_t;


/**************************************************
 *  
 * �豸����Э��
 *      
 *    
 ***************************************************/

typedef enum{

    TG_DEV_IPC               ,       //Ƕ��ʽIPC�豸
    TG_DEV_4G                ,       //4G�豸
    TG_DEV_EMBEDDED_LVS      ,       //Ƕ��ʽLVS�豸
    TG_DEV_PC_LVS            ,       //pc LVS�豸

}TG_DEV_TYPE_E;

typedef enum{

    TG_FIND_ALL_DEV_TYPE            ,       //��ѯ���е��豸
    TG_FIND_SPEC_DEV_ID_TYPE        ,       //ͨ���豸ID��ѯָ�����豸
    TG_FIND_SPEC_DEV_NAME_TYPE      ,       //ͨ���豸���Ʋ�ѯָ�����豸(TBD)
    TG_FIND_SPEC_DEV_TYPE           ,       //ͨ���豸���Ͳ���

}TG_FIND_DEV_TYPE_E;

typedef enum{
	DEVICE_TILT_UP             =21     ,               /* ��̨��SS���ٶ����� */
	DEVICE_TILT_DOWN		            ,  	            /* ��̨��SS���ٶ��¸� */
	DEVICE_PAN_LEFT		            ,	            /* ��̨��SS���ٶ���ת */
	DEVICE_PAN_RIGHT		            ,	            /* ��̨��SS���ٶ���ת */
	DEVICE_UP_LEFT			            ,	            /* ��̨��SS���ٶ���������ת */
	DEVICE_UP_RIGHT		            ,	            /* ��̨��SS���ٶ���������ת */
	DEVICE_DOWN_LEFT		            ,	            /* ��̨��SS���ٶ��¸�����ת */
	DEVICE_DOWN_RIGHT		            ,	            /* ��̨��SS���ٶ��¸�����ת */
	DEVICE_PAN_AUTO		            ,	            /* ��̨��SS���ٶ������Զ�ɨ�� */
	DEVICE_PAN_CIRCLE                  ,               /* ��̨��SS���ٶ��Զ�Բ��ɨ�� */

	DEVICE_ZOOM_IN_P                   ,               /* �������ٶ�SS���(���ʱ��) */
	DEVICE_ZOOM_OUT_P                  ,               /* �������ٶ�SS��С(���ʱ�С) */
	DEVICE_FOCUS_NEAR                  ,               /* �������ٶ�SSǰ�� */
	DEVICE_FOCUS_FAR                   ,               /* �������ٶ�SS��� */
	DEVICE_IRIS_OPEN                   ,               /* ��Ȧ���ٶ�SS���� */
	DEVICE_IRIS_CLOSE                  ,               /* ��Ȧ���ٶ�SS��С */
	DEVICE_PTZ_MOVE_STOP       

}TG_PTZ_CTL_TYPE_E;

typedef struct{

    TG_FIND_DEV_TYPE_E  find_type; 
    TG_DEV_TYPE_E       dev_type;  							//�����ʽΪTG_FIND_SPEC_DEV_TYPE����Ҫ��д���ֶΣ�������ֶκ���
    vd_u64              device_id;							//�����ʽΪTG_FIND_SPEC_DEV_ID_TYPE����Ҫ��д���ֶΣ�������ֶκ���
    vd_char             device_name[TG_DEVICE_NAME_LEN];    //�����ʽΪTG_FIND_SPEC_DEV_NAME_TYPE ����Ҫ��д���ֶΣ�������ֶκ���

}tg_loc_dev_find_req_t;



typedef struct{

    TG_LOC_RESULT_E     result;                         	//return result
    TG_DEV_TYPE_E       dev_type; 							//�����豸����
    vd_u64              device_id;							//�����豸ID
    vd_char             device_name[TG_DEVICE_NAME_LEN];    //�����豸����
    vd_char             ip[TG_LOC_IP_MAX_LEN];          	//�豸IP��ַ
    vd_u16              port;                           	//���ƶ˿�
    vd_u16              reserv;                         	//������չ��ע���豸����,
															//Ҳ�ɸ���device_id�淶�ֶ�parse����������
}tg_loc_dev_find_reply_t;


typedef enum{

	/*��ͨ�û��ɵ�����*/
	TG_MOD_IP_TYPE                  = 0x1           ,
	TG_MOD_DNS_TYPE                 = 0x2           ,
	TG_MOD_NET_ALLOC_TYPE           = 0x4           ,


	/*����ģʽ�¿ɵ����ģ����ڹ�˾�ڲ���Ʒ��������*/

	TG_MOD_CLOUD_GW_ADDR_TYPE       = 0x100         ,
	TG_MOD_CLOUD_USENAME_TYPE       = 0x200         ,
	TG_MOD_CLOUD_REGION_TYPE        = 0x400         ,
	TG_MOD_DEV_SN_TYPE              = 0x800         ,


	/*ƽ����Ŀ*/
	TG_MOD_PA_RF_ADDR_TYPE            = 0x10000     ,   



}TG_DEV_INF_MASK_E;



typedef struct{


	TG_DEV_INF_MASK_E               mask;                   //����,�޸���ĳһ��

	TG_DEV_TYPE_E                   dev_type;               //�豸����

	vd_char                         ip[16];                 //IP��ַ
	vd_char                         gwip[16];               //���ص�ַ
	vd_char                         netmask[16];            //��������   
	vd_char                         dns1[16];
	vd_char                         dns2[16];   
	vd_s32                          alloc_type;             // -1:δ֪;0:��̬IP ;1:DHCP 
	TG_DEV_NET_TYPE                 net_type;               //1:���� 2��wifi

	vd_char                         cloud_gwurl_1[32];      //ͬ������url1��ַ
	vd_char                         cloud_gwurl_2[32];      //ͬ������url1��ַ
	vd_s32                          cloud_gwport;           //ͬ�����ض˿�
	vd_char                         cloud_username[16];     //�ƶ��û���
	vd_char                         cloud_pwd[128];         //�ƶ��û�����
	vd_char                         cloud_region_name[32];  //�ƶ�region����ƽ����Ŀ��Ҫ
	vd_char                         cloud_locale_name[32];  //�ƶ�locale����

	vd_char                         rfdev_ip[16];           //rf �豸ID
	vd_s32                          rfdev_port;             //rf�豸�˿�


	vd_char                         dev_sn[64];             //�豸SN
	vd_u64                          device_id ;             //�豸ID��mac��ַת��          

	vd_char                         mac[20];   
	vd_char                         version[64];            //����汾



}tg_mcast_dev_inf_t;


typedef struct{

	TG_LOC_RESULT_E         result;                 //���ؽ����������ز���ȷ������ͨ��mask�鿴ʱ�������ò���ȷ
	TG_DEV_INF_MASK_E       mask;                   //����,������
	vd_u64                  device_id ;             //���ڱȽ��豸ID

}tg_mcast_dev_inf_set_ans_t;




/**************************************************
 *  
 * ���ƶ˿�Э��
 *      
 *    
 ***************************************************/




/**************************************************
 *  
 * �ͻ��������ӵ����ƿں����������ݴ���������Ϣ���ͣ�TG_LOC_GET_STREAM_ASK
 * tg_loc_msg_head_t + tg_get_stream_ask_t
 *    
 ***************************************************/


typedef enum{

    TG_LOGIN_TYPE_USERNAME  ,
    TG_LOGIN_TYPE_DEVID     ,
    TG_LOGIN_TYPE_DEVNAME   ,
    TG_LOGIN_TYPE_MOBILE    ,
    TG_LOGIN_TYPE_EMAIL     ,

}TG_LOGIN_TYPE_E;


typedef enum{

    TG_SYS_ADMIN        = 1 ,      //ϵͳ������Ȩ�ޣ����ڲ�����ʹ��
    TG_USER_ADMIN           ,      //�û�������Ա�˺�
    TG_COMMON_USER          ,      //��ͨ�û���

    TG_USER_TYPE_BUTT       

}TG_USER_TYPE_E;

typedef struct{

    TG_USER_TYPE_E      user_type;
    TG_LOGIN_TYPE_E     login_type;
    vd_u64              device_id;		//ͨ��dev_id��ʽ��¼
    vd_char             name[64];       //Ϊ�˼��ݸ��ֵ�½���ͣ��ַ�������һЩ
    vd_char             passwd[32];     //�����MD5
	

}tg_login_ask_t;


typedef struct{

    TG_LOC_RESULT_E     result;     
    TG_DEV_TYPE_E       dev_type;           //�豸����
    vd_u32              dev_auth;           //�û��豸Ȩ��
    vd_u64              device_id;

}tg_login_ans_t;

typedef struct{

	vd_u16	            year;	// ��
	vd_u8	            mon;	// ��
	vd_u8	            day;	// ��
	vd_u8	            hour;	// Сʱ
	vd_u8	            min;	// ����
	vd_u8               sec;    // ��
	vd_u8               weekday;// ���ڣ�������Ϊ0

}tg_time_ask_t;

typedef enum{

	TG_OSD_TYPE_TIME = 0,		//��ʾʱ��
	TG_OSD_TYPE_STR,			//��ʾ�ַ�
	TG_OSD_TYPE_LOG				//��ʾλͼLOG
}TG_OSD_TYPE_E;

typedef struct 
{
	HI_S32 xpos;
	HI_S32 ypos;
}tg_position_s;

typedef struct 
{
	HI_U32 u32Width;
	HI_U32 u32Height;
}tg_size_s;

typedef struct{

	HI_S8			channel;
	HI_S8			block;
	HI_S8 			osdenabled;
	HI_S8			reserved;
	TG_OSD_TYPE_E   osdtype;
	HI_S32 			color;
	tg_position_s	point;
	tg_size_s       size;
	HI_S32			datalength;
	HI_S8			buffer[0];

}tg_osd_cfg_t;

typedef struct{

    TG_LOC_RESULT_E         result;       //return result

}tg_time_ans_t;

typedef struct{

	TG_LOC_RESULT_E         result;       //return result

}tg_osd_ans_t;

typedef struct{

    TG_DEV_NET_TYPE     support_net_type;  //��Ĺ�ϵ�������м��ָ�������

}tg_net_inf_ans_t;



typedef struct{

    vd_char     ip[16];        //IP��ַ
    vd_char     gwip[16];      //���ص�ַ
    vd_char     netmask[16];   //��������

}tg_ether_static_inf_t;


typedef struct{

    vd_char     ssid[20];
    vd_char     pwd[16];

}tg_wifi_sta_inf_t;


typedef union{

    tg_wifi_sta_inf_t       wifi_sta_inf;
    tg_ether_static_inf_t   eth_static_inf;

}TG_NET_DEV_SET_U;



/**************************************************
 *  
 * �˽ṹ�����޻ش���Ϣ,��Ϊ������ܶϵ�,���Ǿ����ش�
 * 
 *    
 ***************************************************/

typedef struct{

    TG_NET_ALLOC_STATUS_E   set_type        ;   //��������
    vd_s8                   enable          ;   //ʹ�ܱ�־��0:diable,1:enable
    vd_s8                   reserv[3]       ;
    TG_NET_DEV_SET_U        net_dev_set_u   ;

}tg_net_dev_set_ask_t;


/**************************************************
 *  
 * �ش���Ϣ���ܰ���: 
 * 1.�޻ش�Ϊ������ܶϵ����� 
 * 2���лش�(������磬wifi+4G),������ر�4G�� 
 * 3.�ظ���Ϣ���ܸ��߿ͻ����豸��������
 * 
 *    
 ***************************************************/

typedef struct{

    TG_LOC_RESULT_E         result;       //return result

}tg_net_dev_set_ans_t;




typedef struct{

    vd_u8                   chn;            //ͨ���ţ���0��ʼ��
    vd_s8                   enable;         // ʹ�ܱ�־,0:disable ��1:enable  
    vd_u8                   framerate;      //֡��
    vd_s8                   reserv;
    TG_STREAM_TYPE_E        stream_type;    //���ǻ�Ĺ�ϵ��ֻ��һ������
    vd_u16                  width;          //ͼ����
    vd_u16                  height;         //ͼ��߶�
    vd_s32                  bitrate;        //������
    TG_V_RC_TYPE_E          rc_type;        //rc����

}tg_v_chan_inf_t;


/**************************************************
 *  
 * ÿ��ͨ���ļ���Ϣ
 * 
 *    
 ***************************************************/

typedef struct{

    vd_u8                   chn;            //ͨ���ţ���0��ʼ��
    vd_s8                   reserv[3];   //
    TG_STREAM_TYPE_E        stream_type;    //��Ĺ�ϵ
	vd_char                 chn_name[32];
   
}tg_per_chan_inf_t;



typedef struct{

    TG_LOC_RESULT_E             result;   //return result

}tg_set_ipc_ans_t;

typedef struct{

	TG_LOC_RESULT_E             result;   //return result

}tg_manual_search_dev_ans_t;

/**************************************************
 *  
 * ͨ����Ϣͷ���ṹ�壬������ɸ�tg_per_chan_inf_t�ṹ�壬Ϊ�䳤�ṹ
 * 
 *    
 ***************************************************/

typedef struct{
    TG_LOC_RESULT_E         result;       //return result
    vd_s32                  chan_num;    //��ͨ����
    tg_per_chan_inf_t       chan_inf[0]; //ռλ������ռ�ռ�,��������ɸ�tg_per_chan_inf_t�ṹ��,windows�޴˱�ʾ����

}tg_chan_inf_head_ans_t;

typedef struct{

    vd_char                 dev_id[64];

}tg_set_dev_id_ask_t;


typedef struct{

    TG_LOC_RESULT_E         result;

}tg_set_dev_id_ans_t;


typedef struct{

    TG_LOC_RESULT_E         result;
    vd_char                 dev_id[64];

}tg_get_dev_id_ans_t;


typedef struct {

    TG_LOC_RESULT_E     result;   //return result
    vd_s32              enc_level;

}tg_get_enc_level_ans_t;


typedef struct{

    vd_s32              enc_level;

}tg_set_enc_level_ask_t;


typedef struct {

    TG_LOC_RESULT_E     result;   //return result
   
}tg_set_enc_level_ans_t;





typedef struct{

	vd_char                 url_1[32];       //ͬ������IP��ַ
	vd_char                 url_2[32];       //ͬ������IP��ַ
    vd_u16                  port;           //�˿�
	vd_char                 reserv[2];
}tg_cloud_set_gw_ask_t;



typedef struct{

    TG_LOC_RESULT_E             result;   //return result

}tg_cloud_set_gw_ans_t;



typedef struct{

    vd_char                 username[16];
    vd_char                 pwd[128];

}tg_cloud_set_username_ask_t;



typedef struct{

    TG_LOC_RESULT_E             result;   //return result

}tg_cloud_set_username_ans_t;



typedef struct{

    vd_char     region_name[32];
    vd_char     locale_name[32];

}tg_cloud_set_region_ask_t;



typedef struct{

    TG_LOC_RESULT_E         result;   //return result

}tg_cloud_set_region_ans_t;


typedef struct{

    TG_LOC_RESULT_E         result;   //return result
    vd_char                 url_1[32];       //ͬ������IP��ַ
	vd_char                 url_2[32];       //ͬ������IP��ַ
    vd_u16                  port;           //�˿�
	vd_char                 reserv[2];

}tg_cloud_get_gw_ans_t;


typedef struct{

    TG_LOC_RESULT_E         result;   //return result
    vd_char                 username[16];
    
}tg_cloud_get_username_ans_t;

typedef struct{

    TG_LOC_RESULT_E         result;   //return result
    vd_char                 region_name[32];
    vd_char                 locale_name[32];

}tg_cloud_get_region_ans_t;



typedef struct{

    vd_u16                  chn;                        //ͨ����
    vd_u16                  port;                       //�ͻ��˵����ݶ˿ڣ�ĳЩЭ�飬��RTPЭ�飬��VLC��
                                                        //�ǿͻ���peer�Ķ˿ڣ����豸�������������ͻ���
    vd_char                 ip[TG_LOC_IP_MAX_LEN];      //IP��ַ�����͵�ַ��                                       
    TG_STREAM_TYPE_E        stream_type;                //������
    TG_TRANS_TYPE_E         trans_type;                 //��������
    
}tg_get_stream_ask_t;


/**************************************************
 *  
 * �豸�˻�Ӧ�������ݴ���������Ϣ���ͣ�TG_LOC_GET_STREAM_ANS
 * tg_loc_msg_head_t + tg_get_stream_t_ans_t
 *    
 ***************************************************/
typedef struct {

    TG_LOC_RESULT_E             result;   //return result
    vd_u16                      port;     //�豸���ݴ���˿�
    vd_u16                      reserv;   //����
    vd_u32                      random;   //�����,���豸����,
                                          //���ͻ������ӵ����ݶ˿���������ʱ���豸�˽�����֤
}tg_get_stream_t_ans_t;


typedef struct{

    vd_u64  file_id;                    //file id;
    vd_u16  chn;                        //channel number
    vd_u8   file_type;                  //0:tg priv format,1:MP4 file type
    vd_u8   reserv;                     //reserv bits
    vd_s32  start_time;                 //start time of file
    vd_s32  end_time;                   //end time of file
    vd_s32  file_size;                  //file size
	vd_s16  video_type;                //video type
}tg_file_idx_t;


typedef struct{
    vd_u16						chn;            //channel number,-1:all channels ,other:
    vd_u16						video_type;     //¼������0x01����ʱ¼��0x02���ֶ�¼��0x04������¼��
    vd_s32                      start_time;     //start time,-1:all over time files
    vd_s32                      end_time;       //end time


}tg_file_search_ask_t;


typedef struct{

    TG_LOC_RESULT_E             result;         //return result
    vd_s32                      idx_nums;        //file index number 
   
}tg_file_search_ans_t;


typedef struct{

    vd_s32                      start_time; 
	vd_s32                      end_time;      
	vd_u16						chn;            //channel number,-1:all channels ,other:
	vd_u16		                video_type;     //¼������0x01����ʱ¼��0x02���ֶ�¼��0x04������¼��
    vd_s32                      offnum;       
    vd_s32                      total_num;   //�ܹ�������
}tg_file_idx_ask_t;


typedef struct{

    TG_LOC_RESULT_E             result;         //return result
    vd_s32                      offnum;       
    vd_s32                      total_num;      //�ܹ�������
    tg_file_idx_t               idx_arr[0];

}tg_file_idx_ans_t;


typedef struct{

    vd_u64                  file_id;                    
    vd_u8                   reserv[2];
    vd_u16                  port;                       //�ͻ��˵����ݶ˿ڣ�ĳЩЭ�飬��RTPЭ�飬��VLC��
                                                        //�ǿͻ���peer�Ķ˿ڣ����豸�������������ͻ���
    vd_char                 ip[TG_LOC_IP_MAX_LEN];      //IP��ַ�����͵�ַ��     
    TG_TRANS_TYPE_E         trans_type;                 //��������



}tg_file_pb_ask_t;


typedef struct{

    TG_LOC_RESULT_E             result;   //return result
    vd_u16                      port;     //�豸���ݴ���˿�
    vd_u16                      reserv;   //����
    vd_u32                      random;   //�����,���豸����,
                                          //���ͻ������ӵ����ݶ˿���������ʱ���豸�˽�����֤
}tg_file_pb_ans_t;



typedef struct{

	TG_LOC_RESULT_E             result;   //return result
	//vd_char                     ip[32];
	vd_u16                      port;     //�豸���ݴ���˿�
	vd_u16                      reserv;   //����
	vd_u32                      random;   //�����,���豸����, ���ͻ������ӵ����ݶ˿���������ʱ���豸�˽�����֤
}tg_file_download_ans_t;

/**************************************************
 *  
 * ���ݶ˿�Э��
 *      
 *    
 ***************************************************/

typedef enum{

    TG_FILE_STREAM_METHOD               = 0,
    TG_FILE_FRAME_METHOD                = 1,
    TG_FILE_FRAME_REENCODE_METHOD       = 2

}TG_FILE_HANDLE_METH_E;

typedef struct{

    vd_u32                  random;             //�����,tg_ans_stream_t���ص���������豸���ݿڽ�����֤
    vd_u64                  file_id;
    vd_u16                  file_type;          //0:tg priv format,1:MP4 file type
    vd_u16                  video_type;         //¼������0x01����ʱ¼��0x02���ֶ�¼��0x04������¼��
    vd_u16                  chn;                //channel number
    vd_u8                   method;             //TG_FILE_HANDLE_METHOD
    vd_u32                  offset;
}tg_file_start_ask_t;

typedef struct{
	vd_u32                  random;             //�����,tg_ans_stream_t���ص���������豸���ݿڽ�����֤
	vd_u32                  begin_time;         //¼���ļ��طſ�ʼʱ��
	vd_u32                  end_time;           //¼���ļ��طŽ���ʱ��
	vd_u16                  chn;                //channel number
	vd_u8                   method;             //TG_FILE_HANDLE_METHOD
	vd_s32                  offset;
}tg_file_stream_pb_ask_t;

typedef struct{

    TG_LOC_RESULT_E         result;   //return result
	int                     nsec;

}tg_file_start_ans_t;


typedef struct{

    vd_u32                  random;
    vd_u64                  file_id;
    vd_u8                   seek_type;  //0:by time,1:by offset,
    vd_u8                   reserv[3];
    vd_s32                  opt_value;

}tg_file_seek_ask_t;


#define TG_WEEK_DAY                 (7)

#define TG_MAX_CHN                  (16)

#define TG_MAX_TIMESEGMENT          (4)




typedef struct{

  vd_s16                mask;
  vd_u8                 nBeginHour;
  vd_u8                 nBeginMin;
  vd_u8                 nBeginSec;
  vd_u8                 nEndHour;
  vd_u8                 nEndMin;
  vd_u8                 nEndSec;
  
}tg_time_seg_t;





typedef struct{

    vd_s32                  nChannelID;
    tg_time_seg_t           stuTimeSection[TG_WEEK_DAY][TG_MAX_TIMESEGMENT];
    vd_s32                  nPreRecTime;
    vd_s32                  nStreamType;

}tg_chn_rec_cfg_t;


typedef struct{
    TG_LOC_RESULT_E             result;

}tg_set_rec_ans_t;

typedef struct tg_record_plan_s {
    vd_u32   plan_id;
    vd_s16   mask;
    vd_u8    begin_sec;
    vd_u8    begin_min;
    vd_u8    begin_hour;
    vd_u8    end_sec;
    vd_u8    end_min;
    vd_u8    end_hour;
    vd_u8    wday;
    vd_u8    chn_no;
    vd_u8    reserv[2];
}tg_record_plan_t;

typedef struct{
    TG_LOC_RESULT_E     result;
    vd_s32              nplans;
    tg_record_plan_t    rec_plan[0];
}tg_cfg_rec_inf_t;



/**************************************************
 *  
 * �ͻ��������ӵ����ݿں���ʼ���ݴ���������Ϣ���ͣ�TG_LOC_START_STREAM_ASK
 * tg_loc_msg_head_t + tg_start_stream_ask_t
 *    
 ***************************************************/

typedef struct{

    vd_u32                  random;             //�����,tg_ans_stream_t���ص���������豸���ݿڽ�����֤
    vd_u16                  chn;                //ͨ����
    vd_u16                  reserv;             //����
    TG_STREAM_TYPE_E        stream_type;        //������
    TG_TRANS_TYPE_E         trans_type;         //��������

}tg_start_stream_ask_t;


/**************************************************
 *  
 * �ͻ��������ӵ����ݿں���ʼ���ݴ���������Ϣ���ͣ�TG_LOC_START_STREAM_ANS
 * tg_loc_msg_head_t + tg_start_stream_ans_t
 *    
 ***************************************************/

typedef struct{

    TG_LOC_RESULT_E         result;   //return result

}tg_start_stream_ans_t;


 
/**************************************************
 *    ������Ƶ����Э�飬ͬ��˽��Э�飬��Ϣ����:TG_LOC_H264_TRANS
 *    ���豸�����ͻ��� 
 *    device :tg_loc_msg_head_t + tg_video_net_head_t+payload
 *    ���紫����Ƶ��ʽ,Ŀǰ֧��h264,δ��֧��h265,ͨ�����ݿڴ���
 *    tg_loc_msg_head_t + tg_h264_net_head_t +payload
 *    �����TCP����,��payload_lenΪ��֡���ȣ�pck_n��Ϊ0xffff
 *    ����UDP����,��pck_nΪÿ���ĳ��ȣ������Ƭ����Ϊ1440��Ĭ��Ϊ1024��
 *    
 ***************************************************/

typedef struct {

    vd_u64              pts;          //ʱ���
    vd_u32              frame_n;      //֡���к�
    vd_u16              pck_n;        //packet ���кţ���ʼΪ|0x4000 ,ĩβΪ|0x8000,����RTP����Э��
    vd_u16              chn_n;        //ͨ����
    vd_u32              payload_len;  //payload ���� 
    //vd_char             buff[0];      //�������buff,nal������Ҫ�Լ�parse��δ������,��Ҫ�Ļ�����չ,windows�޴˱�ʾ����

}tg_video_net_head_t;


typedef enum 
{ 

    TG_AUDIO_PCM_TYPE                   ,
    TG_AUDIO_ALAW_PCM_TYPE              ,
    TG_AUDIO_ULAW_PCM_TYPE              ,
    TG_AUDIO_ADPCM_TYPE                 ,
    TG_AUDIO_G711_TYPE                  ,
    TG_AUDIO_G726_TYPE                  ,
    TG_AUDIO_AAC_TYPE                   ,
   
    TG_AUDIO_TYPE_BUTT                  ,

} TG_AUDIO_TYPE_E; 

typedef enum 
{ 
    TG_AUDIO_SAMPLE_RATE_8000           = 8000,    /* 8K samplerate*/
    TG_AUDIO_SAMPLE_RATE_12000          = 12000,   /* 12K samplerate*/    
    TG_AUDIO_SAMPLE_RATE_11025          = 11025,   /* 11.025K samplerate*/
    TG_AUDIO_SAMPLE_RATE_16000          = 16000,   /* 16K samplerate*/
    TG_AUDIO_SAMPLE_RATE_22050          = 22050,   /* 22.050K samplerate*/
    TG_AUDIO_SAMPLE_RATE_24000          = 24000,   /* 24K samplerate*/
    TG_AUDIO_SAMPLE_RATE_32000          = 32000,   /* 32K samplerate*/
    TG_AUDIO_SAMPLE_RATE_44100          = 44100,   /* 44.1K samplerate*/
    TG_AUDIO_SAMPLE_RATE_48000          = 48000,   /* 48K samplerate*/

    TG_AUDIO_SAMPLE_RATE_BUTT,
} TG_AUDIO_SAMPLE_RATE_E; 


typedef enum 
{
    TG_AUDIO_SOUND_MODE_MONO            =0,/*mono*/
    TG_AUDIO_SOUND_MODE_STEREO          =1,/*stereo*/
    TG_AUDIO_SOUND_MODE_BUTT    

} TG_AUDIO_SOUND_MODE_E;


typedef enum 
{
    TG_AUDIO_BIT_WIDTH_8                = 0,   /* 8bit width */
    TG_AUDIO_BIT_WIDTH_16               = 1,   /* 16bit width*/
    TG_AUDIO_BIT_WIDTH_32               = 2,   /* 32bit width*/
    TG_AUDIO_BIT_WIDTH_BUTT,

} TG_AUDIO_BIT_WIDTH_E;

typedef enum{

	TG_VIDEO_IS_SMOOTH,
	TG_VIDEO_IS_BALANCE,
	TG_VIDEO_IS_HD,
	TG_VIDEO_IS_SD,
	TG_VIDEO_IS_1080P = 7,

	TG_VIDEO_LEVEL_BUTTON

}VIDEO_PIC_LEVEL_E;
/**************************************************
 *    ������Ƶ����Э�飬ͬ��˽��Э�飬��Ϣ����:TG_LOC_AUDIO_TRANS
 *    ���豸�����ͻ��� 
 *    device :tg_loc_msg_head_t + tg_audio_head_t+payload
 *    
 *    tg_loc_msg_head_t + tg_h264_net_head_t +payload
 *    �����TCP����,��payload_lenΪ��֡���ȣ�pck_n��Ϊ0xffff
 *    ����UDP����,��pck_nΪÿ���ĳ��ȣ������Ƭ����Ϊ1440��Ĭ��Ϊ1024��
 *    
 ***************************************************/

typedef struct {

    TG_AUDIO_TYPE_E                 audio_type;   //��Ƶ���ͣ���Ϊ�ڴ����������Ƶ��ʽ����ͨ�����������޸�
    vd_u64                          pts;          //ʱ���
    vd_u32                          frame_n;      //֡���к�
    vd_u16                          pck_n;        //packet ���кţ���ʼΪ|0x4000 ,ĩβΪ|0x8000,ֻ��һ��,��Ϊ0xffff,����RTP����Э��
    vd_u8                           bits;         //bitλ TG_AUDIO_BIT_WIDTH_E
    vd_u8                           track;        //������ TG_AUDIO_SOUND_MODE_E
    vd_u32                          bps;          //��Ƶ������
    TG_AUDIO_SAMPLE_RATE_E          sample_rate;  //������  
    vd_u32                          payload_len;  //payload ���� ,���ݳ���                                      //
    //vd_char                         buff[0];      //ռλ��,paylaodָ��,�������buff,windows�޴˱�ʾ����     
                                                                                    
}tg_audio_head_t;


typedef struct{

    vd_u64                          file_id;        
    vd_u8                           file_end;      //0:no end , 1:end
    vd_u8                           reserv[3];     //
    vd_u32                          offset;        //file offset
    vd_u32                          payload_len;  //payload ���� ,���ݳ���  
    vd_char                         buff[0];      //ռλ��,paylaodָ��,�������buff,windows�޴˱�ʾ����  

}tg_file_net_trans_t;



typedef struct{

	vd_u32                  random;             //�����,tg_ans_stream_t���ص���������豸���ݿڽ�����֤
	vd_u64                  file_id;
	vd_u16                  file_type;          //0:tg priv format,1:MP4 file type
	vd_u16                  video_type;         //0:tg priv format,1:MP4 file type
	vd_u32                  offset;
}tg_file_download_info_ask_t;

typedef struct{
	TG_LOC_RESULT_E         result;         //  return result
	vd_u32                  file_size;      //  �ļ��ܴ�С
	vd_u8                   file_type;      //  0:tg priv format,1:MP4 file type
}tg_file_download_info_ans_t;



/*typedef struct {

	vd_char             url[256];
	vd_u16              port;
	vd_s8               chn;
	vd_u8               valid;  //0:diable,1:enable
	VD_IPC_DEV_FIND_PROTOCOL_TYPE_E   dev_find_proto_type;
	vd_u32              manu_type; //
	IPC_CAMERA_TYPE_E   ipc_type;  
	vd_char             user_name[IPC_USE_NAME_LEN];
	vd_char             user_passwd[IPC_USE_PASSWD_LEN];
	vd_char             uuid[128];
	vd_char             ip[64];
	vd_s16              need_low_stream;    //0:no ,1 :need
	vd_s8               venc_type;          //0:jpeg,1:mpeg4,2:h264
	vd_s8               audio_type;         //0:G711,1:G726,2:AAC
	vd_u16              width;
	vd_u16              height;
	vd_s32              frate;
	vd_s32              audio_bitrate;      
	vd_s32              audio_sample_rate;         
}__attribute__((__packed__))tg_ipc_single_inf_t;*/

typedef enum{

	REENC_IS_H264,
	REENC_IS_JPEG

}VD_REENC_TYPE;

typedef struct{
	vd_s32          id;
	vd_s32          enable; 
	vd_s32          src_chn;
	vd_s32          src_frate;
	vd_s32          src_width;
	vd_s32          src_height;
	vd_s32          src_bitrate;   

	vd_s32          re_chn;
	vd_s32          re_frate;
	vd_s32          re_width;
	vd_s32          re_height;
	vd_s32          re_bitrate;                

	VD_REENC_TYPE   re_type; 

}vd_each_reenc_status_t;


typedef struct{

	vd_s32                      num;
	vd_each_reenc_status_t      status[0];

}vd_all_reenc_status_t;


typedef struct{

	vd_char ip[16];
	vd_u16  port;
	vd_u16  reserv;
}pa_rf_device_ip_t;

typedef struct{

	TG_LOC_RESULT_E     result;

}pa_set_rf_device_ip_ans_t;



typedef struct{
	vd_u8                  chn;
	vd_u8                  reserv[3];
	vd_char                chn_name[32];
}tg_set_chn_ask_t;

typedef struct{

	TG_LOC_RESULT_E         result;   //return result

}tg_set_chn_ans_t;



typedef struct{
	vd_char                 disk_serial_num;  //�洢�������к�
	vd_char                 disk_is_normal;   //�洢�����Ƿ�����:0,����;1:����
	vd_char                 reserv[2];        //ռλ��     
	vd_u64                  total_capacity;   //������
	vd_u64                  free_capacity;    //ʣ��ռ�

}tg_per_medium_inf_t;

typedef struct{

	vd_char                  have_storage; //0:�����洢����,1:���洢����
	vd_char                  have_medium;  //0:�������洢����,1:���洢����
	vd_char                  medium_type;  //1:�洢����ΪTF��,2:�洢����ΪӲ��,3:�洢����ΪNAS
	vd_char                  medium_nums;  //�洢��������

	tg_per_medium_inf_t      inf[0];

}tg_storage_inf_ans_t;


typedef struct{

	TG_LOC_RESULT_E         result;   //return result

}tg_reboot_sys_ans_t;


typedef struct{

	TG_LOC_RESULT_E         result;   //return result

}tg_clean_sys_cache_ans_t;




typedef struct{

	vd_u8              chn;
	vd_s8              speed;
	vd_s8              reserv[2];
	TG_PTZ_CTL_TYPE_E  opt;
}tg_ptz_ctl_ask_t;

typedef struct{

	TG_LOC_RESULT_E         result;   //return result

}tg_ptz_ctl_ans_t;


typedef struct{
	TG_LOC_RESULT_E         result;   //return result

}tg_del_reenc_ans_t;

typedef struct{
	TG_LOC_RESULT_E         result;   //return result

}tg_set_preset_ans_t;

typedef struct{
	TG_LOC_RESULT_E         result;   //return result

}tg_common_result_t;


//sensor���
typedef enum{
	TG_SENSOR_TYPE_UNKNOWN = 0,//δ֪���ͣ���ʼ����
	TG_SENSOR_TYPE_SMOKE,//�̸�̽�⴫����
	TG_SENSOR_TYPE_GAS,//���崫����
	TG_SENSOR_TYPE_TH,//��ʪ�ȴ�����
	TG_SENSOR_TYPE_WD,//���򴫸���
	TG_SENSOR_TYPE_WS,//���ٴ�����
	TG_SENSOR_TYPE_GRADIENTER,//ˮƽ��
}TG_SENSOR_TYPE_E;

typedef enum {
	TG_IO_LEVEL_LOW,//����
	TG_IO_LEVEL_HIGH,//����
}TG_IO_LEVEL_E;

//io����
typedef enum{
	TG_IO_DIR_IN,//io����
	TG_IO_DIR_OUT,//io���
}TG_IO_DIR_E;


typedef enum{
	TG_IO_ID_IN_1 = 0,
	TG_IO_ID_IN_2,
	TG_IO_ID_IN_3,
	TG_IO_ID_IN_4,

	TG_IO_ID_IN_5,
	TG_IO_ID_IN_6,
	TG_IO_ID_IN_7,
	TG_IO_ID_IN_8,

	TG_IO_ID_IN_9,
	TG_IO_ID_IN_10,
	TG_IO_ID_IN_11,
	TG_IO_ID_IN_12,

	TG_IO_ID_IN_13,
	TG_IO_ID_IN_14,
	TG_IO_ID_IN_15,
	TG_IO_ID_IN_16,

	TG_IO_ID_OUT_1,
	TG_IO_ID_OUT_2,
	TG_IO_ID_OUT_3,
	TG_IO_ID_OUT_4,
}TG_IO_ID;

typedef struct {
	TG_IO_ID            gpio;//�ĸ�IO�ڣ�16 in��4 out
	TG_IO_DIR_E         dir;//����
	TG_IO_LEVEL_E       level;//
}tg_io_cfg;

//������
typedef enum baudrates{
	TG_BAUDRATE_110,
	TG_BAUDRATE_300,
	TG_BAUDRATE_600,
	TG_BAUDRATE_1200,
	TG_BAUDRATE_2400,
	TG_BAUDRATE_4800,
	TG_BAUDRATE_9600,
	TG_BAUDRATE_14400,
	TG_BAUDRATE_19200,
	TG_BAUDRATE_38400,
	TG_BAUDRATE_56000,
	TG_BAUDRATE_57600,
	TG_BAUDRATE_115200,
	TG_BAUDRATE_12800,
	TG_BAUDRATE_25600,
	TG_BAUDRATE_230400,
}TG_BAUDRATE_E;




//����λ
typedef enum databit{
	TG_DATABIT_5,
	TG_DATABIT_6,
	TG_DATABIT_7,
	TG_DATABIT_8,
}TG_DATABIT_E;

//ֹͣλ
typedef enum stopbit{
	TG_STOPBIT_1,
	TG_STOPBIT_1_5,
	TG_STOPBIT_2,
}TG_STOPBIT_E;

//У��λ
typedef enum parities{
	TG_PARITY_NONE,
	TG_PARITY_ODD,
	TG_PARITY_EVEN,
}TG_PARITIE_E;

//����
typedef enum flows{
	TG_FLOW_NONE,
	TG_FLOW_RTS_CTS,
	TG_FLOW_XON_XOFF,
}TG_FLOW_E;

typedef enum{
	TG_SENSOR_INTERFACE_UNKNOWN = 0,//δ֪�ӿ����ͣ���ʼ����
	TG_SENSOR_INTERFACE_IO,//������
	TG_SENSOR_INTERFACE_RS232,//RS232����ͨ��
	TG_SENSOR_INTERFACE_RS485,//RS485ͨ��
	TG_SENSOR_INTERFACE_NET,//���緽ʽͨ��
}TG_SENSOR_INTERFACE_E;

//��������(rs232����rs485)
typedef struct{
	int             addr;//���rs232��ʾ�ĸ����ڣ�rs485���ʾ�豸��ַ
	TG_BAUDRATE_E   baudrate;//������
	TG_DATABIT_E    databit;//���ݿ��
	TG_STOPBIT_E    stopbit;//ֹͣλ
	TG_PARITIE_E    parity;//��żУ��
	TG_FLOW_E       flow;//����
}tg_serial_cfg;    

//��������
typedef struct{
	char    ip[32];//ip
	int     port;//�˿�
}tg_net_cfg;

typedef union{
	tg_io_cfg      io;//�������豸
	tg_serial_cfg  serial;//�����豸
	tg_net_cfg     net;//�����豸
}TG_SENSOR_INTERFACE_CFG_U;


typedef enum{
	TG_SENSOR_DATA_FORMAT_UNKNOWN = 0,//δ֪���ݸ�ʽ��
	TG_SENSOR_DATA_FORMAT_IO,//�ߵ͵�ƽ
	TG_SENSOR_DATA_FORMAT_RS232,//RS232
	TG_SENSOR_DATA_FORMAT_RS485,//RS485
	TG_SENSOR_DATA_FORMAT_MODBUS_RTU,// MODUBUS RTU
	TG_SENSOR_DATA_FORMAT_MODBUS_ASCII,//MODBUS ASCII
	TG_SENSOR_DATA_FORMAT_USER,
}TG_SENSOR_DATA_FORMAT_E;

//���������������ܽṹ��
typedef struct {
	TG_SENSOR_TYPE_E            type;//�豸���ͣ�����������ʪ�ȵ�
	TG_SENSOR_INTERFACE_E       hw_interface;//�豸�������ӷ�ʽ��io��232��485��net
	TG_SENSOR_INTERFACE_CFG_U   interface_cfg;//����ӿڵ�����������
	TG_SENSOR_DATA_FORMAT_E     format;//���ݸ�ʽ���ߵ͵�ƽ����ͨ232����ͨ485��modbus rtu��modbus net���û��Զ���
}tg_sensor_cfg_t;

//���д���������
typedef struct{
	int             num;
	tg_sensor_cfg_t    sensor_cfg[0];
}tg_sensor_cfg;

//����������Ӧ��
typedef struct{

	TG_LOC_RESULT_E         result;   //return result

}tg_sensor_cfg_ans_t;



typedef struct{

	vd_char                         dns1[16];
	vd_char                         dns2[16];

}tg_dns_inf_t;

typedef struct{

	TG_LOC_RESULT_E         result;   //return result

}tg_get_dns_ans_t;


typedef struct{
	vd_char                         mac[20];       
}tg_mac_inf_t;



typedef struct{
	vd_char                         mac[20];   
	vd_char                         ip[16];        //IP��ַ
	vd_char                         gwip[16];      //���ص�ַ
	vd_char                         netmask[16];   //��������   
	vd_char                         dns1[16];
	vd_char                         dns2[16];   
	vd_s32                          alloc_type;   // -1:δ֪;0:��̬IP ;1:DHCP 
	TG_DEV_NET_TYPE                 net_type;     //1:���� 2��wifi    
}tg_net_inf_t;



typedef struct{

	vd_char                 version[64];

}tg_soft_version_t;



typedef struct {
	vd_u64                  file_id;                    
	vd_u8                   reserv[2];
	vd_u16                  port;                   //�ͻ��˵����ݶ˿ڣ�ĳЩЭ�飬��RTPЭ�飬��VLC��                                                //�ǿͻ���peer�Ķ˿ڣ����豸�������������ͻ���
	vd_char                 ip[TG_LOC_IP_MAX_LEN];  //IP��ַ�����͵�ַ��     
}tg_file_download_ask_t;

typedef struct{

	TG_LOC_RESULT_E         result;   //return result

}tg_file_stream_pb_ans_t;


typedef struct{

	vd_char     pa_process_name[64];

}pa_process_inf_t;

typedef struct{

	TG_LOC_RESULT_E     result;

}pa_process_ans_t;

typedef struct{
	TG_LOC_RESULT_E     result;
	int		channel;
	int		gop;
}tg_gop_inf_t;

typedef struct{

	TG_LOC_RESULT_E     result;

} tg_gop_ans_t;

typedef enum{

	TG_CE_REMOTE_CTL_TYPE       = 0,    //ң����
	TG_CE_DOOR_LOCK_TYPE        = 1,    //�Ŵ�
	TG_CE_INFRARED_TYPE         = 2,    //����
	TG_CE_SMOKE_SENSOR_TYPE     = 3,    //�̸�
	TG_CE_QI_SENSOR_TYPE        = 4,    //����
	TG_CE_WHISTLE_TYPE          = 5,    //����
	TG_CE_PULSATOR_TYPE         = 6,    //����

	TG_CE_TYPE_BUTTON           
}TG_CE_TYPE_E;


typedef struct{

	TG_CE_TYPE_E    ce_type; //�����豸����
	HI_S32          enable;  //0:invalid 1:valid

}tg_ce_single_cfg;

typedef struct{

	HI_S32              num; //����
	tg_ce_single_cfg    cs_cfg[0];

}tg_ce_type_total_t;

typedef struct{
	TG_CE_TYPE_E    ce_type;    //�����豸����

}tg_ce_add_device_ask_t;

typedef struct{

	TG_LOC_RESULT_E         result;     //���ؽ��
	TG_CE_TYPE_E            ce_type;    //�����豸����uuid
	HI_U64                  uuid;		//uuid
}tg_ce_add_device_ans_t;

typedef struct{

	TG_CE_TYPE_E            ce_type;        //�����豸����
	HI_U64					uuid;			//UUID
	HI_S32                  alarm_value;    //��������

}tg_ce_alarm_ask_t;

typedef struct{

	TG_CE_TYPE_E            ce_type;        //�����豸����
	HI_U64                  uuid;			//UUID
	HI_CHAR                 device_name[32];
	HI_S8                   preset;         //Ԥ�õ㣬0�������ã���1��ʼ
	HI_S8                   need_alarm;     //��Ҫ����
	HI_S8                   need_audio;     //��Ҫ��������
	HI_S8                   reserv;
}tg_ce_device_inf_t;

typedef struct{

	HI_S32                  num; //����
	tg_ce_device_inf_t      ce_dev[0];

}tg_ce_total_device_t;

typedef struct{

	HI_S8                   preset;    //Ԥ�õ㣬0�������ã���1��ʼ
	HI_S8                   enable;    //0:�������ã�1��������
	HI_S8                   reserv[2];
	HI_CHAR                 preset_name[32];

}tg_preset_inf_t;

typedef struct{

	HI_S32                  num; //����
	tg_preset_inf_t         preset_inf[0];

}tg_preset_total_t;

typedef struct{

	HI_S8                   preset;    //Ԥ�õ㣬0�������ã���1��ʼ
	HI_S8                   preserv[3];    
}tg_goto_preset_ask_t;

typedef struct{

	TG_LOC_RESULT_E         result;     //���ؽ��
	HI_S32                   enable;    //������ʼ���0��������������1����������

}tg_laying_ask_t;

typedef struct{

	TG_LOC_RESULT_E         result;     //���ؽ��

}tg_laying_ans_t;


typedef struct{

	HI_S32                  countin;	//��������
	HI_S32                  countout;	//��ȥ����
}tg_peoplecount_info_t;



typedef struct{

	TG_LOC_RESULT_E         result;   //return result

}tg_clean_heatpic_ans_t;



typedef struct
{
	HI_S32 bMirror; //���Ҿ��� 0:false ,1:true  //  00  �ر�  10  ����  01 ����  11����  
	HI_S32 bFlip; //���·�ת 0:false ,1:true
}tg_vi_flip_t;

#pragma pack(pop)

#endif//_NET_DEVICE_PROTOCOL_H_