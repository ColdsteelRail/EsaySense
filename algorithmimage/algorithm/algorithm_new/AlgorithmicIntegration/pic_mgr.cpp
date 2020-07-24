#include"pic_mgr.h"
#include"Config.h"
static  pic_mgr* stc_pic_mgr = 0;
#include"NetLibSDK.h"
pic_mgr * pic_mgr::instace()
{
	if (!stc_pic_mgr)
	{
		stc_pic_mgr = new pic_mgr;
	}
	return stc_pic_mgr;
}

pic_mgr::pic_mgr()
{
	thread_.Start(std::bind(&pic_mgr::run, this));
}

pic_mgr::~pic_mgr()
{
}
void pic_mgr::push(std::shared_ptr<FrameNode> frame)
{
	AUTOLOCK(cslist_);
	list_frame_.push_back(frame);
}
void pic_mgr::run()
{
	while (thread_.IsWorking())
	{
		std::shared_ptr<FrameNode> frame;
		AUTOLOCK_BEGIN(cslist_);
		if (list_frame_.size()>0)
		{
			frame = list_frame_.front();
			list_frame_.pop_front();
		}
		AUTOLOCK_END;
		if (!frame)
		{
			myThread::Sleep(10);
			continue;
		}

		string strfile /*= chPath*/;
		strfile += frame->filename;
		bool ret = NetLib_SnapshotAndUpload(frame->rgb_buf, frame->size, frame->width, frame->height, strfile.c_str(), SettingConfig::GetInstance().m_ftp_dir.c_str(),
			SettingConfig::GetInstance().m_ftp_host.c_str(), SettingConfig::GetInstance().m_ftp_user.c_str(), SettingConfig::GetInstance().m_ftp_pwd.c_str());
		printf("NetLib_SnapshotAndUpload %s %d\n", strfile.c_str(), ret);

		continue;
#pragma pack(push,2)
		typedef struct tagBITMAPFILEHEADER
		{
			unsigned short bfType;
			unsigned int bfSize;
			unsigned short bfReserved1;
			unsigned short bfReserved2;
			unsigned int bfOffBits;
		} BITMAPFILEHEADER;
#pragma pack(pop)

		typedef struct tagBITMAPINFOHEADER {
			unsigned int biSize;
			int biWidth;
			int biHeight;
			unsigned short biPlanes;
			unsigned short biBitCount;
			unsigned int biCompression;
			unsigned int biSizeImage;
			int biXPelsPerMeter;
			int biYPelsPerMeter;
			unsigned int biClrUsed;
			unsigned int biClrImportant;
		} BITMAPINFOHEADER;

		BITMAPFILEHEADER bmpFileHeader;
		bmpFileHeader.bfType = ('M' << 8) | 'B'; //'BM';
		bmpFileHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
		bmpFileHeader.bfSize = bmpFileHeader.bfOffBits + frame->size;

		BITMAPINFOHEADER header;
		header.biSize = sizeof(BITMAPINFOHEADER);
		header.biWidth = frame->width;
		header.biHeight = -frame->height;
		header.biBitCount = 24;
		header.biCompression = 0;
		header.biSizeImage = 0;
		header.biClrImportant = 0;
		header.biClrUsed = 0;
		header.biXPelsPerMeter = 100;
		header.biYPelsPerMeter = 100;
		header.biPlanes = 1;

		//´´½¨Ä¿Â¼
		char pPath[255];
		memset(pPath, 0, 255);
		char * pFileName = frame->filename;
		for (int n = strlen(pFileName); n > 0; --n)
		{
			if (pFileName[n] == '\\' || pFileName[n] == '/')
			{
				strncpy(pPath, pFileName, n);
				break;
			}
		}
		//  OS::RecursiveMakeDir(pPath);

		FILE *file = fopen(pFileName, "wb");
		if (file)
		{
			fwrite(&bmpFileHeader, sizeof(BITMAPFILEHEADER), 1, file);
			fwrite(&header, sizeof(BITMAPINFOHEADER), 1, file);
			fwrite(frame->rgb_buf, 1, frame->size, file);
			fclose(file);
		}

		
	}
}