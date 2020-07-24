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

		//�û���ȡ����
		char* GetBuffer(int size);
		void ReleaseBuffer(char *buffer);

	private:
		//�û��ɻ�ȡ�Ķ���
		std::list<CBufferItem *> queue_accessible_objects_;
		//�û�����ʹ�õĶ���
		std::list<CBufferItem *> queue_using_objects_;

		CBaseLock* lock_;
		//����������
		uint32_t num_objects_;
	};

}