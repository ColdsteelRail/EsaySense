#include "cm_type.h"
#include "cm_time.h"
#include "cm_thread_critical_region.h"

#include <assert.h>
#include <list>
#include <vector>

namespace cm {

	class CBufferItem
	{
	public:
		CBufferItem(int size);
		~CBufferItem();

		int m_size;
		char *m_buffer;
	};

	class CBufferPool
	{
	public:
		CBufferPool() { lock_ = CreateLock(); };
		~CBufferPool() { delete lock_; };

		//用户获取对象
		char* GetBuffer(int size);
		void ReleaseBuffer(char *buffer);

	private:
		//用户可获取的对象
		std::list<CBufferItem *> queue_accessible_objects_;
		//用户正在使用的对象
		std::list<CBufferItem *> queue_using_objects_;

		CBaseLock* lock_;
		//对象总数量
		uint32_t num_objects_;
	};

}