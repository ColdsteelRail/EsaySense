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
#define TG_LOC_CTL_PORT                 (10001)     //控制侦听口
                                                    
#define TG_LOC_DATA_PORT                (10002)     //数据侦听口
                                                    
#define TG_NET_SLICE_MAX_LEN            (1024)      //网络切片最大长度

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

    TG_LOC_KEEPLIVE_MSG         = 0x100     ,     //keeplive消息,用于控制通道,每隔TG_KEEPLIVE_INTERVAL 秒发一次，双发都发，采用应答形式，
                                                  //由客户端率先发起，设备端回应，如果超过了TG_KEEPLIVE_MAX_TIMES没有活动包,
                                                  //则认为peer关闭，只需要消息头部，无需消息体

    TG_LOC_FIND_DEV_ASK         = 0x200     ,     //设备发现请求
    TG_LOC_FIND_DEV_ANS                     ,


	TG_MCAST_GET_DEV_INF_ASK                = 0x202     ,     //多播获取设备信息请求
	TG_MCAST_GET_DEV_INF_ANS                = 0x203     ,     //多播获取设备信息回答

	TG_MCAST_SET_DEV_INF_ASK                = 0x204     ,     //多播设置设备信息请求
	TG_MCAST_SET_DEV_INF_ANS                = 0x205     ,     //多播设置设备信息回答


    /*同观本地相关设置*/

    TG_LOC_GET_STREAM_ASK       = 0x1001    ,     //请求传输数据命令 
    TG_LOC_GET_STREAM_ANS       = 0x1002    ,     //开求传输数据命令回答   
                                                                                     //
    TG_LOC_START_STREAM_ASK     = 0x1003    ,     //请求开始传输流命令（数据通道） 
    TG_LOC_START_STREAM_ANS     = 0x1004    ,     //请求开始传输流命令回答(数据通道) 

    TG_LOC_LOGIN_ASK            = 0x1005    ,
    TG_LOC_LOGIN_ANS            = 0x1006    ,

    TG_SET_SYS_TIME_ASK         = 0x1007    ,
    TG_SET_SYS_TIME_ANS         = 0x1008    ,

    TG_DEV_NET_TYPE_ASK         = 0x1009    ,     //设备网络类型询问
    TG_DEV_NET_TYPE_ANS         = 0x100A    ,     //设备网络类型回答

    TG_DEV_NET_SET_ASK          = 0x100B    ,     //设置设备网络请求
    TG_DEV_NET_SET_ANS          = 0x100C    ,     //设置设备网络回答

    TG_DEV_CHAN_INF_ASK         = 0x100D    ,     //获取通道信息请求
    TG_DEV_CHAN_INF_ANS         = 0x100E    ,     //获取通道信息回应

    
    TG_SET_OSD_ASK              = 0x100F    ,     //设置OSD请求
    TG_SET_OSD_ANS              = 0x1010    ,
                                            
    TG_SET_MD_ASK               = 0x1011    ,     //设置MV请求
    TG_SET_MD_ANS               = 0x1012    ,
                                            
    
    TG_DEV_INTERCOM_INF_ASK     = 0x1013    ,     //询问是否可以对讲请求
    TG_DEV_INTERCOM_INF_ANS     = 0x1014    ,     //是否可以对讲回答

    TG_DEV_START_INTERCOM_ASK   = 0x1015    ,     //开启对讲请求
    TG_DEV_START_INTERCOM_ANS   = 0x1016    ,     
    
    TG_SET_DEV_ID_ASK           = 0x1017    ,     //设置设备ID请求
    TG_SET_DEV_ID_ANS           = 0x1018    ,     //设置设备ID回应    


    TG_GET_DEV_ID_ASK           = 0x1019    ,    //读取设备ID请求
    TG_GET_DEV_ID_ANS           = 0x101A    ,    //读取设备ID回应

    TG_LVS_GET_IPC_ASK          = 0x101B    ,    //获取前端IPC的信息请求
    TG_LVS_GET_IPC_ANS          = 0x101C    ,    //获取前端IPC的信息回应

    TG_LVS_SET_IPC_ASK          = 0x101D    ,    //LVS 设置前端IPC的配置请求
    TG_LVS_SET_IPC_ANS          = 0x101E    ,    //LVS 设置前端IPC的回应

    TG_GET_VENC_PARAM_ASK       = 0x101F    ,    //获取视频编码参数请求
    TG_GET_VENC_PARAM_ANS       = 0x1020    ,    //获取视频编码参数请求

    TG_FILE_SEARCH_ASK          = 0x1021    ,    //文件搜索请求
    TG_FILE_SEARCH_ANS          = 0x1022    ,    //文件搜索回答

    TG_START_FILE_STREAM_ASK    = 0x1023    ,    //开始传输文件流请求
    TG_START_FILE_STREAM_ANS    = 0x1024    ,    //开始传输文件流回答

    TG_FILE_PB_ASK              = 0x1025    ,    //文件回放请求
    TG_FILE_PB_ANS              = 0x1026    ,    //文件回放回答
    
    TG_FILE_SEEK_ASK            = 0x1027    ,    //文件seek请求
    TG_FILE_SEEK_ANS            = 0x1028    ,    //文件seek请求

    TG_GET_FILE_INDEX_ASK       = 0x1029    ,    //获取文件索引请求
    TG_GET_FILE_INDEX_ANS       = 0x102A    ,    //获取文件索引回应

    TG_GET_RECORD_PROJ_ASK      = 0x102B    ,    //获取录像计划请求
    TG_GET_RECORD_PROJ_ANS      = 0x102C    ,    //获取录像计划回应

    TG_SET_RECORD_PROJ_ASK      = 0x102D    ,    //设置录像计划请求
    TG_SET_RECORD_PROJ_ANS      = 0x102E    ,    //设置录像计划回应


    TG_SET_ENC_LEVEL_ASK        = 0x1030    ,    //设置编码级别请求
    TG_SET_ENC_LEVEL_ANS        = 0x1031    ,    //设置编码级别回答

    TG_GET_ENC_LEVEL_ASK        = 0x1032    ,    //获取编码级别请求
    TG_GET_ENC_LEVEL_ANS        = 0x1033    ,    //获取编码级别回答

    TG_START_RECORD_ASK         = 0x1034    ,    //开始录像请求
    TG_START_RECORD_ANS         = 0x1035    ,    //开始录像回答

    TG_STOP_RECORD_ASK          = 0x1036    ,    //停止录像请求
    TG_STOP_RECORD_ANS          = 0x1037    ,    //停止录像回答

    TG_MANUAL_SEARCH_DEV_ASK    = 0x1038    ,    //手动搜索设备请求
    TG_MANUAL_SEARCH_DEV_ANS    = 0x1039    ,    //手动搜索设备回答

	TG_GET_REENC_INF_ASK        = 0x103A    ,    //获取重编信息请求
	TG_GET_REENC_INF_ANS        = 0x103B    ,    //获取重编信息回应

	TG_SET_REENC_INF_ASK        = 0x103C    ,    //设置重编信息请求
	TG_SET_REENC_INF_ANS        = 0x103D    ,    //设置重编信息回答

	TG_DEL_REENC_INF_ASK                    = 0x103E    ,    //删除重编信息请求
	TG_DEL_REENC_INF_ANS                    = 0x103F    ,    //删除重编信息请求



	PA_SET_RF_DEVICE_IP_ASK     = 0x1040    ,         //设置RF设备地址请求
	PA_SET_RF_DEVICE_IP_ANS     = 0x1041    ,     //设置RF设备地址回答
	PA_GET_RF_DEVICE_IP_ASK     = 0x1042    ,//获取RF设备IP地址请求
	PA_GET_RF_DEVICE_IP_ANS     = 0x1043     , //获取RF设备IP地址回答



    ////////////////
	TG_FILE_STREAM_PB_BY_TIME_RANGE_ASK     = 0x1044    , //根据时间回放录像文件请求
	TG_FILE_STREAM_PB_BY_TIME_RANGE_ANS     = 0x1045    , //根据时间回放录像文件应答

	TG_GET_SYS_TIME_ASK                     = 0x1100    ,   //获取系统时间
	TG_GET_SYS_TIME_ANS                     = 0x1101    ,   //获取系统时间回答

	TG_GET_STORAGE_ASK                      = 0x1102    ,   //获取存储信息请求
	TG_GET_STORAGE_ANS                      = 0x1103    ,   //获取存储信息请求

	TG_DEL_IPC_ASK                          = 0x1104    ,   //删除前端IPC信息请求
	TG_DEL_IPC_ANS                          = 0x1105    ,   //删除前端IPC信息请求

	TG_GET_CHAN_NAME_ASK                    = 0x1106    ,   //获取通道名称请求
	TG_GET_CHAN_NAME_ANS                    = 0x1107    ,   //获取通道名称请求

	TG_SET_CHAN_NAME_ASK                    = 0x1108    ,   //设置通道名称请求
	TG_SET_CHAN_NAME_ANS                    = 0x1109    ,   //设置通道名称请求



	TG_DEVICE_REBOOT_ASK                    = 0x110A    ,   //系统重启请求
	TG_DEVICE_REBOOT_ANS                    = 0x110B    ,   //系统重启应答

	TG_CLEAN_SYS_CACHE_ASK                  = 0x110C    ,   //清除系统缓存请求
	TG_CLEAN_SYS_CACHE_ANS                  = 0x110D    ,   //清除系统缓存回答

	TG_CLEAN_HEATPIC_ASK                    = 0x110E    ,   //清除热力图请求
	TG_CLEAN_HEATPIC_ANS                    = 0x110F    ,   //清除热力图回答


	TG_PTZ_CTL_ASK                          = 0x1120    ,   //云台命令请求
	TG_PTZ_CTL_ANS                          = 0x1121    ,   //云台命令回答

	TG_GET_DNS_ASK                          = 0x1122    ,   //获取DNS命令请求
	TG_GET_DNS_ANS                          = 0x1123    ,   //获取DNS命令回答

	TG_SET_DNS_ASK                          = 0x1124    ,   //设置DNS命令请求
	TG_SET_DNS_ANS                          = 0x1125    ,   //设置DNS命令回答

	TG_GET_NET_INF_ASK                      = 0x1126    ,   //获取NET命令请求
	TG_GET_NET_INF_ANS                      = 0x1127    ,   //获取NET命令回答


	TG_GET_SOFT_VERSION_ASK                 = 0x1128    ,   //获取软件版本号请求
	TG_SET_SOFT_VERSION_ANS                 = 0x1129    ,   //获取软件版本号回答

	TG_SET_GOP_INF_ASK						= 0x112C    ,   //设置gop请求
	TG_SET_GOP_INF_ANS						= 0x112D    ,   //设置gop回答
	TG_GET_GOP_INF_ASK						= 0x112E    ,   //获取gop请求
	TG_GET_GOP_INF_ANS						= 0x112F    ,   //获取gop回答

	TG_SET_FLIP_ASK                         = 0x1138    ,//设置翻转请求


	//危化品相关定义在此,始于0x1200
	TG_SET_SENSOR_CFG_ASK                       = 0x1201    ,//设置传感器配置请求
	TG_SET_SENSOR_CFG_ANS                       = 0x1202    ,//设置传感器配置应答
	TG_GET_SENSOR_CFG_ASK                       = 0x1203    ,//获取传感器配置请求
	TG_GET_SENSOR_CFG_ANS                       = 0x1204    ,//获取传感器配置应答

	TG_GET_CE_CFG_ASK                           = 0x1400    ,//获取物联设备配置请求
	TG_GET_CE_CFG_ANS                           = 0x1401    ,//获取物联设备配置回答

	TG_ADD_CE_ASK                               = 0x1402    ,//搜索或添加物联设备请求
	TG_ADD_CE_ANS                               = 0x1403    ,//搜索或添加物联设备回答

	TG_GET_CE_DEVICE_ASK                        = 0x1404    ,//获取物联设备信息请求 
	TG_GET_CE_DEVICE_ANS                        = 0x1405    ,//获取物联设备信息回答

	TG_SET_CE_DEVICE_ASK                        = 0x1406    ,//设置物联设备信息请求 
	TG_SET_CE_DEVICE_ANS                        = 0x1407    ,//设置物联设备信息回答 

	TG_DEL_CE_DEVICE_ASK                        = 0x1408    ,//删除物联设备信息请求
	TG_DEL_CE_DEVICE_ANS                        = 0x1409    ,//删除物联设备信息回答

	TG_SET_PRESET_ASK                           = 0x140A    ,//设置预置点请求
	TG_SET_PRESET_ANS                           = 0x140B    ,//设置预置点回答


	TG_GET_PRESET_ASK                           = 0x140C    ,//获取预置点请求
	TG_GET_PRESET_ANS                           = 0x140D    ,//获取预置点回答

	TG_CE_ALARM_ASK                             = 0x140E    ,//物联设备报警上报
	TG_CE_ALARM_ANS                             = 0x140F    ,
	
	TG_GOTO_PRESET_ASK                          = 0x1410    ,//物联设备跳转请求
	TG_GOTO_PRESET_ANS                          = 0x1411    ,//物联设备跳转回答
	
	TG_LAYING_STATUS_ASK                        = 0x1412    ,//一键布防请求
	TG_LAYING_STATUS_ANS                        = 0x1413	,//一键撤防请求
	
	TG_LAYING_GET_STATUS_ASK                    = 0x1414    ,//获取一键布防请求
	TG_LAYING_GET_STATUS_ANS                    = 0x1415    ,//获取一键撤防请求
    /*同观云相关设置*/
    
    TG_CLOUD_SET_GW_ASK         = 0x2001    ,     //设置同观系统网关请求（IP，端口）
    TG_CLOUD_SET_GW_ANS         = 0x2002    ,     //设置同观系统网关回答

    TG_CLOUD_SET_USERNAME_ASK   = 0x2003    ,     //设置同观系统访问用户名请求
    TG_CLOUD_SET_USERMANE_ANS   = 0x2004    ,     //设置同观系统访问用户名回答    
                                                       
    TG_SET_DEV_REGION_ASK       = 0x2005    ,     //设置同观系统region，location名称请求
    TG_SET_DEV_REGION_ANS       = 0x2006    ,                                                 

    TG_CLOUD_GET_GW_ASK         = 0x2007    ,     //获取同观系统网关请求
    TG_CLOUD_GET_GW_ANS         = 0x2008    ,     //获取同观系统网关请求回答

    TG_CLOUD_GET_USERNAME_ASK   = 0x2009    ,     //获取同观系统访问用户名请求
    TG_CLOUD_GET_USERMANE_ANS   = 0x200A    ,     //获取同观系统访问用户名回答   

    TG_GET_DEV_REGION_ASK       = 0x200B    ,     //获取同观系统region，location名称请求
    TG_GET_DEV_REGION_ANS       = 0x200C    ,     //获取同观系统region，location名称回答    


	TG_GET_PROCESS_NAME_ASK                 = 0x200D    ,     //获取工序名称询问
	TG_GET_PROCESS_NAME_ANS                 = 0x200E    ,     //获取工序名称回答

	TG_SET_PROCESS_NAME_ASK                 = 0x200F    ,     //设置工序名称询问
	TG_SET_PROCESS_NAME_ANS                 = 0x2010    ,     //设置工序名称回答



	TG_START_FILE_STREAM_PAUSE_ASK          = 0x1323    ,    //播放暂停请求
	TG_START_FILE_STREAM_PAUSE_ANS          = 0x1324    ,    //播放暂停回答

	TG_START_FILE_STREAM_RESUME_ASK         = 0x1325    ,    //播放暂停恢复请求
	TG_START_FILE_STREAM_RESUME_ANS         = 0x1326    ,    //播放暂停恢复回答  
	TG_START_FILE_STREAM_RELOCATE_ASK       = 0x1327    ,    //播放文件请求
	TG_START_FILE_STREAM_RELOCATE_ANS       = 0x1328    ,    //播放文件回应

	TG_FILE_DOWNLOAD_ASK                    = 0x1329    ,    //文件下载请求
	TG_FILE_DOWNLOAD_ANS                    = 0x1330    ,    //文件下载回答

	TG_FILE_DOWNLOAD_STREAM_ASK             = 0x1331    ,    //传输下载文件流请求
	TG_FILE_DOWNLOAD_STREAM_ANS             = 0x1332    ,    //传输下载文件流回答
                                                             

    /*同观数据传输相关*/

    TG_LOC_H264_TRANS           = 0x3001    ,     //H264数据传输命令（数据通道）
    TG_LOC_AUDIO_TRANS          = 0x3002    ,     //音频数据传输命令（数据通道）
    TG_LOC_FILE_TRANS           = 0x3003    ,     //文件流传输方式命令

	/*同观数据显示*/
	TG_PEOPLECOUNT_SHOW_ASK					= 0x6001    ,     //人数统计数据显示

	TG_GET_CURRENT_UPGRADE_MODE_ASK  		= 0x7000	,	//获取当前升级方式请求
	TG_GET_CURRENT_UPGRADE_MODE_ANS 		= 0x7001	,	//获取当前升级方式回答

	TG_SET_CURRENT_UPGRADE_MODE_ASK 		= 0x7002	,	//设置当前升级方式请求
	TG_SET_CURRENT_UPGRADE_MODE_ANS 		= 0x7003	,	//设置当前升级方式回答

	TG_SET_CURRENT_UPGRADE_IPADDR_PORT_ASK	= 0x7004	,	//设置当前升级IP和端口请求
	TG_SET_CURRENT_UPGRADE_IPADDR_PORT_ANS	= 0x7005	,	//设置当前升级IP和端口回答

}TG_LOC_MSG_TYPE_E;



