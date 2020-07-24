#pragma once
// struct PEERINFO
// {
// 	UINT64 unCookie;
// 	UINT64 unPeerAddr;
// 	DWORD nMTU;
// 	DWORD dwPKGType;
// 	DWORD dwMDTFormat;
// 	DWORD nTransferType;
// 
// };

using namespace std;

#ifdef WIN32
#ifdef _I_TRANSFER_API
#define I_TRANSFER_API_MODE __declspec(dllexport)
#else
#define I_TRANSFER_API_MODE __declspec(dllimport)
#endif

#ifndef _I_TRANSFER_API
#pragma comment(lib,"transter.lib")
#endif
#else
#define I_TRANSFER_API_MODE
#endif

#include <stdint.h>
#include <memory>
struct frameinfo_t;
#define DEFINE_MAIN_LEVEL 0x00
#define DEFINE_SUB_LEVEL 0x01
#define DEFINE_MATA_MIX_START_LEVEL 0x10
#define DEFINE_MATA_MIX_END_LEVEL 0x20

I_TRANSFER_API_MODE void* tslib_stream_start(const char * server ,int port,uint64_t nodeid,uint32_t subid,int level);
I_TRANSFER_API_MODE void tslib_stream_end(void*);
I_TRANSFER_API_MODE int tslib_push_frame(void*handle,const shared_ptr<frameinfo_t> & frameinfo);
I_TRANSFER_API_MODE int tslib_push_meta(void*handle,char * json,int len,uint64_t pts);


I_TRANSFER_API_MODE void* tslib_vod_start(uint64_t sessionid, const char * server ,int port,uint32_t subid);
I_TRANSFER_API_MODE int tslib_push_frame(void*handle,frameinfo_t * frameinfo,uint8_t * frame_ptr,uint8_t * frame_ext_ptrm);
I_TRANSFER_API_MODE void tslib_vod_end(void* handle);




I_TRANSFER_API_MODE bool tslib_sessoin_end(void*handle);
I_TRANSFER_API_MODE bool tslib_sessoin_restart(void*handle);