/**************************************************
 *  
 * 流媒体类型，或的关系,如主码流+音频 = TG_H264_MAIN_STREAM|TG_AUDIO_STREAM
 *      
 *    
 ***************************************************/

typedef enum{

    TG_H264_MAIN_STREAM  = 0x01,   //只有H264主码流
    TG_H264_SUB_STREAM   = 0x02,   //只有H264子码流
    TG_AUDIO_STREAM      = 0x04,   //只有音频流
    TG_H265_MAIN_STREAM  = 0x08,   //有H265主码流
    TG_H265_SUB_STREAM   = 0x10,   //有H265子码流
    TG_VIDEO_LOW_STREAM  = 0x20,   //视频压缩低码流标志
    TG_VIDEO_ORIG_STREAM = 0x40,   //视频压缩原始码流（无处理）

}TG_STREAM_TYPE_E;

typedef enum{ 

    TG_RC_CBR = 0,
    TG_RC_VBR,
    TG_RC_FIXQP

}TG_V_RC_TYPE_E;



typedef enum{

    TG_TRANS_TCP                ,               //传输采用TCP
    TG_TRANS_UDP                ,               //传输采用UDP
    TG_TRANS_RTP                ,               //rtp方式传输
    TG_TRANS_FTP_PASSIVE        ,               //ftp被动方式传输
    TG_TRANS_FTP_INITIATIVE     ,               //ftp主动方式传输
    
}TG_TRANS_TYPE_E;


typedef enum{

	TG_NET_ETHER        = 0x01,  //有线网络
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
    vd_s32              version;   //版本号，便于升级
    vd_u32              msg_len;   //msg length,没有接着有数据结构为 0，不包含本身

}tg_loc_msg_head_t;


/**************************************************
 *  
 * 设备发现协议
 *      
 *    
 ***************************************************/

typedef enum{

    TG_DEV_IPC               ,       //嵌入式IPC设备
    TG_DEV_4G                ,       //4G设备
    TG_DEV_EMBEDDED_LVS      ,       //嵌入式LVS设备
    TG_DEV_PC_LVS            ,       //pc LVS设备

}TG_DEV_TYPE_E;

typedef enum{

    TG_FIND_ALL_DEV_TYPE            ,       //查询所有的设备
    TG_FIND_SPEC_DEV_ID_TYPE        ,       //通过设备ID查询指定的设备
    TG_FIND_SPEC_DEV_NAME_TYPE      ,       //通过设备名称查询指定的设备(TBD)
    TG_FIND_SPEC_DEV_TYPE           ,       //通过设备类型查找

}TG_FIND_DEV_TYPE_E;

typedef enum{
	DEVICE_TILT_UP             =21     ,               /* 云台以SS的速度上仰 */
	DEVICE_TILT_DOWN		            ,  	            /* 云台以SS的速度下俯 */
	DEVICE_PAN_LEFT		            ,	            /* 云台以SS的速度左转 */
	DEVICE_PAN_RIGHT		            ,	            /* 云台以SS的速度右转 */
	DEVICE_UP_LEFT			            ,	            /* 云台以SS的速度上仰和左转 */
	DEVICE_UP_RIGHT		            ,	            /* 云台以SS的速度上仰和右转 */
	DEVICE_DOWN_LEFT		            ,	            /* 云台以SS的速度下俯和左转 */
	DEVICE_DOWN_RIGHT		            ,	            /* 云台以SS的速度下俯和右转 */
	DEVICE_PAN_AUTO		            ,	            /* 云台以SS的速度左右自动扫描 */
	DEVICE_PAN_CIRCLE                  ,               /* 云台以SS的速度自动圆周扫描 */

	DEVICE_ZOOM_IN_P                   ,               /* 焦距以速度SS变大(倍率变大) */
	DEVICE_ZOOM_OUT_P                  ,               /* 焦距以速度SS变小(倍率变小) */
	DEVICE_FOCUS_NEAR                  ,               /* 焦点以速度SS前调 */
	DEVICE_FOCUS_FAR                   ,               /* 焦点以速度SS后调 */
	DEVICE_IRIS_OPEN                   ,               /* 光圈以速度SS扩大 */
	DEVICE_IRIS_CLOSE                  ,               /* 光圈以速度SS缩小 */
	DEVICE_PTZ_MOVE_STOP       

}TG_PTZ_CTL_TYPE_E;

typedef struct{

    TG_FIND_DEV_TYPE_E  find_type; 
    TG_DEV_TYPE_E       dev_type;  							//如果方式为TG_FIND_SPEC_DEV_TYPE，需要填写此字段，否则此字段忽略
    vd_u64              device_id;							//如果方式为TG_FIND_SPEC_DEV_ID_TYPE，需要填写此字段，否则此字段忽略
    vd_char             device_name[TG_DEVICE_NAME_LEN];    //如果方式为TG_FIND_SPEC_DEV_NAME_TYPE ，需要填写此字段，否则此字段忽略

}tg_loc_dev_find_req_t;



typedef struct{

    TG_LOC_RESULT_E     result;                         	//return result
    TG_DEV_TYPE_E       dev_type; 							//返回设备类型
    vd_u64              device_id;							//返回设备ID
    vd_char             device_name[TG_DEVICE_NAME_LEN];    //返回设备名称
    vd_char             ip[TG_LOC_IP_MAX_LEN];          	//设备IP地址
    vd_u16              port;                           	//控制端口
    vd_u16              reserv;                         	//留着扩展，注明设备类型,
															//也可根据device_id规范字段parse是哪种类型
}tg_loc_dev_find_reply_t;


typedef enum{

	/*普通用户可调整的*/
	TG_MOD_IP_TYPE                  = 0x1           ,
	TG_MOD_DNS_TYPE                 = 0x2           ,
	TG_MOD_NET_ALLOC_TYPE           = 0x4           ,


	/*开发模式下可调整的，用于公司内部产品等做调整*/

	TG_MOD_CLOUD_GW_ADDR_TYPE       = 0x100         ,
	TG_MOD_CLOUD_USENAME_TYPE       = 0x200         ,
	TG_MOD_CLOUD_REGION_TYPE        = 0x400         ,
	TG_MOD_DEV_SN_TYPE              = 0x800         ,


	/*平安项目*/
	TG_MOD_PA_RF_ADDR_TYPE            = 0x10000     ,   



}TG_DEV_INF_MASK_E;



typedef struct{


	TG_DEV_INF_MASK_E               mask;                   //掩码,修改了某一项

	TG_DEV_TYPE_E                   dev_type;               //设备类型

	vd_char                         ip[16];                 //IP地址
	vd_char                         gwip[16];               //网关地址
	vd_char                         netmask[16];            //子网掩码   
	vd_char                         dns1[16];
	vd_char                         dns2[16];   
	vd_s32                          alloc_type;             // -1:未知;0:静态IP ;1:DHCP 
	TG_DEV_NET_TYPE                 net_type;               //1:有线 2：wifi

	vd_char                         cloud_gwurl_1[32];      //同观网关url1地址
	vd_char                         cloud_gwurl_2[32];      //同观网关url1地址
	vd_s32                          cloud_gwport;           //同观网关端口
	vd_char                         cloud_username[16];     //云端用户名
	vd_char                         cloud_pwd[128];         //云端用户密码
	vd_char                         cloud_region_name[32];  //云端region名，平安项目需要
	vd_char                         cloud_locale_name[32];  //云端locale名称

	vd_char                         rfdev_ip[16];           //rf 设备ID
	vd_s32                          rfdev_port;             //rf设备端口


	vd_char                         dev_sn[64];             //设备SN
	vd_u64                          device_id ;             //设备ID，mac地址转的          

	vd_char                         mac[20];   
	vd_char                         version[64];            //软件版本



}tg_mcast_dev_inf_t;


typedef struct{

	TG_LOC_RESULT_E         result;                 //返回结果，如果返回不正确，可以通过mask查看时哪项设置不正确
	TG_DEV_INF_MASK_E       mask;                   //掩码,出错项
	vd_u64                  device_id ;             //用于比较设备ID

}tg_mcast_dev_inf_set_ans_t;




/**************************************************
 *  
 * 控制端口协议
 *      
 *    
 ***************************************************/




/**************************************************
 *  
 * 客户端在连接到控制口后发起请求数据传输请求，消息类型：TG_LOC_GET_STREAM_ASK
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

    TG_SYS_ADMIN        = 1 ,      //系统管理者权限，供内部调试使用
    TG_USER_ADMIN           ,      //用户级管理员账号
    TG_COMMON_USER          ,      //普通用户级

    TG_USER_TYPE_BUTT       

}TG_USER_TYPE_E;

typedef struct{

    TG_USER_TYPE_E      user_type;
    TG_LOGIN_TYPE_E     login_type;
    vd_u64              device_id;		//通过dev_id方式登录
    vd_char             name[64];       //为了兼容各种登陆类型，字符串定长一些
    vd_char             passwd[32];     //最好是MD5
	

}tg_login_ask_t;


typedef struct{

    TG_LOC_RESULT_E     result;     
    TG_DEV_TYPE_E       dev_type;           //设备类型
    vd_u32              dev_auth;           //用户设备权限
    vd_u64              device_id;

}tg_login_ans_t;

typedef struct{

	vd_u16	            year;	// 年
	vd_u8	            mon;	// 月
	vd_u8	            day;	// 日
	vd_u8	            hour;	// 小时
	vd_u8	            min;	// 分钟
	vd_u8               sec;    // 秒
	vd_u8               weekday;// 星期，星期天为0

}tg_time_ask_t;

typedef enum{

	TG_OSD_TYPE_TIME = 0,		//显示时间
	TG_OSD_TYPE_STR,			//显示字符
	TG_OSD_TYPE_LOG				//显示位图LOG
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

    TG_DEV_NET_TYPE     support_net_type;  //或的关系，可能有几种复合类型

}tg_net_inf_ans_t;



typedef struct{

    vd_char     ip[16];        //IP地址
    vd_char     gwip[16];      //网关地址
    vd_char     netmask[16];   //子网掩码

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
 * 此结构可能无回答信息,因为网络可能断掉,但是尽量回答
 * 
 *    
 ***************************************************/

typedef struct{

    TG_NET_ALLOC_STATUS_E   set_type        ;   //设置类型
    vd_s8                   enable          ;   //使能标志，0:diable,1:enable
    vd_s8                   reserv[3]       ;
    TG_NET_DEV_SET_U        net_dev_set_u   ;

}tg_net_dev_set_ask_t;


/**************************************************
 *  
 * 回答信息可能包括: 
 * 1.无回答（为网络可能断掉）； 
 * 2：有回答(如多网络，wifi+4G),开启或关闭4G。 
 * 3.回复信息可能告诉客户端设备在重启中
 * 
 *    
 ***************************************************/

typedef struct{

    TG_LOC_RESULT_E         result;       //return result

}tg_net_dev_set_ans_t;




typedef struct{

    vd_u8                   chn;            //通道号（从0开始）
    vd_s8                   enable;         // 使能标志,0:disable ，1:enable  
    vd_u8                   framerate;      //帧率
    vd_s8                   reserv;
    TG_STREAM_TYPE_E        stream_type;    //不是或的关系，只有一种类型
    vd_u16                  width;          //图像宽度
    vd_u16                  height;         //图像高度
    vd_s32                  bitrate;        //比特率
    TG_V_RC_TYPE_E          rc_type;        //rc类型

}tg_v_chan_inf_t;


/**************************************************
 *  
 * 每个通道的简单信息
 * 
 *    
 ***************************************************/

typedef struct{

    vd_u8                   chn;            //通道号（从0开始）
    vd_s8                   reserv[3];   //
    TG_STREAM_TYPE_E        stream_type;    //或的关系
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
 * 通道信息头部结构体，后带若干个tg_per_chan_inf_t结构体，为变长结构
 * 
 *    
 ***************************************************/

typedef struct{
    TG_LOC_RESULT_E         result;       //return result
    vd_s32                  chan_num;    //总通道数
    tg_per_chan_inf_t       chan_inf[0]; //占位符，不占空间,后面接若干个tg_per_chan_inf_t结构体,windows无此表示方法

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

	vd_char                 url_1[32];       //同观网关IP地址
	vd_char                 url_2[32];       //同观网关IP地址
    vd_u16                  port;           //端口
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
    vd_char                 url_1[32];       //同观网关IP地址
	vd_char                 url_2[32];       //同观网关IP地址
    vd_u16                  port;           //端口
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

    vd_u16                  chn;                        //通道号
    vd_u16                  port;                       //客户端的数据端口，某些协议，如RTP协议，如VLC，
                                                        //是客户端peer的端口，从设备端推送码流到客户端
    vd_char                 ip[TG_LOC_IP_MAX_LEN];      //IP地址（推送地址）                                       
    TG_STREAM_TYPE_E        stream_type;                //流类型
    TG_TRANS_TYPE_E         trans_type;                 //传输类型
    
}tg_get_stream_ask_t;


/**************************************************
 *  
 * 设备端回应请求数据传输请求，消息类型：TG_LOC_GET_STREAM_ANS
 * tg_loc_msg_head_t + tg_get_stream_t_ans_t
 *    
 ***************************************************/
typedef struct {

    TG_LOC_RESULT_E             result;   //return result
    vd_u16                      port;     //设备数据传输端口
    vd_u16                      reserv;   //保留
    vd_u32                      random;   //随机数,由设备生成,
                                          //待客户端连接到数据端口请求数据时，设备端进行验证
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
    vd_u16						video_type;     //录像类型0x01：定时录像，0x02：手动录像，0x04：报警录像
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
	vd_u16		                video_type;     //录像类型0x01：定时录像，0x02：手动录像，0x04：报警录像
    vd_s32                      offnum;       
    vd_s32                      total_num;   //总共的条数
}tg_file_idx_ask_t;


typedef struct{

    TG_LOC_RESULT_E             result;         //return result
    vd_s32                      offnum;       
    vd_s32                      total_num;      //总共的条数
    tg_file_idx_t               idx_arr[0];

}tg_file_idx_ans_t;


typedef struct{

    vd_u64                  file_id;                    
    vd_u8                   reserv[2];
    vd_u16                  port;                       //客户端的数据端口，某些协议，如RTP协议，如VLC，
                                                        //是客户端peer的端口，从设备端推送码流到客户端
    vd_char                 ip[TG_LOC_IP_MAX_LEN];      //IP地址（推送地址）     
    TG_TRANS_TYPE_E         trans_type;                 //传输类型



}tg_file_pb_ask_t;


typedef struct{

    TG_LOC_RESULT_E             result;   //return result
    vd_u16                      port;     //设备数据传输端口
    vd_u16                      reserv;   //保留
    vd_u32                      random;   //随机数,由设备生成,
                                          //待客户端连接到数据端口请求数据时，设备端进行验证
}tg_file_pb_ans_t;



typedef struct{

	TG_LOC_RESULT_E             result;   //return result
	//vd_char                     ip[32];
	vd_u16                      port;     //设备数据传输端口
	vd_u16                      reserv;   //保留
	vd_u32                      random;   //随机数,由设备生成, 待客户端连接到数据端口请求数据时，设备端进行验证
}tg_file_download_ans_t;

/**************************************************
 *  
 * 数据端口协议
 *      
 *    
 ***************************************************/

typedef enum{

    TG_FILE_STREAM_METHOD               = 0,
    TG_FILE_FRAME_METHOD                = 1,
    TG_FILE_FRAME_REENCODE_METHOD       = 2

}TG_FILE_HANDLE_METH_E;

typedef struct{

    vd_u32                  random;             //随机数,tg_ans_stream_t返回的随机数，设备数据口进行验证
    vd_u64                  file_id;
    vd_u16                  file_type;          //0:tg priv format,1:MP4 file type
    vd_u16                  video_type;         //录像类型0x01：定时录像，0x02：手动录像，0x04：报警录像
    vd_u16                  chn;                //channel number
    vd_u8                   method;             //TG_FILE_HANDLE_METHOD
    vd_u32                  offset;
}tg_file_start_ask_t;

typedef struct{
	vd_u32                  random;             //随机数,tg_ans_stream_t返回的随机数，设备数据口进行验证
	vd_u32                  begin_time;         //录像文件回放开始时间
	vd_u32                  end_time;           //录像文件回放结束时间
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
 * 客户端在连接到数据口后发起开始数据传输请求，消息类型：TG_LOC_START_STREAM_ASK
 * tg_loc_msg_head_t + tg_start_stream_ask_t
 *    
 ***************************************************/

typedef struct{

    vd_u32                  random;             //随机数,tg_ans_stream_t返回的随机数，设备数据口进行验证
    vd_u16                  chn;                //通道号
    vd_u16                  reserv;             //保留
    TG_STREAM_TYPE_E        stream_type;        //流类型
    TG_TRANS_TYPE_E         trans_type;         //传输类型

}tg_start_stream_ask_t;


/**************************************************
 *  
 * 客户端在连接到数据口后发起开始数据传输请求，消息类型：TG_LOC_START_STREAM_ANS
 * tg_loc_msg_head_t + tg_start_stream_ans_t
 *    
 ***************************************************/

typedef struct{

    TG_LOC_RESULT_E         result;   //return result

}tg_start_stream_ans_t;


 
/**************************************************
 *    网络视频传输协议，同观私有协议，消息类型:TG_LOC_H264_TRANS
 *    由设备发给客户端 
 *    device :tg_loc_msg_head_t + tg_video_net_head_t+payload
 *    网络传输视频格式,目前支持h264,未来支持h265,通过数据口传输
 *    tg_loc_msg_head_t + tg_h264_net_head_t +payload
 *    如果是TCP传输,则payload_len为整帧长度，pck_n填为0xffff
 *    果是UDP传输,则pck_n为每包的长度，最大切片长度为1440，默认为1024。
 *    
 ***************************************************/

typedef struct {

    vd_u64              pts;          //时间戳
    vd_u32              frame_n;      //帧序列号
    vd_u16              pck_n;        //packet 序列号，开始为|0x4000 ,末尾为|0x8000,仿照RTP传输协议
    vd_u16              chn_n;        //通道号
    vd_u32              payload_len;  //payload 长度 
    //vd_char             buff[0];      //后面接着buff,nal类型需要自己parse，未加类型,需要的话再扩展,windows无此表示方法

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
 *    网络音频传输协议，同观私有协议，消息类型:TG_LOC_AUDIO_TRANS
 *    由设备发给客户端 
 *    device :tg_loc_msg_head_t + tg_audio_head_t+payload
 *    
 *    tg_loc_msg_head_t + tg_h264_net_head_t +payload
 *    如果是TCP传输,则payload_len为整帧长度，pck_n填为0xffff
 *    果是UDP传输,则pck_n为每包的长度，最大切片长度为1440，默认为1024。
 *    
 ***************************************************/

typedef struct {

    TG_AUDIO_TYPE_E                 audio_type;   //音频类型，因为在传输过程中音频格式可能通过参数设置修改
    vd_u64                          pts;          //时间戳
    vd_u32                          frame_n;      //帧序列号
    vd_u16                          pck_n;        //packet 序列号，开始为|0x4000 ,末尾为|0x8000,只有一个,则为0xffff,仿照RTP传输协议
    vd_u8                           bits;         //bit位 TG_AUDIO_BIT_WIDTH_E
    vd_u8                           track;        //声道数 TG_AUDIO_SOUND_MODE_E
    vd_u32                          bps;          //音频比特率
    TG_AUDIO_SAMPLE_RATE_E          sample_rate;  //采样率  
    vd_u32                          payload_len;  //payload 长度 ,数据长度                                      //
    //vd_char                         buff[0];      //占位符,paylaod指针,后面接着buff,windows无此表示方法     
                                                                                    
}tg_audio_head_t;


typedef struct{

    vd_u64                          file_id;        
    vd_u8                           file_end;      //0:no end , 1:end
    vd_u8                           reserv[3];     //
    vd_u32                          offset;        //file offset
    vd_u32                          payload_len;  //payload 长度 ,数据长度  
    vd_char                         buff[0];      //占位符,paylaod指针,后面接着buff,windows无此表示方法  

}tg_file_net_trans_t;



typedef struct{

	vd_u32                  random;             //随机数,tg_ans_stream_t返回的随机数，设备数据口进行验证
	vd_u64                  file_id;
	vd_u16                  file_type;          //0:tg priv format,1:MP4 file type
	vd_u16                  video_type;         //0:tg priv format,1:MP4 file type
	vd_u32                  offset;
}tg_file_download_info_ask_t;

typedef struct{
	TG_LOC_RESULT_E         result;         //  return result
	vd_u32                  file_size;      //  文件总大小
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
	vd_char                 disk_serial_num;  //存储介质序列号
	vd_char                 disk_is_normal;   //存储介质是否良好:0,良好;1:坏了
	vd_char                 reserv[2];        //占位符     
	vd_u64                  total_capacity;   //总容量
	vd_u64                  free_capacity;    //剩余空间

}tg_per_medium_inf_t;

typedef struct{

	vd_char                  have_storage; //0:不带存储功能,1:带存储功能
	vd_char                  have_medium;  //0:不带带存储介质,1:带存储介质
	vd_char                  medium_type;  //1:存储介质为TF卡,2:存储介质为硬盘,3:存储介质为NAS
	vd_char                  medium_nums;  //存储介质数量

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


//sensor相关
typedef enum{
	TG_SENSOR_TYPE_UNKNOWN = 0,//未知类型，初始化用
	TG_SENSOR_TYPE_SMOKE,//烟感探测传感器
	TG_SENSOR_TYPE_GAS,//气体传感器
	TG_SENSOR_TYPE_TH,//温湿度传感器
	TG_SENSOR_TYPE_WD,//风向传感器
	TG_SENSOR_TYPE_WS,//风速传感器
	TG_SENSOR_TYPE_GRADIENTER,//水平仪
}TG_SENSOR_TYPE_E;

typedef enum {
	TG_IO_LEVEL_LOW,//常闭
	TG_IO_LEVEL_HIGH,//常开
}TG_IO_LEVEL_E;

//io方向
typedef enum{
	TG_IO_DIR_IN,//io输入
	TG_IO_DIR_OUT,//io输出
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
	TG_IO_ID            gpio;//哪个IO口，16 in，4 out
	TG_IO_DIR_E         dir;//方向
	TG_IO_LEVEL_E       level;//
}tg_io_cfg;

//波特率
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




//数据位
typedef enum databit{
	TG_DATABIT_5,
	TG_DATABIT_6,
	TG_DATABIT_7,
	TG_DATABIT_8,
}TG_DATABIT_E;

//停止位
typedef enum stopbit{
	TG_STOPBIT_1,
	TG_STOPBIT_1_5,
	TG_STOPBIT_2,
}TG_STOPBIT_E;

//校验位
typedef enum parities{
	TG_PARITY_NONE,
	TG_PARITY_ODD,
	TG_PARITY_EVEN,
}TG_PARITIE_E;

//流控
typedef enum flows{
	TG_FLOW_NONE,
	TG_FLOW_RTS_CTS,
	TG_FLOW_XON_XOFF,
}TG_FLOW_E;

typedef enum{
	TG_SENSOR_INTERFACE_UNKNOWN = 0,//未知接口类型，初始化用
	TG_SENSOR_INTERFACE_IO,//开关量
	TG_SENSOR_INTERFACE_RS232,//RS232串口通信
	TG_SENSOR_INTERFACE_RS485,//RS485通信
	TG_SENSOR_INTERFACE_NET,//网络方式通信
}TG_SENSOR_INTERFACE_E;

//串口配置(rs232或者rs485)
typedef struct{
	int             addr;//针对rs232表示哪个串口；rs485则表示设备地址
	TG_BAUDRATE_E   baudrate;//波特率
	TG_DATABIT_E    databit;//数据宽度
	TG_STOPBIT_E    stopbit;//停止位
	TG_PARITIE_E    parity;//奇偶校验
	TG_FLOW_E       flow;//流控
}tg_serial_cfg;    

//网络配置
typedef struct{
	char    ip[32];//ip
	int     port;//端口
}tg_net_cfg;

typedef union{
	tg_io_cfg      io;//开关量设备
	tg_serial_cfg  serial;//串口设备
	tg_net_cfg     net;//网络设备
}TG_SENSOR_INTERFACE_CFG_U;


typedef enum{
	TG_SENSOR_DATA_FORMAT_UNKNOWN = 0,//未知数据格式，
	TG_SENSOR_DATA_FORMAT_IO,//高低电平
	TG_SENSOR_DATA_FORMAT_RS232,//RS232
	TG_SENSOR_DATA_FORMAT_RS485,//RS485
	TG_SENSOR_DATA_FORMAT_MODBUS_RTU,// MODUBUS RTU
	TG_SENSOR_DATA_FORMAT_MODBUS_ASCII,//MODBUS ASCII
	TG_SENSOR_DATA_FORMAT_USER,
}TG_SENSOR_DATA_FORMAT_E;

//单个传感器配置总结构体
typedef struct {
	TG_SENSOR_TYPE_E            type;//设备类型：开关量、温湿度等
	TG_SENSOR_INTERFACE_E       hw_interface;//设备物理连接方式：io、232、485、net
	TG_SENSOR_INTERFACE_CFG_U   interface_cfg;//物理接口电气特性配置
	TG_SENSOR_DATA_FORMAT_E     format;//数据格式：高低电平、普通232、普通485、modbus rtu、modbus net、用户自定义
}tg_sensor_cfg_t;

//所有传感器配置
typedef struct{
	int             num;
	tg_sensor_cfg_t    sensor_cfg[0];
}tg_sensor_cfg;

//传感器配置应答
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
	vd_char                         ip[16];        //IP地址
	vd_char                         gwip[16];      //网关地址
	vd_char                         netmask[16];   //子网掩码   
	vd_char                         dns1[16];
	vd_char                         dns2[16];   
	vd_s32                          alloc_type;   // -1:未知;0:静态IP ;1:DHCP 
	TG_DEV_NET_TYPE                 net_type;     //1:有线 2：wifi    
}tg_net_inf_t;



typedef struct{

	vd_char                 version[64];

}tg_soft_version_t;



typedef struct {
	vd_u64                  file_id;                    
	vd_u8                   reserv[2];
	vd_u16                  port;                   //客户端的数据端口，某些协议，如RTP协议，如VLC，                                                //是客户端peer的端口，从设备端推送码流到客户端
	vd_char                 ip[TG_LOC_IP_MAX_LEN];  //IP地址（推送地址）     
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

	TG_CE_REMOTE_CTL_TYPE       = 0,    //遥控器
	TG_CE_DOOR_LOCK_TYPE        = 1,    //门磁
	TG_CE_INFRARED_TYPE         = 2,    //红外
	TG_CE_SMOKE_SENSOR_TYPE     = 3,    //烟感
	TG_CE_QI_SENSOR_TYPE        = 4,    //气感
	TG_CE_WHISTLE_TYPE          = 5,    //警笛
	TG_CE_PULSATOR_TYPE         = 6,    //震动器

	TG_CE_TYPE_BUTTON           
}TG_CE_TYPE_E;


typedef struct{

	TG_CE_TYPE_E    ce_type; //物联设备类型
	HI_S32          enable;  //0:invalid 1:valid

}tg_ce_single_cfg;

typedef struct{

	HI_S32              num; //总数
	tg_ce_single_cfg    cs_cfg[0];

}tg_ce_type_total_t;

typedef struct{
	TG_CE_TYPE_E    ce_type;    //物联设备类型

}tg_ce_add_device_ask_t;

typedef struct{

	TG_LOC_RESULT_E         result;     //返回结果
	TG_CE_TYPE_E            ce_type;    //物联设备类型uuid
	HI_U64                  uuid;		//uuid
}tg_ce_add_device_ans_t;

typedef struct{

	TG_CE_TYPE_E            ce_type;        //物联设备类型
	HI_U64					uuid;			//UUID
	HI_S32                  alarm_value;    //报警类型

}tg_ce_alarm_ask_t;

typedef struct{

	TG_CE_TYPE_E            ce_type;        //物联设备类型
	HI_U64                  uuid;			//UUID
	HI_CHAR                 device_name[32];
	HI_S8                   preset;         //预置点，0不起作用，从1开始
	HI_S8                   need_alarm;     //需要报警
	HI_S8                   need_audio;     //需要声音报警
	HI_S8                   reserv;
}tg_ce_device_inf_t;

typedef struct{

	HI_S32                  num; //总数
	tg_ce_device_inf_t      ce_dev[0];

}tg_ce_total_device_t;

typedef struct{

	HI_S8                   preset;    //预置点，0不起作用，从1开始
	HI_S8                   enable;    //0:不起作用，1：起作用
	HI_S8                   reserv[2];
	HI_CHAR                 preset_name[32];

}tg_preset_inf_t;

typedef struct{

	HI_S32                  num; //总数
	tg_preset_inf_t         preset_inf[0];

}tg_preset_total_t;

typedef struct{

	HI_S8                   preset;    //预置点，0不起作用，从1开始
	HI_S8                   preserv[3];    
}tg_goto_preset_ask_t;

typedef struct{

	TG_LOC_RESULT_E         result;     //返回结果
	HI_S32                   enable;    //布防开始与否，0：不开启布防，1：开启布防

}tg_laying_ask_t;

typedef struct{

	TG_LOC_RESULT_E         result;     //返回结果

}tg_laying_ans_t;


typedef struct{

	HI_S32                  countin;	//进入人数
	HI_S32                  countout;	//出去人数
}tg_peoplecount_info_t;



typedef struct{

	TG_LOC_RESULT_E         result;   //return result

}tg_clean_heatpic_ans_t;



typedef struct
{
	HI_S32 bMirror; //左右镜像 0:false ,1:true  //  00  关闭  10  左右  01 上下  11中心  
	HI_S32 bFlip; //上下翻转 0:false ,1:true
}tg_vi_flip_t;

#pragma pack(pop)

#endif//_NET_DEVICE_PROTOCOL_H_